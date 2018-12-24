/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/grammar.y" /* yacc.c:339  */

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

#line 87 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_HOME_TNA0Y_DESKTOP_COMPILER_PARSER_HPP_INCLUDED
# define YY_YY_HOME_TNA0Y_DESKTOP_COMPILER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 22 "src/grammar.y" /* yacc.c:355  */

	#include "RuleClasses/RuleClasses.h"
	#include <vector>
	#include <iostream>
	#include <deque>
	//#include "Visitors/PrettyPrinterVisitor.h"

#line 125 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_CLASS = 258,
    T_PUBLIC = 259,
    T_EXTENDS = 260,
    T_STATIC = 261,
    T_MAIN = 262,
    T_VOID = 263,
    T_INT = 264,
    T_BOOL = 265,
    T_IF = 266,
    T_ELSE = 267,
    T_RETURN = 268,
    T_LESS = 269,
    T_PRINTLN = 270,
    T_ASSIGN = 271,
    T_STRING = 272,
    T_AND = 273,
    T_NEW = 274,
    T_THIS = 275,
    T_LENGTH = 276,
    T_WHILE = 277,
    T_TRUE = 278,
    T_FALSE = 279,
    T_NUMBER = 280,
    T_ID = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "src/grammar.y" /* yacc.c:355  */

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

#line 185 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (IProgram*& root);

#endif /* !YY_YY_HOME_TNA0Y_DESKTOP_COMPILER_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 216 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   299

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,     2,     2,     2,
      35,    39,    31,    29,    42,    30,    34,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      28,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   124,   126,   132,   140,   145,   157,   159,
     165,   168,   175,   177,   184,   193,   203,   206,   209,   212,
     220,   223,   226,   234,   239,   242,   245,   248,   251,   255,
     261,   264,   267,   270,   273,   276,   279,   282,   285,   288,
     291,   294,   297,   301,   305,   308,   311,   314,   317,   322,
     325,   328,   333,   338
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_CLASS", "T_PUBLIC", "T_EXTENDS",
  "T_STATIC", "T_MAIN", "T_VOID", "T_INT", "T_BOOL", "T_IF", "T_ELSE",
  "T_RETURN", "T_LESS", "T_PRINTLN", "T_ASSIGN", "T_STRING", "T_AND",
  "T_NEW", "T_THIS", "T_LENGTH", "T_WHILE", "T_TRUE", "T_FALSE",
  "T_NUMBER", "T_ID", "'='", "'<'", "'+'", "'-'", "'*'", "'/'", "'!'",
  "'.'", "'('", "'['", "'{'", "']'", "')'", "'}'", "';'", "','", "$accept",
  "Program", "ClassDeclList", "MainClass", "ClassDecl", "VarDeclList",
  "StatementList", "MethodDeclList", "VarDecl", "MethodDecl", "Type",
  "ArgList", "Argument", "Statement", "Expression", "ExpressionList", "Id",
  "Number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    61,    60,    43,
      45,    42,    47,    33,    46,    40,    91,   123,    93,    41,
     125,    59,    44
};
# endif

