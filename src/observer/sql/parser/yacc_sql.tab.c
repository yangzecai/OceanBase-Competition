/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t id_list_length;
  size_t tuple_num;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  char *id_list[MAX_NUM];
  AggregateType aggregate_type;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->id_list_length = 0;
  context->tuple_num = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 134 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_ON = 35,                        /* ON  */
  YYSYMBOL_LOAD = 36,                      /* LOAD  */
  YYSYMBOL_DATA = 37,                      /* DATA  */
  YYSYMBOL_INFILE = 38,                    /* INFILE  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_MAX = 45,                       /* MAX  */
  YYSYMBOL_MIN = 46,                       /* MIN  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_AVG = 48,                       /* AVG  */
  YYSYMBOL_INNER = 49,                     /* INNER  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_UNIQUE = 51,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 52,                     /* ORDER  */
  YYSYMBOL_BY = 53,                        /* BY  */
  YYSYMBOL_ASC = 54,                       /* ASC  */
  YYSYMBOL_GROUP = 55,                     /* GROUP  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_NULL_T = 57,                    /* NULL_T  */
  YYSYMBOL_NULLABLE_T = 58,                /* NULLABLE_T  */
  YYSYMBOL_IS = 59,                        /* IS  */
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 61,                     /* FLOAT  */
  YYSYMBOL_ID = 62,                        /* ID  */
  YYSYMBOL_PATH = 63,                      /* PATH  */
  YYSYMBOL_SSS = 64,                       /* SSS  */
  YYSYMBOL_STAR = 65,                      /* STAR  */
  YYSYMBOL_STRING_V = 66,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_commands = 68,                  /* commands  */
  YYSYMBOL_command = 69,                   /* command  */
  YYSYMBOL_exit = 70,                      /* exit  */
  YYSYMBOL_help = 71,                      /* help  */
  YYSYMBOL_sync = 72,                      /* sync  */
  YYSYMBOL_begin = 73,                     /* begin  */
  YYSYMBOL_commit = 74,                    /* commit  */
  YYSYMBOL_rollback = 75,                  /* rollback  */
  YYSYMBOL_drop_table = 76,                /* drop_table  */
  YYSYMBOL_show_tables = 77,               /* show_tables  */
  YYSYMBOL_desc_table = 78,                /* desc_table  */
  YYSYMBOL_create_index = 79,              /* create_index  */
  YYSYMBOL_unique_index = 80,              /* unique_index  */
  YYSYMBOL_id_list = 81,                   /* id_list  */
  YYSYMBOL_drop_index = 82,                /* drop_index  */
  YYSYMBOL_create_table = 83,              /* create_table  */
  YYSYMBOL_attr_def_list = 84,             /* attr_def_list  */
  YYSYMBOL_attr_def = 85,                  /* attr_def  */
  YYSYMBOL_number = 86,                    /* number  */
  YYSYMBOL_type = 87,                      /* type  */
  YYSYMBOL_ID_get = 88,                    /* ID_get  */
  YYSYMBOL_null_type = 89,                 /* null_type  */
  YYSYMBOL_insert = 90,                    /* insert  */
  YYSYMBOL_value_tuple = 91,               /* value_tuple  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_value = 93,                     /* value  */
  YYSYMBOL_delete = 94,                    /* delete  */
  YYSYMBOL_update = 95,                    /* update  */
  YYSYMBOL_select = 96,                    /* select  */
  YYSYMBOL_select_attr = 97,               /* select_attr  */
  YYSYMBOL_attribute = 98,                 /* attribute  */
  YYSYMBOL_aggregate = 99,                 /* aggregate  */
  YYSYMBOL_attr_list = 100,                /* attr_list  */
  YYSYMBOL_agg_type = 101,                 /* agg_type  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 103,          /* inner_join_list  */
  YYSYMBOL_where = 104,                    /* where  */
  YYSYMBOL_condition_list = 105,           /* condition_list  */
  YYSYMBOL_condition = 106,                /* condition  */
  YYSYMBOL_comOp = 107,                    /* comOp  */
  YYSYMBOL_order = 108,                    /* order  */
  YYSYMBOL_order_attribute = 109,          /* order_attribute  */
  YYSYMBOL_order_list = 110,               /* order_list  */
  YYSYMBOL_group = 111,                    /* group  */
  YYSYMBOL_group_attribute = 112,          /* group_attribute  */
  YYSYMBOL_group_list = 113,               /* group_list  */
  YYSYMBOL_load_data = 114                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  234

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   155,   155,   157,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   181,   186,   191,   197,   203,   209,   215,   221,   227,
     234,   244,   247,   252,   254,   261,   268,   278,   280,   284,
     291,   300,   303,   304,   305,   306,   309,   316,   317,   318,
     322,   339,   341,   345,   347,   352,   355,   358,   362,   368,
     378,   388,   407,   412,   415,   420,   425,   430,   437,   444,
     451,   457,   465,   467,   470,   475,   476,   477,   478,   480,
     482,   486,   488,   492,   494,   498,   500,   505,   526,   546,
     566,   588,   609,   630,   652,   653,   654,   655,   656,   657,
     658,   659,   661,   663,   667,   674,   681,   688,   695,   702,
     710,   712,   715,   717,   721,   726,   732,   734,   738
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "MAX", "MIN", "COUNT", "AVG", "INNER", "JOIN", "UNIQUE", "ORDER", "BY",
  "ASC", "GROUP", "NOT", "NULL_T", "NULLABLE_T", "IS", "NUMBER", "FLOAT",
  "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "unique_index", "id_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "null_type", "insert",
  "value_tuple", "value_list", "value", "delete", "update", "select",
  "select_attr", "attribute", "aggregate", "attr_list", "agg_type",
  "rel_list", "inner_join_list", "where", "condition_list", "condition",
  "comOp", "order", "order_attribute", "order_list", "group",
  "group_attribute", "group_list", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
