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

// int yydebug = 1;

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
  size_t string_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  char *id_list[MAX_NUM];
  SelectFrame select_frame[QUERY_NUM];
  int select_frame_index;
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
  context->string_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 139 "yacc_sql.tab.c"

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
  YYSYMBOL_TEXT_T = 26,                    /* TEXT_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_MAX = 46,                       /* MAX  */
  YYSYMBOL_MIN = 47,                       /* MIN  */
  YYSYMBOL_COUNT = 48,                     /* COUNT  */
  YYSYMBOL_AVG = 49,                       /* AVG  */
  YYSYMBOL_INNER = 50,                     /* INNER  */
  YYSYMBOL_JOIN = 51,                      /* JOIN  */
  YYSYMBOL_UNIQUE = 52,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 53,                     /* ORDER  */
  YYSYMBOL_BY = 54,                        /* BY  */
  YYSYMBOL_ASC = 55,                       /* ASC  */
  YYSYMBOL_GROUP = 56,                     /* GROUP  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_NULL_T = 58,                    /* NULL_T  */
  YYSYMBOL_NULLABLE_T = 59,                /* NULLABLE_T  */
  YYSYMBOL_IS = 60,                        /* IS  */
  YYSYMBOL_IN = 61,                        /* IN  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_PATH = 65,                      /* PATH  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_STAR = 67,                      /* STAR  */
  YYSYMBOL_STRING_V = 68,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_commands = 70,                  /* commands  */
  YYSYMBOL_command = 71,                   /* command  */
  YYSYMBOL_exit = 72,                      /* exit  */
  YYSYMBOL_help = 73,                      /* help  */
  YYSYMBOL_sync = 74,                      /* sync  */
  YYSYMBOL_begin = 75,                     /* begin  */
  YYSYMBOL_commit = 76,                    /* commit  */
  YYSYMBOL_rollback = 77,                  /* rollback  */
  YYSYMBOL_drop_table = 78,                /* drop_table  */
  YYSYMBOL_show_tables = 79,               /* show_tables  */
  YYSYMBOL_desc_table = 80,                /* desc_table  */
  YYSYMBOL_create_index = 81,              /* create_index  */
  YYSYMBOL_unique_index = 82,              /* unique_index  */
  YYSYMBOL_id_list = 83,                   /* id_list  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_create_table = 85,              /* create_table  */
  YYSYMBOL_attr_def_list = 86,             /* attr_def_list  */
  YYSYMBOL_attr_def = 87,                  /* attr_def  */
  YYSYMBOL_number = 88,                    /* number  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_ID_get = 90,                    /* ID_get  */
  YYSYMBOL_null_type = 91,                 /* null_type  */
  YYSYMBOL_insert = 92,                    /* insert  */
  YYSYMBOL_value_tuple = 93,               /* value_tuple  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update = 97,                    /* update  */
  YYSYMBOL_select = 98,                    /* select  */
  YYSYMBOL_sub_query = 99,                 /* sub_query  */
  YYSYMBOL_select_prepare = 100,           /* select_prepare  */
  YYSYMBOL_select_attr = 101,              /* select_attr  */
  YYSYMBOL_attribute = 102,                /* attribute  */
  YYSYMBOL_aggregate = 103,                /* aggregate  */
  YYSYMBOL_attr_list = 104,                /* attr_list  */
  YYSYMBOL_agg_type = 105,                 /* agg_type  */
  YYSYMBOL_rel_list = 106,                 /* rel_list  */
  YYSYMBOL_inner_join_list = 107,          /* inner_join_list  */
  YYSYMBOL_where = 108,                    /* where  */
  YYSYMBOL_condition_list = 109,           /* condition_list  */
  YYSYMBOL_condition = 110,                /* condition  */
  YYSYMBOL_comOp = 111,                    /* comOp  */
  YYSYMBOL_order = 112,                    /* order  */
  YYSYMBOL_order_attribute = 113,          /* order_attribute  */
  YYSYMBOL_order_list = 114,               /* order_list  */
  YYSYMBOL_group = 115,                    /* group  */
  YYSYMBOL_group_attribute = 116,          /* group_attribute  */
  YYSYMBOL_group_list = 117,               /* group_list  */
  YYSYMBOL_load_data = 118                 /* load_data  */
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
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  251

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   164,   164,   166,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   190,   195,   200,   206,   212,   218,   224,   230,   236,
     243,   253,   256,   261,   263,   270,   277,   287,   289,   293,
     300,   309,   312,   313,   314,   315,   316,   319,   326,   327,
     328,   332,   349,   351,   355,   357,   362,   365,   368,   373,
     376,   383,   393,   403,   424,   446,   454,   459,   462,   467,
     472,   477,   484,   491,   498,   504,   512,   514,   517,   522,
     523,   524,   525,   527,   529,   533,   535,   539,   541,   545,
     547,   552,   573,   593,   613,   635,   656,   677,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   708,   710,   712,
     716,   723,   730,   737,   744,   751,   759,   761,   764,   766,
     770,   775,   781,   783,   787
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
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "MAX", "MIN", "COUNT", "AVG", "INNER", "JOIN", "UNIQUE",
  "ORDER", "BY", "ASC", "GROUP", "NOT", "NULL_T", "NULLABLE_T", "IS", "IN",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "unique_index", "id_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "null_type", "insert",
  "value_tuple", "value_list", "value", "delete", "update", "select",
  "sub_query", "select_prepare", "select_attr", "attribute", "aggregate",
  "attr_list", "agg_type", "rel_list", "inner_join_list", "where",
  "condition_list", "condition", "comOp", "order", "order_attribute",
  "order_list", "group", "group_attribute", "group_list", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
