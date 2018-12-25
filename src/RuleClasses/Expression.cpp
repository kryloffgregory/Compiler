//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CBinOpExpression::CBinOpExpression( std::unique_ptr<IExp> _leftExp, BinOp _binOp,
        std::unique_ptr<IExp> _rightExp, CLocation &_location) :
        leftExp{std::move( _leftExp )},
        rightExp{std::move( _rightExp )},
        binOp( _binOp )
{
    location = _location;
}




void CBinOpExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIndexExpression::CIndexExpression( std::unique_ptr<IExp> _exp, std::unique_ptr<IExp> _indexExp , CLocation &_location) :
        exp{std::move( _exp )},
        indexExp{std::move( _indexExp )}
{
    location = _location;
}



void CIndexExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CLenghtExpression::CLenghtExpression( std::unique_ptr<IExp> _exp, CLocation &_location) :
        exp{std::move( _exp )}
{
    location = _location;
}



void CLenghtExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CMethodExpression::CMethodExpression( std::unique_ptr<IExp> _exp,
        const std::string& _identifier,
        std::vector<std::unique_ptr<IExp>>& _expList,
        CLocation &_location) :

        exp{std::move( _exp )},
        expList{ std::move(_expList) },


        identifier{_identifier }
{
    location = _location;
}





void CMethodExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIntLiteralExpression::CIntLiteralExpression( const int _val, CLocation &_location) :
        val( _val)
{
    location = _location;
}



void CIntLiteralExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CBoolLiteralExpression::CBoolLiteralExpression( const bool _val, CLocation &_location) :
        val(_val)
{
    location = _location;
}



void CBoolLiteralExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIdentifierExpression::CIdentifierExpression( const std::string& id , CLocation &_location) :
        identifier(  id )
{
    location = _location;
}


void CIdentifierExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CThisExpression::CThisExpression( CLocation &_location)
{
    location = _location;
}

void CThisExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CNewIntArrayExpression::CNewIntArrayExpression( std::unique_ptr<IExp> _exp, CLocation &_location) :
        exp{std::move( _exp )}
{
    location = _location;
}


void CNewIntArrayExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CNewExpression::CNewExpression( const std::string& id, CLocation &_location)  :
        identifier( id  )
{
    location = _location;
}



void CNewExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CUnaryOpExpression::CUnaryOpExpression( UnaryOp _op, std::unique_ptr<IExp> _exp, CLocation &_location) :
        exp{std::move( _exp )},
        op{_op}
{
    location = _location;
}



void CUnaryOpExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CBracesExpression::CBracesExpression( std::unique_ptr<IExp> _exp, CLocation &_location) :
        exp{std::move( _exp )}
{
}


void CBracesExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