#endif

#define YYPACT_NINF (-174)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -174,    61,  -174,    -5,    19,    44,   -32,    31,    36,    12,
      22,     0,    52,    60,    64,    74,    75,    27,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,    17,  -174,    76,    21,
      24,  -174,  -174,  -174,  -174,    71,  -174,    73,    82,    82,
     106,   125,   131,  -174,    77,    78,   101,  -174,  -174,  -174,
    -174,  -174,    98,   121,    79,   135,   139,   -45,    81,    48,
    -174,  -174,    51,  -174,  -174,   114,   113,    84,    83,    86,
     115,  -174,  -174,  -174,  -174,   133,    82,    82,  -174,  -174,
    -174,     1,  -174,   132,   136,   138,    41,   149,   116,   127,
    -174,   140,    35,    95,    97,   111,  -174,  -174,  -174,    99,
    -174,  -174,   -38,    -7,   -31,   129,  -174,   -38,   157,    86,
     147,  -174,  -174,  -174,  -174,    -2,   150,   133,   117,   113,
     148,   151,   108,  -174,  -174,  -174,  -174,  -174,  -174,   112,
      57,    63,    41,  -174,   113,   109,   140,   169,   118,   119,
    -174,  -174,   120,  -174,   122,   123,  -174,   -38,   156,   -31,
    -174,  -174,  -174,   146,  -174,   129,   174,   176,  -174,  -174,
    -174,   163,  -174,   165,   152,   128,   130,   151,   168,    69,
     126,  -174,  -174,  -174,  -174,   134,   172,    41,   137,   141,
     187,  -174,   175,   189,   167,  -174,  -174,   165,   190,   129,
      -4,   179,   142,  -174,   -38,  -174,   143,  -174,  -174,   111,
    -174,   144,  -174,   137,  -174,   170,   182,   151,  -174,  -174,
      -3,   179,   145,   142,  -174,   184,  -174,  -174,  -174,  -174,
     182,   168,  -174,  -174
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,    32,     0,     0,
       0,    75,    76,    77,    78,    65,    62,     0,    72,    72,
       0,     0,     0,    23,     0,     0,     0,    24,    25,    26,
      22,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    64,     0,    29,    28,     0,    83,     0,     0,     0,
       0,    27,    35,    66,    67,    79,    72,    72,    58,    55,
      56,     0,    57,     0,     0,     0,     0,     0,     0,     0,
      46,    37,     0,     0,     0,    81,    73,    74,    68,     0,
      71,    70,     0,     0,     0,    85,    59,     0,     0,     0,
       0,    42,    43,    44,    45,    47,     0,    79,     0,    83,
       0,    53,     0,    94,    95,    96,    97,    98,    99,   100,
       0,     0,     0,    84,    83,     0,    37,     0,     0,     0,
      48,    40,     0,    80,     0,   102,    69,     0,     0,     0,
     101,    89,    87,    90,    88,    85,     0,     0,    38,    36,
      41,     0,    49,    33,     0,     0,   112,    53,    51,     0,
       0,    86,    60,   118,    39,     0,     0,     0,     0,     0,
       0,    54,     0,     0,     0,    91,    92,    33,     0,    85,
     104,   110,     0,    61,     0,    50,     0,    34,    30,    81,
     108,     0,   106,     0,   103,   114,   116,    53,    93,    82,
     105,   110,     0,     0,   113,     0,   109,   107,   111,   115,
     116,    51,   117,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,     5,  -174,  -174,    62,    90,  -174,
    -174,  -174,  -174,  -174,   -28,  -173,   -72,  -174,  -174,  -174,
    -174,   153,   154,   -44,  -174,    85,     2,  -113,  -150,  -140,
    -111,  -174,     3,   -11,  -174,   -10,   -16,  -174
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    38,   186,    29,    30,   120,   101,   171,
     125,   102,   151,    31,   193,   158,   114,    32,    33,    34,
      47,    48,    49,    70,    50,   105,   129,    97,   143,   115,
     140,   176,   201,   214,   190,   216,   224,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      94,    36,   165,   141,   191,    71,   210,   226,   133,   134,
     135,   136,   137,   138,   148,   181,   155,    83,   108,    88,
      84,   132,    89,    90,   211,    39,    92,    40,   139,   109,
      51,   166,   133,   134,   135,   136,   137,   138,    52,    53,
     131,    54,   106,   107,   225,   144,    37,   199,   179,   209,
     212,   227,   139,    55,   149,    57,   150,   121,   122,   123,
     124,     2,    56,    58,    62,     3,     4,    59,   162,   164,
       5,     6,     7,     8,     9,    10,    11,    60,    61,    63,
      12,    13,    14,    65,    64,   177,    66,    15,    16,    41,
      42,    43,    44,    41,    42,    43,    44,    17,    88,    67,
      69,    89,    90,   113,    68,    92,    45,   195,    88,    46,
      45,    89,    90,    91,    88,    92,    93,    89,    90,   161,
      88,    92,    72,    89,    90,   163,    88,    92,    73,    89,
      90,   194,   217,    92,    74,    77,    78,    79,    81,    75,
      76,    80,    82,    85,    95,    96,    98,    99,   100,   110,
     103,   104,   116,   111,   112,   117,   118,   126,   119,   127,
     128,   130,   142,   145,   147,   156,   152,   154,   160,   157,
     159,   167,   169,   178,   180,   175,   172,   182,   170,   183,
     184,   188,   173,   185,   174,   189,   192,   187,   196,   198,
     203,   204,   205,   208,   202,   206,   197,   213,   222,   200,
     223,   231,   207,   233,   215,   218,   220,   229,   168,   146,
     228,   219,   153,   230,   232,     0,   221,     0,     0,     0,
       0,     0,    86,    87
};