#endif

#define YYPACT_NINF (-191)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -191,   100,  -191,     1,    66,  -191,   -56,     9,    14,     0,
     -20,   -33,    33,    38,    41,    75,    78,    -3,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,    87,  -191,    19,  -191,    61,
      25,    26,    93,    94,  -191,    35,    37,    73,  -191,  -191,
    -191,  -191,  -191,    77,  -191,  -191,  -191,  -191,    88,  -191,
      86,   104,   104,   107,   110,    65,   127,   128,  -191,  -191,
     113,   116,    89,    84,   -27,    92,    99,  -191,  -191,   -12,
      96,   121,  -191,  -191,   136,     4,   158,   122,   139,  -191,
    -191,   152,   104,   104,   162,  -191,  -191,  -191,    -8,  -191,
     155,   156,  -191,  -191,   157,   142,   112,    40,   -18,    98,
     140,  -191,    40,   171,   114,   129,  -191,  -191,    87,  -191,
     117,  -191,  -191,    96,   163,  -191,  -191,  -191,  -191,  -191,
     -10,   166,   165,   120,  -191,  -191,  -191,  -191,  -191,  -191,
     124,   130,  -191,    13,    22,     4,  -191,   116,   125,   152,
     135,   116,   159,   173,   157,   185,   131,   134,  -191,  -191,
     132,    40,   177,    98,  -191,  -191,  -191,  -191,   168,  -191,
     140,   192,   195,  -191,   137,   146,   138,  -191,  -191,  -191,
    -191,   183,  -191,   186,   165,   187,    29,   143,  -191,  -191,
    -191,   167,   154,   150,   152,  -191,   145,   193,  -191,   196,
     208,   184,  -191,  -191,     4,   151,   160,   213,   129,   186,
     214,    40,  -191,   161,   140,     3,   200,   164,  -191,   116,
    -191,  -191,   165,  -191,   129,  -191,   169,  -191,   151,  -191,
     190,   202,   146,   204,  -191,     5,   200,   170,   164,  -191,
     150,   187,  -191,  -191,  -191,  -191,   202,   205,  -191,  -191,
    -191
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    31,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,    32,     0,
       0,     0,     0,     0,    23,     0,     0,     0,    24,    25,
      26,    22,    21,     0,    79,    80,    81,    82,    69,    66,
       0,    76,    76,     0,     0,     0,     0,     0,    29,    28,
       0,    87,     0,     0,     0,     0,     0,    67,    68,     0,
       0,     0,    27,    35,     0,     0,     0,     0,     0,    70,
      71,    83,    76,    76,     0,    59,    56,    57,     0,    58,
       0,     0,    60,    47,    37,     0,     0,     0,     0,     0,
      89,    61,     0,     0,     0,    85,    77,    78,     0,    72,
       0,    75,    74,     0,     0,    42,    43,    44,    45,    46,
      48,     0,    54,     0,    98,    99,   100,   101,   102,   103,
       0,   104,   106,     0,     0,     0,    88,    87,     0,    83,
       0,    87,     0,     0,    37,     0,     0,     0,    49,    40,
       0,     0,     0,     0,   107,   105,    93,    91,    94,    92,
      89,     0,     0,    84,     0,   108,     0,    73,    38,    36,
      41,     0,    50,    33,    54,    52,     0,     0,    90,    62,
     124,     0,     0,   118,    83,    39,     0,     0,    55,     0,
       0,     0,    95,    96,     0,     0,     0,     0,    85,    33,
       0,     0,    51,     0,    89,   110,   116,     0,    63,    87,
      34,    30,    54,    97,    85,   114,     0,   112,     0,   109,
     120,   122,   108,     0,    86,   111,   116,     0,     0,   119,
     118,    52,   115,   113,   117,   121,   122,     0,    53,   123,
      64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,    15,  -191,  -191,    69,   103,  -191,
    -191,  -191,  -191,  -191,   -14,  -174,   -79,  -191,  -191,  -191,
    -191,   141,   111,   172,   174,    32,  -191,  -135,  -190,  -146,
    -151,  -143,  -106,    -2,     8,    -5,    -1,    -6,    -9,  -191
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    39,   197,    29,    30,   124,   104,   181,
     130,   105,   159,    31,   200,   162,   109,    32,    33,    34,
     102,    35,    60,    61,    62,    77,    63,   115,   151,    86,
     146,   110,   143,   193,   216,   229,   207,   231,   239,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     101,   171,   170,   144,    94,   175,   156,    37,    42,   119,
     198,   133,    46,   225,   173,   242,    43,    44,   219,   188,
      94,   120,   134,   135,   136,   137,   138,   139,   132,    94,
      45,    47,   226,   147,   234,    53,    48,    89,    94,   140,
      90,    49,   141,   142,    50,    94,    95,   157,   233,   158,
      96,    97,    98,    38,    99,   100,    94,   186,   227,   208,
     243,   214,    95,   224,   167,   169,    96,    97,   108,    65,
      99,    95,    40,   232,    41,    96,    97,   166,    51,    99,
      95,    52,   184,    64,    96,    97,   168,    95,    99,    66,
      67,    96,    97,   201,    78,    99,    68,    69,    95,    70,
       2,    71,    96,    97,     3,     4,    99,   202,    72,     5,
       6,     7,     8,     9,    10,    11,    73,    74,    75,    12,
      13,    14,    76,    79,   116,   117,    80,    15,    16,    81,
      82,    83,   222,    54,    55,    56,    57,    17,   134,   135,
     136,   137,   138,   139,    84,    54,    55,    56,    57,    85,
      88,    58,   107,    87,    59,   140,    91,   106,   141,   142,
     103,   111,   112,    58,   125,   126,   127,   128,   129,   113,
     114,     5,   121,   122,   145,   123,   131,   148,   149,   150,
     155,   153,   160,   161,   163,   164,   174,   165,   179,   172,
     177,   176,   182,   180,   185,   189,   183,   187,   190,   192,
     195,   191,   194,   204,   196,   199,   206,   203,   205,   209,
     210,   212,   211,   213,   217,   215,   218,   221,   228,   237,
     238,   241,   250,   178,   220,   223,   154,   248,   230,   152,
     240,   244,   246,   235,   245,   118,   236,   249,     0,   247,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
      93
};

