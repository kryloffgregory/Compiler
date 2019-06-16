//
// Created by gregory on 23.12.18.
//

#pragma once
#include <vector>
#include <memory>

#include "Label.h"
#include "IIRVisitor.h"

namespace IRTree
{
    class IExpr;
    class CExprList;

    class IStm {
    public:
        virtual ~IStm() = default;

        virtual void Accept( IIRTreeVisitor* visitor ) const = 0;
        virtual CExprList* Kids() const = 0;
        virtual IStm* Build( const CExprList* kids ) const = 0;
    };

    typedef std::shared_ptr<const IStm> CStmPtr;


    // Copy result src into dst
    class CMove : public IStm {
    public:
        CMove( std::shared_ptr<const IExpr> dst, std::shared_ptr<const IExpr> src );

        std::shared_ptr<const IExpr> GetDestExpr( ) const;
        std::shared_ptr<const IExpr> GetSrcExpr( ) const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const IExpr> destExpr;
        std::shared_ptr<const IExpr> srcExpr;
    };

    typedef std::shared_ptr<const CMove> CMovePtr;
    // Calculate exp and forget about result
    class CExpr : public IStm {
    public:
        explicit CExpr( std::shared_ptr<const IExpr> exp );

        std::shared_ptr<const IExpr> GetExp( ) const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const IExpr> exp;
    };

    typedef std::shared_ptr<const CExpr> CCExprPtr;

    // Jump to label
    class CJump : public IStm {
    public:
        CJump( std::shared_ptr<const IExpr> exp, const std::vector<std::shared_ptr<const Temp::CLabel>>& labels );

        explicit CJump( std::shared_ptr<const Temp::CLabel> label );

        std::shared_ptr<const IExpr> GetJumpExpr() const;
        std::vector<std::shared_ptr<const Temp::CLabel>> GetLabels() const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;

    private:
        std::shared_ptr<const IExpr> jmpExpr;
        std::vector<std::shared_ptr<const Temp::CLabel>> labels;
    };

    // Jump with condition
    class CCondJump : public IStm {
    public:
        CCondJump( int binOp, std::shared_ptr<const IExpr> left, std::shared_ptr<const IExpr> right,
                   std::shared_ptr<const Temp::CLabel> ifTrueLabel, std::shared_ptr<const Temp::CLabel> ifFalseLabel );

        std::shared_ptr<const IExpr> GetLeftExpr() const;
        std::shared_ptr<const IExpr> GetRightExpr() const;
        int GetBinOp( ) const;
        std::shared_ptr<const Temp::CLabel> GetIfTrueLabel( ) const;
        std::shared_ptr<const Temp::CLabel> GetIfFalseLabel( ) const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const IExpr> leftExpr;
        std::shared_ptr<const IExpr> rightExpr;
        int binOp;
        std::shared_ptr<const Temp::CLabel> ifTrueLabel;
        std::shared_ptr<const Temp::CLabel> ifFalseLabel;
    };

    // Calculate left than right sequentially
    class CSeq : public IStm {
    public:
        CSeq( std::shared_ptr<const IStm> left, std::shared_ptr<const IStm> right );

        std::shared_ptr<const IStm> GetLeftStm() const;
        std::shared_ptr<const IStm> GetRightStm() const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const IStm> leftStm;
        std::shared_ptr<const IStm> rightStm;
    };
    typedef std::shared_ptr<const CSeq> CSeqPtr;


    class CLabel : public IStm {
    public:
        explicit CLabel( std::shared_ptr<const Temp::CLabel> label );

        std::shared_ptr<const Temp::CLabel> GetLabel( ) const;

        void Accept( IIRTreeVisitor* visitor ) const override;
        virtual CExprList* Kids() const override;

        virtual IStm* Build( const CExprList* kids ) const override;
    private:
        std::shared_ptr<const Temp::CLabel> label;
    };
    class CStmList {
    public:
        CStmList( std::shared_ptr<const IStm> head, std::shared_ptr<const CStmList> tail );

        std::shared_ptr<const IStm>& GetHead() const;
        std::shared_ptr<const CStmList>& GetTail() const;

    private:
        mutable std::shared_ptr<const IStm> head;
        mutable std::shared_ptr<const CStmList> tail;
    };

    typedef std::shared_ptr<const CStmList> CStmListPtr;
}