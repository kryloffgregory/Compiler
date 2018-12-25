//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CArg::CArg( std::unique_ptr<IType> _type, const std::string& _identifier, CLocation &_location) :
    type{std::move(_type)},
    id(  _identifier  )
{
    location = _location;
}
void CArg::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}