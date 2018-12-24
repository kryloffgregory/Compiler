#!/bin/sh

if [ $# -ne 1 ]
then
	echo "Please provde test dir"
	exit
fi;

JC=bin/Compiler
DIR=$1
CODE=$DIR/code.java
AST_DOT=$DIR/ast.dot
IR=$DIR/IR
rm -rf $AST_DOT
rm -rf $IR
mkdir $IR
echo WAS $AST_DOT
AST_DOT=$(echo $AST_DOT | python3 -c 'print(input().split("Compiler/")[1], end="")')
echo IS $AST_DOT
echo $JC $CODE $AST_DOT $IR
$JC $CODE $AST_DOT $IR

for file in $(find $DIR -name "*.dot")
do
	echo $file
	dot -Tpdf $file > $file.pdf
	rm $file
done


