//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CStandardType::CStandardType( StandardType _type ) :
        type( _type )
{
}

CStandardType::CStandardType( const CStandardType* other ) :
        type( other->type )
{
}

bool CStandardType::IsPODType() const
{
    return true;
}


void CStandardType::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

CUserType::CUserType( const std::string& _type) :
    type( _type ) {
}

bool CUserType::IsPODType() const
{
    return false;
}


void CUserType::Accept(IVisitor *visitor) const {
    visitor->Visit(this);
}