static const yytype_int16 yycheck[] =
{
      72,     6,   142,   114,   177,    49,    10,    10,    39,    40,
      41,    42,    43,    44,    16,   165,   129,    62,    17,    57,
      65,    28,    60,    61,    28,     6,    64,     8,    59,    28,
      62,   144,    39,    40,    41,    42,    43,    44,     7,     3,
     112,    29,    86,    87,   217,   117,    51,   187,   159,   199,
      54,    54,    59,    31,    56,     3,    58,    22,    23,    24,
      25,     0,    62,     3,    37,     4,     5,     3,   140,   141,
       9,    10,    11,    12,    13,    14,    15,     3,     3,    62,
      19,    20,    21,    62,     8,   157,    62,    26,    27,    45,
      46,    47,    48,    45,    46,    47,    48,    36,    57,    28,
      18,    60,    61,    62,    31,    64,    62,   179,    57,    65,
      62,    60,    61,    62,    57,    64,    65,    60,    61,    62,
      57,    64,    16,    60,    61,    62,    57,    64,     3,    60,
      61,    62,   204,    64,     3,    34,    38,    16,     3,    62,
      62,    62,     3,    62,    30,    32,    62,    64,    62,    17,
      35,    18,     3,    17,    16,    39,    29,    62,    18,    62,
      49,    62,    33,     6,    17,    17,    16,    50,    56,    18,
      62,    62,     3,    17,    28,    52,    57,     3,    60,     3,
      17,    53,    62,    18,    62,    55,    18,    35,    62,    17,
       3,    16,     3,     3,    53,    28,    62,    18,    28,    62,
      18,    17,   197,   231,    62,    62,    62,    62,   146,   119,
     221,   209,   127,   223,   230,    -1,   213,    -1,    -1,    -1,
      -1,    -1,    69,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    82,
      83,    90,    94,    95,    96,   114,     6,    51,    80,     6,
       8,    45,    46,    47,    48,    62,    65,    97,    98,    99,
     101,    62,     7,     3,    29,    31,    62,     3,     3,     3,
       3,     3,    37,    62,     8,    62,    62,    28,    31,    18,
     100,   100,    16,     3,     3,    62,    62,    34,    38,    16,
      62,     3,     3,    62,    65,    62,    98,    99,    57,    60,
      61,    62,    64,    65,    93,    30,    32,   104,    62,    64,
      62,    85,    88,    35,    18,   102,   100,   100,    17,    28,
      17,    17,    16,    62,    93,   106,     3,    39,    29,    18,
      84,    22,    23,    24,    25,    87,    62,    62,    49,   103,
      62,    93,    28,    39,    40,    41,    42,    43,    44,    59,
     107,   107,    33,   105,    93,     6,    85,    17,    16,    56,
      58,    89,    16,   102,    50,   104,    17,    18,    92,    62,
      56,    62,    93,    62,    93,   106,   104,    62,    84,     3,
      60,    86,    57,    62,    62,    52,   108,    93,    17,   107,
      28,   105,     3,     3,    17,    18,    81,    35,    53,    55,
     111,    92,    18,    91,    62,    93,    62,    62,    17,   106,
      62,   109,    53,     3,    16,     3,    28,    81,     3,   105,
      10,    28,    54,    18,   110,    62,   112,    93,    62,   103,
      62,   109,    28,    18,   113,    92,    10,    54,   110,    62,
     112,    17,   113,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    80,    81,    81,    82,    83,    84,    84,    85,
      85,    86,    87,    87,    87,    87,    88,    89,    89,    89,
      90,    91,    91,    92,    92,    93,    93,    93,    93,    94,
      95,    96,    97,    97,    97,    98,    98,    98,    99,    99,
      99,    99,   100,   100,   100,   101,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      11,     0,     1,     0,     3,     4,     8,     0,     3,     5,
       3,     1,     1,     1,     1,     1,     1,     0,     1,     2,
      10,     0,     6,     0,     3,     1,     1,     1,     1,     5,
       8,    10,     1,     2,     2,     1,     3,     3,     4,     6,
       4,     4,     0,     3,     3,     1,     1,     1,     1,     0,
       3,     0,     7,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     4,     1,     3,     2,     4,     2,     4,
       0,     3,     0,     4,     1,     3,     0,     3,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 21: /* exit: EXIT SEMICOLON  */
#line 181 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1409 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 186 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1417 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 191 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1425 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 197 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1433 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 203 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 209 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1449 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 215 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1458 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 221 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1466 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 227 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE unique_index INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 235 "yacc_sql.y"
                {
            CONTEXT->id_list[0] = (yyvsp[-3].string);
            CONTEXT->id_list_length++;
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->id_list, CONTEXT->id_list_length);
			CONTEXT->id_list_length = 0;
		}
