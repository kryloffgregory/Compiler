#include <utility>

#include <utility>

//
// Created by gregory on 23.12.18.
//
#include "Translator.h"
#include "RuleClasses/RuleClasses.h"
#include "IIRVisitor.h"
#include "RuleClasses/RuleClasses.h"

CTranslator::CTranslator( std::shared_ptr<SymbolsTable::CTable> _table ) : symbolsTable(std::move(_table))
{
}

void CTranslator::Visit( const CProgram* program )
{
    if( program->mainClass != nullptr ) {
        program->mainClass->Accept( this );
    }
    for(const auto& classDecl : program->classList) {
        classDecl->Accept(this);
    }
}

void CTranslator::Visit( const CMainClass* mainClass )
{
    curClass = symbolsTable->GetClass( mainClass->identifier );
    curMethod = curClass->GetMethod( "main" );

    frames.emplace_back( Frame::CFrame(curClass, curMethod, symbolsTable.get()) );

    std::shared_ptr<const IRTree::IStm> statements = nullptr;
    if( !(mainClass->statements.empty() ) ) {
        for(const auto& st : mainClass->statements) {
            st->Accept(this);
        }
        statements = parsedStatements.top();
        parsedStatements.pop();
    }

    frames.back().SetStatements( statements );
}

void CTranslator::Visit( const CClassDecl* classDecl )
{
    curClass = symbolsTable->GetClass( classDecl->className  );

    for(const auto& methodDecl : classDecl->methodList) {
        methodDecl->Accept(this);
    }

    curClass = nullptr;
}


void CTranslator::Visit( const CVarDecl* varDecl )
{}


void CTranslator::Visit( const CMethodDecl* methodDecl )
{
    curMethod = curClass->GetMethod( methodDecl->methodName  );

    frames.emplace_back( curClass, curMethod, symbolsTable.get() );

    std::shared_ptr<const IRTree::IStm> statements;
    if( !(methodDecl->statementList.empty())  ) {
        for(const auto& st : methodDecl->statementList) {
            st->Accept(this);
        }
        statements = parsedStatements.top();
        parsedStatements.pop();
    }

    methodDecl->returnExpr->Accept( this );
    std::shared_ptr<const IRTree::IExpr> returnExp = parsedExpressions.top();
    parsedExpressions.pop();

    std::shared_ptr<const IRTree::IStm> moveResult =
            std::shared_ptr<const IRTree::IStm>( new IRTree::CMove( std::shared_ptr<const IRTree::IExpr>(
                    new IRTree::CTemp( frames.back().GetReturnPtr() ) ), returnExp ) );

    std::shared_ptr<const IRTree::IStm> methodStm = moveResult;

    if( statements != nullptr ) {
        methodStm = std::shared_ptr<const IRTree::IStm>( new IRTree::CSeq( statements, moveResult ) );
    }

    frames.back().SetStatements( methodStm );
}

void CTranslator::Visit( const CStandardType* type )
{}

void CTranslator::Visit( const CUserType* type )
{}

void CTranslator::Visit( const CStatementListStatement* statement )
{
    bool any = false;
    IRTree::CStmPtr recStm, lastStm;
    for(const auto& st : statement->statementList) {
        st->Accept(this);
        lastStm = parsedStatements.top();
        parsedStatements.pop();
        if (!any) {
            recStm = lastStm;
            any = true;
        } else {
            recStm = IRTree::CStmPtr( new IRTree::CSeq( recStm,
                                                    lastStm) );
        }
    }
    if (any) {
        parsedStatements.push(recStm);
    }
}

void CTranslator::Visit( const CArrayAssignStatement* statement )
{
    // left[i] = right
    IRTree::CExprPtr left( frames.back().GetVar( statement->arrayId )->GetExp( frames.back() ) );

    statement->elementNumber->Accept( this );
    IRTree::CExprPtr index = parsedExpressions.top( );
    parsedExpressions.pop();
    IRTree::CExprPtr offset( new IRTree::CBinop( IRTree::IExpr::MUL, index,
                                                 IRTree::CExprPtr( new IRTree::CConst( Frame::CFrame::WORD_SIZE ) ) ) );

    // left = MEM( +( MEM(left), BINOP(MUL, i, CONST(W)) ) )
    left = IRTree::CExprPtr( new IRTree::CMem( IRTree::CExprPtr(
            IRTree::CExprPtr( new IRTree::CBinop( IRTree::CBinop::PLUS, IRTree::CExprPtr( new IRTree::CMem( left ) ), offset ) ) ) ) );

    statement->rightPart->Accept( this );
    IRTree::CExprPtr right = parsedExpressions.top();
    parsedExpressions.pop();

    parsedStatements.emplace( new IRTree::CMove( left, right ) );
}

