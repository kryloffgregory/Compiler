#include <iostream>
#include <tr1/memory>
#include <SymbolTable/SymbolTableBuilder.h>
#include <IRT/Translator.h>
#include <Canon/Canon.h>
#include "RuleClasses/RuleClasses.h"
#include "AST/ASTPrinter.h"
#include "SymbolTable/TypeChecker.h"
#include "IRT/IRTreePrinter.h"

extern int yyparse(std::unique_ptr<IProgram> &);
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

    std::unique_ptr<IProgram> root;
    yyparse(root);
    auto printer = std::make_unique<ASTPrinter>(argv[2]);
    root->Accept(printer.get());


    auto stBuilder = std::make_unique<STBuilder>(STBuilder());
    root->Accept(stBuilder.get());
    auto table = stBuilder->GetSymbolsTable();
    for (auto error : stBuilder->GetErrorStorage().GetAllErrors()) {
        std::cout << error << std::endl;
    }
    if (stBuilder->GetErrorStorage().GetAllErrors().empty()) {
        auto typeChecker = std::make_unique<CTypeCheckerVisitor>(CTypeCheckerVisitor(table)) ;
        root->Accept(typeChecker.get());
        for (auto error : typeChecker->GetErrorStorage().GetAllErrors()) {
            std::cout << error << std::endl;
        }
    }

    auto irBuilder = std::make_unique<CTranslator>(CTranslator(table));
    root->Accept(irBuilder.get());
    auto frames = irBuilder->GetFrames();
    for( auto frame : irBuilder->GetFrames() ) {

        std::unique_ptr<IRTree::IRTreePrinter> irPrinter(
                new IRTree::IRTreePrinter(
                        std::string(argv[3]) +
                        std::string("/") +
                        frame.GetName()->GetString() +
                        std::string( ".dot" ) ));
        frame.GetRootStm()->Accept( irPrinter.get() );
        irPrinter->Flush();

        std::unique_ptr<IRTree::IRTreePrinter> irPrinter2(
                new IRTree::IRTreePrinter(
                        std::string(argv[3]) +
                        std::string("/") +
                        frame.GetName()->GetString() +
                        std::string( "Linearizer.dot" ) ));

        auto linearizedFrameStmList = CCanon::Linearize( frame.GetRootStm() );


        /*auto stm = linearizedFrameStmList->GetHead();
        stm->Accept( irPrinter2.get( ) );
        irPrinter2->Flush();*/
        auto tail = linearizedFrameStmList;
        for( auto stm = tail->GetHead( );
             tail != nullptr;
             tail = tail->GetTail( ),
                     stm = ( tail != nullptr ) ? tail->GetHead( ) : nullptr ) {
            stm->Accept( irPrinter2.get( ) );
        }
        irPrinter2->Flush();

    }



    return 0;
}
