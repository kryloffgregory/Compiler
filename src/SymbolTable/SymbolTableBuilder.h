//
// Created by gregory on 10.12.18.
//

#pragma once

#pragma once

#include <string>
#include <Visitor.h>
#include "SymbolTable.h"
#include "../ErrorStorage/ErrorStorage.h"
#include <memory>
//#include <memory>

using namespace SymbolsTable;
class CErrorStorage;
class STBuilder : public IVisitor {
public:

    STBuilder();

    CTable* GetSymbolsTable() { return symbolsTable.get();}
    CErrorStorage GetErrorStorage() { return errorStorage;}

    void Visit( const CProgram* program ) override;

    void Visit( const CMainClass* mainClass ) override;
    void Visit( const CClassDecl* classDecl ) override ;
    void Visit( const CVarDecl* varDecl ) override ;
    void Visit( const CMethodDecl* methodDecl ) override ;
    void Visit( const CStandardType* type ) override ;
    void Visit( const CStatementListStatement* statement ) override {}
    void Visit( const CArrayAssignStatement* statement ) override {}
    void Visit( const CAssignStatement* statement ) override {}
    void Visit( const CIfStatement* statement ) override {}
    void Visit( const CWhileStatement* statement ) override {}
    void Visit( const CPrintStatement* statement ) override {}
    void Visit( const CBinOpExpression* expr ) override {}
    void Visit( const CIndexExpression* expr ) override {}
    void Visit( const CLenghtExpression* expr ) override {}
    void Visit( const CMethodExpression* expr ) override {}
    void Visit( const CIntLiteralExpression* expr ) override {}
    void Visit( const CBoolLiteralExpression* expr ) override {}
    void Visit( const CIdentifierExpression* expr ) override {}
    void Visit( const CThisExpression* expr ) override {}
    void Visit( const CNewIntArrayExpression* expr ) override {}
    void Visit( const CNewExpression* expr ) override {}
    void Visit( const CUnaryOpExpression* expr ) override {}
    void Visit( const CBracesExpression* expr ) override {}
    void Visit( const CArg* arg ) override ;
    void Visit( const CUserType* type) override;

private:

    CClassInfo* curClass = nullptr;
    CMethodInfo* curMethod = nullptr;
    std::shared_ptr<CTable> symbolsTable;
    std::string lastTypeValue;
    CErrorStorage errorStorage;

};


