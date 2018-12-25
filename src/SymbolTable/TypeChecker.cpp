//
// Created by gregory on 17.12.18.
//

#include <RuleClasses/RuleClasses.h>
#include <set>
#include "TypeChecker.h"

CTypeCheckerVisitor::CTypeCheckerVisitor( std::shared_ptr<SymbolsTable::CTable> table ) : symbolsTable(table)
{
}

void CTypeCheckerVisitor::Visit( const CProgram* program )
{
    program->mainClass->Accept( this );
    for(const auto & classDecl : program->classList)
        classDecl->Accept( this );

}

void CTypeCheckerVisitor::Visit( const CMainClass* mainClass )
{
    curClass = symbolsTable->GetClass( mainClass->identifier );
    curMethod = curClass->GetMethod( "main" );

    for(const auto & statement : mainClass->statements)
        statement->Accept( this );


    curMethod = nullptr;
    curClass = nullptr;
}

void CTypeCheckerVisitor::Visit( const CClassDecl* classDecl ) {
    curClass = symbolsTable->GetClass(classDecl->className);
    if (classDecl->isDerived) {
        auto base = curClass->GetBaseClass();

        std::set<std::string> hierarchy;
        while (base != nullptr) {
            if (hierarchy.find(base->GetName()) != hierarchy.end()) {
                errorStorage.PutError(std::string("[Type check] Node type - CClassDeclDerived. ") +
                                      base->GetName() +
                                      " - Cannot derive class from itself. " +
                                      classDecl->location.ToString());
                break;
            }
            hierarchy.insert(base->GetName());
        }
    }
    for(const auto & varDecl : classDecl->varList)
        varDecl->Accept( this );

    for(const auto & methodDecl : classDecl ->methodList)
        methodDecl->Accept( this );


    curClass = nullptr;
}

void CTypeCheckerVisitor::Visit( const CVarDecl* varDecl ) {
    if (curClass == nullptr) {
        errorStorage.PutError("Variable declaration out of scope " + varDecl->location.ToString());
        return;
    }
    varDecl->type->Accept(this);

    std::string lastType = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if (!isPODType(lastType) && symbolsTable->GetClass(lastType) == nullptr) {
        errorStorage.PutError(std::string("[Type check] Node type - CVarDecl. ") +
                              lastType + " " + varDecl->identifier +
                              " - incorrect variable declaration, class " + lastType + " not found. " +
                              varDecl->location.ToString());
    }
}

void CTypeCheckerVisitor::Visit( const CMethodDecl* methodDecl )
{
    if( curClass == nullptr ) {
        errorStorage.PutError( "Method declaration out of scope " + methodDecl->location.ToString() );
        return;
    }
    curMethod = curClass->GetMethod( methodDecl->methodName );
    methodDecl->type->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back( );
    lastTypeValueStack.pop_back();
    if( !isPODType( lastTypeValue ) && symbolsTable->GetClass( lastTypeValue ) == nullptr ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CMethodDecl. " ) +
                               lastTypeValue + " " + methodDecl->methodName +
                               " - incorrect method declaration, class " + lastTypeValue + " not found. " +
                                       methodDecl->location.ToString());
    }

    for(const auto & arg : methodDecl -> argList) {
        arg->Accept( this );
    }
    for(const auto & var : methodDecl -> varList) {
        var->Accept( this );
    }
    for(const auto & statement : methodDecl -> statementList) {
        statement->Accept( this );
    }
    if( methodDecl->returnExpr!= nullptr ) {
        methodDecl->returnExpr->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( const CStandardType* type )
{
    switch( type->type ) {
        case CStandardType::StandardType::INT:
            lastTypeValueStack.emplace_back( "int" );
            break;
        case CStandardType::StandardType::BOOL:
            lastTypeValueStack.emplace_back("boolean" );
            break;
        case CStandardType::StandardType::INT_ARRAY:
            lastTypeValueStack.emplace_back("int[]" );
            break;
        default:
            lastTypeValueStack.emplace_back("int" );
            break;
    }
}

void CTypeCheckerVisitor::Visit( const CUserType* type )
{
    lastTypeValueStack.push_back( type->type);
}


void CTypeCheckerVisitor::Visit( const CStatementListStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "While statement out of scope " + statement->location.ToString() );
        return;
    }

    for(const auto & statement1 : statement->statementList)
        statement1->Accept( this );

}

