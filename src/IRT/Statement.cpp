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

    CExprList* CMove::Kids() const
    {
        if( std::dynamic_pointer_cast<const IRTree::CMem>( destExpr ) != nullptr ) {
            return new CExprList( std::dynamic_pointer_cast<const IRTree::CMem>( destExpr )->GetMem(), std::make_shared<const CExprList>( srcExpr, nullptr ) );
        } else {
            return new CExprList( srcExpr, nullptr );
        }
    }

    IStm* CMove::Build(const CExprList* kids) const
    {
        if( std::dynamic_pointer_cast< const IRTree::CMem >( destExpr ) != nullptr ) {
            return new IRTree::CMove( std::make_shared<IRTree::CMem>( kids->GetHead() ), kids->GetTail()->GetHead() );
        } else {
            return new IRTree::CMove( destExpr, kids->GetHead() );
        }
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

    CExprList* CExpr::Kids() const
    {
        return new IRTree::CExprList( exp, nullptr );
    }

    IStm* CExpr::Build(const CExprList* kids) const
    {
        return new IRTree::CExpr( kids->GetHead() );
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

    CExprList* CJump::Kids() const
    {
        return new IRTree::CExprList( jmpExpr, nullptr );
    }

    IStm* CJump::Build(const CExprList* kids) const
    {
        return new IRTree::CJump( kids->GetHead(), labels );
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

    CExprList* CCondJump::Kids() const {
        //return new IRTree::CExprList( expr, nullptr );
        return new CExprList( leftExpr, std::make_shared<const CExprList>( rightExpr, nullptr ) );
    }

    IStm* CCondJump::Build(const CExprList* kids) const
    {
        return new IRTree::CCondJump( binOp, leftExpr, rightExpr, ifTrueLabel, ifFalseLabel );
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

    CExprList* CSeq::Kids() const
    {

        throw std::logic_error( "Kids() const not applicable to SEQ" );
    }

    IStm* CSeq::Build(const CExprList* kids) const
    {
        throw std::logic_error( "Build() not applicable to SEQ" );
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

    CExprList* CLabel::Kids() const
    {
        return nullptr;
    }

    IStm* CLabel::Build(const CExprList* kids) const
    {
        return new CLabel( label );
    }

    CStmList::CStmList( std::shared_ptr<const IStm> _head, std::shared_ptr<const CStmList> _tail ) :
            head(_head), tail( _tail )
    {}

    std::shared_ptr<const IStm>& CStmList::GetHead() const
    {
        return head;
    }

    std::shared_ptr<const CStmList>& CStmList::GetTail() const
    {
        return tail;
    }
}