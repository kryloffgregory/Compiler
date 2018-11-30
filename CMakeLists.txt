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
        "scr/AST/*")

add_executable(Compiler ${SRCFILES}
        ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS} src/AST/ASTPrinter.cpp src/AST/ASTPrinter.h)