void CTypeCheckerVisitor::Visit( const CArrayAssignStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Assign statement out of scope " + statement->location.ToString() );
        return;
    }

    //SymbolsTable::CVarInfo* var = curMethod->GetVar( statement->arrayId);
    //var->GetType()->Accept( this );
    //std::string leftType = lastTypeValueStack.back();
//lastTypeValueStack.pop_back();
    statement->rightPart->Accept( this );
    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( "int" != lastTypeValue ) {
        errorStorage.PutError( "Incompatible types " + statement->location.ToString() );
    }
}

void CTypeCheckerVisitor::Visit( const CAssignStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Assign statement out of scope " + statement->location.ToString() );
        return;
    }

    SymbolsTable::CVarInfo* var = curMethod->GetVar( statement->left);
    if(var == nullptr) {
        errorStorage.PutError( " Unreferenced variable " + statement->left + " " + statement->location.ToString() );
        return;
    }
    statement->right->Accept( this );
    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( var->GetType() != lastTypeValue ) {
        errorStorage.PutError( "Incompatible types " + statement->location.ToString() );
    }
}

void CTypeCheckerVisitor::Visit( const CIfStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "If statement out of scope " + statement->location.ToString() );
        return;
    }

    statement->condition->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "boolean" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CIfStatement. " ) +
                               "Expression of type " + lastTypeValue + " cannot be used as condition. " +
                               statement->location.ToString());
    }

    if( statement->statementIfTrue != nullptr ) {
        statement->statementIfTrue->Accept( this );
    }
    if( statement->statementIfFalse != nullptr ) {
        statement->statementIfFalse->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( const CWhileStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "While statement out of scope " + statement->location.ToString( ) );
        return;
    }

    statement->condition->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "boolean" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CWhileStatement. " ) +
                               "Expression of type " + lastTypeValue + " cannot be used as condition. " +
                               statement->location.ToString());
    }

    if( statement->cycleBody != nullptr ) {
        statement->cycleBody->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( const CPrintStatement* statement )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Print statement out of scope " + statement->location.ToString() );
        return;
    }

    statement->expression->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "int" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CPrintStatement. " ) +
                               "Expression of type " + lastTypeValue + " cannot be printed. Simple java can only print variables of type 'int'. " +
                               statement->location.ToString());
    }
}

void CTypeCheckerVisitor::Visit( const CBinOpExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.emplace_back("boolean" );
        return;
    }

    expr->leftExp->Accept( this );
    auto left = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    expr->rightExp->Accept( this );
    auto right = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();

    if( expr->binOp == CBinOpExpression::MINUS || expr->binOp == CBinOpExpression::PLUS ||
        expr->binOp == CBinOpExpression::TIMES || expr->binOp== CBinOpExpression::DIVIDE ) {
        if( left != "int" || right != "int" ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CBinOpExpression. " ) +
                                   "Expression of type " + (left != "int" ? left : right) + " cannot be used in arithmetic operations, use 'int'. " +
                                   expr->location.ToString());
        }
        lastTypeValueStack.emplace_back("int" );
    }
    if( expr->binOp== CBinOpExpression::AND ) {
        if( left != "boolean" || right != "boolean" ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CBinOpExpression. " ) +
                                   "Expression of type " + (left != "boolean" ? left : right) + " cannot be used in logic operations, use 'bool'. " +
                                   expr->location.ToString());
        }
        lastTypeValueStack.emplace_back("boolean" );
    }
    if( expr->binOp == CBinOpExpression::LESS ) {
        if( left != "int" || right != "int" ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CBinOpExpression. " ) +
                                   "Expression of type " + (left != "int" ? left : right) + " cannot be used in comparasion operations, use 'bool'. " +
                                   expr->location.ToString());
        }
        lastTypeValueStack.emplace_back("boolean" );
    }
}

