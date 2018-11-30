//
// Created by gregory on 19.11.18.
//



class CBracesExpression;
class CUnaryOpExpression;
class CNewExpression;
class CNewIntArrayExpression;
class CThisExpression;
class CIdentifierExpression;
class CBoolLiteralExpression;
class CIntLiteralExpression;
class CMethodExpression;
class CLenghtExpression;
class CIndexExpression;
class CBinOpExpression;
class CArrayAssignStatement;
class CAssignStatement;
class CStatementListStatement;
class CIfStatement;
class CPrintStatement;
class CWhileStatement;
class CStandardType;
class CUserType;
class CMethodDecl;
class CVarDecl;
class CClassDeclDerived;
class CClassDecl;
class CProgram;
class CMainClass;
class CExpressionRest;
class CArg;

class IVisitor {
public:
    virtual ~IVisitor()
    {}

    virtual void Visit( const CProgram* program ) = 0;
    virtual void Visit( const CMainClass* mainClass ) = 0;
    virtual void Visit( const CClassDecl* classDecl ) = 0;
    virtual void Visit( const CVarDecl* varDecl ) = 0;
    virtual void Visit( const CMethodDecl* methodDecl ) = 0;
    virtual void Visit( const CStandardType* type ) = 0;
    virtual void Visit( const CStatementListStatement* statement ) = 0;
    virtual void Visit( const CArrayAssignStatement* statement ) = 0;
    virtual void Visit( const CAssignStatement* statement ) = 0;
    virtual void Visit( const CIfStatement* statement ) = 0;
    virtual void Visit( const CWhileStatement* statement ) = 0;
    virtual void Visit( const CPrintStatement* statement ) = 0;
    virtual void Visit( const CBinOpExpression* expr ) = 0;
    virtual void Visit( const CIndexExpression* expr ) = 0;
    virtual void Visit( const CLenghtExpression* expr ) = 0;
    virtual void Visit( const CMethodExpression* expr ) = 0;
    virtual void Visit( const CIntLiteralExpression* expr ) = 0;
    virtual void Visit( const CBoolLiteralExpression* expr ) = 0;
    virtual void Visit( const CIdentifierExpression* expr ) = 0;
    virtual void Visit( const CThisExpression* expr ) = 0;
    virtual void Visit( const CNewIntArrayExpression* expr ) = 0;
    virtual void Visit( const CNewExpression* expr ) = 0;
    virtual void Visit( const CUnaryOpExpression* expr ) = 0;
    virtual void Visit( const CBracesExpression* expr ) = 0;
    virtual void Visit( const CArg* arg ) = 0;
    virtual void Visit( const CUserType* type) = 0;
};

#pragma once