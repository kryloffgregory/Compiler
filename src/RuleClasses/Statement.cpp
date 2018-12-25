//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CStatementListStatement::CStatementListStatement( std::deque<std::unique_ptr<IStatement>>& _statementList, CLocation &_location) :

        statementList{std::move( _statementList )}
{
}



void CStatementListStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CIfStatement::CIfStatement( std::unique_ptr<IExp> _condition,
                            std::unique_ptr<IStatement> _statementIfTrue,
                            std::unique_ptr<IStatement> _statementIfFalse, CLocation &_location ) :
        condition{std::move( _condition )},
        statementIfTrue{std::move( _statementIfTrue )},
        statementIfFalse{std::move( _statementIfFalse )}
{
}


void CIfStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CWhileStatement::CWhileStatement(
        std::unique_ptr<IExp> _condition,
        std::unique_ptr<IStatement> _cycleBody,
        CLocation &_location) :
        condition{std::move( _condition )},
        cycleBody{std::move( _cycleBody )}
{
}



void CWhileStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CPrintStatement::CPrintStatement( std::unique_ptr<IExp> _expression, CLocation &_location) :
        expression{std::move( _expression )}
{
}



void CPrintStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CAssignStatement::CAssignStatement( const std::string& _left, std::unique_ptr<IExp> _right, CLocation &_location) :
        left(  _left  ),right{std::move( _right )}
{
}



void CAssignStatement::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CArrayAssignStatement::CArrayAssignStatement(
        const std::string& _arrayId,
        std::unique_ptr<IExp> _elementNumber,
        std::unique_ptr<IExp> _rightPart,
        CLocation &_location) :
        arrayId( _arrayId  ),
        elementNumber{std::move( _elementNumber )},
        rightPart{std::move( _rightPart )}
{
    location = _location;
}



void CArrayAssignStatement::Accept( IVisitor* visitor ) const
{
    return visitor->Visit( this );
}