void CTypeCheckerVisitor::Visit( const CIndexExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.emplace_back("int" );
        return;
    }

    expr->exp->Accept( this );
    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "int[]" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CIndexExpression. " ) +
                               "Cannot get element of not variable which is not array. " +
                               expr->location.ToString());
    }

    expr->indexExp->Accept( this );
    lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "int" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CIndexExpression. " ) +
                               "Cannot get element of array, when index is not an integer. " +
                               expr->location.ToString());
    }

    lastTypeValueStack.emplace_back("int" );
}

void CTypeCheckerVisitor::Visit( const CLenghtExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString( ) );
        lastTypeValueStack.emplace_back("int" );
        return;
    }

    expr->exp->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "int[]" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CLengthExpression. " ) +
                               "Cannot get length of not array expression. " +
                               expr->location.ToString());
    }

    lastTypeValueStack.emplace_back("int" );
}


void CTypeCheckerVisitor::Visit( const CMethodExpression* expr )
{
    expr->exp->Accept( this );
    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    SymbolsTable::CClassInfo* usedClass = symbolsTable->GetClass( lastTypeValue );
    if( usedClass == nullptr ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CMethodExpression. " ) +
                               "Cannot find such class " + lastTypeValue + "." +
                               expr->location.ToString());
        lastTypeValueStack.emplace_back("int" );
    } else {
        SymbolsTable::CMethodInfo* usedMethod = usedClass->GetMethod( expr->identifier );
        if(usedMethod == nullptr) {
            errorStorage.PutError("Class " + usedClass->GetName() + " does not have method " + expr->identifier + expr->location.ToString());
            lastTypeValueStack.emplace_back("int");
            return;
        }
        if(!expr->expList.empty()) {
            int typeValuePointer = static_cast<int>(lastTypeValueStack.size());
            for(const auto & arg : expr->expList)
                arg->Accept( this );

            auto params = usedMethod->GetParams();
            if( lastTypeValueStack.size() - typeValuePointer != params.size() ) {
                errorStorage.PutError( std::string( "[Type check] Node type - CMethodExpression. " ) +
                                       "Invalid number of arguments " + usedMethod->GetName( ) + "." +
                                       expr->location.ToString());
            }
            for( int i = typeValuePointer; i < lastTypeValueStack.size(); ++i ) {
                if( params[i - typeValuePointer]->GetType() != lastTypeValueStack[i] ) {
                    errorStorage.PutError( std::string( "[Type check] Node type - CMethodExpression. " ) +
                                           "Wrong function argument type " + params[i - typeValuePointer]->GetName( ) + ". " +
                                           expr->location.ToString());
                }
            }
            for(int i = 0, size = static_cast<int>(lastTypeValueStack.size() - typeValuePointer); i < size; ++i ) {
                lastTypeValueStack.pop_back();
            }
        } else {
            auto params = usedMethod->GetParams();
            if(!params.empty()) {
                errorStorage.PutError( std::string( "[Type check] Node type - CMethodExpression. " ) +
                                       "Wrong function argument count " + expr->identifier+ ". " +
                                       expr->location.ToString());
            }
        }
        lastTypeValueStack.push_back( usedMethod->GetReturnType()->GetType() );
    }
}




void CTypeCheckerVisitor::Visit( const CIntLiteralExpression* expr )
{
    lastTypeValueStack.emplace_back("int" );
}

void CTypeCheckerVisitor::Visit( const CBoolLiteralExpression* expr )
{
    lastTypeValueStack.emplace_back("boolean" );
}

