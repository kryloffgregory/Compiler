%{
#include <stdio.h>
#include <string.h>


#include <vector>
#include "RuleClasses/RuleClasses.h"
#include "Location/Location.h"
#include <bits/unique_ptr.h>


int yylex(void);
void yyerror(std::unique_ptr<IProgram> & root, const char *);
int yydebug = 1;
extern CLocation location;

extern "C" int yywrap()
{
        return 1;
}
%}

%code requires {
    #include <bits/unique_ptr.h>
	#include "RuleClasses/RuleClasses.h"
	#include <vector>
	#include <iostream>
	#include <deque>
	//#include "Visitors/PrettyPrinterVisitor.h"
}

%parse-param {std::unique_ptr<IProgram> & root}


%union {
    std::string* val;
    int intVal;
    bool boolVal;
    std::unique_ptr<IProgram>* programVal;
    std::unique_ptr<IMainClass>* mainClassDeclarationVal;
    std::vector<std::unique_ptr<IClassDecl>>* classDeclarationListVal;
    std::unique_ptr<IClassDecl>* classDeclarationVal;
    std::vector<std::unique_ptr<IVarDecl>>* variableDeclarationListVal;
    std::unique_ptr<IVarDecl>* variableDeclarationVal;
    std::unique_ptr<IMethodDecl>* methodDeclarationVal;
    std::vector<std::unique_ptr<IMethodDecl>>* methodDeclarationListVal;
    std::unique_ptr<IArg>* argVal;
    std::vector<std::unique_ptr<IArg>>* formalListVal;
    std::unique_ptr<IStatement>* statementVal;
    std::unique_ptr<IType>* typeVal;
    std::unique_ptr<IExp>* expressionVal;
    std::vector<std::unique_ptr<IExp>>* expressionListVal;
    std::deque<std::unique_ptr<IStatement>>* statementListVal;
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


%destructor {
    delete $$;
}
    MainClass
    Program
    ClassDeclList
    ClassDecl
    VarDeclList
    VarDecl
    MethodDecl
    MethodDeclList
    Argument
    ArgList
    Statement
    Type
    StatementList
    Expression
    ExpressionList







%%
Program:
    MainClass ClassDeclList {
        root = std::unique_ptr<IProgram>{ new CProgram(std::move(*$1), *$2, location)};
        $$ = 0;

        delete $1;
        delete $2;
    }

;
ClassDeclList:
    %empty {
        $$ = new std::vector<std::unique_ptr<IClassDecl> >();
    } | ClassDeclList ClassDecl {
        $1->push_back(std::move(*$2));
        delete $2;
        $$ = $1;
    }
;
MainClass:
    T_CLASS Id '{' T_PUBLIC T_STATIC T_VOID T_MAIN '(' T_STRING '[' ']' Id ')' '{'
        StatementList '}' '}' {

        //std::cerr<<"mainClass\n";
        $$ = new std::unique_ptr<IMainClass> { new CMainClass( *$2, *$12, *$15, location)};
        delete $2;
        delete $12;
        delete $15;
    }
;
ClassDecl :
    T_CLASS Id  '{'
        VarDeclList
        MethodDeclList
    '}' {
        $$ = new std::unique_ptr<IClassDecl> { new CClassDecl(*$2, *$4, *$5, false, "", location)};
        delete $2;
        delete $4;
        delete $5;
    } | T_CLASS Id T_EXTENDS Id '{'
        VarDeclList
        MethodDeclList
        '}' {
            $$ = new std::unique_ptr<IClassDecl> {new CClassDecl(*$2, *$6, *$7, true, *$4, location)};
            delete $2;
            delete $6;
            delete $7;
            delete $4;
    }

;



VarDeclList :
    %empty {
        $$ = new std::vector<std::unique_ptr<IVarDecl >>();
    } | VarDeclList VarDecl {
        $1->push_back(std::move(*$2));
        $$ = $1;
        delete $2;
    }
;
StatementList:
    %empty {
        //std::cerr<<"Empty statement List\n";
        $$ = new std::deque<std::unique_ptr<IStatement >> ();
    } | Statement StatementList {
        $2->push_front(std::move(*$1));
        $$ = $2;
        delete $1;
    }
;

MethodDeclList:
    %empty {
        $$ = new std::vector<std::unique_ptr<IMethodDecl>>();
    } | MethodDeclList MethodDecl {
        $1->push_back(std::move(*$2));
        $$ = $1;
        delete $2;
    }
;

VarDecl :
    Type Id ';' {

        $$ = new std::unique_ptr<IVarDecl> {new CVarDecl(std::move(*$1), *$2, location)};
        delete $1;
        delete $2;
    }

 ;

MethodDecl :
    T_PUBLIC Type Id '(' ArgList ')' '{'
        VarDeclList
        StatementList
        T_RETURN Expression ';'
    '}' {
        $$ = new std::unique_ptr<IMethodDecl> {new CMethodDecl(std::move(*$2), *$3, *$5, *$8, *$9, std::move(*$11), location)};
        delete $2;
        delete $3;
        delete $5;
        delete $8;
        delete $9;
        delete $11;
    }
;

Type:
    T_INT '[' ']' {
        $$ = new std::unique_ptr<IType> {new CStandardType( CStandardType::StandardType::INT_ARRAY, location)};
    }
    | T_BOOL {
        $$ = new std::unique_ptr<IType> {new CStandardType( CStandardType::StandardType::BOOL, location)};
    }
    | T_INT {
        $$ = new std::unique_ptr<IType> {new CStandardType( CStandardType::StandardType::INT, location )};
    }
    | Id {
        $$ = new std::unique_ptr<IType> {new CUserType( *$1, location)};
    }


;

ArgList :
    %empty {
        $$ = new std::vector<std::unique_ptr<IArg>>();
    }
    | Argument {
        $$ = new std::vector<std::unique_ptr<IArg>>();
        $$->push_back( std::move( *$1));
        delete $1;
    }
    | ArgList ',' Argument {
        std::cerr<<"ArgList\n";
        $1->push_back(std::move(*$3));
        delete $3;
        $$ = $1;
     }
;

Argument :
    Type Id {
        $$ = new std::unique_ptr<IArg> {new  CArg(std::move(*$1), *$2, location)};
        delete $1;
        delete $2;
    }
    ;


Statement:
	'{' StatementList '}' {
		$$ = new std::unique_ptr<IStatement> {new CStatementListStatement( *$2, location)};
		delete $2;
	}
	| T_IF '(' Expression ')' Statement T_ELSE Statement {
		$$ = new std::unique_ptr<IStatement> {new CIfStatement( std::move(*$3), std::move(*$5), std::move(*$7), location)};
		delete $3;
		delete $5;
		delete $7;
	}
	| T_WHILE '(' Expression ')' Statement {
		$$ = new std::unique_ptr<IStatement> {new CWhileStatement( std::move(*$3), std::move(*$5), location)};
		delete $3;
		delete $5;

	}
	| T_PRINTLN '(' Expression ')' ';' {
		$$ = new std::unique_ptr<IStatement> {new CPrintStatement( std::move(*$3), location)};
		delete $3;
	}
	| Id '=' Expression ';' {
		$$ = new std::unique_ptr<IStatement> {new CAssignStatement( *$1, std::move(*$3), location)};
		delete $1;
		delete $3;
	}
	| Id '[' Expression ']' '=' Expression ';' {
		$$ = new std::unique_ptr<IStatement> {new CArrayAssignStatement( *$1, std::move(*$3), std::move(*$6), location)};
		delete $1;
		delete $3;
		delete $6;
}
;

Expression:
	Expression T_AND Expression {
		$$ = new std::unique_ptr<IExp> {new CBinOpExpression( std::move(*$1), CBinOpExpression::BinOp::AND, std::move(*$3), location)};
		delete $1;
		delete $3;
	}
	| Expression '<' Expression {
		$$ = new std::unique_ptr<IExp> {new CBinOpExpression( std::move(*$1), CBinOpExpression::BinOp::LESS, std::move(*$3), location)};
        delete $1;
        		delete $3;
	}
	| Expression '+' Expression {
		$$ = new std::unique_ptr<IExp> {new CBinOpExpression( std::move(*$1), CBinOpExpression::BinOp::PLUS, std::move(*$3), location)};
	    delete $1;
	    delete $3;
	}
	| Expression '-' Expression {
		$$ = new std::unique_ptr<IExp> {new CBinOpExpression( std::move(*$1), CBinOpExpression::BinOp::MINUS, std::move(*$3), location)};
	    delete $1;
        delete $3;
	}
	| '-' Expression  {
		$$ = new std::unique_ptr<IExp> { new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::MINUS, std::move(*$2), location)};
	    delete $2;
	}
	| Expression '*' Expression {
		$$ = new std::unique_ptr<IExp> { new CBinOpExpression(  std::move(*$1), CBinOpExpression::BinOp::TIMES, std::move(*$3), location)};
	    delete $1;
	    delete $3;
	}
	| Expression '/' Expression {
		$$ = new std::unique_ptr<IExp> {  new CBinOpExpression( std::move(*$1), CBinOpExpression::BinOp::DIVIDE, std::move(*$3), location)};
	    delete $1;
	    delete $3;
	}
	| Expression '[' Expression ']' {
		$$ = new std::unique_ptr<IExp> {new CIndexExpression( std::move(*$1), std::move(*$3), location)};
		delete $1;
		delete $3;
	}
	| Expression '.' T_LENGTH {
		$$ = new std::unique_ptr<IExp> {new CLenghtExpression(std::move(*$1), location)};
		delete $1;
	}
	| Expression '.' Id '(' ExpressionList ')' {
		$$ = new std::unique_ptr<IExp> { new CMethodExpression(std::move(*$1), *$3, *$5, location)};
		delete $1;
		delete $3;
		delete $5;
	}
	| Number {
	    $$ = new std::unique_ptr<IExp> { new CIntLiteralExpression($1, location)};
	}
	| T_TRUE {
	    $$ = new std::unique_ptr<IExp> {new CBoolLiteralExpression(true, location)};
	}
	| T_FALSE {
	    $$ = new std::unique_ptr<IExp> {new CBoolLiteralExpression(false, location)};
	}

	| Id {
		$$ = new std::unique_ptr<IExp> {new CIdentifierExpression( *$1, location)};
		delete $1;
	}
	| T_THIS {
		$$ = new std::unique_ptr<IExp> {new CThisExpression(location )};
	}
	| T_NEW T_INT '[' Expression ']' {
		$$ = new std::unique_ptr<IExp> {new CNewIntArrayExpression( std::move(*$4), location )};
		delete $4;
	}
	| T_NEW Id'(' ')' {
		$$ = new std::unique_ptr<IExp> {new CNewExpression( *$2, location)};
		delete $2;
	}
	| '!' Expression  {
		$$ = new std::unique_ptr<IExp> {new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::NOT, std::move(*$2), location)};
	    delete $2;
	}
	| '(' Expression ')' {
		$$ = new std::unique_ptr<IExp> {new CBracesExpression( std::move(*$2), location)};
		delete $2;
};

ExpressionList:
    %empty {
        $$ = new std::vector<std::unique_ptr<IExp>>();
    }
    | Expression {
        $$ = new std::vector<std::unique_ptr<IExp>>();
        $$->push_back(std::move(*$1));
        delete $1;
    }
    | ExpressionList ',' Expression {
            $1->push_back(std::move(*$3));
    		$$ = $1;
    		delete $3;
    };
Id:
    T_ID {
        //std::cerr<<"ID:" << *$1<<"\n";
        $$ = $1;
    };
Number:
    T_NUMBER {
        $$ = $1;
    };
%%

void yyerror(std::unique_ptr<IProgram >& root, const char *s)
{
	std::cerr <<"ERROR: " << s <<"\n";
	std::cerr << location.lineNumber<<":"<<location.firstColumn<<"\n";
}