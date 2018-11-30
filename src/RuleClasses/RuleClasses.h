//
// Created by gregory on 19.11.18.
//
#pragma once

#include "RuleClassInterfaces.h"
#include <string>
#include <vector>
#include <memory>
#include <deque>
#include "../Visitor.h"

class CProgram : public IProgram{
public:
    CProgram( IMainClass* _mainClass, std::vector<IClassDecl*>& _classList);

    void Accept( IVisitor* visitor ) const override;



    const IMainClass* mainClass;
    const std::vector<IClassDecl*> classList;
};

class CMainClass : public IMainClass {
public:
    CMainClass( std::string &_identifier, std::string &_arsId, std::deque<IStatement*>& _statements);

    void Accept( IVisitor* visitor ) const override;


    const std::string identifier;
    const std::string argsIdentifier;
    const std::deque<IStatement*> statements;
};

class CMethodDecl : public IMethodDecl {
public:
    CMethodDecl(
            IType* _type,
            const std::string& _methodName,
            std::vector<IArg*>& _argList,
            std::vector<IVarDecl*>& _varList,
            std::deque<IStatement*>& _statementList,
            IExp* _returnExpr
            );

    void Accept( IVisitor* visitor ) const override;


    const std::shared_ptr<IType> type;
    const std::string methodName;
    const std::vector<IArg*>argList;
    const std::vector<IVarDecl*> varList;
    const std::deque<IStatement*> statementList;
    const IExp* returnExpr;
};

class CClassDecl : public IClassDecl{
public:
    CClassDecl(const std::string _className, std::vector<IVarDecl*>& _varList, std::vector<IMethodDecl*>& _methodList );

    void Accept( IVisitor* visitor ) const override;


    const std::string className;
    const std::vector<IVarDecl*> varList;
    const std::vector<IMethodDecl*>  methodList;
};


class CVarDecl : public IVarDecl{
public:
    CVarDecl( IType* _type, const std::string& _identifier);

    void Accept( IVisitor* visitor ) const override;


    const std::shared_ptr<IType> type;
    const std::string identifier;
};


class CStandardType : public IType {
public:
    enum StandardType { INT = 0, INT_ARRAY, BOOL };

    CStandardType( StandardType _type);

    CStandardType( const CStandardType* other );

    void Accept( IVisitor* visitor ) const override;

    bool IsPODType() const override;

    StandardType type;
};
class CUserType : public IType {
public:
    CUserType(const std::string& _type);


    bool IsPODType() const override;

    void Accept(IVisitor* visitor) const override;

    const std::string type;
};

class CArg : public IArg {
public:
    CArg(IType* _type, const std::string& _id);
    void Accept( IVisitor*  visitor ) const override;


    IType* type;
    const std::string id;

};

class CStatementListStatement : public IStatement{
public:
    CStatementListStatement( std::deque<IStatement*>& _statementList);

    void Accept( IVisitor* visitor ) const override;


    const std::deque<IStatement*>  statementList;
};

class CIfStatement : public IStatement{
public:
    CIfStatement( IExp* _condition, IStatement* _statementIfTrue, IStatement* _statementIfFalse);

    void Accept( IVisitor* visitor ) const override;


    const std::shared_ptr<IExp> condition;
    const std::shared_ptr<IStatement> statementIfTrue;
    const std::shared_ptr<IStatement> statementIfFalse;
};

class CWhileStatement : public IStatement{
public:
    CWhileStatement( IExp* _condition, IStatement* _cycleBody);

    void Accept( IVisitor* visitor ) const override;


    const std::shared_ptr<IExp> condition;
    const std::shared_ptr<IStatement> cycleBody;
};

class CPrintStatement : public IStatement {
public:
    CPrintStatement( IExp* _expression);

    void Accept( IVisitor* visitor ) const override;


    const std::shared_ptr<IExp> expression;
};

class CAssignStatement : public IStatement {
public:
    CAssignStatement( const std::string& _left, IExp* _right);

    void Accept( IVisitor* visitor ) const override;


    const std::string left;
    const std::shared_ptr<IExp> right;
};

class CArrayAssignStatement : public IStatement{
public:
    CArrayAssignStatement( const std::string& _arrayId, IExp* _elementNumber, IExp* _rightPart);

    void Accept( IVisitor* visitor ) const override;


    const std::string arrayId;
    const std::shared_ptr<IExp> elementNumber;
    const std::shared_ptr<IExp> rightPart;
};

class CBinOpExpression : public IExp{
public:
    enum BinOp { AND, LESS, PLUS, MINUS, TIMES, DIVIDE };

    CBinOpExpression( IExp* _leftExp, BinOp _binOp, IExp* _rightExp);

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> leftExp;
    const std::shared_ptr<IExp> rightExp;
    BinOp binOp;
};

class CIndexExpression : public IExp{
public:
    CIndexExpression( IExp* _exp, IExp* _indexExp);

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> exp;
    const std::shared_ptr<IExp> indexExp;
};

class CLenghtExpression : public IExp{
public:
    CLenghtExpression( IExp* _exp);

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> exp;
};

class CMethodExpression : public IExp{
public:
    CMethodExpression( IExp* _exp, const std::string& _identifier, std::vector<IExp*>& _expList);

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> exp;
    const std::vector<IExp*> expList;
    const std::string identifier;
};

class CIntLiteralExpression : public IExp{
public:
    CIntLiteralExpression( const int _val);

    void Accept( IVisitor*  visitor ) const override;


    const int val;
};

class CBoolLiteralExpression : public IExp {
public:
    CBoolLiteralExpression( const bool _val);

    void Accept( IVisitor*  visitor ) const override;


    const bool val;
};

class CIdentifierExpression : public IExp {
public:
    CIdentifierExpression( const std::string& id);

    void Accept( IVisitor*  visitor ) const override;


    const std::string identifier;
};

class CThisExpression : public IExp{
public:
    CThisExpression();

    void Accept( IVisitor*  visitor ) const override;
};

class CNewIntArrayExpression : public IExp{
public:
    CNewIntArrayExpression( IExp* _exp );

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> exp;
};

class CNewExpression : public IExp{
public:
    CNewExpression( const std::string& id );

    void Accept( IVisitor* visitor ) const override;

    const std::string identifier;
};

class CUnaryOpExpression : public IExp{
public:
    enum UnaryOp { MINUS, NOT };

    CUnaryOpExpression( UnaryOp _op, IExp* _exp);

    void Accept( IVisitor*  visitor ) const override;


    const std::shared_ptr<IExp> exp;
    UnaryOp op;
};

class CBracesExpression : public IExp {
public:
    CBracesExpression( IExp* _exp );

    void Accept( IVisitor*  visitor ) const override;

    const std::shared_ptr<IExp> exp;
};