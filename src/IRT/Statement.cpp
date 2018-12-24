//
// Created by gregory on 23.12.18.
//

#include "Statement.h"
#include "Expression.h"
#include <vector>

namespace IRTree
{
    CMove::CMove( std::shared_ptr<const IExpr> dst, std::shared_ptr<const IExpr> src ) :
            destExpr( dst ),
            srcExpr( src )
    {}

    std::shared_ptr<const IExpr> CMove::GetDestExpr() const
    {
        return destExpr;
    }

    std::shared_ptr<const IExpr> CMove::GetSrcExpr() const
    {
        return srcExpr;
    }

    void CMove::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CExpr::CExpr( std::shared_ptr<const IExpr> _exp ) :
            exp(std::move(_exp))
    {}

    std::shared_ptr<const IExpr> CExpr::GetExp() const
    {
        return exp;
    }

    void CExpr::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CJump::CJump( std::shared_ptr<const IExpr> _exp, const std::vector<std::shared_ptr<const Temp::CLabel>>& _labels ) :
            jmpExpr(std::move(_exp)),
            labels( _labels )
    {}

    CJump::CJump( std::shared_ptr<const Temp::CLabel> label ) :
            jmpExpr( new CName(label) ),
            labels( {label} )
    {}



    std::shared_ptr<const IExpr> CJump::GetJumpExpr() const
    {
        return jmpExpr;
    }

    std::vector<std::shared_ptr<const Temp::CLabel>> CJump::GetLabels() const
    {
        return labels;
    }

    void CJump::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CCondJump::CCondJump( int _binOp, std::shared_ptr<const IExpr> _left, std::shared_ptr<const IExpr> _right,
                          std::shared_ptr<const Temp::CLabel> _ifTrueLabel, std::shared_ptr<const Temp::CLabel> _ifFalseLabel ) :
            leftExpr(std::move(_left)),
            rightExpr(std::move(_right)),
            binOp( _binOp ),
            ifTrueLabel(std::move(_ifTrueLabel)),
            ifFalseLabel(std::move(_ifFalseLabel))
    {}

    std::shared_ptr<const IExpr> CCondJump::GetLeftExpr() const
    {
        return leftExpr;
    }

    std::shared_ptr<const IExpr> CCondJump::GetRightExpr() const
    {
        return rightExpr;
    }

    int CCondJump::GetBinOp() const
    {
        return binOp;
    }

    std::shared_ptr<const Temp::CLabel> CCondJump::GetIfTrueLabel( ) const
    {
        return ifTrueLabel;
    }

    std::shared_ptr<const Temp::CLabel> CCondJump::GetIfFalseLabel() const
    {
        return ifFalseLabel;
    }

    void CCondJump::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CSeq::CSeq( std::shared_ptr<const IStm> left, std::shared_ptr<const IStm> right ) :
            leftStm(std::move(left)),
            rightStm(std::move(right))
    {}

    std::shared_ptr<const IStm> CSeq::GetLeftStm() const
    {
        return leftStm;
    }

    std::shared_ptr<const IStm> CSeq::GetRightStm() const
    {
        return rightStm;
    }

    void CSeq::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CLabel::CLabel( std::shared_ptr<const Temp::CLabel> _label ) :
            label(std::move(_label))
    {}

    std::shared_ptr<const Temp::CLabel> CLabel::GetLabel() const
    {
        return label;
    }

    void CLabel::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

}