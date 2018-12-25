#include <utility>


//
// Created by gregory on 27.11.18.
//


#include "RuleClasses.h"

CClassDecl::CClassDecl(const std::string &_className,
        std::vector<std::unique_ptr<IVarDecl>>& _varList,
        std::vector<std::unique_ptr<IMethodDecl>>& _methodList,
        const bool _isDerived,
        const std::string &_baseClass,
        CLocation &_location) :

        className{_className},
        varList{std::move( _varList) },
        methodList{std::move( _methodList) },
        isDerived(_isDerived),
        baseClass{_baseClass}
{
    location = _location;
}



void CClassDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

