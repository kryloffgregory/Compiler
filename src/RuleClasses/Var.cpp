//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CVarDecl::CVarDecl( IType* _type, const std::string& _identifier, CLocation &_location) :
        type( _type ),
        identifier( _identifier )
{
    location = _location;
}



void CVarDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}
