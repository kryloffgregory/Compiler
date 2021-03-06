//
// Created by gregory on 23.12.18.
//
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "Statement.h"
#include "Label.h"
#include "../SymbolTable/Symbol.h"


namespace IRTree
{
    class IStm;

    class CExprList {
    public:
        CExprList( const std::shared_ptr<const IExpr> head, std::shared_ptr<const CExprList> tail );

        std::shared_ptr<const IExpr> GetHead() const;
        std::shared_ptr<const CExprList> GetTail() const;
    private:
        std::shared_ptr<const IExpr> head;
        std::shared_ptr<const CExprList> tail;
    };

    class IExpr {
    public:
        enum BINOP {
            PLUS, MINUS, MUL, DIV, AND, OR, LESS, XOR
        };
        enum CJUMP {
            EQ=8, NE, LT, GT, LE, GE, ULT, ULE, UGT, UGE
        };

        virtual ~IExpr() = default;;

        virtual void Accept( IIRTreeVisitor* visitor ) const = 0;

        virtual CExprList* Kids() const = 0;
        virtual IExpr* Build( const CExprList* kids ) const = 0;
    };

    typedef std::shared_ptr<const IExpr> CExprPtr;



    // Const expression
    class CConst : public IExpr {
    public:
        explicit CConst( int value );
        int GetValue() const;

        void Accept( IIRTreeVisitor* visitor ) const override;

        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        int value;
    };

    // Name for jumps
    class CName : public IExpr {
    public:
        explicit CName( std::shared_ptr<const Temp::CLabel> name );
        std::shared_ptr<const Temp::CLabel> GetName() const;

        void Accept( IIRTreeVisitor* visitor ) const override;


        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const Temp::CLabel> name;
    };

    // Temprorary variable
    class CTemp : public IExpr {
    public:
        explicit CTemp(std::shared_ptr<Temp::CTemp> temp );
        std::shared_ptr<Temp::CTemp> GetTemp( ) const;

        void Accept( IIRTreeVisitor* visitor ) const override;

        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<Temp::CTemp> temp;
    };

    // Binary operator
    class CBinop : public IExpr {
    public:
        CBinop( BINOP binop, CExprPtr left, CExprPtr right );

        BINOP GetBinOp() const;
        const CExprPtr GetLeft() const;
        const CExprPtr GetRight() const;

        void Accept( IIRTreeVisitor* visitor ) const override;


        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        BINOP binop;
        const CExprPtr left;
        const CExprPtr right;
    };

    // Reading memory with address returned by expression
    class CMem : public IExpr {
    public:
        explicit CMem( CExprPtr mem );
        const CExprPtr GetMem() const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        const CExprPtr mem;
    };


    // Method call with args
    class CCall : public IExpr {
    public:
        CCall( const std::string &funcName, const std::vector<CExprPtr>& arguments );

        const std::string GetFunctionName() const;
        std::vector<CExprPtr> GetArguments() const;

        void Accept( IIRTreeVisitor* visitor ) const override;

        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        const std::string funcName;
        std::vector<CExprPtr> arguments;
    };
    typedef std::shared_ptr<const CCall> CCallPtr;

    // Do statement than process and return expression
    class CESeq : public IExpr {
    public:
        CESeq( CStmPtr statement, CExprPtr expression );
        const CStmPtr GetStatement() const;
        const CExprPtr GetExpression() const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IExpr* Build( const CExprList* kids ) const override;
    private:
        const CStmPtr statement;
        const CExprPtr expression;
    };
    typedef std::shared_ptr<const CESeq> CESeqPtr;



}