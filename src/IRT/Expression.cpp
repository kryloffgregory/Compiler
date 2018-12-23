//
// Created by gregory on 23.12.18.
//
#include "Expression.h"

namespace IRTree
{

    CConst::CConst( int _value ) :
            value( _value )
    {}

    int CConst::GetValue() const
    {
        return value;
    }

    void CConst::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CName::CName( std::shared_ptr<const Temp::CLabel> _name ) :
            name( _name )
    {}

    std::shared_ptr<const Temp::CLabel> CName::GetName() const
    {
        return name;
    }

    void CName::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CTemp::CTemp( const std::shared_ptr<Temp::CTemp> _temp ) :
            temp( _temp )
    {}

    std::shared_ptr<Temp::CTemp> CTemp::GetTemp() const
    {
        return temp;
    }

    void CTemp::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CBinop::CBinop( BINOP _binop, CExprPtr _left, CExprPtr _right ) :
            binop( _binop ),
            left( _left ),
            right( _right )
    {}

    IExpr::BINOP CBinop::GetBinOp( ) const
    {
        return binop;
    }

    const CExprPtr CBinop::GetLeft() const
    {
        return left;
    }

    const CExprPtr CBinop::GetRight() const
    {
        return right;
    }

    void CBinop::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CMem::CMem( CExprPtr _mem ) :
            mem( _mem )
    {}

    const CExprPtr CMem::GetMem() const
    {
        return mem;
    }

    void CMem::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CCall::CCall( const std::string &_funcName, const std::vector<CExprPtr>& _arguments ) :
            funcName( _funcName ),
            arguments( _arguments )
    {}

    const std::string CCall::GetFunctionName() const
    {
        return funcName;
    }

    std::vector<CExprPtr> CCall::GetArguments() const
    {
        return arguments;
    }

    void CCall::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CESeq::CESeq( CStmPtr _statement, CExprPtr _expression ) :
            statement( _statement ),
            expression( _expression )
    {}

    const CStmPtr CESeq::GetStatement() const
    {
        return statement;
    }

    const CExprPtr CESeq::GetExpression() const
    {
        return expression;
    }

    void CESeq::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

}