#line 1486 "yacc_sql.tab.c"
    break;

  case 31: /* unique_index: %empty  */
#line 244 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
        }
#line 1494 "yacc_sql.tab.c"
    break;

  case 32: /* unique_index: UNIQUE  */
#line 248 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;//"create_unique_index";
        }
#line 1502 "yacc_sql.tab.c"
    break;

  case 34: /* id_list: COMMA ID id_list  */
#line 254 "yacc_sql.y"
                        {
            CONTEXT->id_list_length++;
            CONTEXT->id_list[CONTEXT->id_list_length] = (yyvsp[-1].string);
	  }
#line 1511 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 262 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1520 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 269 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
		}
#line 1533 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 280 "yacc_sql.y"
                                   {    }
#line 1539 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 285 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), NOT_NULL);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1550 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_type  */
#line 292 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1561 "yacc_sql.tab.c"
    break;

  case 41: /* number: NUMBER  */
#line 300 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1567 "yacc_sql.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 303 "yacc_sql.y"
          { (yyval.number)=INTS; }
#line 1573 "yacc_sql.tab.c"
    break;

  case 43: /* type: STRING_T  */
#line 304 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 1579 "yacc_sql.tab.c"
    break;

  case 44: /* type: FLOAT_T  */
#line 305 "yacc_sql.y"
              { (yyval.number)=FLOATS; }
