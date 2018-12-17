//
// Created by gregory on 27.11.18.
//


#include "RuleClasses.h"

CClassDecl::CClassDecl(const std::string _className, std::vector<IVarDecl*>& _varList, std::vector<IMethodDecl*>& _methodList, bool _isDerived, const std::string _baseClass,
        CLocation &_location) :

        className(  _className ),
        varList( _varList ),
        methodList( _methodList ),
        isDerived(_isDerived),
        baseClass(_baseClass)
{
    location = _location;
}



void CClassDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

