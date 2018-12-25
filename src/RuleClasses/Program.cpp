//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CProgram::CProgram( std::unique_ptr<IMainClass> _mainClass, std::vector<std::unique_ptr<IClassDecl>>& _classList, CLocation &_location) :
        mainClass{ std::move( _mainClass) },
        classList{std::move( _classList )}
{
    location = _location;
}



void CProgram::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}