#line 1585 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 306 "yacc_sql.y"
             { (yyval.number)=DATES; }
#line 1591 "yacc_sql.tab.c"
    break;

  case 46: /* ID_get: ID  */
#line 310 "yacc_sql.y"
    {
      char *temp=(yyvsp[0].string); 
      snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1600 "yacc_sql.tab.c"
    break;

  case 47: /* null_type: %empty  */
#line 316 "yacc_sql.y"
                { (yyval.number)=NOT_NULL; }
#line 1606 "yacc_sql.tab.c"
    break;

  case 48: /* null_type: NULLABLE_T  */
#line 317 "yacc_sql.y"
                 { (yyval.number)=NULLABLE; }
#line 1612 "yacc_sql.tab.c"
    break;

  case 49: /* null_type: NOT NULL_T  */
#line 318 "yacc_sql.y"
                 { (yyval.number)=NOT_NULL; }
#line 1618 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_tuple SEMICOLON  */
#line 323 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			CONTEXT->tuple_num++;
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length, CONTEXT->tuple_num);

      //临时变量清零
      CONTEXT->value_length=0;
      CONTEXT->tuple_num=0;
    }
#line 1639 "yacc_sql.tab.c"
    break;

  case 52: /* value_tuple: COMMA LBRACE value value_list RBRACE value_tuple  */
#line 341 "yacc_sql.y"
                                                       {
        CONTEXT->tuple_num++;
	  }
#line 1647 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 347 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1655 "yacc_sql.tab.c"
    break;

  case 55: /* value: NUMBER  */
#line 352 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1663 "yacc_sql.tab.c"
    break;

  case 56: /* value: FLOAT  */
