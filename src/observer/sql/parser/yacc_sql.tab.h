/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    SELECT = 264,                  /* SELECT  */
    DESC = 265,                    /* DESC  */
    SHOW = 266,                    /* SHOW  */
    SYNC = 267,                    /* SYNC  */
    INSERT = 268,                  /* INSERT  */
    DELETE = 269,                  /* DELETE  */
    UPDATE = 270,                  /* UPDATE  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    COMMA = 273,                   /* COMMA  */
    TRX_BEGIN = 274,               /* TRX_BEGIN  */
    TRX_COMMIT = 275,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 276,            /* TRX_ROLLBACK  */
    INT_T = 277,                   /* INT_T  */
    STRING_T = 278,                /* STRING_T  */
    FLOAT_T = 279,                 /* FLOAT_T  */
    DATE_T = 280,                  /* DATE_T  */
    TEXT_T = 281,                  /* TEXT_T  */
    HELP = 282,                    /* HELP  */
    EXIT = 283,                    /* EXIT  */
    DOT = 284,                     /* DOT  */
    INTO = 285,                    /* INTO  */
    VALUES = 286,                  /* VALUES  */
    FROM = 287,                    /* FROM  */
    WHERE = 288,                   /* WHERE  */
    AND = 289,                     /* AND  */
    SET = 290,                     /* SET  */
    ON = 291,                      /* ON  */
    LOAD = 292,                    /* LOAD  */
    DATA = 293,                    /* DATA  */
    INFILE = 294,                  /* INFILE  */
    EQ = 295,                      /* EQ  */
    LT = 296,                      /* LT  */
    GT = 297,                      /* GT  */
    LE = 298,                      /* LE  */
    GE = 299,                      /* GE  */
    NE = 300,                      /* NE  */
    MAX = 301,                     /* MAX  */
    MIN = 302,                     /* MIN  */
    COUNT = 303,                   /* COUNT  */
    AVG = 304,                     /* AVG  */
    INNER = 305,                   /* INNER  */
    JOIN = 306,                    /* JOIN  */
    UNIQUE = 307,                  /* UNIQUE  */
    ORDER = 308,                   /* ORDER  */
    BY = 309,                      /* BY  */
    ASC = 310,                     /* ASC  */
    GROUP = 311,                   /* GROUP  */
    NOT = 312,                     /* NOT  */
    NULL_T = 313,                  /* NULL_T  */
    NULLABLE_T = 314,              /* NULLABLE_T  */
    IS = 315,                      /* IS  */
    IN = 316,                      /* IN  */
    NUMBER = 317,                  /* NUMBER  */
    FLOAT = 318,                   /* FLOAT  */
    ID = 319,                      /* ID  */
    PATH = 320,                    /* PATH  */
    SSS = 321,                     /* SSS  */
    STAR = 322,                    /* STAR  */
    STRING_V = 323                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 135 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 142 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
