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
#include "MensagensDeErro.h"
#include "ControleDeVariaveis.h"
#include "Atributos.h"
#include "EntradaESaida.h"
#include "TratamentoString.h"
#include "ControleDeFluxo.h"
#include "TratamentoArray.h"
#include "TratamentoOperadoresCompostos.h"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo boolean"
#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_TIPOS_DIFERENTES "Os operandos de expressões relacionais precisam ser do mesmo tipo"
//#define prefixo_variavel_sistema "temp"

#define YYDEBUG 0

using namespace std;

using namespace MapaTipos;
using namespace ControleDeVariaveis;
using namespace MensagensDeErro;
using namespace Atributos;
using namespace EntradaESaida;
using namespace TratamentoString;
using namespace ControleDeFluxo;
using namespace TratamentoArray;
using namespace TratamentoOperadoresCompostos;

int yylex(void);
void yyerror(string);
string definicoesDeFuncoes();

bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoAritmeticaComposta(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoLogicaBinaria(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoLogicaUnaria(string, ATRIBUTOS);
ATRIBUTOS tratarExpressaoLogicaComposta(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);
//string gerarNovaVariavel();

ATRIBUTOS tratarDeclaracaoSemAtribuicao(ATRIBUTOS);
ATRIBUTOS tratarDeclaracaoComAtribuicao(ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS, ATRIBUTOS, bool ehDinamica = false);

int conta;


#line 124 "y.tab.c" /* yacc.c:339  */

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
    TK_OP_ARIT_UNA = 262,
    TK_OP_ARIT_PRIO1 = 263,
    TK_OP_ARIT_PRIO2 = 264,
    TK_OP_ARIT_PRIO3 = 265,
    TK_OP_ARIT_COMP_PRIO1 = 266,
    TK_OP_ARIT_COMP_PRIO2 = 267,
    TK_OP_LOG_BIN_PRIO1 = 268,
    TK_OP_LOG_BIN_PRIO2 = 269,
    TK_OP_LOG_COMP_PRIO1 = 270,
    TK_OP_LOG_COMP_PRIO2 = 271,
    TK_OP_LOG_UNA = 272,
    TK_OP_REL_PRIO1 = 273,
    TK_OP_REL_PRIO2 = 274,
    TK_IF = 275,
    TK_ELSE = 276,
    TK_WHILE = 277,
    TK_DO = 278,
    TK_FOR = 279,
    TK_SWITCH = 280,
    TK_CASE = 281,
    TK_DEFAULT = 282,
    TK_BREAK = 283,
    TK_CONTINUE = 284,
    TK_LEN = 285,
    TK_TIPO_INT = 286,
    TK_TIPO_FLOAT = 287,
    TK_TIPO_CHAR = 288,
    TK_TIPO_BOOL = 289,
    TK_TIPO_STRING = 290,
    TK_PALAVRA_PRINT = 291,
    TK_PALAVRA_SCAN = 292,
    TK_CONVERSAO_EXPLICITA = 293,
    TK_PALAVRA_VAR = 294,
    TK_ID = 295,
    TK_PALAVRA_FUNC = 296,
    TK_BACKSCOPE = 297,
    TK_PALAVRA_GLOBAL = 298,
    IFX = 299
  };
#endif
/* Tokens.  */
#define TK_NUM 258
#define TK_BOOL 259
#define TK_CHAR 260
#define TK_STRING 261
#define TK_OP_ARIT_UNA 262
#define TK_OP_ARIT_PRIO1 263
#define TK_OP_ARIT_PRIO2 264
#define TK_OP_ARIT_PRIO3 265
#define TK_OP_ARIT_COMP_PRIO1 266
#define TK_OP_ARIT_COMP_PRIO2 267
#define TK_OP_LOG_BIN_PRIO1 268
#define TK_OP_LOG_BIN_PRIO2 269
#define TK_OP_LOG_COMP_PRIO1 270
#define TK_OP_LOG_COMP_PRIO2 271
#define TK_OP_LOG_UNA 272
#define TK_OP_REL_PRIO1 273
#define TK_OP_REL_PRIO2 274
#define TK_IF 275
#define TK_ELSE 276
#define TK_WHILE 277
#define TK_DO 278
#define TK_FOR 279
#define TK_SWITCH 280
#define TK_CASE 281
#define TK_DEFAULT 282
#define TK_BREAK 283
#define TK_CONTINUE 284
#define TK_LEN 285
#define TK_TIPO_INT 286
#define TK_TIPO_FLOAT 287
#define TK_TIPO_CHAR 288
#define TK_TIPO_BOOL 289
#define TK_TIPO_STRING 290
#define TK_PALAVRA_PRINT 291
#define TK_PALAVRA_SCAN 292
#define TK_CONVERSAO_EXPLICITA 293
#define TK_PALAVRA_VAR 294
#define TK_ID 295
#define TK_PALAVRA_FUNC 296
#define TK_BACKSCOPE 297
#define TK_PALAVRA_GLOBAL 298
#define IFX 299

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

#line 263 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   547

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  213

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

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
      51,    52,     2,     2,    50,     2,    53,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    47,
       2,    54,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   122,   122,   131,   136,   143,   151,   154,   156,   158,
     160,   162,   164,   166,   169,   175,   181,   187,   193,   199,
     205,   211,   217,   224,   231,   238,   254,   271,   288,   296,
     313,   316,   334,   351,   399,   408,   418,   427,   435,   455,
     460,   462,   480,   480,   480,   482,   483,   483,   485,   487,
     487,   488,   488,   490,   490,   491,   491,   494,   515,   546,
     566,   579,   585,   587,   590,   597,   600,   609,   615,   620,
     626,   638,   648,   654,   664,   673,   682,   775,   777,   779,
     781,   783,   788,   790,   792,   794,   796,   799,   815,   838,
     846,   869,   878,   901,   903,   912,   918,   921,   939,   942,
     949,   961,   963,   971,   977,   981,   983,  1016,  1027,  1060,
    1066,  1116,  1128,  1138,  1145,  1148,  1196,  1206
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM", "TK_BOOL", "TK_CHAR",
  "TK_STRING", "TK_OP_ARIT_UNA", "TK_OP_ARIT_PRIO1", "TK_OP_ARIT_PRIO2",
  "TK_OP_ARIT_PRIO3", "TK_OP_ARIT_COMP_PRIO1", "TK_OP_ARIT_COMP_PRIO2",
  "TK_OP_LOG_BIN_PRIO1", "TK_OP_LOG_BIN_PRIO2", "TK_OP_LOG_COMP_PRIO1",
  "TK_OP_LOG_COMP_PRIO2", "TK_OP_LOG_UNA", "TK_OP_REL_PRIO1",
  "TK_OP_REL_PRIO2", "TK_IF", "TK_ELSE", "TK_WHILE", "TK_DO", "TK_FOR",
  "TK_SWITCH", "TK_CASE", "TK_DEFAULT", "TK_BREAK", "TK_CONTINUE",
  "TK_LEN", "TK_TIPO_INT", "TK_TIPO_FLOAT", "TK_TIPO_CHAR", "TK_TIPO_BOOL",
  "TK_TIPO_STRING", "TK_PALAVRA_PRINT", "TK_PALAVRA_SCAN",
  "TK_CONVERSAO_EXPLICITA", "TK_PALAVRA_VAR", "TK_ID", "TK_PALAVRA_FUNC",
  "TK_BACKSCOPE", "TK_PALAVRA_GLOBAL", "IFX", "'{'", "'}'", "';'", "'['",
  "']'", "','", "'('", "')'", "'.'", "'='", "':'", "$accept", "S", "UP_S",
  "BLOCO", "COMANDOS", "COMANDO", "E", "ARRAY", "DIMENSOES_INDICES",
  "VALOR", "FUNCAO", "DECLARACAO_FUNCAO", "NOME_DECLARACAO_FUNC",
  "FUNC_ID", "PARAMETROS_DECLARACAO", "PARAMETROS_CHAMADA",
  "ARGS_FUNC_DECLARACAO", "ARGS_FUNC_CHAMADA", "ID", "STRING",
  "INICIO_DECLARACAO", "MULTI_DECLARACAO", "CRIACAO_VARIAVEL",
  "ATRIBUICAO_VARIAVEL_CRIACAO", "ATRIBUICAO_VARIAVEL", "PRINT",
  "ARG_PRINT", "SCAN", "ARGS_SCAN", "ARG_SCAN", "TIPO", "E_FLUXO_CONTROLE",
  "COMANDO_IF", "EMPILHAR_TAG_WHILE", "COMANDO_WHILE",
  "EMPILHAR_TAG_DOWHILE", "COMANDO_DOWHILE", "INIT", "INIT_VAR", "INITS",
  "CONDICAO", "UPDATE", "UPDATE_VAR", "UPDATES", "EMPILHAR_TAG_FOR",
  "COMANDO_FOR", "EMPILHAR_TAG_SWITCH", "COMANDO_SWITCH", "DEFAULT",
  "CASES", "CASE", "E_BREAK_CONTINUE", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   123,   125,    59,    91,    93,
      44,    40,    41,    46,    61,    58
};
# endif