#line 355 "yacc_sql.y"
            {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1671 "yacc_sql.tab.c"
    break;

  case 57: /* value: SSS  */
#line 358 "yacc_sql.y"
          {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1680 "yacc_sql.tab.c"
    break;

  case 58: /* value: NULL_T  */
#line 362 "yacc_sql.y"
             {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1688 "yacc_sql.tab.c"
    break;

  case 59: /* delete: DELETE FROM ID where SEMICOLON  */
#line 369 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1700 "yacc_sql.tab.c"
    break;

  case 60: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 379 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1712 "yacc_sql.tab.c"
    break;

  case 61: /* select: SELECT select_attr FROM ID rel_list inner_join_list where order group SEMICOLON  */
#line 389 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
    }
#line 1732 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: STAR  */
#line 407 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1742 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: attribute attr_list  */
#line 412 "yacc_sql.y"
                          {

    }
#line 1750 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: aggregate attr_list  */
#line 415 "yacc_sql.y"
                          {

    }
#line 1758 "yacc_sql.tab.c"
    break;

  case 65: /* attribute: ID  */
#line 420 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1768 "yacc_sql.tab.c"
    break;

  case 66: /* attribute: ID DOT ID  */
#line 425 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1778 "yacc_sql.tab.c"
    break;

  case 67: /* attribute: ID DOT STAR  */
#line 430 "yacc_sql.y"
                  {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), "*");
      selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1788 "yacc_sql.tab.c"
    break;

  case 68: /* aggregate: agg_type LBRACE ID RBRACE  */
#line 437 "yacc_sql.y"
                              {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Aggregate aggregate;
      aggregate_init(&aggregate, CONTEXT->aggregate_type, 1, &attr, NULL);
			selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggregate);
    }
#line 1800 "yacc_sql.tab.c"
    break;

  case 69: /* aggregate: agg_type LBRACE ID DOT ID RBRACE  */
#line 444 "yacc_sql.y"
                                       {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Aggregate aggregate;
      aggregate_init(&aggregate, CONTEXT->aggregate_type, 1, &attr, NULL);
			selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggregate);
    }
#line 1812 "yacc_sql.tab.c"
    break;

  case 70: /* aggregate: agg_type LBRACE value RBRACE  */
#line 451 "yacc_sql.y"
                                   {
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, CONTEXT->aggregate_type, 0, NULL, value);
			selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggregate);
    }
#line 1823 "yacc_sql.tab.c"
    break;

  case 71: /* aggregate: agg_type LBRACE STAR RBRACE  */
#line 457 "yacc_sql.y"
                                  {
      value_init_string(&CONTEXT->values[CONTEXT->value_length++], "*");
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, CONTEXT->aggregate_type, 0, NULL, value);
			selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggregate);
    }
#line 1835 "yacc_sql.tab.c"
    break;

  case 73: /* attr_list: COMMA attribute attr_list  */
#line 467 "yacc_sql.y"
                                {

    }
#line 1843 "yacc_sql.tab.c"
    break;

  case 74: /* attr_list: COMMA aggregate attr_list  */
#line 470 "yacc_sql.y"
                                {

    }
#line 1851 "yacc_sql.tab.c"
    break;

  case 75: /* agg_type: MAX  */
#line 475 "yacc_sql.y"
              { CONTEXT->aggregate_type = AGG_MAX; }
#line 1857 "yacc_sql.tab.c"
    break;

  case 76: /* agg_type: MIN  */
#line 476 "yacc_sql.y"
          { CONTEXT->aggregate_type = AGG_MIN; }
#line 1863 "yacc_sql.tab.c"
    break;

  case 77: /* agg_type: COUNT  */
#line 477 "yacc_sql.y"
            { CONTEXT->aggregate_type = AGG_COUNT; }
#line 1869 "yacc_sql.tab.c"
    break;

  case 78: /* agg_type: AVG  */
#line 478 "yacc_sql.y"
          { CONTEXT->aggregate_type = AGG_AVG; }
#line 1875 "yacc_sql.tab.c"
    break;

  case 80: /* rel_list: COMMA ID rel_list  */
