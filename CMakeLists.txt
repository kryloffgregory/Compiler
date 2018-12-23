cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
project(Compiler)

find_package(FLEX)
find_package(BISON)


FLEX_TARGET(FlexLexer  src/lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
BISON_TARGET(BisonParser  src/grammar.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
ADD_FLEX_BISON_DEPENDENCY(FlexLexer BisonParser)
include_directories(
        ${PROJECT_SOURCE_DIR}/src)


FILE(GLOB SRCFILES "*.cpp" "*.h" "src/*.cpp" "src/*.h"
        "src/RuleClasses/*.cpp" "src/RuleClasses/*.h"
        "src/Location/*"
        "src/AST/*"
        "src/SymbolTable/*"
        "src/ErrorStorage/ErrorStorage.h"
        "src/ErrorStorage/ErrorStorage.cpp")

add_executable(Compiler ${SRCFILES} ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS} src/SymbolTable/TypeChecker.h src/SymbolTable/TypeChecker.cpp src/IRT/Expression.h src/IRT/Statement.h src/IRT/IIRVisitor.h src/IRT/Label.h src/IRT/Expression.cpp src/IRT/Statement.cpp src/IRT/Translator.h src/ActivationRecords/IFrame.h src/ActivationRecords/IAccess.h src/IRT/Translator.cpp src/IRT/Label.cpp src/IRT/Frame.h src/SymbolTable/Symbol.h src/SymbolTable/Symbol.cpp src/IRT/Frame.cpp src/IRT/IRTreePrinter.h src/IRT/IRTreePrinter.cpp)