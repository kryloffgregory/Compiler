//
// Created by gregory on 27.11.18.
//

#include <RuleClasses/RuleClasses.h>
#include "ASTPrinter.h"

ASTPrinter::ASTPrinter(const std::string &filename) :
    file{filename},
    nodeNumber(0) {
    file << "strict graph {"<<"\n";
}

ASTPrinter::~ASTPrinter() {
    file << "}\n";
    file.close();
}
void ASTPrinter::Visit(const CProgram *program) {
    int head = nodeNumber;
    PrintHead(head, "Program");
    nodeNumber++;
    PrintEdge(head);
    program->mainClass->Accept(this);
    for(auto classDecl : program->classList) {
        PrintEdge(head);
        classDecl->Accept(this);
    }
}

void ASTPrinter::Visit(const CClassDecl* classDecl) {
    int head = nodeNumber;
    PrintHead(head, "ClassDeclaration: " + classDecl->className);
    if(classDecl->isDerived) {
        PrintEdge(head);
        PrintLeaf(head, "extends: ", classDecl->baseClass);
    }
    for(auto varDecl : classDecl -> varList) {
        PrintEdge(head);
        varDecl->Accept(this);
    }
    for(auto methodDecl : classDecl->methodList) {
        PrintEdge(head);
        methodDecl->Accept(this);
    }
}

void  ASTPrinter::Visit(const CVarDecl *varDecl) {
    int head = nodeNumber;
    PrintHead(head, "Variable");
    PrintEdge(head);
    varDecl->type->Accept(this);
    PrintLeaf(head, "ID", varDecl->identifier);
}

void ASTPrinter::Visit(const CMethodDecl *methodDecl) {
    int head = nodeNumber;
    PrintHead(head, "Method: " + methodDecl->methodName);
    PrintEdge(head);
    methodDecl->type->Accept(this);
    for(auto arg : methodDecl-> argList) {
        PrintEdge(head);
        arg->Accept(this);
    }
    for(auto var : methodDecl->varList) {
        PrintEdge(head);
        var->Accept(this);
    }
    for(auto statement : methodDecl->statementList) {
        PrintEdge(head);
        statement->Accept(this);
    }
    PrintEdge(head);
    methodDecl->returnExpr->Accept(this);

}
void ASTPrinter::Visit(const CMainClass *mainClass) {
    int head = nodeNumber;
    PrintHead(head, "MainClass:" + mainClass->identifier);
    PrintEdge(head);
    PrintLeaf(head, "String[]", mainClass->argsIdentifier);
    for(auto statement : mainClass -> statements) {
        PrintEdge(head);
        statement->Accept(this);
    }
}





void ASTPrinter::Visit(const CPrintStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "System.out.Println");
    PrintEdge(head);
    statement->expression->Accept(this);
}




void ASTPrinter::Visit(const CWhileStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "while");
    PrintEdge(head);
    statement->condition->Accept(this);
    PrintEdge(head);
    statement->cycleBody->Accept(this);
}

void ASTPrinter::Visit(const CStandardType *type) {

        switch(type->type) {
            case CStandardType::StandardType::BOOL:
                PrintHead(nodeNumber, "Bool");
                break;
            case CStandardType::StandardType::INT:
                PrintHead(nodeNumber, "Int");
                break;
            case CStandardType::StandardType::INT_ARRAY:
                PrintHead(nodeNumber, "Int[]");
                break;
            }

    }

void ASTPrinter::Visit(const CStatementListStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "{   }");
    for(auto innStatement : statement->statementList) {

        PrintEdge(head);
        innStatement->Accept(this);
    }

}

void ASTPrinter::Visit(const CIfStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "if-then-else");
    PrintEdge(head);
    statement->condition->Accept(this);
    PrintEdge(head);
    statement->statementIfTrue->Accept(this);
    if(statement->statementIfFalse != nullptr) {
        PrintEdge(head);
        statement->statementIfFalse->Accept(this);
    }

}

void ASTPrinter::Visit(const CAssignStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "=");
    PrintEdge(head);
    PrintLeaf(head, "lvalue", statement->left);
    PrintEdge(head);
    statement->right->Accept(this);

}