#line 482 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		}
#line 1883 "yacc_sql.tab.c"
    break;

  case 82: /* inner_join_list: INNER JOIN ID ON condition condition_list inner_join_list  */
#line 488 "yacc_sql.y"
                                                               {
      selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
    }
#line 1891 "yacc_sql.tab.c"
    break;

  case 84: /* where: WHERE condition condition_list  */
#line 494 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1899 "yacc_sql.tab.c"
    break;

  case 86: /* condition_list: AND condition condition_list  */
#line 500 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1907 "yacc_sql.tab.c"
    break;

  case 87: /* condition: ID comOp value  */
#line 506 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 88: /* condition: value comOp value  */
#line 527 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1956 "yacc_sql.tab.c"
    break;

  case 89: /* condition: ID comOp ID  */
#line 547 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 1980 "yacc_sql.tab.c"
    break;

  case 90: /* condition: value comOp ID  */
#line 567 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2006 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID DOT ID comOp value  */
#line 589 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2031 "yacc_sql.tab.c"
    break;

  case 92: /* condition: value comOp ID DOT ID  */
#line 610 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2056 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID DOT ID comOp ID DOT ID  */
#line 631 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2079 "yacc_sql.tab.c"
    break;

  case 94: /* comOp: EQ  */
#line 652 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2085 "yacc_sql.tab.c"
    break;

  case 95: /* comOp: LT  */
#line 653 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2091 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: GT  */
#line 654 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2097 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: LE  */
#line 655 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2103 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: GE  */
#line 656 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2109 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: NE  */
#line 657 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2115 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: IS  */
#line 658 "yacc_sql.y"
         { CONTEXT->comp = IS_NULL; }
#line 2121 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: IS NOT  */
#line 659 "yacc_sql.y"
             { CONTEXT->comp = IS_NOT_NULL; }
#line 2127 "yacc_sql.tab.c"
    break;

  case 103: /* order: ORDER BY order_attribute order_list  */
#line 663 "yacc_sql.y"
                                          {
    }
#line 2134 "yacc_sql.tab.c"
    break;

  case 104: /* order_attribute: ID  */
#line 667 "yacc_sql.y"
       {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2146 "yacc_sql.tab.c"
    break;

  case 105: /* order_attribute: ID DOT ID  */
#line 674 "yacc_sql.y"
                {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2158 "yacc_sql.tab.c"
    break;

  case 106: /* order_attribute: ID ASC  */
#line 681 "yacc_sql.y"
             {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2170 "yacc_sql.tab.c"
    break;

  case 107: /* order_attribute: ID DOT ID ASC  */
#line 688 "yacc_sql.y"
                    {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2182 "yacc_sql.tab.c"
    break;

  case 108: /* order_attribute: ID DESC  */
#line 695 "yacc_sql.y"
              {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2194 "yacc_sql.tab.c"
    break;

  case 109: /* order_attribute: ID DOT ID DESC  */
#line 702 "yacc_sql.y"
                     {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
    }
#line 2206 "yacc_sql.tab.c"
    break;

  case 111: /* order_list: COMMA order_attribute order_list  */
#line 712 "yacc_sql.y"
                                       {
    }
#line 2213 "yacc_sql.tab.c"
    break;

  case 113: /* group: GROUP BY group_attribute group_list  */
#line 717 "yacc_sql.y"
                                          {
    }
#line 2220 "yacc_sql.tab.c"
    break;

  case 114: /* group_attribute: ID  */
#line 721 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_group(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2230 "yacc_sql.tab.c"
    break;

  case 115: /* group_attribute: ID DOT ID  */
#line 726 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_group(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2240 "yacc_sql.tab.c"
    break;

  case 117: /* group_list: COMMA group_attribute group_list  */
#line 734 "yacc_sql.y"
                                       {
    }
#line 2247 "yacc_sql.tab.c"
    break;

  case 118: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 739 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2256 "yacc_sql.tab.c"
    break;


#line 2260 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 744 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
