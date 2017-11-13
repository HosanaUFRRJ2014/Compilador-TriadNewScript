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
#line 1 "sintatica.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <algorithm> 
#include <sstream>
#include <map>
#include <vector>



#include "MapaTipos.h"

#include "controleDeVariaveis.h"

#include "MensagensDeErro.h"

#include "Atributos.h"

#include "TratamentoString.h"

#include "EntradaESaida.h"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo boolean"
#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_TIPOS_DIFERENTES "Os operandos de expressões relacionais precisam ser do mesmo tipo"

using namespace std;

using namespace MapaTipos;
using namespace ControleDeVariaveis;
using namespace MensagensDeErro;
using namespace Atributos;
using namespace TratamentoString;
using namespace EntradaESaida;

int yylex(void);
void yyerror(string);
bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);


#line 109 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_NUM = 258,
    TK_BOOL = 259,
    TK_CHAR = 260,
    TK_STRING = 261,
    TK_OP_LOGICO_BIN = 262,
    TK_OP_LOGICO_UNA = 263,
    TK_OP_RELACIONAL = 264,
    TK_MAIN = 265,
    TK_ID = 266,
    TK_TIPO_INT = 267,
    TK_TIPO_FLOAT = 268,
    TK_TIPO_CHAR = 269,
    TK_TIPO_BOOL = 270,
    TK_TIPO_STRING = 271,
    TK_PALAVRA_VAR = 272,
    TK_PALAVRA_PRINT = 273,
    TK_PALAVRA_SCAN = 274,
    TK_BACKSCOPE = 275,
    TK_PALAVRA_GLOBAL = 276,
    TK_FIM = 277,
    TK_ERROR = 278,
    TK_CONVERSAO_EXPLICITA = 279
  };