void CTranslator::Visit( const CAssignStatement* statement )
{
    // left = right
    IRTree::CExprPtr left( frames.back().GetVar( statement->left )->GetExp( frames.back() ) );

    statement->right->Accept( this );
    IRTree::CExprPtr right = parsedExpressions.top();
    parsedExpressions.pop();

    parsedStatements.emplace( new IRTree::CMove( left, right ) );
}

void CTranslator::Visit( const CIfStatement* ifStatement )
{
    ifStatement->condition->Accept( this );
    IRTree::CExprPtr condition = parsedExpressions.top();
    parsedExpressions.pop();

    std::shared_ptr<const Temp::CLabel> trueLabel(new Temp::CLabel());
    std::shared_ptr<const Temp::CLabel> falseLabel(new Temp::CLabel());
    std::shared_ptr<const Temp::CLabel> joinLabel(new Temp::CLabel());

    IRTree::CStmPtr trueStatement, falseStatement;
    if( ifStatement->statementIfTrue != nullptr ) {
        ifStatement->statementIfTrue->Accept( this );
        trueStatement = parsedStatements.top();
        parsedStatements.pop();
    }
    if( ifStatement->statementIfFalse != nullptr ) {
        ifStatement->statementIfFalse->Accept( this );
        falseStatement = parsedStatements.top();
        parsedStatements.pop();
    }

    IRTree::CStmPtr endifJump = IRTree::CStmPtr(new IRTree::CJump(joinLabel));
    falseStatement = IRTree::CStmPtr(new IRTree::CSeq(IRTree::CStmPtr(new IRTree::CLabel(falseLabel)), IRTree::CStmPtr(new IRTree::CSeq(falseStatement, endifJump))));
    trueStatement = IRTree::CStmPtr( new IRTree::CSeq( IRTree::CStmPtr( new IRTree::CLabel( trueLabel ) ), IRTree::CStmPtr( new IRTree::CSeq( trueStatement, endifJump ) ) ) );
    IRTree::CStmPtr bothStatement;

    if (ifStatement->statementIfFalse != nullptr) {
        bothStatement = IRTree::CStmPtr(new IRTree::CSeq(trueStatement, IRTree::CStmPtr(new IRTree::CSeq(falseStatement, IRTree::CStmPtr(new IRTree::CLabel(joinLabel))))));
    } else {
        // TODO: check this
        bothStatement = IRTree::CStmPtr(new IRTree::CSeq(trueStatement, IRTree::CStmPtr(new IRTree::CLabel(joinLabel))));
    }

    parsedStatements.push( IRTree::CStmPtr( new IRTree::CSeq( IRTree::CStmPtr( new IRTree::CCondJump( IRTree::IExpr::EQ, condition,
                                                                                                      IRTree::CExprPtr( new IRTree::CConst(1) ), trueLabel, falseLabel ) ), bothStatement) ) );
}

void CTranslator::Visit( const CWhileStatement* whileStatement )
{
    whileStatement->cycleBody->Accept( this );
    IRTree::CStmPtr bodyCycleStatement = parsedStatements.top();
    parsedStatements.pop();

    whileStatement->condition->Accept( this );
    IRTree::CExprPtr condition = parsedExpressions.top();
    parsedExpressions.pop();

    std::shared_ptr<const Temp::CLabel> testLabel( new Temp::CLabel() );
    std::shared_ptr<const Temp::CLabel> nextStepLabel( new Temp::CLabel( ) );
    std::shared_ptr<const Temp::CLabel> doneLabel( new Temp::CLabel() );

    // SEQ( SEQ( LABEL(nextStepLabel), body), JUMP(test) )
    bodyCycleStatement = IRTree::CStmPtr( new IRTree::CSeq( IRTree::CStmPtr(
            new IRTree::CSeq( IRTree::CStmPtr( new IRTree::CLabel(nextStepLabel) ), bodyCycleStatement ) ),
                                                            IRTree::CStmPtr( new IRTree::CJump( testLabel ) ) ) );

    // SEQ( CCONDJUMP(eq, condition, 1, nextStepLabel, doneLabel), bodyCycleStatement )
    IRTree::CStmPtr conditionStatement = IRTree::CStmPtr( new IRTree::CSeq( IRTree::CStmPtr(
            new IRTree::CCondJump( IRTree::IExpr::EQ, condition, IRTree::CExprPtr( new IRTree::CConst( 1 ) ), nextStepLabel, doneLabel ) ),
                                                                            bodyCycleStatement ) );

    // SEQ( SEQ( LABEL(testLabel, condition) ), doneLabel )
    parsedStatements.push( IRTree::CStmPtr( new IRTree::CSeq( IRTree::CStmPtr( new IRTree::CSeq(
            IRTree::CStmPtr( new IRTree::CLabel( testLabel ) ), conditionStatement ) ),
                                                              IRTree::CStmPtr( new IRTree::CLabel( doneLabel ) ) ) ) );
}

