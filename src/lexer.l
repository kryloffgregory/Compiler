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
    std::cerr<<"class";
    return T_CLASS;
}

public   {
    std::cerr<<"public";

    return T_PUBLIC;
}
static {
    return T_STATIC;
}
void {
    return T_VOID;
}
main {
    std::cerr<<"main\n";
    return T_MAIN;
}
int {
    std::cerr<<"int";
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


[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.val= new std::string(yytext);
    std::cerr<<"id: "<<yytext<<"\n";
    return T_ID;
}

[ \t\n\v\r\f]+ {
    std::cerr<<"space\n";

}

0|[1-9][0-9]* {
    yylval.intVal = std::atoi(yytext);
    std::cerr<<"num: "<<yytext<<"\n";
    return T_NUMBER;
}



. {

    std::cerr << "unknown symbol: " <<  yytext <<"\n";
    //printf("Unknown symbol:\n");
    return (int) yytext[0];
}
%%