static const yytype_int16 yycheck[] =
{
      79,   147,   145,   109,    16,   151,    16,     6,    64,    17,
     184,    29,    32,    10,   149,    10,     7,     3,   208,   170,
      16,    29,    40,    41,    42,    43,    44,    45,   107,    16,
      30,    64,    29,   112,   224,    38,     3,    64,    16,    57,
      67,     3,    60,    61,     3,    16,    58,    57,   222,    59,
      62,    63,    64,    52,    66,    67,    16,   163,    55,   194,
      55,   204,    58,   214,   143,   144,    62,    63,    64,     8,
      66,    58,     6,   219,     8,    62,    63,    64,     3,    66,
      58,     3,   161,    64,    62,    63,    64,    58,    66,    64,
      64,    62,    63,    64,    62,    66,     3,     3,    58,    64,
       0,    64,    62,    63,     4,     5,    66,   186,    35,     9,
      10,    11,    12,    13,    14,    15,    39,    29,    32,    19,
      20,    21,    18,    16,    92,    93,    16,    27,    28,    64,
       3,     3,   211,    46,    47,    48,    49,    37,    40,    41,
      42,    43,    44,    45,    31,    46,    47,    48,    49,    33,
      66,    64,    16,    64,    67,    57,    64,    36,    60,    61,
      64,     3,    40,    64,    22,    23,    24,    25,    26,    30,
      18,     9,    17,    17,    34,    18,    64,     6,    64,    50,
      17,    64,    16,    18,    64,    61,    51,    57,     3,    64,
      17,    32,    58,    62,    17,     3,    64,    29,     3,    53,
      17,    64,    64,    36,    18,    18,    56,    64,    54,    64,
      17,     3,    16,    29,    54,    64,     3,     3,    18,    29,
      18,    17,    17,   154,   209,    64,   123,   241,    64,   118,
     232,   236,   238,    64,    64,    94,   228,   246,    -1,   240,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      76
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    84,
      85,    92,    96,    97,    98,   100,   118,     6,    52,    82,
       6,     8,    64,     7,     3,    30,    32,    64,     3,     3,
       3,     3,     3,    38,    46,    47,    48,    49,    64,    67,
     101,   102,   103,   105,    64,     8,    64,    64,     3,     3,
      64,    64,    35,    39,    29,    32,    18,   104,   104,    16,
      16,    64,     3,     3,    31,    33,   108,    64,    66,    64,
      67,    64,   102,   103,    16,    58,    62,    63,    64,    66,
      67,    95,    99,    64,    87,    90,    36,    16,    64,    95,
     110,     3,    40,    30,    18,   106,   104,   104,   100,    17,
      29,    17,    17,    18,    86,    22,    23,    24,    25,    26,
      89,    64,    95,    29,    40,    41,    42,    43,    44,    45,
      57,    60,    61,   111,   111,    34,   109,    95,     6,    64,
      50,   107,   101,    64,    87,    17,    16,    57,    59,    91,
      16,    18,    94,    64,    61,    57,    64,    95,    64,    95,
     110,   108,    64,   106,    51,   108,    32,    17,    86,     3,
      62,    88,    58,    64,    95,    17,   111,    29,   109,     3,
       3,    64,    53,   112,    64,    17,    18,    83,    94,    18,
      93,    64,    95,    64,    36,    54,    56,   115,   106,    64,
      17,    16,     3,    29,   110,    64,   113,    54,     3,   107,
      83,     3,    95,    64,   109,    10,    29,    55,    18,   114,
      64,   116,   108,    94,   107,    64,   113,    29,    18,   117,
     112,    17,    10,    55,   114,    64,   116,   115,    93,   117,
      17
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    82,    83,    83,    84,    85,    86,    86,    87,
      87,    88,    89,    89,    89,    89,    89,    90,    91,    91,
      91,    92,    93,    93,    94,    94,    95,    95,    95,    95,
      95,    96,    97,    98,    99,   100,   101,   101,   101,   102,
     102,   102,   103,   103,   103,   103,   104,   104,   104,   105,
     105,   105,   105,   106,   106,   107,   107,   108,   108,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   118
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      11,     0,     1,     0,     3,     4,     8,     0,     3,     5,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       2,    10,     0,     6,     0,     3,     1,     1,     1,     1,
       1,     5,     8,    10,    11,     1,     1,     2,     2,     1,
       3,     3,     4,     6,     4,     4,     0,     3,     3,     1,
       1,     1,     1,     0,     3,     0,     7,     0,     3,     0,
       3,     3,     3,     3,     3,     5,     5,     7,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     0,     4,
       1,     3,     2,     4,     2,     4,     0,     3,     0,     4,
       1,     3,     0,     3,     8
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
#line 190 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1433 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 195 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 200 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1449 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 206 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1457 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 212 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1465 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 218 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1473 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 224 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1482 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 230 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1490 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 236 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1499 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE unique_index INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 244 "yacc_sql.y"
                {
            CONTEXT->id_list[0] = (yyvsp[-3].string);
            CONTEXT->id_list_length++;
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (const char**)CONTEXT->id_list, CONTEXT->id_list_length);
			CONTEXT->id_list_length = 0;
		}