#define YYPACT_NINF -93

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-93)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,   -20,    22,   -93,   -93,     8,   -93,    52,    59,   -20,
     -93,    50,    -2,    84,   -20,   -93,    66,    57,    44,    69,
     -93,    53,   -93,     0,   -93,   -20,   -93,    89,    44,    76,
      44,   -93,   -93,    75,    71,     3,   -93,   -20,   -93,    80,
     -93,    85,   -20,    44,    86,   -20,   -21,   -93,    82,   -93,
      87,    44,    -6,   -93,   -93,    88,    91,    92,    -6,    98,
      -6,   -17,    65,   256,   256,   256,   100,   101,   -93,   256,
     256,   115,   -17,     2,   -93,   -93,   -93,   -93,   256,   256,
     256,   133,   -93,   -93,   148,   163,   -93,   -93,    81,   193,
     256,    93,   107,    64,    26,   178,   256,   256,   256,   256,
     256,   256,     4,   256,    -6,   102,    -6,   -93,   126,   103,
     256,   106,   -93,    54,   263,    64,    64,    26,    26,   -93,
     120,   208,   144,   -93,   -93,   256,   117,   223,   -93,   256,
     -93,    -6,   118,   -93,   -93,   238,    10,   -93,   -93,   -93,
     256,   238
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,    52,     0,     1,     2,     0,     0,
       4,     0,     0,     0,     0,     8,     0,     0,    12,     0,
       8,    18,    17,     0,     9,     0,    19,     0,    12,     0,
       0,     6,    13,     0,     0,     0,    16,     0,    14,     0,
       7,     0,     0,    20,     0,     0,     0,    21,     0,    23,
       0,     0,    10,     8,    22,     0,     0,     0,    10,     0,
      10,     0,    10,     0,     0,     0,     0,     0,    11,     0,
       0,     0,    19,     0,    44,    41,    42,    53,     0,     0,
       0,     0,    43,    40,     0,     0,    24,     5,     0,     0,
       0,     0,     0,    34,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,     0,    48,    30,    31,    32,    33,    35,    36,    38,
       0,     0,     0,    27,    26,     0,     0,     0,    46,    49,
      37,     0,     0,    15,    45,    50,     0,    25,    29,    39,
       0,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,   -19,    19,   130,   -93,   -93,
     -28,   -93,   109,   -92,   -32,   -93,    -1,   -93
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,     3,    10,    18,    59,    23,    24,    32,
      25,    46,    47,    60,    81,   136,    82,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       5,    28,    37,    14,    30,    55,     4,    30,    12,    56,
      69,    91,   122,    17,   124,    45,    57,    26,    50,    70,
       4,    51,     6,    45,    33,   119,     1,    26,     4,    26,
       4,    58,    84,    85,    62,    15,    41,    88,    89,   137,
      31,    44,    26,    40,    49,     8,    93,    94,    95,   139,
      26,    61,   140,    21,    22,     9,    13,    61,   109,    61,
     102,    72,   103,    11,   113,   114,   115,   116,   117,   118,
       4,   121,    92,    19,    21,    22,    55,    66,   127,    68,
      56,    71,    97,    98,    99,   100,   101,    57,   102,    29,
     103,     4,    16,   132,    20,   100,   101,   135,   102,    96,
     103,   120,    58,    61,    27,    61,    34,    39,   141,    97,
      98,    99,   100,   101,    36,   102,    38,   103,    42,    52,
      43,    96,   107,    63,    53,    48,    64,    65,    90,   110,
      61,    97,    98,    99,   100,   101,    96,   102,    67,   103,
      86,    87,   111,   123,   126,   128,    97,    98,    99,   100,
     101,    96,   102,   125,   103,   129,   131,   133,    35,   138,
      54,    97,    98,    99,   100,   101,    96,   102,     0,   103,
       0,     0,   104,     0,     0,     0,    97,    98,    99,   100,
     101,    96,   102,     0,   103,     0,     0,   105,     0,     0,
       0,    97,    98,    99,   100,   101,    96,   102,     0,   103,
       0,     0,   106,     0,     0,     0,    97,    98,    99,   100,
     101,    96,   102,     0,   103,     0,     0,   112,     0,     0,
       0,    97,    98,    99,   100,   101,    96,   102,     0,   103,
       0,   108,     0,     0,     0,     0,    97,    98,    99,   100,
     101,    96,   102,     0,   103,     0,   130,     0,     0,     0,
       0,    97,    98,    99,   100,   101,    96,   102,     0,   103,
       0,   134,     0,     0,     0,     0,    97,    98,    99,   100,
     101,     0,   102,     0,   103,    73,    74,     0,     0,    75,
      76,    77,     4,     0,     0,     0,    78,     0,     0,    79,
       0,    80,    98,    99,   100,   101,     0,   102,     0,   103
};