void CTranslator::Visit( const CPrintStatement* printStatement )
{
    printStatement->expression->Accept( this );
    IRTree::CExprPtr expr = parsedExpressions.top();
    parsedExpressions.pop();
    parsedStatements.emplace( new IRTree::CExpr( IRTree::CExprPtr( new IRTree::CCall(  "name_println" , { expr } ) ) ));
}

void CTranslator::Visit( const CBinOpExpression* expr )
{
    expr->leftExp->Accept( this );
    std::shared_ptr<const IRTree::IExpr> left = parsedExpressions.top();
    parsedExpressions.pop();

    expr->rightExp->Accept( this );
    std::shared_ptr<const IRTree::IExpr> right = parsedExpressions.top();
    parsedExpressions.pop();

    IRTree::CExprPtr binOp;
    switch( expr->binOp )
    {
        case CBinOpExpression::AND:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::AND, left, right ) );
        case CBinOpExpression::LESS:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::LESS, left, right ) );
            break;
        case CBinOpExpression::PLUS:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::PLUS, left, right ) );
            break;
        case CBinOpExpression::MINUS:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::MINUS, left, right ) );
            break;
        case CBinOpExpression::TIMES:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::MUL, left, right ) );
            break;
        case CBinOpExpression::DIVIDE:
            binOp = std::shared_ptr<const IRTree::IExpr>( new IRTree::CBinop( IRTree::IExpr::DIV, left, right ) );
            break;
    }

    parsedExpressions.emplace( IRTree::CExprPtr( binOp ) );
}

void CTranslator::Visit( const CIndexExpression* expr )
{
    expr->exp->Accept( this );
    IRTree::CExprPtr array( new IRTree::CMem( parsedExpressions.top() ) );
    parsedExpressions.pop();

    expr->indexExp->Accept( this );
    IRTree::CExprPtr index = parsedExpressions.top();
    parsedExpressions.pop();
    index = IRTree::CExprPtr( new IRTree::CBinop( IRTree::IExpr::PLUS, index, IRTree::CExprPtr( new IRTree::CConst( 1 ) ) ) );

    IRTree::CExprPtr offset( new IRTree::CBinop( IRTree::IExpr::MUL, index, IRTree::CExprPtr( new IRTree::CConst( Frame::CFrame::WORD_SIZE ) ) ) );

    parsedExpressions.push( IRTree::CExprPtr( new IRTree::CMem( IRTree::CExprPtr( new IRTree::CBinop( IRTree::IExpr::PLUS, array, offset ) ) ) ) );
}

void CTranslator::Visit( const CLenghtExpression* expr )
{
    expr->exp->Accept( this );
    IRTree::CExprPtr arrayLen = parsedExpressions.top();
    parsedExpressions.pop();

    IRTree::CExprPtr lenght( new IRTree::CTemp( std::shared_ptr<Temp::CTemp>( new Temp::CTemp() ) ) );

    parsedExpressions.push( IRTree::CExprPtr( new IRTree::CESeq( IRTree::CStmPtr( new IRTree::CMove( lenght, arrayLen ) ), lenght ) ) );
}

void CTranslator::Visit( const CMethodExpression* expr )
{
    expr->exp->Accept( this );
    IRTree::CExprPtr object = parsedExpressions.top();
    parsedExpressions.pop();

    std::vector<IRTree::CExprPtr> arguments;
    arguments.push_back(object);
    if( !(expr->expList.empty()) ) {
        auto expresionsStackSize = parsedExpressions.size();
        for(const auto& arg : expr->expList) {
            arg->Accept(this);
        }
        auto newExpressionsStackSize = parsedExpressions.size();
        for( ; expresionsStackSize < newExpressionsStackSize; ++expresionsStackSize ) {
            arguments.push_back( parsedExpressions.top() );
            parsedExpressions.pop();
        }
    }

    IRTree::CExprPtr returnValue( new IRTree::CTemp( std::shared_ptr<Temp::CTemp>( frames.back().GetReturnPtr() ) ) );

    parsedExpressions.push( IRTree::CExprPtr( new IRTree::CESeq( IRTree::CStmPtr( new IRTree::CMove(
            returnValue, IRTree::CExprPtr( new IRTree::CCall( expr->identifier, arguments ) ) ) ), returnValue ) ) );
}

void CTranslator::Visit( const CIntLiteralExpression* expr )
{
    parsedExpressions.emplace( IRTree::CExprPtr( new IRTree::CConst( expr->val ) ) );
}

