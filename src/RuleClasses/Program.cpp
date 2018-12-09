//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CProgram::CProgram( IMainClass* _mainClass, std::vector<IClassDecl*>& _classList, CLocation &_location) :
        mainClass( _mainClass ),
        classList( _classList )
{
    location = _location;
}



void CProgram::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}