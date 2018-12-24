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

mkdir $IR

$JC $CODE $AST_DOT $IR

for file in $(find $DIR -name "*.dot")
do
	dot -Tpdf $file > $file.pdf
	rm $file
done


