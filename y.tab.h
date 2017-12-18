/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
