//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CArg::CArg( IType* _type, const std::string& _identifier) :
    type(_type),
    id(  _identifier  )
{
}
void CArg::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}