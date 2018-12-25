//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CVarDecl::CVarDecl( std::unique_ptr<IType> _type, const std::string& _identifier, CLocation &_location) :
        type{ std::move( _type )},
        identifier( _identifier )
{
    location = _location;
}



void CVarDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}