#define YYPACT_NINF -129

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-129)))

#define YYTABLE_NINF -110

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-110)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     196,  -129,  -129,  -129,  -129,   360,   360,   -30,  -129,  -129,
      -5,     5,    61,   -22,     8,    29,    61,   311,    72,    40,
    -129,  -129,   122,   451,  -129,    34,  -129,    43,    43,    56,
    -129,    50,    66,  -129,    70,    71,  -129,  -129,    98,  -129,
     108,  -129,   109,  -129,   112,  -129,    87,   472,  -129,   130,
     360,   360,     2,    34,    89,  -129,    97,   -10,    34,   138,
     100,    19,  -129,   235,  -129,  -129,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,  -129,   119,     3,
    -129,  -129,   360,  -129,   113,  -129,  -129,   104,   284,   106,
     114,  -129,   378,   492,   116,  -129,    49,   111,   117,   121,
     360,   -29,  -129,  -129,    61,   120,   124,  -129,   128,    52,
     130,  -129,   504,   516,   528,   105,    90,   362,   259,     6,
     125,  -129,   492,   -33,   492,   123,  -129,   129,   360,   159,
       9,   360,   284,  -129,   154,  -129,     2,   492,  -129,  -129,
      18,  -129,    34,   142,  -129,  -129,   139,   360,  -129,   360,
     113,   405,   141,    56,  -129,  -129,   146,  -129,   144,   424,
     174,  -129,  -129,  -129,  -129,  -129,  -129,  -129,   168,  -129,
    -129,  -129,   492,   492,  -129,   284,   360,   360,     9,   164,
     284,  -129,  -129,   437,   492,   163,  -129,   185,  -129,   167,
     360,   360,   188,   185,  -129,   492,  -129,   165,  -129,   172,
     329,   171,   177,  -129,   284,   360,   284,   284,  -129,  -129,
    -129,  -129,  -129
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    34,    35,    36,    60,     0,     0,     0,   116,   117,
       0,     0,     0,     0,    57,    47,     0,     0,     0,     0,
       8,     2,     6,     0,    30,    28,    40,    42,     0,    38,
      37,     0,    62,    63,     0,     0,    12,    82,     0,    83,
       0,    84,     0,    85,     0,    86,     0,    26,    38,    19,
       0,     0,     0,    29,    66,    46,     0,     0,    33,     0,
       0,     0,     1,     3,     5,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,     0,
      43,    44,     0,     9,     0,    10,    11,     0,     3,     0,
       0,    13,     0,    72,     0,    57,     0,     0,     0,    75,
       0,     0,     3,    31,     0,     0,     0,    39,     0,    14,
      15,    16,    22,    23,    17,    18,    24,    25,    20,    21,
       0,    52,    56,     0,    70,    69,    61,    65,     0,     0,
      94,     0,     3,    71,     0,    73,     0,    67,    54,    50,
       0,    45,    32,     0,    59,     4,     0,     0,    51,     0,
       0,     0,     0,     0,    97,    98,     0,    93,    96,     0,
      87,    77,    78,    79,    80,    81,    76,    74,     0,    49,
      58,    41,    55,    68,    64,     3,     0,   100,     0,     0,
       3,    53,    90,     0,    99,     0,    95,     0,    88,     0,
     102,     0,   112,   114,    92,   106,   105,     0,   101,   104,
       0,     0,     0,   113,     3,     0,     3,     3,   110,   108,
     103,   115,   111
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,   126,   -18,   -85,     7,  -129,  -129,   -11,
    -129,  -129,  -129,  -129,  -129,   199,  -129,  -129,     0,  -129,
    -129,    79,  -128,  -129,   -94,  -129,  -129,  -129,    94,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,    53,  -129,
    -129,  -129,    38,  -129,  -129,  -129,  -129,  -129,  -129,    55,
    -129,  -129
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,    19,    20,    21,    22,    23,    24,    57,    25,
      26,    27,    56,    28,   102,    80,   140,   123,    48,    30,
      31,   126,    32,   127,    33,    34,    94,    35,    98,    99,
     166,    36,    37,    38,    39,    40,    41,   156,   157,   158,
     185,   197,   198,   199,    42,    43,    44,    45,   202,   192,
     193,    46
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    53,   154,   129,    64,    58,     1,     2,     3,     4,
       5,   138,    47,    49,    66,    67,    68,   147,    54,   148,
       6,    50,    29,   139,    61,  -110,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   155,    75,    76,   103,
     104,    12,    95,    14,    15,   108,    51,   160,    13,    95,
     154,    16,    97,    96,    17,   121,    52,    92,    93,   -48,
      96,    67,    68,    29,     1,     2,     3,     4,   168,    55,
     169,   107,    62,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   155,    63,   122,    78,    29,   124,
     182,    59,    60,   142,    79,   188,   196,    83,    66,    67,
      68,    14,    15,    71,    72,  -110,    74,   137,    75,    76,
      82,   196,    17,    66,    67,    68,    84,    85,    86,   209,
      87,   211,   212,    75,    76,     1,     2,     3,     4,     5,
     153,    88,    29,    89,    91,   151,    97,    90,   159,     6,
      68,   105,     7,   100,   -89,   -91,  -107,  -109,   101,   120,
       8,     9,   106,   125,   172,   128,   173,   130,    10,    11,
      12,    13,    14,    15,   144,   131,   134,    -3,   133,   135,
      16,   136,   143,    17,   145,    29,   146,   149,   153,   150,
      29,   152,   170,   183,   184,   161,   162,   163,   164,   165,
      29,   171,   176,   177,   178,   180,    -6,   195,   200,     1,
       2,     3,     4,     5,    29,    29,    29,    29,   181,   187,
     190,   191,   195,     6,   194,   201,     7,   204,   -89,   -91,
    -107,  -109,   205,   208,     8,     9,   207,    81,   141,   174,
     167,   186,    10,    11,    12,    13,    14,    15,     1,     2,
       3,     4,     5,   210,    16,     0,     0,    17,   203,     0,
       0,     0,     6,     0,     0,     7,     0,   -89,   -91,  -107,
    -109,     0,     0,     8,     9,     0,     0,    66,    67,    68,
       0,    10,    11,    12,    13,    14,    15,  -110,    76,     0,
       0,    -6,     0,    16,     0,     0,    17,     1,     2,     3,
       4,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     7,     0,   -89,   -91,  -107,  -109,
       0,     0,     8,     9,     1,     2,     3,     4,     5,     0,
      10,    11,    12,    13,    14,    15,     0,     0,     6,     0,
       0,     0,    16,     0,     0,    17,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,    75,    76,    12,
       0,    14,    15,    59,    60,     0,     0,     0,     0,    16,
       0,     0,    17,     1,     2,     3,     4,     5,     0,     0,
      66,    67,    68,     0,     0,    71,    72,     6,  -110,     0,
      75,    76,     0,     0,   206,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     0,    75,    76,    12,     0,
      14,    15,     0,     0,     0,     0,     0,     0,    16,     0,
       0,    17,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     0,    75,    76,     0,     0,     0,     0,     0,
     132,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,    75,    76,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,    75,    76,   175,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,    75,
      76,     0,     0,     0,     0,     0,   179,     0,     0,  -110,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   189,
      75,    76,     0,     0,     0,     0,     0,     0,    77,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     0,
      75,    76,    66,    67,    68,  -110,    70,    71,    72,    73,
      74,     0,    75,    76,    66,    67,    68,     0,  -110,    71,
      72,    73,    74,     0,    75,    76,    66,    67,    68,     0,
       0,     0,    72,     0,     0,     0,    75,    76
};

