cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
project(Compiler)

find_package(FLEX)
find_package(BISON)

include(CTest)

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

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(Compiler ${SRCFILES} ${FLEX_FlexLexer_OUTPUTS} ${BISON_BisonParser_OUTPUTS} src/SymbolTable/TypeChecker.h src/SymbolTable/TypeChecker.cpp src/IRT/Expression.h src/IRT/Statement.h src/IRT/IIRVisitor.h src/IRT/Label.h src/IRT/Expression.cpp src/IRT/Statement.cpp src/IRT/Translator.h src/ActivationRecords/IFrame.h src/ActivationRecords/IAccess.h src/IRT/Translator.cpp src/IRT/Label.cpp src/IRT/Frame.h src/SymbolTable/Symbol.h src/SymbolTable/Symbol.cpp src/IRT/Frame.cpp src/IRT/IRTreePrinter.h src/IRT/IRTreePrinter.cpp)


add_custom_target(cppcheck
	COMMAND cppcheck --std=c++11 --enable=all --inconclusive --verbose --quiet --suppress=*:${CMAKE_CURRENT_BINARY_DIR}/lexer.h --suppress=*:${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp --suppress=*:${CMAKE_CURRENT_BINARY_DIR}/parser.cpp --suppress=*:"*yacc.c*" --suppress=*:"*grammar.tab.c" ${PROJECT_SOURCE_DIR}/src)

add_custom_target(memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log")

# TESTS

enable_testing()
 
file(GLOB files "tests/examples/test_*")
set(validator ${CMAKE_CURRENT_SOURCE_DIR}/tests/examples/build_graph.sh)
foreach(filename ${files})
	message("${validator} ${filename}")
	add_test(NAME "graph_${filename}"
        COMMAND ${validator} ${filename})
endforeach()

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/tests/bad/*.java")
set(validator ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.sh)
foreach(filename ${files})
        add_test(NAME "bad_${filename}"
        COMMAND ${validator} ${filename} 1)
endforeach()

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/tests/good/*.java")
set(validator ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.sh)
foreach(filename ${files})
        add_test(NAME "good_${filename}"
        COMMAND ${validator} ${filename} 0)
endforeach()