#endif
/* Tokens.  */
#define TK_NUM 258
#define TK_BOOL 259
#define TK_CHAR 260
#define TK_STRING 261
#define TK_OP_LOGICO_BIN 262
#define TK_OP_LOGICO_UNA 263
#define TK_OP_RELACIONAL 264
#define TK_MAIN 265
#define TK_ID 266
#define TK_TIPO_INT 267
#define TK_TIPO_FLOAT 268
#define TK_TIPO_CHAR 269
#define TK_TIPO_BOOL 270
#define TK_TIPO_STRING 271
#define TK_PALAVRA_VAR 272
#define TK_PALAVRA_PRINT 273
#define TK_PALAVRA_SCAN 274
#define TK_BACKSCOPE 275
#define TK_PALAVRA_GLOBAL 276
#define TK_FIM 277
#define TK_ERROR 278
#define TK_CONVERSAO_EXPLICITA 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 208 "y.tab.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   195

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,    34,    32,    41,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    40,
      28,    25,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      26,    27,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    72,    72,    79,    84,    92,   100,   103,   105,   107,
     109,   111,   113,   119,   121,   125,   135,   142,   151,   157,
     163,   169,   178,   186,   190,   203,   205,   207,   209,   211,
     259,   264,   266,   282,   329,   399,   415,   439,   454,   462,
     480,   489,   491,   493,   495,   513,   519,   525,   528,   534,
     540,   546,   554,   566,   568,   585,   588,   609,   618,   627,
     637,   655,   672,   693,   703,   708,   711,   714,   720
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM", "TK_BOOL", "TK_CHAR",
  "TK_STRING", "TK_OP_LOGICO_BIN", "TK_OP_LOGICO_UNA", "TK_OP_RELACIONAL",
  "TK_MAIN", "TK_ID", "TK_TIPO_INT", "TK_TIPO_FLOAT", "TK_TIPO_CHAR",
  "TK_TIPO_BOOL", "TK_TIPO_STRING", "TK_PALAVRA_VAR", "TK_PALAVRA_PRINT",
  "TK_PALAVRA_SCAN", "TK_BACKSCOPE", "TK_PALAVRA_GLOBAL", "TK_FIM",
  "TK_ERROR", "TK_CONVERSAO_EXPLICITA", "'='", "\"==\"", "\"!=\"", "'<'",
  "'>'", "\"<=\"", "\">=\"", "'+'", "'-'", "'*'", "'/'", "'('", "')'",
  "'{'", "'}'", "';'", "','", "':'", "$accept", "S", "UP_S", "BLOCO",
  "COMANDOS", "COMANDO", "PRINT", "ARG_PRINT", "SCAN", "ARGS_SCAN",
  "ARG_SCAN", "TIPO", "DECLARACOES", "DECLARACAO", "ID", "TERMO",
  "VALOR_ATRIBUICAO", "E", "E1", "STRING", "E_UNARIA", "E_LOGICA",
  "TERMO_REL", "E_REL", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    61,   280,   281,    60,    62,
     282,   283,    43,    45,    42,    47,    40,    41,   123,   125,
      59,    44,    58
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -67

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -66,    41,    52,    23,    58,    39,    51,    29,    75,
      44,   -66,    89,   -66,   125,   125,   -66,    65,    93,    73,
     -66,   -66,   -66,   -66,   136,   125,    82,    56,   102,   114,
     -66,    87,    32,    -1,   -66,   -66,   127,   128,   -66,   108,
     139,   -66,   115,   140,    61,   127,   -66,    92,     6,     6,
     -66,   -66,     6,   133,   134,     3,   116,   -66,   140,   140,
     140,   140,   136,   140,   -66,   -66,   -66,    24,    61,   -66,
     -66,   119,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   121,   -66,   133,   -66,    79,   131,   137,   -66,
     124,    79,   -66,   -66,   -66,    13,   122,   135,    11,   142,
     136,    -4,   -66,   -66,   -66,   -66,   -66,   -66,   146,    12,
      32,   147,   127,   167,   148,   145,   149,   150,   152,    -4,
     165,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      31,    35,     0,     0,     0,     0,    31,     0,     0,     0,
       0,     1,     0,    30,     0,     0,    32,     0,     0,     0,
      38,    63,    40,    56,     0,     0,     0,     0,     0,    39,
      53,     0,    41,    47,    55,    42,    43,     0,    65,     0,
       0,    37,     0,     0,    66,    61,    44,    54,     0,     0,
      39,    57,     0,    66,    47,     0,    65,    34,     0,     0,
       0,     0,     0,     0,    33,    36,     3,     0,    54,    58,
      59,     0,    50,    51,    64,    68,    45,    46,    48,    49,
      60,    67,     0,     2,     0,    52,     3,     0,     0,    12,
       0,     3,    13,    14,    11,    39,    66,     0,     0,    65,
       0,     0,     4,     5,     7,     8,    10,     9,     0,    39,
      18,    55,    19,    20,     0,    23,     0,     0,     0,     0,
       0,    15,    21,    22,    25,    26,    27,    28,    29,    24
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   -66,   123,    96,   -66,   -66,   -66,   -66,    69,
     -66,   -66,   187,   -65,     0,    68,    -3,   -12,   -24,    94,
     -33,   -23,   132,   -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    82,    89,    90,    91,    92,   108,    93,   114,
     115,   129,     5,     6,    50,    30,    31,    44,    33,    34,
      35,    36,    37,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    45,    32,    32,    54,    55,     7,     1,    56,    20,
      62,    22,    39,    47,    29,    29,    53,     1,    62,   -62,
     -62,    94,    46,    11,    29,    29,    94,    20,    29,    22,
      23,    68,     3,    60,    61,     1,    78,    79,    14,    80,
      74,   -66,     3,    54,     9,    10,    76,    77,    43,   -17,
       1,   106,     8,    97,    15,    84,     2,    52,    97,    20,
      67,    22,    29,    98,    58,    59,    99,     1,    98,    16,
      12,    99,     9,    10,    96,     3,    14,   112,    17,    96,
     113,    18,    20,    21,    22,    23,    95,    24,   110,    49,
       1,    95,     3,    58,    59,    51,     2,    87,    88,    19,
     109,   116,    40,    43,    41,    20,    21,    22,    23,    42,
      24,    26,    27,     1,    48,    28,    69,    70,    -6,   116,
      71,   -62,     9,    10,    58,    59,    43,    57,    20,    21,
      22,    23,   -41,    24,    62,    52,     1,    63,    28,    20,
      21,    22,    23,    20,    24,    22,    23,     1,    64,    25,
      65,     1,    66,    75,    58,    59,    85,    26,    27,    86,
      43,    28,   104,   102,    43,    58,    59,   100,    60,    61,
      72,    73,    28,   101,   -65,   105,    67,   124,   125,   126,
     127,   128,   107,   117,   -16,   118,   119,   103,   123,    83,
     121,   120,   122,    13,   111,    81
};