static const yytype_int16 yycheck[] =
{
       0,    12,   130,    88,    22,    16,     3,     4,     5,     6,
       7,    40,     5,     6,     8,     9,    10,    50,    40,    52,
      17,    51,    22,    52,    17,    19,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,   130,    18,    19,    49,
      50,    38,    40,    40,    41,    63,    51,   132,    39,    40,
     178,    48,    52,    51,    51,    52,    51,    50,    51,    51,
      51,     9,    10,    63,     3,     4,     5,     6,    50,    40,
      52,    52,     0,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   178,    45,    79,    53,    88,    82,
     175,    42,    43,   104,    51,   180,   190,    47,     8,     9,
      10,    40,    41,    13,    14,    15,    16,   100,    18,    19,
      54,   205,    51,     8,     9,    10,    50,    47,    47,   204,
      22,   206,   207,    18,    19,     3,     4,     5,     6,     7,
     130,    23,   132,    24,    47,   128,   136,    25,   131,    17,
      10,     3,    20,    54,    22,    23,    24,    25,    51,    30,
      28,    29,    52,    40,   147,    51,   149,    51,    36,    37,
      38,    39,    40,    41,    40,    51,    55,    45,    52,    52,
      48,    50,    52,    51,    46,   175,    51,    54,   178,    50,
     180,    22,    40,   176,   177,    31,    32,    33,    34,    35,
     190,    52,    51,    47,    50,    21,     0,   190,   191,     3,
       4,     5,     6,     7,   204,   205,   206,   207,    40,    45,
      47,    26,   205,    17,    47,    27,    20,    52,    22,    23,
      24,    25,    50,    46,    28,    29,    55,    28,   102,   150,
     136,   178,    36,    37,    38,    39,    40,    41,     3,     4,
       5,     6,     7,   205,    48,    -1,    -1,    51,   193,    -1,
      -1,    -1,    17,    -1,    -1,    20,    -1,    22,    23,    24,
      25,    -1,    -1,    28,    29,    -1,    -1,     8,     9,    10,
      -1,    36,    37,    38,    39,    40,    41,    18,    19,    -1,
      -1,    46,    -1,    48,    -1,    -1,    51,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    20,    -1,    22,    23,    24,    25,
      -1,    -1,    28,    29,     3,     4,     5,     6,     7,    -1,
      36,    37,    38,    39,    40,    41,    -1,    -1,    17,    -1,
      -1,    -1,    48,    -1,    -1,    51,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    18,    19,    38,
      -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,     3,     4,     5,     6,     7,    -1,    -1,
       8,     9,    10,    -1,    -1,    13,    14,    17,    16,    -1,
      18,    19,    -1,    -1,    55,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    38,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    51,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      52,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    18,    19,    52,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    18,
      19,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    52,
      18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    47,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      18,    19,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,     8,     9,    10,    -1,    12,    13,
      14,    15,    16,    -1,    18,    19,     8,     9,    10,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    18,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    20,    28,    29,
      36,    37,    38,    39,    40,    41,    48,    51,    57,    58,
      59,    60,    61,    62,    63,    65,    66,    67,    69,    74,
      75,    76,    78,    80,    81,    83,    87,    88,    89,    90,
      91,    92,   100,   101,   102,   103,   107,    62,    74,    62,
      51,    51,    51,    65,    40,    40,    68,    64,    65,    42,
      43,    62,     0,    45,    60,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    18,    19,    47,    53,    51,
      71,    71,    54,    47,    50,    47,    47,    22,    23,    24,
      25,    47,    62,    62,    82,    40,    51,    74,    84,    85,
      54,    51,    70,    49,    50,     3,    52,    52,    60,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      30,    52,    62,    73,    62,    40,    77,    79,    51,    61,
      51,    51,    52,    52,    55,    52,    50,    62,    40,    52,
      72,    59,    65,    52,    40,    46,    51,    50,    52,    54,
      50,    62,    22,    74,    78,    80,    93,    94,    95,    62,
      61,    31,    32,    33,    34,    35,    86,    84,    50,    52,
      40,    52,    62,    62,    77,    52,    51,    47,    50,    52,
      21,    40,    61,    62,    62,    96,    94,    45,    61,    52,
      47,    26,   105,   106,    47,    62,    80,    97,    98,    99,
      62,    27,   104,   105,    52,    50,    55,    55,    46,    61,
      98,    61,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    66,    67,    68,    68,    69,    70,
      70,    71,    71,    72,    72,    73,    73,    74,    74,    74,
      75,    76,    76,    76,    77,    77,    78,    78,    79,    79,
      80,    81,    82,    83,    84,    84,    85,    86,    86,    86,
      86,    86,    87,    87,    87,    87,    87,    88,    88,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    99,    99,   100,   101,   102,
     103,   104,   104,   105,   105,   106,   107,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     4,     2,     0,     2,     1,     2,
       2,     2,     1,     2,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     2,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     3,
       1,     5,     1,     2,     2,     4,     1,     0,     1,     3,
       2,     3,     2,     3,     1,     3,     1,     1,     5,     4,
       1,     3,     1,     1,     3,     1,     2,     4,     3,     1,
       3,     4,     1,     4,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     7,     0,
       6,     0,     8,     1,     0,     3,     1,     1,     1,     1,
       0,     1,     0,     3,     1,     1,     1,     0,    10,     0,
       9,     3,     0,     2,     1,     4,     1,     1
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
#line 123 "sintatica.y" /* yacc.c:1646  */
    {

//				cout << "/*Compilador TriadNewScript*/\n" << "#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n#define TAMANHO_INICIAL_STRING 10\n#define FATOR_MULTIPLICADOR_STRING 2\n#define FATOR_CARGA_STRING 1\n\n" << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << $1.traducao << endl << $6.traducao << "FIMCODINTER:\treturn 0;\n}" << endl;
				cout << "/*Compilador TriadNewScript*/\n" << "#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n" << constroiDefinesParaStringDinamica() << substituirTodasAsDeclaracoesProvisorias((yyvsp[0]).traducaoDeclaracaoDeVariaveis) << "\n\n" << definicoesDeFuncoes() << "\nint main(void)\n{\n" << (yyvsp[0]).traducao << "FIMCODINTER:\treturn 0;\n}" << endl;
			}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 131 "sintatica.y" /* yacc.c:1646  */
    {
				aumentarEscopo();
			}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 137 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
				diminuirEscopo();
			}
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 144 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				if((yyvsp[-1]).traducao != "" && (yyvsp[-1]).estruturaDoConteudo != constante_estrutura_bloco){
					(yyval).traducao = (yyvsp[-1]).traducao + "\n";// + constroiPrint($1.tipo, $1.label);
				}
				(yyval).traducao = (yyval).traducao + (yyvsp[0]).traducao;
			}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 170 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoAritmetica((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 176 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoAritmetica((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 182 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoAritmetica((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 188 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoLogicaBinaria((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 194 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoLogicaBinaria((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 200 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoLogicaUnaria((yyvsp[-1]).label, (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 206 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoRelacional((yyvsp[-1]).label,(yyvsp[-2]),(yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 212 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoRelacional((yyvsp[-1]).label,(yyvsp[-2]),(yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;
			}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 218 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoAritmeticaComposta((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;

			}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 225 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoAritmeticaComposta((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;

			}
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 232 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoLogicaComposta((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;

			}
#line 1708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 239 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = tratarExpressaoLogicaComposta((yyvsp[-1]).label, (yyvsp[-2]), (yyvsp[0]));
				(yyval).estruturaDoConteudo = constante_estrutura_expressao;

			}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 255 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_variavel)
				{
					(yyval) = (yyvsp[0]);
					(yyval).traducao = (yyvsp[0]).traducao + "\t" + (yyvsp[0]).label + " = " + (yyvsp[0]).label + " " + (yyvsp[-1]).label[0] + " 1;\n";
				}
				else
				{
					string params[2] = {
						(yyvsp[-1]).label,
						"o operando não é uma variável"
					};
					yyerror(montarMensagemDeErro(MSG_ERRO_OPERADOR_UNARIO_INVALIDO_PARA_OPERANDO, params, 2));
				}
			}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 272 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-1]).estruturaDoConteudo == constante_estrutura_variavel)
				{
					(yyval) = (yyvsp[-1]);
					(yyval).traducao = "\t" + (yyvsp[-1]).label + " = " + (yyvsp[-1]).label + " " + (yyvsp[0]).label[0] + " 1;\n" + (yyvsp[-1]).traducao;
				}
				else
				{
					string params[2] = {
						(yyvsp[0]).label,
						"o operando não é uma variável"
					};
					yyerror(montarMensagemDeErro(MSG_ERRO_OPERADOR_UNARIO_INVALIDO_PARA_OPERANDO, params, 2));
				}
			}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 289 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[0]);
				if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_variavel)
					(yyval).label = recuperarNomeTraducao((yyval).label);

			}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 297 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[0]).traducao;
				if(verificarPossibilidadeDeConversaoExplicita((yyvsp[0]).tipo, (yyvsp[-1]).tipo)){
					(yyval).label = gerarNovaVariavel();
					(yyval).tipo = (yyvsp[-1]).tipo;
					(yyval).tamanho = (yyvsp[-1]).tamanho;
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyval).tipo + " " + (yyval).label + ";\n";

					(yyval).traducao = (yyval).traducao + "\t" + (yyval).label + " = " + (yyvsp[-1]).label + (yyvsp[0]).label + ";\n";
				}else{
					string params[2] = {(yyvsp[0]).tipo, (yyvsp[-1]).tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}
			}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 317 "sintatica.y" /* yacc.c:1646  */
    {
			(yyval) = (yyvsp[-1]);


			//$$.estruturaDoConteudo = constante_estrutura_array;
		}
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 335 "sintatica.y" /* yacc.c:1646  */
    {
						if((yyvsp[0]).tipo != constante_tipo_inteiro)
						{
							//dispara erro ...
						}

						if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_variavel)
						{
							//Fazer lógica para índice como variável.
						}
						else //Ele será inteiro de TK_NUM
						{
							//Fazer lógica para índice como sendo numero inteiro.
						}
					}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 352 "sintatica.y" /* yacc.c:1646  */
    {
						if((yyvsp[0]).tipo != constante_tipo_inteiro)
						{
							//dispara erro ...
						}

						if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_variavel)
						{
							//Fazer lógica para índice como variável.
						}
						else //Ele será inteiro de TK_NUM
						{
							//Fazer lógica para índice como sendo numero inteiro.
							(yyval) = (yyvsp[0]);
							adicionarTamanhoDimensoesArray((yyvsp[0]).label);



						}

					}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 400 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).tipo + " " + (yyval).label + ";\n";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
			}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 409 "sintatica.y" /* yacc.c:1646  */
    {
				string nomeUpperCase = (yyvsp[0]).label;
				transform(nomeUpperCase.begin(), nomeUpperCase.end(), nomeUpperCase.begin(), ::toupper);
				(yyval).label = nomeUpperCase;
				(yyval).estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
				//incluirNoMapa($$.label,0, $1.tipo);
				(yyval).tipo = (yyvsp[0]).tipo;
			}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 419 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).tipo + " " + (yyval).label + ";\n";
				(yyval).traducao = "\t" + (yyval).label + " = " + (yyvsp[0]).label + ";\n";
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
			}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 428 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[0]);
				//cout << "//Entrou em VALOR: STRING\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << endl;
				(yyval).estruturaDoConteudo = constante_estrutura_tipoPrimitivo;

			}
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 436 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << "//Entrou em VALOR: ID" << "\n";
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra ID: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if((yyvsp[0]).tipo == ""){
					string params[1] = {(yyvsp[0]).label};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}

				DADOS_VARIAVEL metadata = recuperarDadosVariavel((yyvsp[0]).label);

				//IMPORTANTE: comentando essas duas linhas pq o william falou que poderia dar problemas na parte dele.
				/*$1.ehDinamica = metadata.ehDinamica;
				$1.tamanho = metadata.tamanho;*/

				//$1.tipo = metadata.tipo; //pode ser que precise
			}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 456 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval) = (yyvsp[-1]);
			}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 463 "sintatica.y" /* yacc.c:1646  */
    {
			//	DADOS_VARIAVEL metadata = recuperarDadosVariavel($.label, $1.escopoDeAcesso);
				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-4]).traducaoDeclaracaoDeVariaveis + constante_tipo_inteiro + ' ' + (yyval).label + ";\n";

			/*	if($1.ehDinamica)
					$$.traducao = $1.traducao + '\t' + $$.label + " = " + $1.labelTamanhoDinamicoString + ";\n";

				else*/
					(yyval).traducao = (yyvsp[-4]).traducao + '\t' + (yyval).label + " = sizeof(" + recuperarNomeTraducao((yyvsp[-4]).label) + ");\n";

				(yyval).tipo = constante_tipo_inteiro;

			}
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 495 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "//Entrou em ID: TK_ID\n";
				if(variavelJaDeclarada((yyvsp[0]).label))
				{
					DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label);
					(yyval).label = metaData.nome;
					(yyval).tipo = metaData.tipo;
					(yyval).estruturaDoConteudo = constante_estrutura_variavel;
					(yyval).tamanho = metaData.tamanho;
					(yyval).ehDinamica = metaData.ehDinamica;
			//		cout << "//Entrou em ID: TK_ID\n" << "metaData.nome: " << metaData.nome << "\nlabel$: " << $$.label << "label1: " << $1.label << endl;
				}
				else
				{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA ,params, 1));
				}

			}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 516 "sintatica.y" /* yacc.c:1646  */
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
					(yyval).tipo = metaData.tipo;
					(yyval).tamanho = metaData.tamanho;
					(yyval).ehDinamica = metaData.ehDinamica;

					if((yyval).tipo == "")
						(yyval).estruturaDoConteudo = constante_estrutura_variavelSemTipo;
					else
						(yyval).estruturaDoConteudo = constante_estrutura_variavel;

					(yyval).escopoDeAcesso = escopo;
				}else{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 547 "sintatica.y" /* yacc.c:1646  */
    {
				if(variavelJaDeclarada((yyvsp[0]).label, false, 0)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel((yyvsp[0]).label, 0);
					(yyval).tipo = metaData.tipo;
					(yyval).tamanho = metaData.tamanho;
					(yyval).ehDinamica = metaData.ehDinamica;
					if((yyval).tipo == "")
						(yyval).estruturaDoConteudo = constante_estrutura_variavelSemTipo;
					else
						(yyval).estruturaDoConteudo = constante_estrutura_variavel;

					(yyval).escopoDeAcesso = 0;
				}else{
					string params[1] = {(yyvsp[0]).label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 567 "sintatica.y" /* yacc.c:1646  */
    {
			//	cout << "Entrou em TK_STRING\n";
			//	$$.label = gerarNovaVariavel();
			//	cout << "//Entrou em STRING: TK_STRING\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << endl;
				(yyval).tamanho = atualizarTamanhoString((yyvsp[0]).label.length()); //tamanho modificado pelo \0 e pelas aspas
		//		$$.traducaoDeclaracaoDeVariaveis = "char " + $$.label + "[" + to_string($$.tamanho) + "];\n";
				(yyval).label = (yyvsp[0]).label;
			}
#line 2037 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 580 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
					}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 591 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
						(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
				//		cout << "//Entrou em MULTI_DECLARACAO: ATRIBUICAO_VARIAVEL_CRIACAO , MULTI_DECLARACAO\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << "\nlabel3" << $3.label <<endl;
					}
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 601 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval) = tratarDeclaracaoSemAtribuicao((yyvsp[0]));
						//$$.tipo = constante_tipo_criacao_sem_atribuicao;
						(yyval).estruturaDoConteudo = constante_estrutura_variavelSemTipo;
						(yyval).label = (yyvsp[0]).label;
				//		cout << "//Entrou em CRIACAO_VARIAVEL TK_PALAVRA_VAR TK_ID\n" << "label2: " << $2.label << "\nlabel$: " << $$.label << endl;
					}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 610 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval) = tratarDeclaracaoComAtribuicao((yyvsp[-2]),(yyvsp[0]));
					}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 616 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval) = tratarDeclaracaoComAtribuicao((yyvsp[-2]),(yyvsp[0]));
					}
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 621 "sintatica.y" /* yacc.c:1646  */
    {
						(yyval) = tratarDeclaracaoSemAtribuicao((yyvsp[0]));
					}
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 627 "sintatica.y" /* yacc.c:1646  */
    {
				//		cout << "//Entrou em ID '=' VALOR_ATRIBUICAO\n";
						(yyval) = tratarAtribuicaoVariavel((yyvsp[-2]),(yyvsp[0]));
						/*cout << "--ATRIBUICAO_VARIAVEL----------------\n";
						//cout << "label1: " << dolar1.label << " tamaho: " << dolar1.tamanho << endl;
						//cout << "label3: " << dolar3.label << " tamaho: " << dolar3.tamanho << endl;
						cout << "label$$: " << $$.label << " tamaho: " << $$.tamanho << endl;
						cout << "------------------\n";*/
					}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 639 "sintatica.y" /* yacc.c:1646  */
    {

				(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyval).traducao + (yyvsp[-1]).traducao;

			}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 649 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao + "\n" + constroiPrint(recuperarNomeTraducao((yyvsp[0]).label));
			}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 655 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << " // Entrei em TK_PALAVRA_SCAN '(' ARGS_SCAN ')'';' \n";
				(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyval).traducao + (yyvsp[-1]).traducao;
				(yyval).labelTamanhoDinamicoString = (yyvsp[-1]).labelTamanhoDinamicoString;

			}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 665 "sintatica.y" /* yacc.c:1646  */
    {
				//cout << $1.traducaoDeclaracaoDeVariaveis << " *******\n";
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + (yyvsp[-2]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[-2]).traducao;
				(yyval).labelTamanhoDinamicoString = (yyvsp[-2]).labelTamanhoDinamicoString;

			}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 674 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).labelTamanhoDinamicoString = (yyvsp[0]).labelTamanhoDinamicoString;


			}
