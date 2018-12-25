//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CMethodDecl::CMethodDecl(
        std::unique_ptr<IType> _type,
        const std::string& _methodName,
        std::vector<std::unique_ptr<IArg>>& _argList,
        std::vector<std::unique_ptr<IVarDecl>>& _varList,
        std::deque<std::unique_ptr<IStatement>>& _statementList,
        std::unique_ptr<IExp> _returnExpr,
        CLocation &_location
) :
        type{std::move( _type )},
        methodName( _methodName),
        argList{std::move( _argList )},
        varList{std::move( _varList )},
        statementList{std::move( _statementList )},
        returnExpr{std::move( _returnExpr )}
{
    location = _location;
}



void CMethodDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}


