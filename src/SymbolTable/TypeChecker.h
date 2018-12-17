//
// Created by gregory on 17.12.18.
//

#pragma once

#include <ErrorStorage/ErrorStorage.h>
#include "../Visitor.h"
#include "SymbolTable.h"

class IType;
class CTypeCheckerVisitor : public IVisitor {
public:
    explicit CTypeCheckerVisitor( SymbolsTable::CTable* table );

    void Visit( const CProgram* program ) override;

    void Visit( const CMainClass* mainClass ) override;
    void Visit( const CClassDecl* classDecl ) override ;
    void Visit( const CVarDecl* varDecl ) override ;
    void Visit( const CMethodDecl* methodDecl ) override ;
    void Visit( const CStandardType* type ) override ;
    void Visit( const CStatementListStatement* statement ) override ;
    void Visit( const CArrayAssignStatement* statement ) override ;
    void Visit( const CAssignStatement* statement ) override ;
    void Visit( const CIfStatement* statement ) override ;
    void Visit( const CWhileStatement* statement ) override ;
    void Visit( const CPrintStatement* statement ) override ;
    void Visit( const CBinOpExpression* expr ) override ;
    void Visit( const CIndexExpression* expr ) override ;
    void Visit( const CLenghtExpression* expr ) override ;
    void Visit( const CMethodExpression* expr ) override ;
    void Visit( const CIntLiteralExpression* expr ) override ;
    void Visit( const CBoolLiteralExpression* expr ) override ;
    void Visit( const CIdentifierExpression* expr ) override ;
    void Visit( const CThisExpression* expr ) override ;
    void Visit( const CNewIntArrayExpression* expr ) override ;
    void Visit( const CNewExpression* expr ) override ;
    void Visit( const CUnaryOpExpression* expr ) override ;
    void Visit( const CBracesExpression* expr ) override ;
    void Visit( const CArg* arg ) override ;
    void Visit( const CUserType* type) override;

    const CErrorStorage& GetErrorStorage() const;

private:
    bool isPODType( const std::string& type ) const;

    SymbolsTable::CClassInfo* curClass = nullptr;
    SymbolsTable::CMethodInfo* curMethod = nullptr;
    SymbolsTable::CTable* symbolsTable;
    std::vector<std::string> lastTypeValueStack;

    CErrorStorage errorStorage;
};