#line 2159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 683 "sintatica.y" /* yacc.c:1646  */
    {
	//			cout << "\n//Entrou em ID TIPO\n";
				/*int tamanho = 0;
				bool ehDinamica = true;
				$$.label = gerarNovaVariavel();
				string dolarDolar = $$.label;

				//cout << "label1\n";
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $3.label + " " + $$.label + ";\n";
				//cout << "label2\n";
			//	cout << "$$label: " << $$.label << endl;
			//	cout << "$1label: " << $1.label << endl;
				DADOS_VARIAVEL metadata;
				if($1.escopoDeAcesso >= 0)
				{
					metadata = recuperarDadosVariavel($1.label, $1.escopoDeAcesso);
				}
				else
				{
					metadata = recuperarDadosVariavel($1.label);
				}

				//cout << "label3\n";
				if(metadata.tipo == ""){
					metadata.tipo = $3.tipo;
					metadata.ehDinamica = ehDinamica;
					if($1.escopoDeAcesso >= 0)
					{
						adicionarDefinicaoDeTipo($1.label, $3.tipo, tamanho,ehDinamica, $1.escopoDeAcesso);
						atualizarNoMapa(metadata, $1.escopoDeAcesso);
					}
					else
					{
						//cout << "label5.1\n";
						adicionarDefinicaoDeTipo($1.label, $3.tipo,tamanho,ehDinamica);
						//cout << "label5.2\n";
						atualizarNoMapa(metadata);
						//cout << "label5.3\n";
					}
				}
				else if(metadata.tipo != $3.tipo)
				{
				//TODO: criar mensagem de erro própria para o input
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[3] = {$1.label.replace(0, strPrefixoVarUsuario.length(), ""), $1.tipo, $3.tipo};
				yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
				}*/
				bool ehDinamica = true;
		/*		ATRIBUTOS $$;
				$$ = copiarDadosAtributos($$);
				$$ = concatenarTraducoesAtributos($$,$$);
				imprimirAtributos($$);
				imprimirAtributos($$);*/
				(yyval) = tratarAtribuicaoVariavel((yyvsp[-2]), (yyvsp[0]), ehDinamica);
				(yyval).label = gerarNovaVariavel();
				string dolarDolar = (yyval).label;
				int tamanho = 0;
				(yyval).traducao = "";
				int escopo = numeroEscopoAtual;
				if((yyval).escopoDeAcesso >= 0)
					escopo = (yyval).escopoDeAcesso;

				if((yyvsp[0]).tipo == constante_tipo_string)
				{
					//adicionarDefinicaoDeTipo($1.label, $3.tipo,tamanho,ehDinamica);

					string labelRecuperada = recuperarNomeTraducao((yyvsp[-2]).label, escopo);
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + "char * " + (yyval).label + ";\n";

					(yyval) =  traducaoStringDinamica((yyval), labelRecuperada);
					(yyval).traducao = (yyval).traducao + montarCopiarString(labelRecuperada, (yyval).label) + ";\n";


				}

				else
				{
					(yyval).traducaoDeclaracaoDeVariaveis = (yyval).traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario((yyvsp[0]).label) + " " + (yyval).label + ";\n";
					(yyval).traducao =  constroiScan((yyval).label, (yyvsp[0]).tipo);
					if((yyvsp[0]).tipo == constante_tipo_booleano)
					{
						(yyval) = validarEntradaBooleanEmTempoExecucao((yyval));

					}

					(yyval).traducao = (yyval).traducao + "\t" + recuperarNomeTraducao((yyvsp[-2]).label, escopo) + " = " + (yyval).label + ";\n";

				}

			}
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 800 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2]).tipo != constante_tipo_booleano) ;
					//dispara erro ...

				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis +
													constante_tipo_inteiro + " " + (yyval).label + ";\n";

				string tagFim = gerarNovaTagIf(true);

				(yyval).traducao = (yyvsp[-2]).traducao + "\t" + (yyval).label + " = " + "!" + (yyvsp[-2]).label + ";\n" +
							"\t" + "if" + "(" + (yyval).label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
							(yyvsp[0]).traducao + "\t" + tagFim + ":;\n";
			}
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 816 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-4]).tipo != constante_tipo_booleano) ;
					//dispara erro ...

				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-4]).traducaoDeclaracaoDeVariaveis + (yyvsp[-2]).traducaoDeclaracaoDeVariaveis +
													(yyvsp[0]).traducaoDeclaracaoDeVariaveis +
													constante_tipo_inteiro + " " + (yyval).label + ";\n";

				//Criar tag para pular o bloco do else (que ficara logo em seguida no cod. interm.)
				string tagBlocoIf = gerarNovaTagIf(false);
				//Criar tag de fim do if.
				string tagFim = gerarNovaTagIf(true);

				(yyval).traducao = (yyvsp[-4]).traducao + "\t" + (yyval).label + " = " + (yyvsp[-4]).label + ";\n" +
								"\t" + "if" + "(" + (yyval).label + ")\n" + "\t\t" + "goto " + tagBlocoIf + ";\n" +
								(yyvsp[0]).traducao + "\t" + "goto " + tagFim + ";\n" + "\t" + tagBlocoIf + ":\n" +
								(yyvsp[-2]).traducao + "\t" + tagFim + ":;\n";
			}
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 838 "sintatica.y" /* yacc.c:1646  */
    {
						string tagInicio = gerarNovaTagWhile(false);
						string tagFim = gerarNovaTagWhile(true);
						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);
					}
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 847 "sintatica.y" /* yacc.c:1646  */
    {
					if((yyvsp[-2]).tipo != constante_tipo_booleano) ;
						//dispara erro ...

					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();

					(yyval).label = gerarNovaVariavel();
					(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis +
														constante_tipo_inteiro + " " + (yyval).label + ";\n";

					(yyval).traducao = "\t" + tagInicio + ":\n" + (yyvsp[-2]).traducao + "\t" + (yyval).label + " = " + "!" + (yyvsp[-2]).label + ";\n" +
									"\t" + "if" + "(" + (yyval).label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									(yyvsp[0]).traducao + "\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":;\n";

					removerTopoTagInicio();
					removerTopoTagFim();
				}
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 869 "sintatica.y" /* yacc.c:1646  */
    {
						string tagInicio = gerarNovaTagDoWhile(false);
						string tagFim = gerarNovaTagDoWhile(true);

						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);
					}
