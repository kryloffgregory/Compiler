%{
#include <stdio.h>
#include <string.h>


#include <vector>
#include "RuleClasses/RuleClasses.h"
#include "Location/Location.h"


int yylex(void);
void yyerror(IProgram* root, const char *);
int yydebug = 1;
extern CLocation location;

extern "C" int yywrap()
{
        return 1;
}
%}

%code requires {
	#include "RuleClasses/RuleClasses.h"
	#include <vector>
	#include <iostream>
	#include <deque>
	//#include "Visitors/PrettyPrinterVisitor.h"
}

%parse-param {IProgram*& root}


%union {
    std::string* val;
    int intVal;
    bool boolVal;
    IProgram* programVal;
    IMainClass* mainClassDeclarationVal;
    std::vector<IClassDecl*>* classDeclarationListVal;
    IClassDecl* classDeclarationVal;
    std::vector<IVarDecl*>* variableDeclarationListVal;
    IVarDecl* variableDeclarationVal;
    IMethodDecl* methodDeclarationVal;
    std::vector<IMethodDecl*>* methodDeclarationListVal;
    IArg* argVal;
    std::vector<IArg*>* formalListVal;
    IStatement* statementVal;
    IType* typeVal;
    IExp* expressionVal;
    std::vector<IExp*>* expressionListVal;
    std::deque<IStatement*>* statementListVal;
}


%start Program

%token T_CLASS
%token T_PUBLIC
%token T_EXTENDS
%token T_STATIC
%token T_MAIN
%token T_VOID
%token T_INT
%token T_BOOL
%token T_IF
%token T_ELSE
%token T_RETURN
%token T_LESS
%token T_PRINTLN
%token T_ASSIGN


%token T_STRING
%token T_AND
%token T_NEW
%token T_THIS
%token T_LENGTH
%token T_WHILE

%token T_TRUE
%token T_FALSE



%token<intVal> T_NUMBER
%token<val> T_ID

%right '='
%left T_AND
%left '<'
%left '+' '-'
%left '*' '/'
%left '!'
%left '.'
%right '(' '['

%type <programVal> Program
%type <mainClassDeclarationVal> MainClass
%type <classDeclarationListVal> ClassDeclList
%type <classDeclarationVal> ClassDecl
%type <variableDeclarationListVal> VarDeclList
%type <variableDeclarationVal> VarDecl
%type <methodDeclarationVal> MethodDecl
%type <methodDeclarationListVal> MethodDeclList
%type <argVal> Argument
%type <formalListVal> ArgList
%type <statementVal> Statement
%type <typeVal> Type
%type <statementListVal> StatementList
%type <expressionVal> Expression
%type <expressionListVal> ExpressionList
%type <intVal> Number
%type <val> Id

%locations
%%
Program:
    MainClass ClassDeclList {
        root = new CProgram($1, *$2, location);
    }

;
ClassDeclList:
    %empty {
        $$ = new std::vector<IClassDecl *>();
    } | ClassDeclList ClassDecl {
        $1->push_back($2);
        $$ = $1;
    }
;
MainClass:
    T_CLASS Id '{' T_PUBLIC T_STATIC T_VOID T_MAIN '(' T_STRING '[' ']' Id ')' '{'
        StatementList '}' '}' {

        std::cerr<<"mainClass\n";
        $$ = new CMainClass( *$2, *$12, *$15, location);
    }
;
ClassDecl :
    T_CLASS Id  '{'
        VarDeclList
        MethodDeclList
    '}' {
        $$ = new CClassDecl(*$2, *$4, *$5, false, "", location);
    } | T_CLASS Id T_EXTENDS Id '{'
        VarDeclList
        MethodDeclList
        '}' {
            $$ = new CClassDecl(*$2, *$6, *$7, true, *$4, location);
    }

;



VarDeclList :
    %empty {
        $$ = new std::vector<IVarDecl *>();
    } | VarDeclList VarDecl {
        $1->push_back($2);
        $$ = $1;
    }
;
StatementList:
    %empty {
        std::cerr<<"Empty statement List\n";
        $$ = new std::deque<IStatement *> ();
    } | Statement StatementList {
        $2->push_front($1);
        $$ = $2;
    }
;

MethodDeclList:
    %empty {
        $$ = new std::vector<IMethodDecl*>();
    } | MethodDeclList MethodDecl {
        $1->push_back($2);
        $$ = $1;
    }
;