#line 1510 "yacc_sql.tab.c"
    break;

  case 31: /* unique_index: %empty  */
#line 253 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
        }
#line 1518 "yacc_sql.tab.c"
    break;

  case 32: /* unique_index: UNIQUE  */
#line 257 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;//"create_unique_index";
        }
#line 1526 "yacc_sql.tab.c"
    break;

  case 34: /* id_list: COMMA ID id_list  */
#line 263 "yacc_sql.y"
                        {
            CONTEXT->id_list_length++;
            CONTEXT->id_list[CONTEXT->id_list_length] = (yyvsp[-1].string);
	  }
#line 1535 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 271 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1544 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 278 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
		}
#line 1557 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 289 "yacc_sql.y"
                                   {    }
#line 1563 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 294 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), NOT_NULL);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1574 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_type  */
#line 301 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 41: /* number: NUMBER  */
#line 309 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1591 "yacc_sql.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 312 "yacc_sql.y"
          { (yyval.number)=INTS; }
#line 1597 "yacc_sql.tab.c"
    break;

  case 43: /* type: STRING_T  */
#line 313 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 1603 "yacc_sql.tab.c"
    break;

  case 44: /* type: FLOAT_T  */
#line 314 "yacc_sql.y"
              { (yyval.number)=FLOATS; }