#line 2344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 879 "sintatica.y" /* yacc.c:1646  */
    {
					if((yyvsp[-2]).tipo != constante_tipo_booleano);
						//dispara erro ...

					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();

					(yyval).label = gerarNovaVariavel();
					(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[-5]).traducaoDeclaracaoDeVariaveis +
														constante_tipo_inteiro + " " + (yyval).label + ";\n";

					(yyval).traducao = "\t" + tagInicio + ":\n" + (yyvsp[-5]).traducao +
									(yyvsp[-2]).traducao + "\t" + (yyval).label + " = " + "!" + (yyvsp[-2]).label + ";\n" +
									"\t" + "if" + "(" + (yyval).label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									"\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":;\n";

					removerTopoTagInicio();
					removerTopoTagFim();
				}
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 903 "sintatica.y" /* yacc.c:1646  */
    { //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
			(yyval).traducaoDeclaracaoDeVariaveis = "";
			(yyval).traducao = "";
			(yyval).label = "";
			(yyval).tipo = "";
		}
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 913 "sintatica.y" /* yacc.c:1646  */
    {
			(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
			(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
		}
#line 2389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 922 "sintatica.y" /* yacc.c:1646  */
    {
			//$1.tipo == constante_tipo_criacao_sem_atribuicao
			if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_variavelSemTipo){

				string params[1] = {(yyvsp[0]).label};
				yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_SEM_ATRIBUICAO_FOR,params,1));
			}else{
				(yyval) = (yyvsp[0]);
			}
		}
