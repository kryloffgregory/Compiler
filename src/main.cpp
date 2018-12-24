#include <iostream>
#include <SymbolTable/SymbolTableBuilder.h>
#include <IRT/Translator.h>
#include "RuleClasses/RuleClasses.h"
#include "AST/ASTPrinter.h"
#include "SymbolTable/TypeChecker.h"
#include "IRT/IRTreePrinter.h"

extern int yyparse(IProgram* &);
extern FILE* yyin;

int main(int argc, char *argv[]) {
    if (argc != 4) {
    	printf("Usage: %s input.java ast.dot ir_dir\n", argv[0]);
        exit(1);
    }
	
    FILE *input = fopen(argv[1], "r");
    if (input == nullptr) {
        printf("Can not open file!\n");
        exit(1);
    }

    yyin = input;

    IProgram *root;
    yyparse(root);
    ASTPrinter printer(argv[2]);
    printer.Visit(dynamic_cast<CProgram * >(root));

    STBuilder stBuilder;
    stBuilder.Visit(dynamic_cast<CProgram * >(root));
    auto table = stBuilder.GetSymbolsTable();
    for (auto error : stBuilder.GetErrorStorage().GetAllErrors()) {
        std::cout << error << std::endl;
    }
    if (stBuilder.GetErrorStorage().GetAllErrors().empty()) {
        CTypeCheckerVisitor typeChecker(table);
        typeChecker.Visit(dynamic_cast<CProgram * >(root));
        for (auto error : typeChecker.GetErrorStorage().GetAllErrors()) {
            std::cout << error << std::endl;
        }
    }

    CTranslator irBuilder(table);
    irBuilder.Visit(dynamic_cast<CProgram * >(root));
    auto frames = irBuilder.GetFrames();
    for( const auto& frame : irBuilder.GetFrames() ) {

        std::shared_ptr<IRTree::IRTreePrinter> printer(
                new IRTree::IRTreePrinter(std::string(argv[3]) + std::string("/") + frame.GetName()->GetString() + std::string( ".dot" ) ) );
        frame.GetRootStm()->Accept( printer.get() );
        printer->Flush();
    }
    return 0;
}
