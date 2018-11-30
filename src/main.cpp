#include <iostream>
//#include "../y.tab.h"
#include "RuleClasses/RuleClasses.h"
#include "AST/ASTPrinter.h"


extern int yyparse(IProgram* &);
extern FILE* yyin;

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can not open file!\n");
        exit(1);
    }

    yyin = input;

    IProgram* root;
    yyparse(root);
    ASTPrinter printer("out.dot");
    printer.Visit(static_cast<CProgram* >(root));


    return 0;
}