#line 2404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 943 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[0]).tipo != constante_tipo_booleano);
					//dispara erro ...
				(yyval) = (yyvsp[0]);
			}
#line 2414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 949 "sintatica.y" /* yacc.c:1646  */
    { //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
				/*
				$$.traducaoDeclaracaoDeVariaveis = "";
				$$.traducao = "";
				$$.label = "";
				$$.tipo = constante_tipo_condicao_vazia_for;
				*/
				yyerror(MSG_ERRO_FOR_SEM_CONDICAO);
			}
#line 2428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 963 "sintatica.y" /* yacc.c:1646  */
    { //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
			(yyval).traducaoDeclaracaoDeVariaveis = "";
			(yyval).traducao = "";
			(yyval).label = "";
			(yyval).tipo = "";
		}
#line 2439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 972 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;
			}
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 984 "sintatica.y" /* yacc.c:1646  */
    {

			if((yyvsp[0]).estruturaDoConteudo == constante_estrutura_expressao){
				//dispara erro ...
				if((yyvsp[0]).tipo != constante_tipo_booleano){
					if(variavelJaDeclarada((yyvsp[0]).label)){
						(yyval) = (yyvsp[0]);
					}
					else{
						//dispara erro ex: 1 + 1
					}
				}else{
					// dispara erro 10 < 3
				}
			}else{
				//dispara erro ex: vairiavel
			}
		}
#line 2471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1016 "sintatica.y" /* yacc.c:1646  */
    {
						//string tagInicio = gerarNovaTagFor(false);
						string tagInicio = gerarNovaTagUpdateFor();
						string tagFim = gerarNovaTagFor(true);
						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);

						//cout << "TRADUCAO VAZIA DE EMPILHAR_TAG_FOR:" << endl << endl << $$.traducao;
					}
#line 2485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1028 "sintatica.y" /* yacc.c:1646  */
    {
				string tagInicio = gerarNovaTagFor(false);
				string tagUpdate = obterTopoPilhaInicio();
				string tagFim = obterTopoPilhaFim();

				(yyval).label = gerarNovaVariavel();
				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-6]).traducaoDeclaracaoDeVariaveis + (yyvsp[-4]).traducaoDeclaracaoDeVariaveis +
													(yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis
													+ constante_tipo_inteiro + " " + (yyval).label + ";\n";

				//if($6.tipo != constante_tipo_condicao_vazia_for){

					(yyval).traducao = (yyvsp[-6]).traducao + "\t" + tagInicio + ":\n" +
									(yyvsp[-4]).traducao + "\t" + (yyval).label + " = " + "!" + (yyvsp[-4]).label + ";\n" +
									"\t" + "if" + "(" + (yyval).label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									(yyvsp[0]).traducao + "\t" + tagUpdate + ":\n" +
									(yyvsp[-2]).traducao + "\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":;\n";
				//}else{
					/*
					$$.traducao = $4.traducao + "\t" + tagInicio + ":\n" +
									$10.traducao + $8.traducao + "\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":\n";
					*/
				//}

				removerTopoTagInicio();
				removerTopoTagFim();
			}
#line 2519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1060 "sintatica.y" /* yacc.c:1646  */
    {
						pair<string,int> tagFim = gerarNovaTagSwitch(false);
						adicionarTagFim(tagFim.first);
					}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1067 "sintatica.y" /* yacc.c:1646  */
    {
					if((yyvsp[-5]).estruturaDoConteudo != constante_estrutura_variavel)
					{
						//dispara erro... precisa ser variavel
					}

					//$3.tipo != constante_tipo_string && $3.tipo != constante_tipo_flutuante
					if((yyvsp[-5]).tipo == (yyvsp[-2]).tipo) {
						//(...)
						//pair<string,int> tagFimENumProx = gerarNovaTagSwitch(false);
						//string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second);
						pair<string,int> tagFimENumProx = gerarNovaTagSwitch(true);
						string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second-1);
						pair<string,string> condicaoCase = gerarNovaTagCondicaoCase();


						//string tagFim = gerarNovaTagSwitch(false).first;

						//$$.label = gerarNovaVariavel();

						//Outra parte da árvore já tera a $3.traducaoDeclaracaoDeVariaveis salva. Portanto, teríamos repetição.
						(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[-1]).traducaoDeclaracaoDeVariaveis;

						if((yyvsp[-1]).tipo == constante_tipo_default){

							(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-2]).traducao + (yyvsp[-1]).traducao +
										//"\t" + "goto " + tagFim + ";\n"
										//"\t" + tagFimENumProx.first + ":\n";
										"\t" + obterTopoPilhaFim() + ":;\n";

						}else{
							(yyval).traducao = (yyvsp[-5]).traducao + (yyvsp[-2]).traducao + (yyvsp[-1]).traducao +
										//"\t" + "goto " + tagFim + ";\n"
										"\t" + condicaoCase.first + ":\n" +
										"\t" + tagCaseAtual + ":\n" +
										//"\t" + tagFimENumProx.first + ":\n";
										"\t" + obterTopoPilhaFim() + ":;\n";
						}

						(yyval).traducao = substituirVariaveisCase((yyval).traducao, (yyvsp[-5]).label);
						removerTopoTagFim();

					}
					else{
						yyerror(MSG_ERRO_TIPO_CASE_DISTINTO);
					}
				}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1117 "sintatica.y" /* yacc.c:1646  */
    {
			pair<string,int> tagFimENumProx = gerarNovaTagSwitch(true);
			string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second-1);
			pair<string,string> condicaoCase = gerarNovaTagCondicaoCase();

			(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
			(yyval).traducao = "\t" + condicaoCase.first + ":\n" +
							"\t" + tagCaseAtual + ":\n" + (yyvsp[0]).traducao;
			(yyval).tipo = constante_tipo_default;
		}
