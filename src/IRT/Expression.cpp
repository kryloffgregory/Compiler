#include <utility>

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

    CExprList* CConst::Kids() const
    {
        return nullptr;
    }

    IExpr* CConst::Build( const CExprList* kids ) const
    {
        return new CConst( value );
    }

    CName::CName( std::shared_ptr<const Temp::CLabel> _name ) :
            name(std::move(_name))
    {}

    std::shared_ptr<const Temp::CLabel> CName::GetName() const
    {
        return name;
    }

    void CName::Accept( IIRTreeVisitor* visitor ) const
    {
        visitor->Visit( this );
    }

    CExprList* CName::Kids() const
    {
        return nullptr;
    }

    IExpr* CName::Build( const CExprList* kids ) const
    {
        return new CName( name );
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

    IRTree::CExprList* CTemp::Kids() const
    {
        return nullptr;
    }

    IRTree::IExpr* CTemp::Build( const CExprList* kids ) const
    {
        return new CTemp( temp );
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

    CExprList* CBinop::Kids() const
    {
        return new IRTree::CExprList( left, std::make_shared<IRTree::CExprList>( right, nullptr ) );
    }

    IExpr* CBinop::Build( const CExprList* kids ) const
    {
        return new CBinop( BINOP(binop), kids->GetHead(), kids->GetTail()->GetHead() );
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


    CExprList* CMem::Kids() const
    {
        return new IRTree::CExprList( mem, nullptr );
    }

    IExpr* CMem::Build( const CExprList* kids ) const
    {
        return new CMem( kids->GetHead() );
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

    CExprList* CCall::Kids() const
    {
        CExprList* list = nullptr;
        std::shared_ptr<const CExprList> tlist = nullptr;
        int n = arguments.size();
        if (n == 0){
            return nullptr;
        }
        for (int i = n - 1; i > 0; --i) {
            CExprPtr tmp = arguments[i];
            tlist =  std::make_shared<const CExprList>(tmp, tlist);
        }
        return new CExprList( arguments[0], tlist);
    }

    IExpr* CCall::Build( const CExprList* kids ) const
    {
        std::vector<CExprPtr> arguments;
        auto current = kids;
        std::shared_ptr<const CExprList> tcurrent;

        if (current != nullptr) {
            arguments.push_back(current->GetHead());
            tcurrent = current->GetTail();
        }

        while (tcurrent != nullptr) {
            arguments.push_back(tcurrent->GetHead());
            tcurrent = tcurrent->GetTail();
        }
        return new CCall( funcName, arguments);

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

    CExprList* CESeq::Kids() const
    {
        throw std::logic_error( "Kids() not applicable to ESEQ" );
    }

    IExpr* CESeq::Build( const CExprList* kids ) const
    {
        throw std::logic_error( "Build() not applicable to ESEQ" );
    }

    CExprList::CExprList( std::shared_ptr<const IExpr> _head, std::shared_ptr<const CExprList> _tail ) :
            head( _head ), tail( _tail )
    {
    }

    std::shared_ptr<const IExpr> CExprList::GetHead() const
    {
        return head;
    }

    std::shared_ptr<const CExprList> CExprList::GetTail() const
    {
        return tail;
    }
}