static const yytype_int16 yycheck[] =
{
       1,    20,    30,     5,     4,    11,    26,     4,     9,    15,
      27,     9,   104,    14,   106,    43,    22,    18,    39,    36,
      26,    42,     0,    51,    25,    21,     3,    28,    26,    30,
      26,    37,    64,    65,    53,    37,    37,    69,    70,   131,
      40,    42,    43,    40,    45,    37,    78,    79,    80,    39,
      51,    52,    42,     9,    10,     3,     6,    58,    90,    60,
      34,    62,    36,     4,    96,    97,    98,    99,   100,   101,
      26,   103,    73,     7,     9,    10,    11,    58,   110,    60,
      15,    62,    28,    29,    30,    31,    32,    22,    34,    36,
      36,    26,     8,   125,    37,    31,    32,   129,    34,    18,
      36,   102,    37,   104,    35,   106,    17,    36,   140,    28,
      29,    30,    31,    32,    38,    34,    41,    36,    38,    37,
      35,    18,    41,    35,    37,    39,    35,    35,    13,    36,
     131,    28,    29,    30,    31,    32,    18,    34,    40,    36,
      40,    40,    35,    41,    41,    39,    28,    29,    30,    31,
      32,    18,    34,    27,    36,    35,    12,    40,    28,    41,
      51,    28,    29,    30,    31,    32,    18,    34,    -1,    36,
      -1,    -1,    39,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    18,    34,    -1,    36,    -1,    -1,    39,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    18,    34,    -1,    36,
      -1,    -1,    39,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    18,    34,    -1,    36,    -1,    -1,    39,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    18,    34,    -1,    36,
      -1,    38,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    18,    34,    -1,    36,    -1,    38,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    18,    34,    -1,    36,
      -1,    38,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    -1,    34,    -1,    36,    19,    20,    -1,    -1,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,    33,
      -1,    35,    29,    30,    31,    32,    -1,    34,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    44,    46,    26,    59,     0,    45,    37,     3,
      47,     4,    59,     6,     5,    37,     8,    59,    48,     7,
      37,     9,    10,    50,    51,    53,    59,    35,    48,    36,
       4,    40,    52,    59,    17,    50,    38,    53,    41,    36,
      40,    59,    38,    35,    59,    53,    54,    55,    39,    59,
      39,    42,    37,    37,    55,    11,    15,    22,    37,    49,
      56,    59,    48,    35,    35,    35,    49,    40,    49,    27,
      36,    49,    59,    19,    20,    23,    24,    25,    30,    33,
      35,    57,    59,    60,    57,    57,    40,    40,    57,    57,
      13,     9,    59,    57,    57,    57,    18,    28,    29,    30,
      31,    32,    34,    36,    39,    39,    39,    41,    38,    57,
      36,    35,    39,    57,    57,    57,    57,    57,    57,    21,
      59,    57,    56,    41,    56,    27,    41,    57,    39,    35,
      38,    12,    57,    40,    38,    57,    58,    56,    41,    39,
      42,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    52,    53,    53,    53,    53,
      54,    54,    54,    55,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,    17,     6,     8,     0,     2,
       0,     2,     0,     2,     3,    13,     3,     1,     1,     1,
       0,     1,     3,     2,     3,     7,     5,     5,     4,     7,
       3,     3,     3,     3,     2,     3,     3,     4,     3,     6,
       1,     1,     1,     1,     1,     5,     4,     2,     3,     0,
       1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (root, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, IProgram*& root)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (root);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, IProgram*& root)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, root);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, IProgram*& root)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, IProgram*& root)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (IProgram*& root)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 118 "src/grammar.y" /* yacc.c:1646  */
    {
        root = new CProgram((yyvsp[-1].mainClassDeclarationVal), *(yyvsp[0].classDeclarationListVal), location);
    }
#line 1512 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 124 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.classDeclarationListVal) = new std::vector<IClassDecl *>();
    }
#line 1520 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 126 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].classDeclarationListVal)->push_back((yyvsp[0].classDeclarationVal));
        (yyval.classDeclarationListVal) = (yyvsp[-1].classDeclarationListVal);
    }
#line 1529 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 133 "src/grammar.y" /* yacc.c:1646  */
    {

        std::cerr<<"mainClass\n";
        (yyval.mainClassDeclarationVal) = new CMainClass( *(yyvsp[-15].val), *(yyvsp[-5].val), *(yyvsp[-2].statementListVal), location);
    }
#line 1539 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 143 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.classDeclarationVal) = new CClassDecl(*(yyvsp[-4].val), *(yyvsp[-2].variableDeclarationListVal), *(yyvsp[-1].methodDeclarationListVal), false, "", location);
    }
