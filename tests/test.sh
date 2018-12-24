#!/bin/sh

if [ $# -ne 2 ]
then
	echo "Please provde dir and result"
	exit
fi;

TMP_DIR=`mktemp -d`

JC=bin/Compiler
CODE=$1
AST_DOT=$TMP_DIR/ast.dot
IR=$TMP_DIR/IR

$JC $CODE $AST_DOT $IR > /dev/null 2>&1
RET=$?

rm -rf $TMP_DIR
NZ=0
if [ $RET -ne 0 ]
then
	NZ=1
fi;
if [ $NZ -ne $2 ]
then
	exit 1
fi;

