//
// Created by gregory on 27.11.18.
//

#include "RuleClasses.h"

CMethodDecl::CMethodDecl(
        IType* _type,
        const std::string& _methodName,
        std::vector<IArg*>& _argList,
        std::vector<IVarDecl*>& _varList,
        std::deque<IStatement*>& _statementList,
        IExp* _returnExpr
) :
        type( _type ),
        methodName( _methodName),
        argList( _argList ),
        varList( _varList ),
        statementList( _statementList ),
        returnExpr( _returnExpr )
{
}



void CMethodDecl::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}

