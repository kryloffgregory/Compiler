//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CStatementListStatement::CStatementListStatement( std::deque<IStatement*>& _statementList) :

        statementList( _statementList )
{
}



void CStatementListStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIfStatement::CIfStatement( IExp* _condition, IStatement* _statementIfTrue, IStatement* _statementIfFalse ) :
        condition( _condition ),
        statementIfTrue( _statementIfTrue ),
        statementIfFalse( _statementIfFalse )
{
}


void CIfStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CWhileStatement::CWhileStatement( IExp* _condition, IStatement* _cycleBody) :
        condition( _condition ),
        cycleBody( _cycleBody )
{
}



void CWhileStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CPrintStatement::CPrintStatement( IExp* _expression) :
        expression( _expression )
{
}



void CPrintStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CAssignStatement::CAssignStatement( const std::string& _left, IExp* _right) :
        left(  _left  ),right( _right )
{
}



void CAssignStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CArrayAssignStatement::CArrayAssignStatement( const std::string& _arrayId, IExp* _elementNumber, IExp* _rightPart) :
        arrayId( _arrayId  ),
        elementNumber( _elementNumber ),
        rightPart( _rightPart )
{
}



void CArrayAssignStatement::Accept( IVisitor* visitor ) const
{
    return visitor->Visit( this );
}