void ASTPrinter::Visit(const CArrayAssignStatement *statement) {
    int head = nodeNumber;
    PrintHead(head, "=");
    PrintEdge(head);
    PrintLeaf(head, "lvalue-array", statement->arrayId);
    PrintEdge(head);
    statement->elementNumber->Accept(this);
    PrintEdge(head);
    statement->rightPart->Accept(this);
}

void ASTPrinter::Visit(const CIndexExpression *expr) {
    int head = nodeNumber;
    PrintHead(head,"[]");
    PrintEdge(head);
    expr->exp->Accept(this);
    PrintEdge(head);
    expr->indexExp->Accept(this);

}

void ASTPrinter::Visit(const CLenghtExpression *expr) {
    int head = nodeNumber;
    PrintHead(head, ".length");
    PrintEdge(head);
    expr->exp->Accept(this);

}

void ASTPrinter::Visit(const CNewExpression *expr) {
    int head = nodeNumber;
    PrintHead(head, "new");
    PrintLeaf(head, "class", expr->identifier);
}

void ASTPrinter::Visit(const CMethodExpression *expr) {
    int head = nodeNumber;
    PrintHead(head, "call method");
    PrintEdge(head);
    expr->exp->Accept(this);
    PrintLeaf(head, "method", expr->identifier);
    for(auto arg : expr->expList) {
        PrintEdge(head);
        arg->Accept(this);
    }

}

void ASTPrinter::Visit(const CBinOpExpression *expr) {
    int head = nodeNumber;
    switch (expr->binOp) {
        case CBinOpExpression::AND:
            PrintHead(head, "AND");
            break;
        case CBinOpExpression::DIVIDE:
            PrintHead(head, "/");
            break;
        case CBinOpExpression::TIMES:
            PrintHead(head, "*");
            break;
        case CBinOpExpression::LESS:
            PrintHead(head, "<");
            break;
        case CBinOpExpression::MINUS:
            PrintHead(head, "-");
            break;
        case CBinOpExpression::PLUS:
            PrintHead(head, "+");
            break;
    }
    PrintEdge(head);
    expr->leftExp->Accept(this);
    PrintEdge(head);
    expr->rightExp->Accept(this);

}

void ASTPrinter::Visit(const CIdentifierExpression *expr) {
    int head = nodeNumber;
    PrintLeaf(head, "ID", expr->identifier);
}

void ASTPrinter::Visit(const CIntLiteralExpression *expr) {
    PrintLeaf(nodeNumber, "const", std::to_string(expr->val));

}

void ASTPrinter::Visit(const CBoolLiteralExpression *expr) {
    PrintLeaf(nodeNumber, "const", std::to_string(expr->val));

}

void ASTPrinter::Visit(const CThisExpression *expr) {
    PrintLeaf(nodeNumber, "this", "");

}

void ASTPrinter::Visit(const CNewIntArrayExpression *expr) {
    int head = nodeNumber;
    PrintHead(head, "new int");
    PrintEdge(head);
    expr->exp->Accept(this);
}

void ASTPrinter::Visit(const CUnaryOpExpression *expr) {
    int head = nodeNumber;
    switch (expr->op) {
        case CUnaryOpExpression::NOT:
            PrintHead(head, "not");
        case CUnaryOpExpression::MINUS:
            PrintHead(head, "-");
    }
    PrintEdge(head);
    expr->exp->Accept(this);

}

void ASTPrinter::Visit(const CBracesExpression *expr) {
    int head = nodeNumber;
    PrintHead(head, "()");
    PrintEdge(head);
    expr->exp->Accept(this);

}

void ASTPrinter::Visit(const CArg *arg) {
    int head = nodeNumber;
    PrintHead(head, "argument");
    PrintEdge(head);
    arg->type->Accept(this);
    PrintLeaf(head, "ID", arg->id);

}




void ASTPrinter::PrintHead(int node, const std::string& label) {
    file << node << " [label=\"" << label << "\"];" << std::endl;
}

void ASTPrinter::PrintEdge(int prevNode) {
    file << prevNode << " -- " << ++nodeNumber << std::endl;
}

void ASTPrinter::PrintLeaf(int prevNode, const std::string& label, const std::string& name) {
    //file << prevNode << " -- " << ++nodeNumber << std::endl;
    file << nodeNumber << " [label=\"" << label << " : " << name << "\"];" << std::endl;

}

void ASTPrinter::Visit(const CUserType *type) {
    PrintLeaf(nodeNumber, "type", type->type);
}
