//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CProgram::CProgram( IMainClass* _mainClass, std::vector<IClassDecl*>& _classList) :
        mainClass( _mainClass ),
        classList( _classList )
{
}



void CProgram::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}