#line 1609 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 315 "yacc_sql.y"
             { (yyval.number)=DATES; }
#line 1615 "yacc_sql.tab.c"
    break;

  case 46: /* type: TEXT_T  */
#line 316 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1621 "yacc_sql.tab.c"
    break;

  case 47: /* ID_get: ID  */
#line 320 "yacc_sql.y"
    {
      char *temp=(yyvsp[0].string); 
      snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1630 "yacc_sql.tab.c"
    break;

  case 48: /* null_type: %empty  */
#line 326 "yacc_sql.y"
                { (yyval.number)=NOT_NULL; }
#line 1636 "yacc_sql.tab.c"
    break;

  case 49: /* null_type: NULLABLE_T  */
#line 327 "yacc_sql.y"
                 { (yyval.number)=NULLABLE; }
#line 1642 "yacc_sql.tab.c"
    break;

  case 50: /* null_type: NOT NULL_T  */
#line 328 "yacc_sql.y"
                 { (yyval.number)=NOT_NULL; }
#line 1648 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE value_tuple SEMICOLON  */
#line 333 "yacc_sql.y"
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
#line 1669 "yacc_sql.tab.c"
    break;

  case 53: /* value_tuple: COMMA LBRACE value value_list RBRACE value_tuple  */
#line 351 "yacc_sql.y"
                                                       {
        CONTEXT->tuple_num++;
	  }
#line 1677 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 357 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1685 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 362 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1693 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 365 "yacc_sql.y"
            {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1701 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 368 "yacc_sql.y"
          {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
			CONTEXT->string_length = strlen((yyvsp[0].string));
		value_init_text(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string), CONTEXT->string_length);
		}
#line 1711 "yacc_sql.tab.c"
    break;

  case 59: /* value: NULL_T  */
#line 373 "yacc_sql.y"
             {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1719 "yacc_sql.tab.c"
    break;

  case 60: /* value: sub_query  */
#line 376 "yacc_sql.y"
                {
      Selects* sub_query = &(CONTEXT->ssql + CONTEXT->select_frame_index + 1)->sstr.selection;
      value_init_sub_query(&CONTEXT->values[CONTEXT->value_length++], sub_query);
    }
#line 1728 "yacc_sql.tab.c"
    break;

  case 61: /* delete: DELETE FROM ID where SEMICOLON  */
#line 384 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1740 "yacc_sql.tab.c"
    break;

  case 62: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 394 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1752 "yacc_sql.tab.c"
    break;

  case 63: /* select: select_prepare select_attr FROM ID rel_list inner_join_list where order group SEMICOLON  */
#line 404 "yacc_sql.y"
                {
			// (CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, (yyvsp[-6].string));

      Condition* this_frame_conditions = CONTEXT->conditions + CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length;
      selects_append_conditions(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, this_frame_conditions, CONTEXT->condition_length);

			(CONTEXT->ssql + CONTEXT->select_frame_index)->flag=SCF_SELECT;//"select";
			// (CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;

      CONTEXT->condition_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length;
      CONTEXT->value_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_value_length;
      CONTEXT->select_frame_index--;
    }
#line 1775 "yacc_sql.tab.c"
    break;

  case 64: /* sub_query: LBRACE select_prepare select_attr FROM ID rel_list inner_join_list where order group RBRACE  */
#line 425 "yacc_sql.y"
    {
			selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, (yyvsp[-6].string));

      size_t last_condition_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length;
      Condition* this_frame_conditions = CONTEXT->conditions + last_condition_length;
      size_t this_frame_condition_length = CONTEXT->condition_length - last_condition_length;
      selects_append_conditions(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, this_frame_conditions, this_frame_condition_length);

			(CONTEXT->ssql + CONTEXT->select_frame_index)->flag=SCF_SELECT;//"select";

			//临时变量清零
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;

      CONTEXT->condition_length = last_condition_length;
      CONTEXT->value_length = CONTEXT->select_frame[CONTEXT->select_frame_index].last_value_length;
      CONTEXT->select_frame_index--;
    }
#line 1798 "yacc_sql.tab.c"
    break;

  case 65: /* select_prepare: SELECT  */
#line 446 "yacc_sql.y"
           {
      CONTEXT->select_frame_index++;
      CONTEXT->select_frame[CONTEXT->select_frame_index].last_condition_length = CONTEXT->condition_length;
      CONTEXT->select_frame[CONTEXT->select_frame_index].last_value_length = CONTEXT->value_length;
    }
#line 1808 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: STAR  */
#line 454 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
#line 1818 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: attribute attr_list  */
#line 459 "yacc_sql.y"
                          {

    }
#line 1826 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: aggregate attr_list  */
#line 462 "yacc_sql.y"
                          {

    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 69: /* attribute: ID  */
#line 467 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
#line 1844 "yacc_sql.tab.c"
    break;

  case 70: /* attribute: ID DOT ID  */
#line 472 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
#line 1854 "yacc_sql.tab.c"
    break;

  case 71: /* attribute: ID DOT STAR  */
#line 477 "yacc_sql.y"
                  {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), "*");
      selects_append_attribute(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
    }
#line 1864 "yacc_sql.tab.c"
    break;

  case 72: /* aggregate: agg_type LBRACE ID RBRACE  */
#line 484 "yacc_sql.y"
                              {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Aggregate aggregate;
      aggregate_init(&aggregate, (yyvsp[-3].number), 1, &attr, NULL);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
#line 1876 "yacc_sql.tab.c"
    break;

  case 73: /* aggregate: agg_type LBRACE ID DOT ID RBRACE  */
#line 491 "yacc_sql.y"
                                       {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Aggregate aggregate;
      aggregate_init(&aggregate, (yyvsp[-5].number), 1, &attr, NULL);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
#line 1888 "yacc_sql.tab.c"
    break;

  case 74: /* aggregate: agg_type LBRACE value RBRACE  */
#line 498 "yacc_sql.y"
                                   {
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, (yyvsp[-3].number), 0, NULL, value);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
#line 1899 "yacc_sql.tab.c"
    break;

  case 75: /* aggregate: agg_type LBRACE STAR RBRACE  */
#line 504 "yacc_sql.y"
                                  {
      value_init_string(&CONTEXT->values[CONTEXT->value_length++], "*");
      Value* value = &CONTEXT->values[CONTEXT->value_length - 1];
      Aggregate aggregate;
      aggregate_init(&aggregate, (yyvsp[-3].number), 0, NULL, value);
			selects_append_aggregate(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &aggregate);
    }
#line 1911 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA attribute attr_list  */
#line 514 "yacc_sql.y"
                                {

    }
#line 1919 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA aggregate attr_list  */
#line 517 "yacc_sql.y"
                                {

    }
#line 1927 "yacc_sql.tab.c"
    break;

  case 79: /* agg_type: MAX  */
#line 522 "yacc_sql.y"
              { (yyval.number) = AGG_MAX; }
#line 1933 "yacc_sql.tab.c"
    break;

  case 80: /* agg_type: MIN  */
#line 523 "yacc_sql.y"
          { (yyval.number) = AGG_MIN; }
#line 1939 "yacc_sql.tab.c"
    break;

  case 81: /* agg_type: COUNT  */
#line 524 "yacc_sql.y"
            { (yyval.number) = AGG_COUNT; }
#line 1945 "yacc_sql.tab.c"
    break;

  case 82: /* agg_type: AVG  */
#line 525 "yacc_sql.y"
          { (yyval.number) = AGG_AVG; }
#line 1951 "yacc_sql.tab.c"
    break;

  case 84: /* rel_list: COMMA ID rel_list  */
#line 529 "yacc_sql.y"
                        {	
				selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, (yyvsp[-1].string));
		}
#line 1959 "yacc_sql.tab.c"
    break;

  case 86: /* inner_join_list: INNER JOIN ID ON condition condition_list inner_join_list  */
#line 535 "yacc_sql.y"
                                                               {
      selects_append_relation(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, (yyvsp[-4].string));
    }
#line 1967 "yacc_sql.tab.c"
    break;

  case 88: /* where: WHERE condition condition_list  */
#line 541 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1975 "yacc_sql.tab.c"
    break;

  case 90: /* condition_list: AND condition condition_list  */
#line 547 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1983 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID comOp value  */
#line 553 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2008 "yacc_sql.tab.c"
    break;

  case 92: /* condition: value comOp value  */
#line 574 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 0, NULL, right_value);
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
#line 2032 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID comOp ID  */
#line 594 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2056 "yacc_sql.tab.c"
    break;

  case 94: /* condition: value comOp ID  */
#line 614 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2082 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID DOT ID comOp value  */
#line 636 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2107 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp ID DOT ID  */
#line 657 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-3].number), 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2132 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID DOT ID comOp ID DOT ID  */
#line 678 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, (yyvsp[-3].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2155 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: EQ  */
#line 699 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2161 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: LT  */
#line 700 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2167 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: GT  */
#line 701 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2173 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: LE  */
#line 702 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2179 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: GE  */
#line 703 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2185 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: NE  */
#line 704 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2191 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: IS  */
#line 705 "yacc_sql.y"
         { (yyval.number) = IS_NULL; }
#line 2197 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: IS NOT  */
#line 706 "yacc_sql.y"
             { (yyval.number) = IS_NOT_NULL; }
#line 2203 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: IN  */
#line 707 "yacc_sql.y"
         { (yyval.number) = OP_IN; }
#line 2209 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: NOT IN  */
#line 708 "yacc_sql.y"
             { (yyval.number) = NOT_IN; }
#line 2215 "yacc_sql.tab.c"
    break;

  case 109: /* order: ORDER BY order_attribute order_list  */
#line 712 "yacc_sql.y"
                                          {
    }
#line 2222 "yacc_sql.tab.c"
    break;

  case 110: /* order_attribute: ID  */
#line 716 "yacc_sql.y"
       {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2234 "yacc_sql.tab.c"
    break;

  case 111: /* order_attribute: ID DOT ID  */
#line 723 "yacc_sql.y"
                {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2246 "yacc_sql.tab.c"
    break;

  case 112: /* order_attribute: ID ASC  */
#line 730 "yacc_sql.y"
             {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2258 "yacc_sql.tab.c"
    break;

  case 113: /* order_attribute: ID DOT ID ASC  */
#line 737 "yacc_sql.y"
                    {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_ASC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2270 "yacc_sql.tab.c"
    break;

  case 114: /* order_attribute: ID DESC  */
#line 744 "yacc_sql.y"
              {
      RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2282 "yacc_sql.tab.c"
    break;

  case 115: /* order_attribute: ID DOT ID DESC  */
#line 751 "yacc_sql.y"
                     {
      RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
      Order order;
      order_init(&order, ORDER_DESC, &attr);
			selects_append_order(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &order);
    }
#line 2294 "yacc_sql.tab.c"
    break;

  case 117: /* order_list: COMMA order_attribute order_list  */
#line 761 "yacc_sql.y"
                                       {
    }
#line 2301 "yacc_sql.tab.c"
    break;

  case 119: /* group: GROUP BY group_attribute group_list  */
#line 766 "yacc_sql.y"
                                          {
    }
#line 2308 "yacc_sql.tab.c"
    break;

  case 120: /* group_attribute: ID  */
#line 770 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_group(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
#line 2318 "yacc_sql.tab.c"
    break;

  case 121: /* group_attribute: ID DOT ID  */
#line 775 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_group(&(CONTEXT->ssql + CONTEXT->select_frame_index)->sstr.selection, &attr);
		}
#line 2328 "yacc_sql.tab.c"
    break;

  case 123: /* group_list: COMMA group_attribute group_list  */
#line 783 "yacc_sql.y"
                                       {
    }
#line 2335 "yacc_sql.tab.c"
    break;

  case 124: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 788 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2344 "yacc_sql.tab.c"
    break;


#line 2348 "yacc_sql.tab.c"

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

#line 793 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
  context.select_frame_index = -1;

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