static const yytype_uint8 yycheck[] =
{
       0,    24,    14,    15,    28,    28,     6,    11,    28,     3,
       7,     5,    15,    25,    14,    15,    28,    11,     7,     7,
       7,    86,    25,     0,    24,    25,    91,     3,    28,     5,
       6,    43,    36,    34,    35,    11,    60,    61,    25,    62,
      37,     9,    36,    67,    20,    21,    58,    59,    24,    37,
      11,    40,    11,    86,    25,    67,    17,    33,    91,     3,
      36,     5,    62,    86,    32,    33,    86,    11,    91,    40,
      12,    91,    20,    21,    86,    36,    25,   100,     3,    91,
     100,    37,     3,     4,     5,     6,    86,     8,   100,    33,
      11,    91,    36,    32,    33,    27,    17,    18,    19,    10,
     100,   101,    37,    24,    11,     3,     4,     5,     6,    36,
       8,    32,    33,    11,    32,    36,    48,    49,    39,   119,
      52,     7,    20,    21,    32,    33,    24,    40,     3,     4,
       5,     6,    40,     8,     7,    33,    11,     9,    36,     3,
       4,     5,     6,     3,     8,     5,     6,    11,    40,    24,
      11,    11,    37,    37,    32,    33,    37,    32,    33,    38,
      24,    36,    40,    39,    24,    32,    33,    36,    34,    35,
      37,    37,    36,    36,     7,    40,    36,    12,    13,    14,
      15,    16,    40,    37,    37,    37,    41,    91,   119,    66,
      40,    42,    40,     6,   100,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    17,    36,    44,    55,    56,    57,    11,    20,
      21,     0,    12,    55,    25,    25,    40,     3,    37,    10,
       3,     4,     5,     6,     8,    24,    32,    33,    36,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    59,
      37,    11,    36,    24,    60,    64,    59,    60,    32,    33,
      57,    58,    33,    60,    61,    64,    66,    40,    32,    33,
      34,    35,     7,     9,    40,    11,    37,    36,    60,    58,
      58,    58,    37,    37,    37,    37,    60,    60,    61,    61,
      64,    65,    45,    46,    60,    37,    38,    18,    19,    46,
      47,    48,    49,    51,    56,    57,    60,    63,    64,    66,
      36,    36,    39,    47,    40,    40,    40,    40,    50,    57,
      60,    62,    64,    66,    52,    53,    57,    37,    37,    41,
      42,    40,    40,    52,    12,    13,    14,    15,    16,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    46,    47,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    50,    50,    50,    50,
      50,    51,    52,    52,    53,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    56,    57,    57,    57,    58,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    63,    63,    63,
      64,    64,    64,    64,    64,    64,    65,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     4,     2,     0,     2,     2,     2,
       2,     1,     1,     1,     1,     5,     1,     1,     1,     1,
       1,     5,     3,     1,     3,     1,     1,     1,     1,     1,
       2,     0,     3,     5,     4,     1,     5,     4,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     1,     3,     3,
       3,     3,     4,     1,     2,     1,     1,     2,     3,     3,
       3,     2,     1,     1,     3,     1,     1,     3,     3
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 73 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n" << substituirTodasAsDeclaracoesProvisorias((yyvsp[-5]).traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << (yyvsp[-5]).traducao << endl << (yyvsp[0]).traducao << "\treturn 0;\n}" << endl;
			}
