//
// Created by gregory on 27.11.18.
//


#include "RuleClasses.h"

CClassDecl::CClassDecl(const std::string _className, std::vector<IVarDecl*>& _varList, std::vector<IMethodDecl*>& _methodList ) :

        className(  _className ),
        varList( _varList ),
        methodList( _methodList )
{
}



void CClassDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