void CTranslator::Visit( const CBoolLiteralExpression* expr )
{
    parsedExpressions.emplace( IRTree::CExprPtr( new IRTree::CConst( expr->val ) ) );
}

void CTranslator::Visit( const CIdentifierExpression* expr )
{
    parsedExpressions.emplace( frames.back().GetVar( expr->identifier )->GetExp( frames.back() ) );
}

void CTranslator::Visit( const CThisExpression* expr )
{
    parsedExpressions.emplace( new IRTree::CTemp( frames.back().GetThisPtr() ) );
}

void CTranslator::Visit( const CNewIntArrayExpression* expr )
{
    expr->exp->Accept( this );
    IRTree::CExprPtr arraySize = parsedExpressions.top();
    parsedStatements.pop();

    // (len + 1) * wordSize
    IRTree::CExprPtr allocationSize( new IRTree::CMem( IRTree::CExprPtr(
            new IRTree::CBinop( IRTree::IExpr::MUL,
                                IRTree::CExprPtr( new IRTree::CBinop( IRTree::IExpr::PLUS, arraySize, IRTree::CExprPtr( new IRTree::CConst( 1 ) ) ) ),
                                IRTree::CExprPtr( new IRTree::CConst(frames.back().WORD_SIZE) ) ) ) ) );

    IRTree::CExprPtr temp( new IRTree::CTemp( std::shared_ptr<Temp::CTemp>( new Temp::CTemp() ) ) );

    IRTree::CExprPtr mallocCall( new IRTree::CCall(  "__malloc" , { allocationSize } ) );
    IRTree::CStmPtr allocateMemory( new IRTree::CMove( temp, mallocCall ) );

    IRTree::CStmPtr clearMemory( new IRTree::CExpr( IRTree::CExprPtr( new IRTree::CCall(  "__memset" ,
                                                                                         { IRTree::CExprPtr( new IRTree::CConst( 0 ) ), allocationSize } ) ) ) );
    IRTree::CStmPtr moveSize( new IRTree::CMove( temp, arraySize ) );

    parsedExpressions.push( IRTree::CExprPtr( new IRTree::CESeq( IRTree::CStmPtr( new IRTree::CSeq(
            allocateMemory, IRTree::CStmPtr( new IRTree::CSeq( clearMemory, moveSize ) ) ) ), temp ) ) );
}

void CTranslator::Visit( const CNewExpression* expr )
{
    SymbolsTable::CClassInfo* object = symbolsTable->GetClass( expr->identifier );
    int objectSize = object->GerVars().size();

    IRTree::CExprPtr allocationSize(new IRTree::CConst(objectSize * frames.back().WORD_SIZE));

    IRTree::CExprPtr temp( new IRTree::CTemp( std::shared_ptr<Temp::CTemp>( new Temp::CTemp() ) ) );
    IRTree::CExprPtr mallocCall( new IRTree::CCall(  "__malloc" , { allocationSize } ) );
    IRTree::CStmPtr allocateMemory( new IRTree::CMove( temp, mallocCall ) );

    IRTree::CStmPtr clearMemory( new IRTree::CExpr( IRTree::CExprPtr( new IRTree::CCall(  "__memset" ,
                                                                                         { temp, IRTree::CExprPtr(new IRTree::CConst(0)) } ) ) ) );

    parsedExpressions.push( IRTree::CExprPtr( new IRTree::CESeq( IRTree::CStmPtr( new IRTree::CSeq(
            allocateMemory, clearMemory ) ), temp ) ) );
}

void CTranslator::Visit( const CUnaryOpExpression* expr )
{
    expr->exp->Accept( this );
    std::shared_ptr<const IRTree::IExpr> right = parsedExpressions.top();
    parsedExpressions.pop();

    IRTree::CExprPtr binOp;
    if (expr->op == CUnaryOpExpression::UnaryOp::MINUS) {
        binOp = std::shared_ptr<const IRTree::IExpr>(
                new IRTree::CBinop( IRTree::IExpr::MINUS, IRTree::CExprPtr( new IRTree::CConst( 0 ) ), right ) );
    } else {
        // TODO: Check if it is true
        binOp = std::shared_ptr<const IRTree::IExpr>(
                new IRTree::CBinop( IRTree::IExpr::XOR, IRTree::CExprPtr( new IRTree::CConst( 1 ) ), right ) );
    }

    parsedExpressions.emplace(binOp);
}

void CTranslator::Visit( const CBracesExpression* expr )
{
    if( expr->exp != nullptr ) {
        expr->exp->Accept( this );
    }
}





void CTranslator::Visit( const CArg* formal )
{
}

std::vector<Frame::CFrame> CTranslator::GetFrames() const
{
    return frames;
}