#line 1388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 79 "sintatica.y" /* yacc.c:1646  */
    {
				aumentarEscopo();
			}
#line 1396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 85 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao =  (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao =  (yyval).traducao + "\n" + (yyvsp[-1]).traducao;
				diminuirEscopo();
			}
#line 1406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 93 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = substituirTodasAsDeclaracoesProvisorias((yyvsp[-1]).traducaoDeclaracaoDeVariaveis) + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				if((yyvsp[-1]).traducao != "" && (yyvsp[-1]).tipo != constante_tipo_bloco){
					(yyval).traducao = (yyvsp[-1]).traducao + "\n" ;//+ constroiPrint($1.tipo, $1.label);
				}
				(yyval).traducao = (yyval).traducao + (yyvsp[0]).traducao;
			}
#line 1418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 114 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "\t{\n" + (yyvsp[0]).traducao + "\t}\n";
				(yyval).tipo = constante_tipo_bloco;
			}
#line 1427 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 126 "sintatica.y" /* yacc.c:1646  */
    {
			
				(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyvsp[-2]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyval).traducao + (yyvsp[-2]).traducao;
			
			}
#line 1438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "sintatica.y" /* yacc.c:1646  */
    {
					
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint((yyvsp[0]).label);
				
			}
#line 1448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 143 "sintatica.y" /* yacc.c:1646  */
    {	
				DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label);
				(yyval).label = metaData.nome;
				(yyval).tipo = metaData.tipo;
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint((yyval).label);
				
			}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 152 "sintatica.y" /* yacc.c:1646  */
    {
				
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint((yyvsp[0]).label);
			}
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 158 "sintatica.y" /* yacc.c:1646  */
    {
				
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint((yyvsp[0]).label);
			}
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 164 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint((yyvsp[0]).label);
			}
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 170 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << " // Entrei em TK_PALAVRA_SCAN '(' ARGS_SCAN ')'';' \n";
				(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyvsp[-2]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyval).traducao + (yyvsp[-2]).traducao;
	
			}
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 179 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << $3.traducao << " *******\n";
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + (yyvsp[-2]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[-2]).traducao;
			
			}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 191 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "\n//Entrou em ID TIPO\n";
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = "\t" + (yyvsp[0]).label + " " + (yyval).label + ";\n";
				(yyval).traducao =  constroiScan((yyval).label);
				adicionarDefinicaoDeTipo((yyvsp[-2]).label, (yyvsp[0]).tipo);
				
				(yyval).traducao = (yyval).traducao + "\t" + (yyvsp[-2]).label + " = " + (yyval).label + ";\n";
				
		
			}
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 260 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			}
#line 1533 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 267 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelJaDeclarada((yyvsp[-1]).label, false))
				{
					//mensagem de erro dupla declaração
					string params[1] = {(yyvsp[-1]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}
				
				else
				{
					(yyval).traducaoDeclaracaoDeVariaveis = "\t" + construirDeclaracaoProvisoriaDeInferenciaDeTipo((yyvsp[-1]).label);
					incluirNoMapa((yyvsp[-1]).label);
				}
			}
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 283 "sintatica.y" /* yacc.c:1646  */
    {	
				//cout << "Entrou em TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';': \n\n\n";
				if(variavelJaDeclarada((yyvsp[-3]).label, false))
				{
					//mensagem de erro dupla declaração
					string params[1] = {(yyvsp[-3]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}
				else
				{
					//cout << "Entrou no else: \n\n\n";
					string tipo = (yyvsp[-1]).tipo;
					string label = prefixo_variavel_usuario;
					label = label + (yyvsp[-3]).label;
					if(tipo == constante_tipo_booleano)
					{
						tipo = constante_tipo_inteiro;
						tipo = "\t" + tipo;
						label = prefixo_variavel_usuario;
						label = label + "_" + (yyvsp[-3]).label;
					}
					if(tipo == constante_tipo_string)
					{
						tipo = constante_tipo_caracter;
						tipo = "\t" + tipo;
						
					//	$2.label = prefixo_variavel_usuario + $2.label;
					
						(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + (yyvsp[-3]).label + "[" + to_string((yyvsp[-1]).tamanho) + "];\n";
						(yyval).traducao = (yyvsp[-1]).traducao + montarCopiarString((yyvsp[-3]).label, (yyvsp[-1]).label) + ";\n";
					
					}
					
					else
					{
					//	$2.label = prefixo_variavel_usuario + $2.label;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + label + ";\n";
					(yyval).traducao = (yyvsp[-1]).traducao + "\t" + label + " = " + (yyvsp[-1]).label + ";\n";
					incluirNoMapa((yyvsp[-3]).label, (yyvsp[-1]).tipo);
					(yyval).label = label;
					}
					(yyval).tipo = (yyvsp[-1]).tipo;
				}
				
			}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 330 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em ID '=' VALOR_ATRIBUICAO ';': \n\n\n";			
				if((yyvsp[-3]).label != (yyvsp[-1]).label)
				{
					DADOS_VARIAVEL metaData;
					if((yyvsp[-3]).escopoDeAcesso >= 0){
						metaData = recuperarDadosVariavel((yyvsp[-3]).label, (yyvsp[-3]).escopoDeAcesso);
					}
					else{
						metaData = recuperarDadosVariavel((yyvsp[-3]).label);
					}
					if(metaData.tipo == "")
					{
						//isso aqui também pode causar problema no futuro devido as lacunas
						metaData.tipo = (yyvsp[-1]).tipo;
						
						string tipo = (yyvsp[-1]).tipo;
						if(tipo == constante_tipo_booleano)
						{
							tipo = constante_tipo_inteiro;
							tipo = "\t" + tipo;
						}
						if((yyvsp[-3]).escopoDeAcesso >= 0){
							
							//adicionarDefinicaoDeTipo($1.label, tipo, $1.tamanho + $3.tamanho,$1.escopoDeAcesso);
							adicionarDefinicaoDeTipo((yyvsp[-3]).label, tipo,(yyvsp[-3]).escopoDeAcesso);
							atualizarNoMapa(metaData, (yyvsp[-3]).escopoDeAcesso);
						}
						else{
							
							//adicionarDefinicaoDeTipo($1.label, tipo,$1.tamanho + $3.tamanho);
							adicionarDefinicaoDeTipo((yyvsp[-3]).label, tipo);
							atualizarNoMapa(metaData);
						}
						
						
						
					//	adicionarDefinicaoDeTipo($1.label, tipo, $1.tamanho + $3.tamanho);
						
						
						(yyvsp[-3]).tipo = (yyvsp[-1]).tipo;
					}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
					if((yyvsp[-3]).tipo == (yyvsp[-1]).tipo){
						(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;
						if((yyvsp[-1]).tipo == constante_tipo_string)
							(yyval).traducao =  (yyvsp[-1]).traducao + montarCopiarString((yyvsp[-3]).label, (yyvsp[-1]).label) + ";\n";	
						else
						(yyval).traducao = (yyvsp[-1]).traducao + "\t" + (yyvsp[-3]).label + " = " + (yyvsp[-1]).label + ";\n";
					}
					else
					{
						
						string strPrefixoVarUsuario = prefixo_variavel_usuario;
						string params[3] = {(yyvsp[-3]).label.replace(0, strPrefixoVarUsuario.length(), ""), (yyvsp[-3]).tipo, (yyvsp[-1]).tipo};
						yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
					}
					(yyval).label = (yyvsp[-3]).label;
					(yyval).tipo = (yyvsp[-3]).tipo;
				}
				else
				{
					(yyval) = (yyvsp[-1]);
				}
			}
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 400 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelJaDeclarada((yyvsp[0]).label))
				{
					DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label);
					
					(yyval).label = metaData.nome;
					(yyval).tipo = metaData.tipo;
				}
				else
				{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA ,params, 1));
				}
			}
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 416 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2]).tipo != constante_tipo_inteiro){
					string params[1] = {(yyvsp[-2]).tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_PARAMETRO_BACKSCOPE_DEVE_SER_INTEIRO, params, 1));
				}
				
				int qtdRetornoEscopo = stoi((yyvsp[-2]).label);
				if(ehMaiorIgualQueEscopoAtual(qtdRetornoEscopo))
					yyerror(montarMensagemDeErro(MSG_ERRO_PARAMETRO_BACKSCOPE_MAIOR_OU_IGUAL_ESCOPO_ATUAL));
				
				int escopo = escopoResultante(qtdRetornoEscopo);

				if(variavelJaDeclarada((yyvsp[0]).label, true, escopo)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label, escopo);
					(yyval).label = metaData.nome;
					(yyval).tipo = metaData.tipo;
					(yyval).escopoDeAcesso = escopo;
				}else{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 440 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelJaDeclarada((yyvsp[0]).label, false, 0)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label, 0);
					(yyval).label = metaData.nome;
					(yyval).tipo = metaData.tipo;
					(yyval).escopoDeAcesso = 0;
				}else{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 455 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = "\t"  + (yyvsp[0]).tipo + " " + (yyval).label + ";\n";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 463 "sintatica.y" /* yacc.c:1646  */
    {
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra ID: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if((yyvsp[0]).label.find(prefixo_variavel_usuario) == 0 && (yyvsp[0]).tipo == ""){
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {(yyvsp[0]).label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}

				if((yyvsp[0]).tipo == constante_tipo_booleano){
					(yyvsp[0]).label.replace((yyvsp[0]).label.find("_"), 1, "__");
				}
				
				(yyval) = (yyvsp[0]);
			}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 481 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = "\t" + (yyvsp[0]).tipo + " " + (yyval).label + ";\n";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 496 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao;
				if(verificarPossibilidadeDeConversaoExplicita((yyvsp[0]).tipo, (yyvsp[-1]).tipo)){
					(yyval).label = gerarNovaVariavel();
					(yyval).tipo = (yyvsp[-1]).tipo;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + "\t" + (yyval).tipo + " " + (yyval).label + ";\n";
					
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + (yyvsp[0]).label + ";\n";
				}else{
					string params[2] = {(yyvsp[0]).tipo, (yyvsp[-1]).tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}
			}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 514 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em E+E: \n\n\n";
				(yyval) = tratarExpressaoAritmetica("+", (yyvsp[-2]), (yyvsp[0]));							
			}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 520 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em E-E: \n\n\n";
				(yyval) = tratarExpressaoAritmetica("-", (yyvsp[-2]), (yyvsp[0]));
			}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 529 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em E*E: \n\n\n";
				(yyval) = tratarExpressaoAritmetica("*", (yyvsp[-2]), (yyvsp[0]));
			}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 535 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em E/E: \n\n\n";
				(yyval) = tratarExpressaoAritmetica("/", (yyvsp[-2]), (yyvsp[0]));
			}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 541 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em (E): \n\n\n";
				(yyval) = (yyvsp[-1]);
			}
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 547 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "Entrou em (E1): \n\n\n";
				(yyval) = (yyvsp[-1]);
			}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 555 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "Entrou em (-TERMO): \n\n\n";
				(yyval).label = (yyvsp[-1]).label;
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyval).traducao + (yyvsp[-1]).traducao;
				
				
				(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + (yyval).label + " * (-1);\n";
				(yyval).tipo = (yyvsp[-1]).tipo; 
			}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 569 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "Entrou em TK_CONVERSAO_EXPLICITA E: \n\n\n";
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao;
				if(verificarPossibilidadeDeConversaoExplicita((yyvsp[0]).tipo, (yyvsp[-1]).tipo)){
					(yyval).label = gerarNovaVariavel();
					(yyval).tipo = (yyvsp[-1]).tipo;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + "\t" + (yyval).tipo + " " + (yyval).label + ";\n";
					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + (yyvsp[0]).label + ";\n";
				}else{
					string params[2] = {(yyvsp[0]).tipo, (yyvsp[-1]).tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}	
			}
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 589 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "Entrou em TK_STRING\n";
				(yyval).label = gerarNovaVariavel();
				//$$.tamanho = $1.label.length() +1 -2; //-2 exclui o tamanho das aspas
				string codigoTraduzido = geraDeclaracaoString((yyval).label, (yyvsp[0]).label);
				(yyval).tamanho = (yyvsp[0]).label.length() +1 -2 - global_numCaracteresEspeciais; //-2 exclui o tamanho das aspas a global vem do namespace TratamentoString
				(yyval).traducaoDeclaracaoDeVariaveis = "\tchar " + (yyval).label + "[" + to_string((yyval).tamanho) + "];\n";
				(yyval).traducao = codigoTraduzido;
				
			//	cout << mapaStrings[$$.label].valor << "\n";
				
				//cout << $$.traducaoDeclaracaoDeVariaveis << "\n";
				
				(yyval).tipo = (yyvsp[0]).tipo;
				
				global_numCaracteresEspeciais = 0;
				
				
			}
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 610 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em TERMO de E_UNARIA\n";
				(yyval).label = (yyvsp[0]).label;
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyval).label + " * (-1);\n";
				(yyval).tipo = (yyvsp[0]).tipo; 
			}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 619 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em ++TERMO de E_UNARIA\n";
				(yyval).label = (yyvsp[0]).label;
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyval).label + " + 1;\n";
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 628 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em --TERMO de E_UNARIA\n";
				(yyval).label = (yyvsp[0]).label;
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyval).label + " = " + (yyval).label + " - 1;\n";
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 638 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em E_LOGICA TK_OP_LOGICO_BIN E_LOGICA de E_LOGICA\n";
				if((yyvsp[-2]).tipo == constante_tipo_booleano && (yyvsp[0]).tipo == constante_tipo_booleano){
					(yyval).label = gerarNovaVariavel();
					(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
					string tipo = constante_tipo_inteiro;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + "\t\t" + tipo + " " + (yyval).label + ";\n";
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
					(yyval).traducao = (yyval).traducao + "\t\t" + (yyval).label + " = " + (yyvsp[-2]).label + " " + (yyvsp[-1]).label + " " + (yyvsp[0]).label + ";\n";
					(yyval).tipo = constante_tipo_booleano;
				}
				else{
					yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 656 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em TK_OP_LOGICO_UNA E_LOGICA de E_LOGICA\n";
				if((yyvsp[0]).tipo == constante_tipo_booleano){
					(yyval).label = gerarNovaVariavel();
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
					string tipo = constante_tipo_inteiro;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + "\t\t" + tipo + " " + (yyval).label + ";\n";
					(yyval).traducao = (yyvsp[0]).traducao;
					(yyval).traducao = (yyval).traducao + "\t\t" + (yyval).label + " = " + (yyvsp[-1]).label + (yyvsp[0]).label + ";\n";
					(yyval).tipo = constante_tipo_booleano;
				}
				else{
					yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 673 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[0]).label.find(prefixo_variavel_usuario) == 0 && (yyvsp[0]).tipo == "")
				{
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {(yyvsp[0]).label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}
				
				(yyvsp[0]).label.replace((yyvsp[0]).label.find("_"), 1, "__");


/*
				if($1.tipo == "")
					adicionarDefinicaoDeTipo($1.label, constante_tipo_inteiro);
				$1.tipo = constante_tipo_booleano;
*/
				(yyval) = (yyvsp[0]);
			}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 694 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em TK_BOOL de E_LOGICA\n";
				string nomeUpperCase = (yyvsp[0]).label;
				transform(nomeUpperCase.begin(), nomeUpperCase.end(), nomeUpperCase.begin(), ::toupper);
				(yyval).label = nomeUpperCase;
				incluirNoMapa((yyval).label, (yyvsp[0]).tipo);
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 704 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
			}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 715 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em TERMO_REL TK_OP_RELACIONAL TERMO_REL\n";
				(yyval) = tratarExpressaoRelacional((yyvsp[-1]).label,(yyvsp[-2]),(yyvsp[0]));	
			}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 721 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "Entrou em (E_REL) \n";
				(yyval) = (yyvsp[-1]);
			}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2051 "y.tab.c" /* yacc.c:1646  */
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 727 "sintatica.y" /* yacc.c:1906  */