#line 2595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1128 "sintatica.y" /* yacc.c:1646  */
    {
			(yyval).traducaoDeclaracaoDeVariaveis = "";
			(yyval).traducao = "";
			//$$.label = "";
			//$$.tipo = "";
		}
#line 2606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1139 "sintatica.y" /* yacc.c:1646  */
    {
			(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-1]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis;
			(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[0]).traducao;
			(yyval).tipo = (yyvsp[0]).tipo;
		}
#line 2616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1149 "sintatica.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2]).estruturaDoConteudo != constante_estrutura_tipoPrimitivo)
			{
				//dispara erro ...
			}
			//Regra TERMO possui produção que leva em ID, o que não pode.
			//constante_estrutura_variavel
			//$2.label.find(prefixo_variavel_usuario) == std::string::npos
			if( ((yyvsp[-2]).tipo == constante_tipo_inteiro || (yyvsp[-2]).tipo == constante_tipo_caracter) &&
				(yyvsp[-2]).estruturaDoConteudo == constante_estrutura_variavel){

				pair<string,int> tagCaseENumProx = gerarNovaTagSwitch(true);
				string proxCase = tag_case_inicio + to_string(tagCaseENumProx.second);

				//Para referenciar o inicio do teste da condição de cada case. Serve como controle para quando devemos executar
				//todos os cases quando algo for verdadeiro.
				pair<string,string> condicaoCase = gerarNovaTagCondicaoCase();
				string proxCondicaoCase = tag_condicao_case + condicaoCase.second;

				//Gerar primeira label que receberá o resultado da condição de igualdade.
				(yyval).label = gerarNovaVariavel();
				//Gerar segunda label que receberá a negação da condição de igualdade.
				string tempIrProxCondCase = gerarNovaVariavel();

				(yyval).traducaoDeclaracaoDeVariaveis = (yyvsp[-2]).traducaoDeclaracaoDeVariaveis + (yyvsp[0]).traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + (yyval).label + ";\n" +
													"\t" + constante_tipo_inteiro + " " + tempIrProxCondCase + ";\n";
				(yyval).tipo = (yyvsp[-2]).tipo;

				//Adicionar a tag do inicio do case antes do comando em si.
				(yyvsp[0]).traducao = "\t" + tagCaseENumProx.first + ":\n" + (yyvsp[0]).traducao +
													"\t" + "goto " + proxCase + ";\n";

				(yyval).traducao = "\t" + condicaoCase.first + ":\n" +
								(yyvsp[-2]).traducao + "\t" + (yyval).label + " = " + tarja_variavel + " == " + (yyvsp[-2]).label + ";\n" +
								"\t" + tempIrProxCondCase + " = " + "!" + (yyval).label + ";\n" +
								"\t" + "if" + "(" + tempIrProxCondCase + ")\n" +
								"\t\t" + "goto " + proxCondicaoCase + ";\n" +
								(yyvsp[0]).traducao; //+
								//"\t" + "goto " + proxCase + ":\n"; //+
								//"\t" + "goto " + tarja_tagFim + ";\n";
			}else{
				yyerror(MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO);
			}
		}
#line 2666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1197 "sintatica.y" /* yacc.c:1646  */
    {
						string salvadorDaPatria = "\t";
						if(!pilhaFimVazia()){
							(yyval).traducao = salvadorDaPatria + "goto " + obterTopoPilhaFim() + ";\n";
						}else{
							yyerror(MSG_ERRO_BREAK_NAO_PERMITIDO);
						}
					}
#line 2679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1207 "sintatica.y" /* yacc.c:1646  */
    {
						string salvadorDaPatria = "\t";
						if(!pilhaInicioVazia()){
							(yyval).traducao = salvadorDaPatria + "goto " + obterTopoPilhaInicio() + ";\n";
						}else{
							yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
						}
					}
#line 2692 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2696 "y.tab.c" /* yacc.c:1646  */
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
#line 1217 "sintatica.y" /* yacc.c:1906  */


#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL> tabelaDeVariaveis;
extern int yylineno; //Define a linha atual do arquivo fonte.

int yyparse();

int main( int argc, char* argv[] )
{
	conta = 0;
	mapaTipos = criarMapa();
	inicializarMapaDeContexto();
	//inicializarMapaDeStrings();
	//PARA O DEBUG
	//yydebug = 1;
	yyparse();



	return 0;
}

//TEMPORARIA!!!

string definicoesDeFuncoes()
{
	return "";
}


ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	//cout << "Entrou em exp arti\n";
	ATRIBUTOS dolarDolar;

	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);

	string label_old = dolarDolar.label;

	if(resultado == constante_erro)
	{
		string params[3] = {op,dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
		dolarDolar.tipo = constante_erro;
		return dolarDolar;
	}

	/*
	*TODO
	*Tratar conversão para tipo String
	*
	*/
	if(resultado == constante_tipo_string)
	{
		string varTamDolar1 = gerarNovaVariavel();
		string varTamDolar3 = gerarNovaVariavel();
		string varTamDolarDolar = gerarNovaVariavel();
		string traducao = realizarOperacaoAritmeticaString(op, &dolarDolar,&dolar1,&dolar3, varTamDolarDolar, varTamDolar1, varTamDolar3);

		if(traducao == "") //o operador ainda não está implementado. Fiz assim para não alterar no mapa, vou apagar o if
		{
			string params[3] = {op,dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
			dolarDolar.tipo = constante_erro;
			return dolarDolar;

		}

		dolarDolar.traducao = dolarDolar.traducao + traducao;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + realizarTraducaoDeclaracaoDeStringConcatenada(op, &dolarDolar, &dolar1,&dolar3, varTamDolarDolar, varTamDolar1, varTamDolar3);

	}

	else
	{
		if(dolar1.tipo == dolar3.tipo) //se não houver necessidade de conversão
		{
			//cout << "label0\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + dolar1.tipo + " " + dolarDolar.label + ";\n";
		}

		else if(dolar1.tipo != resultado)
		{
			//cout << "label1\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + label_old +  ";\n" + resultado + " " + dolarDolar.label +  ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + label_old + " " + op + " " + dolar3.label + ";\n";
		}
		else if(dolar3.tipo != resultado)
		{
			//cout << "label3\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar3.label + ";\n";
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + label_old +  ";\n" + resultado + " " + dolarDolar.label +  ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + label_old + ";\n";

		}

	}

	dolarDolar.tipo = resultado;
	return dolarDolar;
}

ATRIBUTOS tratarExpressaoAritmeticaComposta(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	string operadorSimples = removerSimboloIgualdade(op);
	dolarDolar = tratarExpressaoAritmetica(operadorSimples, dolar1, dolar3);
	dolarDolar.traducao += "\t" + dolar1.label +  " = " + dolarDolar.label + ";\n";
	return dolarDolar;

}

ATRIBUTOS tratarExpressaoLogicaUnaria(string op, ATRIBUTOS dolar2)
{
	ATRIBUTOS dolarDolar;
	if(dolar2.tipo == constante_tipo_booleano)
	{
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolar2.traducaoDeclaracaoDeVariaveis;
		string tipo = constante_tipo_inteiro;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolar2.traducao;
		dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + op + " "+ dolar2.label + ";\n";
		dolarDolar.tipo = constante_tipo_booleano;
		return dolarDolar;
	}else{
		yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
	}
}

ATRIBUTOS tratarExpressaoLogicaBinaria(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	if(dolar1.tipo == constante_tipo_booleano && dolar3.tipo == constante_tipo_booleano){
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(constante_tipo_booleano) + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
		dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
		dolarDolar.tipo = constante_tipo_booleano;
		return dolarDolar;
	}
	else{
		yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
	}
}

ATRIBUTOS tratarExpressaoLogicaComposta(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	string operadorSimples = removerSimboloIgualdade(op);
	dolarDolar = tratarExpressaoLogicaBinaria(operadorSimples, dolar1, dolar3);
	dolarDolar.traducao += "\t" + dolar1.label +  " = " + dolarDolar.label + ";\n";
	return dolarDolar;

}

ATRIBUTOS tratarExpressaoRelacional(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis += dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	/*dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t\t" + constante_tipo_inteiro + " " + dolarDolar.label + ";\n";*/

	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;

	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo,op);

	//string label_old = dolarDolar.label;
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(constante_tipo_booleano) + " " + dolarDolar.label + ";\n";
	string operador = op;

	//FIXME - remover a verificação de string daqui, após a implementação dessa operações corretamente.
	if(resultado == constante_erro || resultado == constante_tipo_string)
	{

		string params[3] = {op, dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
		dolarDolar.tipo = constante_erro;
		return dolarDolar;
	}

	if(dolar1.tipo == dolar3.tipo)
	{
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";

			//dolar1.label = dolarDolar.label;
			string novaVariavel = gerarNovaVariavel();

			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + novaVariavel + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + novaVariavel + " = " +"(" + resultado + ")" + dolar3.label + ";\n";
			dolar3.label = novaVariavel;
		}

	}

	else
	{
		string varConvert = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(resultado) + " " + varConvert + ";\n";

		if(dolar1.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + tipoCodigoIntermediario(resultado) + ")" + dolar1.label + ";\n";

			dolar1.label = varConvert;
		}

		else if(dolar3.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + tipoCodigoIntermediario(resultado) + ")" + dolar3.label + ";\n";
			dolar3.label = varConvert;

		}

	}

	dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label +" "+ op +" "+ dolar3.label + ";\n";

	dolarDolar.tipo = constante_tipo_booleano;


	return dolarDolar;

}