VarDecl :
    Type Id ';' {

        std::cerr<<"VarDecl\n"<<"\n";
        $$ = new CVarDecl($1, *$2, location);
    }

 ;

MethodDecl :
    T_PUBLIC Type Id '(' ArgList ')' '{'
        VarDeclList
        StatementList
        T_RETURN Expression ';'
    '}' {
        $$ = new CMethodDecl($2, *$3, *$5, *$8, *$9, $11, location);
    }
;

Type:
    T_INT '[' ']' {
        $$ = new CStandardType( CStandardType::StandardType::INT_ARRAY, location);
    }
    | T_BOOL {
        $$ = new CStandardType( CStandardType::StandardType::BOOL, location);
    }
    | T_INT {
        $$ = new CStandardType( CStandardType::StandardType::INT, location );
    }
    | Id {
        $$ = new CUserType( *$1, location);
    }


;

ArgList :
    %empty {
        $$ = new std::vector<IArg*>();
    }
    | Argument {
        $$ = new std::vector<IArg*>(1, $1);
    }
    | ArgList ',' Argument {
        std::cerr<<"ArgList\n";
        $1->push_back($3);
        $$ = $1;
     }
;

Argument :
    Type Id { $$ = new CArg($1, *$2, location);}
    ;


Statement:
	'{' StatementList '}' {
		$$ = new CStatementListStatement( *$2, location);
	}
	| T_IF '(' Expression ')' Statement T_ELSE Statement {
		$$ = new CIfStatement( $3, $5, $7, location);
	}
	| T_WHILE '(' Expression ')' Statement {
		$$ = new CWhileStatement( $3, $5, location);
	}
	| T_PRINTLN '(' Expression ')' ';' {
		$$ = new CPrintStatement( $3, location);
	}
	| Id '=' Expression ';' {
	    std::cerr<<"ex=ex"<<"\n";
		$$ = new CAssignStatement( *$1, $3, location);
	}
	| Id '[' Expression ']' '=' Expression ';' {
		$$ = new CArrayAssignStatement( *$1, $3, $6, location);
}
;

Expression:
	Expression T_AND Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::AND, $3, location);
	}
	| Expression '<' Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::LESS, $3, location);
	}
	| Expression '+' Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::PLUS, $3, location);
	}
	| Expression '-' Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::MINUS, $3, location);
	}
	| '-' Expression  {
		$$ = new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::MINUS, $2, location);
	}
	| Expression '*' Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::TIMES, $3, location);
	}
	| Expression '/' Expression {
		$$ = new CBinOpExpression( $1, CBinOpExpression::BinOp::DIVIDE, $3, location);
	}
	| Expression '[' Expression ']' {
		$$ = new CIndexExpression( $1, $3, location);
	}
	| Expression '.' T_LENGTH {
		$$ = new CLenghtExpression( $1, location);
	}
	| Expression '.' Id '(' ExpressionList ')' {
		$$ = new CMethodExpression( $1, *$3, *$5, location);
	}
	| Number {
	    $$ = new CIntLiteralExpression($1, location);
	}
	| T_TRUE {
	    $$ = new CBoolLiteralExpression(true, location);
	}
	| T_FALSE {
	    $$ = new CBoolLiteralExpression(false, location);
	}

	| Id {
	    std::cerr<<"expr-id"<<"\n";
		$$ = new CIdentifierExpression( *$1, location);
	}
	| T_THIS {
		$$ = new CThisExpression(location );
	}
	| T_NEW T_INT '[' Expression ']' {
		$$ = new CNewIntArrayExpression( $4, location );
	}
	| T_NEW Id'(' ')' {
		$$ = new CNewExpression( *$2, location);
	}
	| '!' Expression  {
		$$ = new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::NOT, $2, location);
	}
	| '(' Expression ')' {
		$$ = new CBracesExpression( $2, location);
};

ExpressionList:
    %empty {
        $$ = new std::vector<IExp*>();
    }
    | Expression {
        $$ = new std::vector<IExp*>(1, $1);
    }
    | ExpressionList ',' Expression {
            $1->push_back($3);
    		$$ = $1;
    };
Id:
    T_ID {
        std::cerr<<"ID:" << *$1<<"\n";
        $$ = $1;
    };
Number:
    T_NUMBER {
        $$ = $1;
    };
%%

void yyerror(IProgram * root, const char *s)
{
	std::cerr <<"ERROR: " << s <<"\n";
	std::cerr << location.lineNumber<<":"<<location.firstColumn<<"\n";
}