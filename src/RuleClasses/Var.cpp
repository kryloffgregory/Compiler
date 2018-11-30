//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CVarDecl::CVarDecl( IType* _type, const std::string& _identifier) :
        type( _type ),
        identifier( _identifier )
{
}



void CVarDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}
