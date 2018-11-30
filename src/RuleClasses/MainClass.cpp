//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CMainClass::CMainClass( std::string& _identifier, std::string& _arsId, std::deque<IStatement*>& _statements) :
        identifier( _identifier),
        argsIdentifier(_arsId),
        statements( _statements )
{
}



void CMainClass::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}