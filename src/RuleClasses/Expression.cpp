//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CBinOpExpression::CBinOpExpression( IExp* _leftExp, BinOp _binOp, IExp* _rightExp) :
        leftExp( _leftExp ),
        rightExp( _rightExp ),
        binOp( _binOp )
{
}




void CBinOpExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIndexExpression::CIndexExpression( IExp* _exp, IExp* _indexExp ) :
        exp( _exp ),
        indexExp( _indexExp )
{
}



void CIndexExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CLenghtExpression::CLenghtExpression( IExp* _exp) :
        exp( _exp )
{
}



void CLenghtExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CMethodExpression::CMethodExpression( IExp* _exp, const std::string& _identifier, std::vector<IExp*>& _expList) :

        exp( _exp ),
        expList( _expList ),
        identifier( _identifier )
{
}





void CMethodExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIntLiteralExpression::CIntLiteralExpression( const int _val) :
        val( _val)
{
}



void CIntLiteralExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CBoolLiteralExpression::CBoolLiteralExpression( const bool _val) :
        val(_val)
{
}



void CBoolLiteralExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIdentifierExpression::CIdentifierExpression( const std::string& id ) :
        identifier(  id )
{
}


void CIdentifierExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CThisExpression::CThisExpression( )
{
}

void CThisExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CNewIntArrayExpression::CNewIntArrayExpression( IExp* _exp) :
        exp( _exp )
{
}


void CNewIntArrayExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CNewExpression::CNewExpression( const std::string& id)  :
        identifier( id  )
{
}



void CNewExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CUnaryOpExpression::CUnaryOpExpression( UnaryOp _op, IExp* _exp) :
        exp( _exp ),
        op( _op )
{
}



void CUnaryOpExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CBracesExpression::CBracesExpression( IExp* _exp) :
        exp( _exp )
{
}


void CBracesExpression::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