#line 1547 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 148 "src/grammar.y" /* yacc.c:1646  */
    {
            (yyval.classDeclarationVal) = new CClassDecl(*(yyvsp[-6].val), *(yyvsp[-2].variableDeclarationListVal), *(yyvsp[-1].methodDeclarationListVal), true, *(yyvsp[-4].val), location);
    }
#line 1555 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 157 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.variableDeclarationListVal) = new std::vector<IVarDecl *>();
    }
#line 1563 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 159 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].variableDeclarationListVal)->push_back((yyvsp[0].variableDeclarationVal));
        (yyval.variableDeclarationListVal) = (yyvsp[-1].variableDeclarationListVal);
    }
#line 1572 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 165 "src/grammar.y" /* yacc.c:1646  */
    {
        std::cerr<<"Empty statement List\n";
        (yyval.statementListVal) = new std::deque<IStatement *> ();
    }
#line 1581 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 168 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyvsp[0].statementListVal)->push_front((yyvsp[-1].statementVal));
        (yyval.statementListVal) = (yyvsp[0].statementListVal);
    }
#line 1590 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 175 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.methodDeclarationListVal) = new std::vector<IMethodDecl*>();
    }
#line 1598 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 177 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyvsp[-1].methodDeclarationListVal)->push_back((yyvsp[0].methodDeclarationVal));
        (yyval.methodDeclarationListVal) = (yyvsp[-1].methodDeclarationListVal);
    }
#line 1607 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 184 "src/grammar.y" /* yacc.c:1646  */
    {

        std::cerr<<"VarDecl\n"<<"\n";
        (yyval.variableDeclarationVal) = new CVarDecl((yyvsp[-2].typeVal), *(yyvsp[-1].val), location);
    }
#line 1617 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 197 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.methodDeclarationVal) = new CMethodDecl((yyvsp[-11].typeVal), *(yyvsp[-10].val), *(yyvsp[-8].formalListVal), *(yyvsp[-5].variableDeclarationListVal), *(yyvsp[-4].statementListVal), (yyvsp[-2].expressionVal), location);
    }
#line 1625 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 203 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.typeVal) = new CStandardType( CStandardType::StandardType::INT_ARRAY, location);
    }
#line 1633 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 206 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.typeVal) = new CStandardType( CStandardType::StandardType::BOOL, location);
    }
#line 1641 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 209 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.typeVal) = new CStandardType( CStandardType::StandardType::INT, location );
    }
#line 1649 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 212 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.typeVal) = new CUserType( *(yyvsp[0].val), location);
    }
#line 1657 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 220 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.formalListVal) = new std::vector<IArg*>();
    }
#line 1665 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 223 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.formalListVal) = new std::vector<IArg*>(1, (yyvsp[0].argVal));
    }
#line 1673 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 226 "src/grammar.y" /* yacc.c:1646  */
    {
        std::cerr<<"ArgList\n";
        (yyvsp[-2].formalListVal)->push_back((yyvsp[0].argVal));
        (yyval.formalListVal) = (yyvsp[-2].formalListVal);
     }
#line 1683 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 234 "src/grammar.y" /* yacc.c:1646  */
    { (yyval.argVal) = new CArg((yyvsp[-1].typeVal), *(yyvsp[0].val), location);}
#line 1689 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 239 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.statementVal) = new CStatementListStatement( *(yyvsp[-1].statementListVal), location);
	}
#line 1697 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 242 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.statementVal) = new CIfStatement( (yyvsp[-4].expressionVal), (yyvsp[-2].statementVal), (yyvsp[0].statementVal), location);
	}
#line 1705 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 245 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.statementVal) = new CWhileStatement( (yyvsp[-2].expressionVal), (yyvsp[0].statementVal), location);
	}
#line 1713 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 248 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.statementVal) = new CPrintStatement( (yyvsp[-2].expressionVal), location);
	}
#line 1721 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 251 "src/grammar.y" /* yacc.c:1646  */
    {
	    std::cerr<<"ex=ex"<<"\n";
		(yyval.statementVal) = new CAssignStatement( *(yyvsp[-3].val), (yyvsp[-1].expressionVal), location);
	}
