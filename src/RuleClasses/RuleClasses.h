//
// Created by gregory on 19.11.18.
//
#pragma once

#include "RuleClassInterfaces.h"
#include <string>
#include <vector>
#  include <bits/unique_ptr.h>
#include <deque>
#include "../Visitor.h"
#include "../Location/Location.h"

class CProgram : public IProgram{
public:
    CProgram( std::unique_ptr<IMainClass> _mainClass, std::vector<std::unique_ptr<IClassDecl>>& _classList, CLocation &location);

    void Accept( IVisitor* visitor ) const override;



    std::unique_ptr<IMainClass> mainClass;
    const std::vector<std::unique_ptr<IClassDecl>> classList;
};

class CMainClass : public IMainClass {
public:
    CMainClass( std::string &_identifier, std::string &_arsId, std::deque<std::unique_ptr<IStatement>>& _statements, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::string identifier;
    const std::string argsIdentifier;
    const std::deque<std::unique_ptr<IStatement>> statements;
};

class CMethodDecl : public IMethodDecl {
public:
    CMethodDecl(
            std::unique_ptr<IType> _type,
            const std::string& _methodName,
            std::vector<std::unique_ptr<IArg>>& _argList,
            std::vector<std::unique_ptr<IVarDecl>>& _varList,
            std::deque<std::unique_ptr<IStatement>>& _statementList,
            std::unique_ptr<IExp> _returnExpr,
            CLocation &location
            );

    void Accept( IVisitor* visitor ) const override;


    std::unique_ptr<IType> type;
    const std::string methodName;
    const std::vector<std::unique_ptr<IArg>>argList;
    const std::vector<std::unique_ptr<IVarDecl>> varList;
    const std::deque<std::unique_ptr<IStatement>> statementList;
    const std::unique_ptr<IExp> returnExpr;
};

class CClassDecl : public IClassDecl{
public:
    CClassDecl(const std::string &_className,
            std::vector<std::unique_ptr<IVarDecl>>& _varList,
            std::vector<std::unique_ptr<IMethodDecl>>& _methodList,
            const bool isDerived,
            const std::string &baseClass,
            CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::string className;
    const std::vector<std::unique_ptr<IVarDecl>> varList;
    const std::vector<std::unique_ptr<IMethodDecl>>  methodList;
    bool isDerived;
    const std::string baseClass;
};



class CVarDecl : public IVarDecl{
public:
    CVarDecl( std::unique_ptr<IType> _type, const std::string& _identifier, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::unique_ptr<IType> type;
    const std::string identifier;
};


class CStandardType : public IType {
public:
    enum StandardType { INT = 0, INT_ARRAY, BOOL };

    CStandardType( StandardType _type, CLocation &location);

    explicit CStandardType( const CStandardType* other );

    void Accept( IVisitor* visitor ) const override;

    bool IsPODType() const override;

    StandardType type;
};
class CUserType : public IType {
public:
    CUserType(const std::string& _type, CLocation &location);


    bool IsPODType() const override;

    void Accept(IVisitor* visitor) const override;

    const std::string type;
};

class CArg : public IArg {
public:
    CArg(std::unique_ptr<IType> _type, const std::string& _id, CLocation &location);
    void Accept( IVisitor*  visitor ) const override;


    std::unique_ptr<IType> type;
    const std::string id;

};

class CStatementListStatement : public IStatement{
public:
    CStatementListStatement( std::deque<std::unique_ptr<IStatement>>& _statementList, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::deque<std::unique_ptr<IStatement>>  statementList;
};

class CIfStatement : public IStatement{
public:
    CIfStatement( std::unique_ptr<IExp> _condition,
            std::unique_ptr<IStatement> _statementIfTrue,
            std::unique_ptr<IStatement> _statementIfFalse,
            CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::unique_ptr<IExp> condition;
    const std::unique_ptr<IStatement> statementIfTrue;
    const std::unique_ptr<IStatement> statementIfFalse;
};

class CWhileStatement : public IStatement{
public:
    CWhileStatement( std::unique_ptr<IExp> _condition, std::unique_ptr<IStatement> _cycleBody, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::unique_ptr<IExp> condition;
    const std::unique_ptr<IStatement> cycleBody;
};

class CPrintStatement : public IStatement {
public:
    CPrintStatement( std::unique_ptr<IExp> _expression, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::unique_ptr<IExp> expression;
};

class CAssignStatement : public IStatement {
public:
    CAssignStatement( const std::string& _left, std::unique_ptr<IExp> _right, CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::string left;
    const std::unique_ptr<IExp> right;
};

class CArrayAssignStatement : public IStatement{
public:
    CArrayAssignStatement( const std::string& _arrayId,
            std::unique_ptr<IExp> _elementNumber,
            std::unique_ptr<IExp> _rightPart,
            CLocation &location);

    void Accept( IVisitor* visitor ) const override;


    const std::string arrayId;
    const std::unique_ptr<IExp> elementNumber;
    const std::unique_ptr<IExp> rightPart;
};

class CBinOpExpression : public IExp{
public:
    enum BinOp { AND, LESS, PLUS, MINUS, TIMES, DIVIDE };

    CBinOpExpression( std::unique_ptr<IExp> _leftExp, BinOp _binOp, std::unique_ptr<IExp> _rightExp, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> leftExp;
    const std::unique_ptr<IExp> rightExp;
    BinOp binOp;
};

class CIndexExpression : public IExp{
public:
    CIndexExpression( std::unique_ptr<IExp> _exp, std::unique_ptr<IExp> _indexExp, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> exp;
    const std::unique_ptr<IExp> indexExp;
};

class CLenghtExpression : public IExp{
public:
    CLenghtExpression( std::unique_ptr<IExp> _exp, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> exp;
};

class CMethodExpression : public IExp{
public:
    CMethodExpression( std::unique_ptr<IExp> _exp, const std::string& _identifier, std::vector<std::unique_ptr<IExp>>& _expList, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> exp;
    const std::vector<std::unique_ptr<IExp> > expList;
    const std::string identifier;
};

class CIntLiteralExpression : public IExp{
public:
    CIntLiteralExpression( const int _val, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const int val;
};

class CBoolLiteralExpression : public IExp {
public:
    CBoolLiteralExpression( const bool _val, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const bool val;
};

class CIdentifierExpression : public IExp {
public:
    CIdentifierExpression( const std::string& id, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::string identifier;
};

class CThisExpression : public IExp{
public:
    explicit CThisExpression(CLocation &location);

    void Accept( IVisitor*  visitor ) const override;
};

class CNewIntArrayExpression : public IExp{
public:
    CNewIntArrayExpression( std::unique_ptr<IExp> _exp,CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> exp;
};

class CNewExpression : public IExp{
public:
    CNewExpression( const std::string& id ,CLocation &location);

    void Accept( IVisitor* visitor ) const override;

    const std::string identifier;
};

class CUnaryOpExpression : public IExp{
public:
    enum UnaryOp { MINUS, NOT };

    CUnaryOpExpression( UnaryOp _op, std::unique_ptr<IExp> _exp, CLocation &location);

    void Accept( IVisitor*  visitor ) const override;


    const std::unique_ptr<IExp> exp;
    UnaryOp op;
};

class CBracesExpression : public IExp {
public:
    CBracesExpression( std::unique_ptr<IExp> _exp , CLocation &location);

    void Accept( IVisitor*  visitor ) const override;

    const std::unique_ptr<IExp> exp;
};