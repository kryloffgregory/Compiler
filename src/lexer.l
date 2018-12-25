%{
#include <stdio.h>
#include "parser.hpp"

#include <iostream>
#include <string>
#include "Location/Location.h"

int yycolumnno = 0;
CLocation location;

#define YY_USER_ACTION { \
    if (yylineno != location.lineNumber) { \
        yycolumnno = 0; \
    } \
    \
    location.lineNumber = yylineno; \
    location.firstColumn = yycolumnno; \
    location.lastColumn = yycolumnno + yyleng - 1; \
    \
    yycolumnno += yyleng; \
}

void yyerror(char *s);
%}

%option noyywrap
%option yylineno

%%
\n {

}
\/\/.* {
}
class   {
    return T_CLASS;
}

public   {

    return T_PUBLIC;
}
static {
    return T_STATIC;
}
void {
    return T_VOID;
}
main {
    return T_MAIN;
}
int {
    return T_INT;
}
boolean {
    return T_BOOL;
}
String {
    return T_STRING;
}
extends {
    return T_EXTENDS;
}
if {
    return T_IF;
}
else {
    return T_ELSE;
}
return {
    return T_RETURN;
}
&& {
    return T_AND;}
length {
    return T_LENGTH;
}
while {
    return T_WHILE;
}
System\.out\.println {
    return T_PRINTLN;
}
new {
    return T_NEW;
}
false {
    return T_FALSE;
}
true {
    return T_TRUE;
}
this {
    return T_THIS;
}

[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.val= new std::string(yytext);
    return T_ID;
}

[ \t\n\v\r\f]+ {

}

0|[1-9][0-9]* {
    yylval.intVal = std::atoi(yytext);
    return T_NUMBER;
}



. {

    return (int) yytext[0];
}
%%