void CTypeCheckerVisitor::Visit( const CIdentifierExpression* expr )
{
    if( curClass == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.emplace_back("int" );
        return;
    }

    if( curMethod == nullptr ) {
        auto varInfo = curClass->GetVar( expr->identifier);
        if( varInfo == nullptr ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CIdentifierExpression. " ) +
                                   "Undeclared identifier " + expr->identifier+ ". " +
                                   expr->location.ToString());
            lastTypeValueStack.emplace_back("int" );
            return;
        }
        lastTypeValueStack.push_back( varInfo->GetType() );
        return;
    }


    auto varInfo = curMethod->GetVar( expr->identifier );
    if( varInfo == nullptr ) {
        varInfo = curClass->GetVar( expr->identifier );
        if( varInfo == nullptr ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CIdentifierExpression. " ) +
                                   "Undeclared identifier " + expr->identifier+ ". " +
                                   expr->location.ToString());
            lastTypeValueStack.emplace_back("int" );
            return;
        }
    }
    lastTypeValueStack.push_back( varInfo->GetType() );
}

void CTypeCheckerVisitor::Visit( const CThisExpression* expr )
{
    if( curClass == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.push_back( curClass->GetName( ) );
        return;
    }
    lastTypeValueStack.push_back( curClass->GetName() );
}

void CTypeCheckerVisitor::Visit( const CNewIntArrayExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.push_back( "int[]" );
        return;
    }

    expr->exp->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( lastTypeValue != "int" ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CNewIntArrayExpression. " ) +
                               "Cannot create array of non integer length. " +
                               expr->location.ToString());
    }

    lastTypeValueStack.emplace_back("int[]" );
}

void CTypeCheckerVisitor::Visit( const CNewExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString() );
        lastTypeValueStack.push_back( expr->identifier );
        return;
    }

    if( symbolsTable->GetClass( expr->identifier ) == nullptr ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CNewExpression. " ) +
                               "Undefined class name - " + expr->identifier + ". " +
                               expr->location.ToString() );
    }

    lastTypeValueStack.push_back( expr->identifier);
}

void CTypeCheckerVisitor::Visit( const CUnaryOpExpression* expr )
{
    if( curClass == nullptr || curMethod == nullptr ) {
        errorStorage.PutError( "Expression out of scope " + expr->location.ToString( ) );
        lastTypeValueStack.emplace_back("int" );
        return;
    }

    expr->exp->Accept( this );

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( expr->op == CUnaryOpExpression::MINUS ) {
        if( lastTypeValue != "int" ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CUnaryOpExpression. " ) +
                                   "Expression of type " + lastTypeValue + " cannot be used in arithmetic operations, use 'int'. " +
                                   expr->location.ToString());
        } else {
            lastTypeValueStack.emplace_back("int" );
        }
    }

    if( expr->op == CUnaryOpExpression::NOT ) {
        if( lastTypeValue != "boolean" ) {
            errorStorage.PutError( std::string( "[Type check] Node type - CUnaryOpExpression. " ) +
                                   "Expression of type " + lastTypeValue + " cannot be used in logic operations, use 'boolean'. " +
                                   expr->location.ToString() );
        } else {
            lastTypeValueStack.emplace_back("boolean" );
        }
    }
}

void CTypeCheckerVisitor::Visit( const CBracesExpression* expr )
{
    if( expr->exp != nullptr ) {
        expr->exp->Accept( this );
    }
}

void CTypeCheckerVisitor::Visit( const CArg* param )
{
    if( param->type != nullptr ) {
        param->type->Accept( this );
    }

    std::string lastTypeValue = lastTypeValueStack.back();
    lastTypeValueStack.pop_back();
    if( !isPODType( lastTypeValue ) && symbolsTable->GetClass( lastTypeValue ) == nullptr ) {
        errorStorage.PutError( std::string( "[Type check] Node type - CFormalList. " ) +
                               lastTypeValue + " " + param->id +
                               " - wrong argument type in method declaration, class " + lastTypeValue + " not found. " +
                               param->location.ToString());
    }
}

const CErrorStorage& CTypeCheckerVisitor::GetErrorStorage() const
{
    return errorStorage;
}

 bool CTypeCheckerVisitor::isPODType( const std::string& type )
{
    return  type == "int" || type == "boolean" || type == "int[]";
}