//
// Created by gregory on 23.12.18.
//

#pragma once
#include "Visitor.h"

#include "Expression.h"
#include "Statement.h"
#include "Frame.h"

#include <stack>

class CTranslator : public IVisitor {
public:
    explicit CTranslator( SymbolsTable::CTable* table );

    void Visit( const CProgram* program ) override;
    void Visit( const CMainClass* mainClass ) override;
    void Visit( const CClassDecl* classDecl ) override;
    void Visit( const CVarDecl* varDecl ) override;
    void Visit( const CMethodDecl* methodDecl ) override;
    void Visit( const CStandardType* type ) override;
    void Visit( const CUserType* type ) override;
    void Visit( const CStatementListStatement* statement ) override;
    void Visit( const CArrayAssignStatement* statement ) override;
    void Visit( const CAssignStatement* statement ) override;
    void Visit( const CIfStatement* statement ) override;
    void Visit( const CWhileStatement* statement ) override;
    void Visit( const CPrintStatement* statement ) override;
    void Visit( const CBinOpExpression* expr ) override;
    void Visit( const CIndexExpression* expr ) override;
    void Visit( const CLenghtExpression* expr ) override;
    void Visit( const CMethodExpression* expr ) override;
    void Visit( const CIntLiteralExpression* expr ) override;
    void Visit( const CBoolLiteralExpression* expr ) override;
    void Visit( const CIdentifierExpression* expr ) override;
    void Visit( const CThisExpression* expr ) override;
    void Visit( const CNewIntArrayExpression* expr ) override;
    void Visit( const CNewExpression* expr ) override;
    void Visit( const CUnaryOpExpression* expr ) override;
    void Visit( const CBracesExpression* expr ) override;

    void Visit( const CArg* list ) override;

    std::vector<Frame::CFrame> GetFrames() const;
private:
    std::stack<std::shared_ptr<const IRTree::IExpr>> parsedExpressions;
    std::stack<std::shared_ptr<const IRTree::IStm>> parsedStatements;

    std::vector<Frame::CFrame> frames;

    SymbolsTable::CTable* symbolsTable;
    SymbolsTable::CClassInfo* curClass = nullptr;
    SymbolsTable::CMethodInfo* curMethod = nullptr;
};