#line 1730 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 255 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.statementVal) = new CArrayAssignStatement( *(yyvsp[-6].val), (yyvsp[-4].expressionVal), (yyvsp[-1].expressionVal), location);
}
#line 1738 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 261 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::AND, (yyvsp[0].expressionVal), location);
	}
#line 1746 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 264 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::LESS, (yyvsp[0].expressionVal), location);
	}
#line 1754 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 267 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::PLUS, (yyvsp[0].expressionVal), location);
	}
#line 1762 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 270 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::MINUS, (yyvsp[0].expressionVal), location);
	}
#line 1770 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 273 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::MINUS, (yyvsp[0].expressionVal), location);
	}
#line 1778 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 276 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::TIMES, (yyvsp[0].expressionVal), location);
	}
#line 1786 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 279 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBinOpExpression( (yyvsp[-2].expressionVal), CBinOpExpression::BinOp::DIVIDE, (yyvsp[0].expressionVal), location);
	}
#line 1794 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 282 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CIndexExpression( (yyvsp[-3].expressionVal), (yyvsp[-1].expressionVal), location);
	}
#line 1802 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 285 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CLenghtExpression( (yyvsp[-2].expressionVal), location);
	}
#line 1810 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 288 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CMethodExpression( (yyvsp[-5].expressionVal), *(yyvsp[-3].val), *(yyvsp[-1].expressionListVal), location);
	}
#line 1818 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 291 "src/grammar.y" /* yacc.c:1646  */
    {
	    (yyval.expressionVal) = new CIntLiteralExpression((yyvsp[0].intVal), location);
	}
#line 1826 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 294 "src/grammar.y" /* yacc.c:1646  */
    {
	    (yyval.expressionVal) = new CBoolLiteralExpression(true, location);
	}
#line 1834 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 297 "src/grammar.y" /* yacc.c:1646  */
    {
	    (yyval.expressionVal) = new CBoolLiteralExpression(false, location);
	}
#line 1842 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 301 "src/grammar.y" /* yacc.c:1646  */
    {
	    std::cerr<<"expr-id"<<"\n";
		(yyval.expressionVal) = new CIdentifierExpression( *(yyvsp[0].val), location);
	}
#line 1851 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 305 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CThisExpression(location );
	}
#line 1859 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 308 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CNewIntArrayExpression( (yyvsp[-1].expressionVal), location );
	}
#line 1867 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 311 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CNewExpression( *(yyvsp[-2].val), location);
	}
#line 1875 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 314 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CUnaryOpExpression( CUnaryOpExpression::UnaryOp::NOT, (yyvsp[0].expressionVal), location);
	}
#line 1883 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 317 "src/grammar.y" /* yacc.c:1646  */
    {
		(yyval.expressionVal) = new CBracesExpression( (yyvsp[-1].expressionVal), location);
}
#line 1891 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 322 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.expressionListVal) = new std::vector<IExp*>();
    }
#line 1899 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 325 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.expressionListVal) = new std::vector<IExp*>(1, (yyvsp[0].expressionVal));
    }
#line 1907 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "src/grammar.y" /* yacc.c:1646  */
    {
            (yyvsp[-2].expressionListVal)->push_back((yyvsp[0].expressionVal));
    		(yyval.expressionListVal) = (yyvsp[-2].expressionListVal);
    }
#line 1916 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 333 "src/grammar.y" /* yacc.c:1646  */
    {
        std::cerr<<"ID:" << *(yyvsp[0].val)<<"\n";
        (yyval.val) = (yyvsp[0].val);
    }
#line 1925 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 338 "src/grammar.y" /* yacc.c:1646  */
    {
        (yyval.intVal) = (yyvsp[0].intVal);
    }
#line 1933 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
    break;


#line 1937 "/home/tna0y/Desktop/Compiler/parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (root, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (root, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, root);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (root, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 341 "src/grammar.y" /* yacc.c:1906  */


void yyerror(IProgram * root, const char *s)
{
	std::cerr <<"ERROR: " << s <<"\n";
	std::cerr << location.lineNumber<<":"<<location.firstColumn<<"\n";
}
