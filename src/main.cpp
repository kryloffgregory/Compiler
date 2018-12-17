#include <iostream>
#include <SymbolTable/SymbolTableBuilder.h>
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
    printer.Visit(dynamic_cast<CProgram* >(root));

    STBuilder stBuilder;
    stBuilder.Visit(dynamic_cast<CProgram* >(root));
    auto table = stBuilder.GetSymbolsTable();
    for (auto error : stBuilder.GetErrorStorage().GetAllErrors()) {
        std::cout << error <<std::endl;
    }

    return 0;
}