#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL> tabelaDeVariaveis;
extern int yylineno; //Define a linha atual do arquivo fonte.

int yyparse();

int main( int argc, char* argv[] )
{
	
	mapaTipos = criarMapa();
	inicializarMapaDeContexto();
	yyparse();
	
	

	return 0;
}

ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	
	dolarDolar.label = gerarNovaVariavel();
	
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;				
/*	
//remover esta verificação se for tratar como erro a não atribuição
	if(dolar1.tipo == "" && dolar3.tipo == "")
	{

		dolar1.tipo = constante_tipo_inteiro;
		dolar3.tipo = constante_tipo_inteiro;
		
	}	
	if(dolar1.tipo == "")
	{
		dolar1.tipo = dolar3.tipo;
	}
	if(dolar3.tipo == "")
	{
		dolar3.tipo = dolar1.tipo;
	}	
*/		
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);
	
	if(!(dolar1.tipo == constante_tipo_string || dolar3.tipo == constante_tipo_string))
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
	
	string label_old = dolarDolar.label;
	
	if(resultado == constante_erro)
	{
		string params[3] = {op,dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
	
	/*
	*TODO	
	*Tratar caso de ser do tipo String
	*
	*/
	else if(dolar1.tipo == constante_tipo_string && dolar3.tipo == constante_tipo_string)
	{
		//realizando a soma das traduções fora das funções
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + realizarTraducaoDeclaracaoDeString(op, dolarDolar, dolar1,dolar3);
		
		string traducao = realizarOperacaoAritmeticaString(op, dolarDolar,dolar1,dolar3);
		
		if(traducao == "") //o operador ainda não está implementado. Fiz assim para não alterar no mapa, vou apagar o if
		{
			string params[3] = {op,dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
		
		}
			
		
		dolarDolar.traducao = dolarDolar.traducao + traducao;
			
	
	}
		
	else if((dolar1.tipo == dolar3.tipo) && (dolar1.tipo == resultado)) //se não houver necessidade de conversão
	{
	
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
	}
	
	
	else if(dolar3.tipo == resultado) 
	{
		
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
		
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + label_old + " " + op + " " + dolar3.label + ";\n";
	}
	else if(dolar1.tipo == resultado)
	{
			
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + label_old + ";\n";
		
	}
	
	dolarDolar.tipo = resultado;
	return dolarDolar;	
}



ATRIBUTOS tratarExpressaoRelacional(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t\t" + constante_tipo_inteiro + " " + dolarDolar.label + ";\n";
	
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo,op);
	
	string label_old = dolarDolar.label;
	string operador = op;
	
	string varConvert = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
	if(resultado == constante_erro)
	{
		
		string params[3] = {dolar1.tipo, dolar3.tipo, op};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
		
	else if(dolar1.tipo == dolar3.tipo)
	{	
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
	
			dolar1.label = varConvert;
			varConvert = gerarNovaVariavel();
	
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
			dolar3.label = varConvert;
		}
							
	}
	
	
	else if(dolar3.tipo == resultado)
	{
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
		dolar1.label = varConvert;
	}
	
	else if(dolar1.tipo == resultado)
	{
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
		dolar3.label = varConvert;
		
	}
	
	dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label +" "+ op +" "+ dolar3.label + ";\n";
	
	dolarDolar.tipo = constante_tipo_booleano;
	
	
	return dolarDolar;
	
}



bool verificarPossibilidadeDeConversaoExplicita(string tipoOrigem, string tipoDestino){
	
	return tipoOrigem != constante_tipo_booleano;
}


void yyerror( string MSG )
{
	cout << "Linha " << yylineno << ": " << MSG << endl;
	exit (0);
}				
