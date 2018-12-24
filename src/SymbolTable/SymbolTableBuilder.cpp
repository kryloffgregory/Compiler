//
// Created by gregory on 13.12.18.
//

#include "SymbolTableBuilder.h"
#include <iostream>
#include <RuleClasses/RuleClasses.h>

STBuilder::STBuilder() : symbolsTable(new CTable()) {
}

void STBuilder::Visit(const CProgram *program) {
    std::cout << std::endl << "TableBuilder:" << std::endl;
    program->mainClass->Accept(this);
    for(auto classDecl : program->classList)
        classDecl->Accept(this);
}

void STBuilder::Visit(const CMainClass *mainClass) {
    if( !(symbolsTable->AddClass( mainClass->identifier ) )) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CMainClass. " ) +
                               mainClass->identifier + " redefined. " + mainClass->location.ToString());
    }
    curClass = symbolsTable->GetClass( mainClass->identifier );

    if( !curClass->AddMethod( "main", "" ) ) {
        errorStorage.PutError(std::string("[Table builder] Node type - CMainClass. ") +
                              "Method main in class " + curClass->GetName() + " redefined. "
                              + mainClass->location.ToString());
    }
    curMethod = curClass->GetMethod( "main" );
    for(auto statement : mainClass->statements) {
        statement->Accept(this);
    }

    curMethod = nullptr;
    curClass = nullptr;
}

void STBuilder::Visit(const CClassDecl *classDecl) {
    if( !symbolsTable->AddClass( classDecl->className) ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CClassDecl. " ) +
                                       classDecl->className+ " redefined." +
                               classDecl->location.ToString());
    }

    curClass = symbolsTable->GetClass( classDecl->className );

    if(classDecl->isDerived) {
        curClass->SetBaseClass( symbolsTable->GetClass( classDecl->baseClass) );
    }
    for(auto varDecl : classDecl->varList) {
        varDecl->Accept(this);
    }

    for(auto methodDecl : classDecl->methodList) {
        methodDecl->Accept(this);
    }

    curClass = nullptr;
}

void STBuilder::Visit(const CVarDecl *varDecl) {
    varDecl->type->Accept( this );
    std::string type = lastTypeValue;
    std::string id = varDecl->identifier;

    if( curClass == nullptr ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CVarDecl. " ) +
                               "Var " + id + " is defined out of scope" + ". " +
                               varDecl->location.ToString());
    } else if( curMethod == nullptr ) {
        if( !curClass->AddVar( id, type ) ) {
            errorStorage.PutError( std::string( "[Table builder] Node type - CVarDecl. " ) +
                                   "Var " + id + " is already defined in " + curClass->GetName() + ". " +
                                   varDecl->location.ToString());
        }
    } else if( !curMethod->AddLocalVar( id, type ) ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CVarDecl. " ) +
                               "Var " + id + " is already defined in " + curClass->GetName() + "::" + curMethod->GetName() + ". " +
                               varDecl->location.ToString());
    }
}

void STBuilder::Visit(const CMethodDecl *methodDecl) {
    methodDecl->type->Accept(this);
    std::string returnType = lastTypeValue;

    if( curClass == nullptr ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CMethodDecl. " ) +
                               "Method " + methodDecl->methodName + " is defined out of scope" + ". " +
                               methodDecl->location.ToString());
        return;
    }
    if( curClass->GetBaseClass() != nullptr ) {
        for( auto method : curClass->GetBaseClass()->GetMethods() ) {
            if( method->GetName() == methodDecl->methodName ) {
                errorStorage.PutError( std::string( "[Table builder] Node type - CMethodDecl. " ) +
                                       "Method " + methodDecl->methodName + " already defined in base class " + methodDecl->methodName + ". " +
                                               methodDecl->location.ToString());
                return;
            }
        }
    }
    if( !curClass->AddMethod( methodDecl->methodName, returnType ) ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CMethodDecl. " ) +
                               "Method " + methodDecl->methodName + " is already defined in class " + curClass->GetName() + ". " +
                                       methodDecl->location.ToString());
    } else {

        curMethod = curClass->GetMethod( methodDecl->methodName);
        for(auto arg : methodDecl->argList) {
            arg->Accept(this);
        }
        for(auto var: methodDecl->varList) {
            var->Accept(this);
        }
        curMethod = nullptr;
    }
}

void STBuilder::Visit(const CStandardType *type) {
    switch( type->type ) {
        case CStandardType::StandardType::INT:
            lastTypeValue = "int";
            break;
        case CStandardType::StandardType::BOOL:
            lastTypeValue = "boolean";
            break;
        case CStandardType::StandardType::INT_ARRAY:
            lastTypeValue = "int[]";
        default:
            break;
    }
}

void STBuilder::Visit(const CArg *arg) {
    arg->type->Accept( this );
    std::string type = lastTypeValue;
    std::string id = arg->id;

    if( curMethod == nullptr ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CFormalParam. " ) +
                               "Var " + id + " is defined out of scope" + ". " +
                               arg->location.ToString());
    } else if( !curMethod->AddParamVar( id, type ) ) {
        errorStorage.PutError( std::string( "[Table builder] Node type - CFormalParam. " ) +
                               "Var " + id + " is already defined in " + curMethod->GetName() + ". " +
                               arg->location.ToString());
    }
}

void STBuilder::Visit(const CUserType *type) {
    lastTypeValue = type->type;
}