//TK_PALAVRA_VAR TK_ID ';'
ATRIBUTOS tratarDeclaracaoSemAtribuicao(ATRIBUTOS dolar2){

	ATRIBUTOS dolarDolar;

	if(variavelJaDeclarada(dolar2.label, false)){
		//mensagem de erro dupla declaração
		string params[1] = {dolar2.label};
		yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
	}

	else
	{
		incluirNoMapa(dolar2.label,0);
		dolarDolar.label = dolar2.label;
		dolarDolar.traducaoDeclaracaoDeVariaveis = construirDeclaracaoProvisoriaDeInferenciaDeTipo(dolar2.label);
	}

	return dolarDolar;

}

//TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
ATRIBUTOS tratarDeclaracaoComAtribuicao(ATRIBUTOS dolar2, ATRIBUTOS dolar4)
{
	ATRIBUTOS dolarDolar;

	if(variavelJaDeclarada(dolar2.label, false))
	{
		//mensagem de erro dupla declaração
		string params[1] = {dolar2.label};
		yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
	}
	else //Você cria a variável e inclui no mapaDeContexto.
	{
		//cout << "Entrou no else: \n\n\n";
		int tamanho = 0;
		incluirNoMapa(dolar2.label,dolar4.tamanho, dolar4.tipo);
		string tipo = dolar4.tipo;
		string label = recuperarNomeTraducao(dolar2.label);

		//meramente para leitura do código intermediário
		string labelPrefix = prefixo_variavel_usuario;
		labelPrefix = labelPrefix + dolar2.label;


		if(tipo == constante_tipo_booleano)
			tipo = constante_tipo_inteiro;

		if(tipo == constante_tipo_string)
		{
			if(dolar4.ehDinamica)
			{
				tipo = constante_tipo_caracter;
					dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " * " + label+ "; //" + labelPrefix + "\n";

					//TENTATIVA ATRIBUICAO COM MALLOC
					dolarDolar.traducao = dolar4.traducao + "\t" + label +" = (char*) malloc(sizeof(" + dolar4.label + "));\n\t" + montarCopiarString(label, dolar4.label) + ";\n";

					//TENTATIVA ATRIBUINDO PONTEIRO
					//dolarDolar.traducao = dolar4.traducao + "\t" + label +" = "+ dolar4.label + "; //" + labelPrefix + "\n";

			}
			else
			{
				tipo = constante_tipo_caracter;
				dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " " + label + "[" + to_string(dolar4.tamanho) + "]; //" + labelPrefix + "\n";
				dolarDolar.traducao = dolar4.traducao + montarCopiarString(label, dolar4.label) + ";\n";

			}

		}

		else
		{
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " " + label + "; //" + labelPrefix + "\n";
			dolarDolar.traducao = dolar4.traducao + "\t" + label + " = " + dolar4.label + ";\n";
		}

		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis;
		dolarDolar.label = label;
		dolarDolar.tipo = dolar4.tipo;
		dolarDolar.ehDinamica = dolar4.ehDinamica;
		dolarDolar.tamanho = dolar4.tamanho;
	}


	return dolarDolar;

}

//ID '=' VALOR_ATRIBUICAO ';'
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS dolar1, ATRIBUTOS dolar3, bool ehDinamica)
{
	ATRIBUTOS dolarDolar;
	string tipo = "";
	int tamanho = 0;
	string labelRecuperada = recuperarNomeTraducao(dolar1.label);

	//bool ehDinamica = false;
	/*std::cout << "sin dolar1.ehDinamica:" << dolar1.ehDinamica << '\n';
	std::cout << "sin dolar3.ehDinamica:" << dolar3.ehDinamica << '\n';
	std::cout << "sin ehDinamica:" << ehDinamica << '\n';*/

	if(dolar1.label != dolar3.label)
	{
		DADOS_VARIAVEL metaData;
		if(dolar1.escopoDeAcesso >= 0){
			metaData = recuperarDadosVariavel(dolar1.label, dolar1.escopoDeAcesso);
		}
		else{
			metaData = recuperarDadosVariavel(dolar1.label);
		}

		if(metaData.tipo == "")
		{
			//isso aqui também pode causar problema no futuro devido as lacunas
			metaData.tipo = dolar3.tipo;
			//atualizarNoMapa(metaData);
			tipo = metaData.tipo;
			if(tipo == constante_tipo_booleano)
			{
				tipo = constante_tipo_inteiro;
				tipo = "\t" + tipo;
			}

			if(tipo == constante_tipo_string)
			{
				metaData.tamanho = dolar3.tamanho;
			}

			metaData.ehDinamica = ehDinamica;
			if(dolar1.escopoDeAcesso >= 0){
				adicionarDefinicaoDeTipo(dolar1.label, tipo, dolar3.tamanho,ehDinamica, dolar1.escopoDeAcesso);
				atualizarNoMapa(metaData, dolar1.escopoDeAcesso);
			}
			else{
				adicionarDefinicaoDeTipo(dolar1.label, tipo,dolar3.tamanho,ehDinamica);
				atualizarNoMapa(metaData);
			}

			dolar1.tipo = dolar3.tipo;
		}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
		if(dolar1.tipo == dolar3.tipo)
		{
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar3.traducaoDeclaracaoDeVariaveis;

			if(dolar3.tipo == constante_tipo_string)
				dolarDolar.traducao = dolar3.traducao + montarCopiarString(labelRecuperada, dolar3.label) + ";\n";
			else
				dolarDolar.traducao = dolar3.traducao + "\t" + labelRecuperada + " = " + dolar3.label + ";\n";
		}
		else
		{

			string strPrefixoVarUsuario = prefixo_variavel_usuario;
			string labelVar = dolar1.label;
			//para remover o prefixo só se tiver prefixo
			if(dolar1.label.find(strPrefixoVarUsuario) == 0)
				labelVar = dolar1.label.replace(0, strPrefixoVarUsuario.length(), "");

			string params[3] = {labelVar, dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
		}

		dolarDolar.label = dolar1.label;
		dolarDolar.tipo = dolar1.tipo;
		dolarDolar.tamanho = dolar3.tamanho;
		dolarDolar.ehDinamica = ehDinamica;
		dolarDolar.escopoDeAcesso = dolar1.escopoDeAcesso;

	}
	else
	{
		dolarDolar = dolar3;
	}


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
