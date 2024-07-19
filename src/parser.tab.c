/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

#include "../include/ast.h"
#include "../include/symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_UNDECLARED 10
#define ERR_DECLARED 11
#define ERR_VARIABLE 20
#define ERR_FUNCTION 21

void parser_declare_identifier(symbol_table *table, char* identifier, entry_nature nature, entry_type data_type);
void parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature);

struct id_stack{
    char *current_id;
    struct id_stack *next_id;
};

int yylex(void);
extern int get_line_number();
extern void *arvore;
void yyerror (char const *mensagem);
void yylex_destroy();

void parser_declare_identifier(symbol_table *table, char* identifier, entry_nature nature, entry_type data_type){

    if(search_symbol_table(table, identifier) != NULL){
        printf("Line %d: ERROR (%d): Variable %s already declared in this scope.\n", get_line_number(), ERR_DECLARED, identifier);
        exit(ERR_DECLARED);
    }

    symbol_table_entry newEntry = create_table_entry(identifier, get_line_number(), nature, data_type, NULL);
    insert_symbol_table(table, newEntry);

    /*print_symbol_table(table);
    printf("\n");*/
}

void parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature){

    symbol_table_entry *searched_entry = search_table_stack(&table, identifier);

    if(searched_entry == NULL){
        printf("Line %d: ERROR (%d): Undeclared identifier %s.\n", get_line_number(), ERR_UNDECLARED, identifier);
        exit(ERR_UNDECLARED);
    } else {
        if(expected_nature == FUNCTION && searched_entry->nature == IDENTIFIER){
            printf("Line %d: ERROR (%d): Variable identifier %s used as function.\n", get_line_number(), ERR_VARIABLE, identifier);
            exit(ERR_VARIABLE);
        }
        if(expected_nature == IDENTIFIER && searched_entry->nature == FUNCTION){
            printf("Line %d: ERROR (%d): Function identifier %s used as variable.\n", get_line_number(), ERR_FUNCTION, identifier);
            exit(ERR_FUNCTION);
        }
    }
}


node_s *head = NULL;

symbol_table globalTable = {
    .entry = {
        .identifier = NULL
    },
    .next_entry = NULL
};

table_stack symbolTableStack = {
   .table = &globalTable,
   .prev_table = NULL
};
table_stack *tableStackHead = &symbolTableStack;

struct id_stack idStack = { .current_id = NULL, .next_id = NULL };
struct id_stack *idStackHead = &idStack;


#line 151 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* '='  */
  YYSYMBOL_4_ = 4,                         /* '<'  */
  YYSYMBOL_5_ = 5,                         /* '>'  */
  YYSYMBOL_6_ = 6,                         /* '+'  */
  YYSYMBOL_7_ = 7,                         /* '-'  */
  YYSYMBOL_8_ = 8,                         /* '*'  */
  YYSYMBOL_9_ = 9,                         /* '/'  */
  YYSYMBOL_10_ = 10,                       /* '%'  */
  YYSYMBOL_11_ = 11,                       /* '!'  */
  YYSYMBOL_TK_PR_INT = 12,                 /* TK_PR_INT  */
  YYSYMBOL_TK_PR_FLOAT = 13,               /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_BOOL = 14,                /* TK_PR_BOOL  */
  YYSYMBOL_TK_PR_IF = 15,                  /* TK_PR_IF  */
  YYSYMBOL_TK_PR_ELSE = 16,                /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_WHILE = 17,               /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_RETURN = 18,              /* TK_PR_RETURN  */
  YYSYMBOL_TK_OC_LE = 19,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 20,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 21,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 22,                  /* TK_OC_NE  */
  YYSYMBOL_TK_OC_AND = 23,                 /* TK_OC_AND  */
  YYSYMBOL_TK_OC_OR = 24,                  /* TK_OC_OR  */
  YYSYMBOL_TK_IDENTIFICADOR = 25,          /* TK_IDENTIFICADOR  */
  YYSYMBOL_TK_LIT_INT = 26,                /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 27,              /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_LIT_FALSE = 28,              /* TK_LIT_FALSE  */
  YYSYMBOL_TK_LIT_TRUE = 29,               /* TK_LIT_TRUE  */
  YYSYMBOL_TK_ERRO = 30,                   /* TK_ERRO  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_global_var = 39,                /* global_var  */
  YYSYMBOL_func = 40,                      /* func  */
  YYSYMBOL_header = 41,                    /* header  */
  YYSYMBOL_par_list = 42,                  /* par_list  */
  YYSYMBOL_arg_list = 43,                  /* arg_list  */
  YYSYMBOL_ret_comm = 44,                  /* ret_comm  */
  YYSYMBOL_comm_block = 45,                /* comm_block  */
  YYSYMBOL_comm_lst = 46,                  /* comm_lst  */
  YYSYMBOL_comm = 47,                      /* comm  */
  YYSYMBOL_var_decl = 48,                  /* var_decl  */
  YYSYMBOL_attrib_comm = 49,               /* attrib_comm  */
  YYSYMBOL_func_call = 50,                 /* func_call  */
  YYSYMBOL_flux_ctrl = 51,                 /* flux_ctrl  */
  YYSYMBOL_exp = 52,                       /* exp  */
  YYSYMBOL_or_exp = 53,                    /* or_exp  */
  YYSYMBOL_and_exp = 54,                   /* and_exp  */
  YYSYMBOL_eq_exp = 55,                    /* eq_exp  */
  YYSYMBOL_comp_exp = 56,                  /* comp_exp  */
  YYSYMBOL_sum_exp = 57,                   /* sum_exp  */
  YYSYMBOL_mult_exp = 58,                  /* mult_exp  */
  YYSYMBOL_un_exp = 59,                    /* un_exp  */
  YYSYMBOL_operand = 60,                   /* operand  */
  YYSYMBOL_id_list = 61,                   /* id_list  */
  YYSYMBOL_lit = 62,                       /* lit  */
  YYSYMBOL_type = 63,                      /* type  */
  YYSYMBOL_new_table = 64,                 /* new_table  */
  YYSYMBOL_cleanup_table = 65              /* cleanup_table  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   129

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    11,     2,     2,     2,    10,     2,     2,
      32,    33,     8,     6,    31,     7,     2,     9,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       4,     3,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   123,   131,   141,   148,   154,   164,   173,
     179,   185,   189,   196,   205,   209,   214,   222,   244,   248,
     252,   256,   260,   264,   269,   289,   298,   310,   316,   330,
     340,   353,   358,   365,   370,   377,   382,   389,   396,   399,
     406,   413,   420,   427,   430,   437,   444,   449,   456,   463,
     470,   475,   481,   486,   491,   496,   500,   504,   511,   522,
     535,   539,   543,   547,   553,   557,   561,   566,   572
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "'='", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "TK_PR_INT", "TK_PR_FLOAT",
  "TK_PR_BOOL", "TK_PR_IF", "TK_PR_ELSE", "TK_PR_WHILE", "TK_PR_RETURN",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR",
  "TK_IDENTIFICADOR", "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE",
  "TK_LIT_TRUE", "TK_ERRO", "','", "'('", "')'", "';'", "'{'", "'}'",
  "$accept", "program", "global_var", "func", "header", "par_list",
  "arg_list", "ret_comm", "comm_block", "comm_lst", "comm", "var_decl",
  "attrib_comm", "func_call", "flux_ctrl", "exp", "or_exp", "and_exp",
  "eq_exp", "comp_exp", "sum_exp", "mult_exp", "un_exp", "operand",
  "id_list", "lit", "type", "new_table", "cleanup_table", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      16,   -65,   -65,   -65,   -65,    13,    16,    16,   -17,     0,
       8,    43,   -65,   -65,   -65,     2,   -65,   -65,   -65,     1,
      30,   -24,    57,    53,    58,    42,     5,   -65,   -65,    66,
      44,   -65,   -65,   -65,   -65,   -17,   -65,    69,    50,    77,
      50,   -65,    42,    42,    42,    42,    81,   -65,   -65,   -65,
     -65,    42,   -65,   -65,    91,    93,    37,    84,    38,    90,
     -65,   -65,   -65,    42,    14,   -65,    83,   -65,   -65,   -65,
     108,    50,    94,    85,    87,   -65,   -65,    88,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,   -65,   -65,    39,   -65,   -65,   -65,    97,   114,   -65,
     -65,   -65,   -65,    93,    37,    84,    84,    38,    38,    38,
      38,    90,    90,   -65,   -65,   -65,   -65,    42,   -65,   100,
     -17,   -17,   -65,   -65,   -65,   -65,   110,   -65,   -65,   -17,
     -65,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    64,    65,    66,    67,     0,     2,     2,     0,     0,
       0,     0,     1,     3,     4,    67,    68,     5,    58,    24,
       0,     0,     0,     0,     0,     0,     0,    14,    22,    67,
       0,    19,    20,    21,    23,     0,     6,     0,     0,     0,
       0,    10,     0,     0,     0,     0,    54,    60,    61,    62,
      63,     0,    56,    13,    31,    33,    35,    38,    43,    46,
      50,    53,    55,     0,     0,    15,     0,    16,    68,    59,
       0,     0,     0,     0,     0,    51,    52,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    27,     0,    11,    17,    18,     0,     0,     9,
      67,    67,    57,    32,    34,    36,    37,    39,    40,    41,
      42,    44,    45,    47,    48,    49,    26,     0,     8,     0,
       0,     0,    12,     7,    68,    68,    29,    30,    67,     0,
      68,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,    86,   -65,   -65,   -65,   -65,   -65,   -65,   -34,   -65,
      98,    -3,   -65,     7,   -65,   -40,   -65,    51,    49,    29,
      23,    25,   -38,   -65,   -65,   -65,    -6,    -4,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    21,    93,    28,    16,    29,
      30,     9,    32,    52,    34,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    19,    62,    10,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      11,    68,    73,    74,    96,    22,    75,    76,    63,    39,
      40,    77,    31,    12,     1,     2,     3,    23,    15,    24,
      25,    44,    33,    91,    94,    45,    31,    26,     1,     2,
       3,    17,    70,    18,    72,    37,    33,    64,    27,    46,
      47,    48,    49,    50,    86,    87,    51,    92,     4,    44,
     113,   114,   115,    45,    38,     1,     2,     3,    80,    81,
     126,   127,     1,     2,     3,    98,   131,    46,    47,    48,
      49,    50,   116,   117,    51,    67,    20,   122,     1,     2,
       3,    23,    41,    24,    25,    42,   124,   125,    82,    83,
      43,    26,    13,    14,    69,   130,   120,   121,    88,    89,
      90,    71,    65,    84,    85,   107,   108,   109,   110,   105,
     106,   111,   112,    64,    95,    78,    79,    97,   100,    99,
     101,   102,   118,   119,   129,   123,   128,    66,   104,   103
};

static const yytype_uint8 yycheck[] =
{
       4,    35,    42,    43,    68,    11,    44,    45,     3,    33,
      34,    51,    15,     0,    12,    13,    14,    15,    35,    17,
      18,     7,    15,    63,    64,    11,    29,    25,    12,    13,
      14,    31,    38,    25,    40,    34,    29,    32,    36,    25,
      26,    27,    28,    29,     6,     7,    32,    33,    32,     7,
      88,    89,    90,    11,    24,    12,    13,    14,    21,    22,
     124,   125,    12,    13,    14,    71,   130,    25,    26,    27,
      28,    29,    33,    34,    32,    31,    33,   117,    12,    13,
      14,    15,    25,    17,    18,    32,   120,   121,     4,     5,
      32,    25,     6,     7,    25,   129,   100,   101,     8,     9,
      10,    24,    36,    19,    20,    82,    83,    84,    85,    80,
      81,    86,    87,    32,    31,    24,    23,     9,    33,    25,
      33,    33,    25,     9,   128,    25,    16,    29,    79,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    14,    32,    38,    39,    40,    41,    48,
      63,    64,     0,    38,    38,    35,    45,    31,    25,    61,
      33,    42,    63,    15,    17,    18,    25,    36,    44,    46,
      47,    48,    49,    50,    51,    64,    65,    34,    24,    33,
      34,    25,    32,    32,     7,    11,    25,    26,    27,    28,
      29,    32,    50,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    62,     3,    32,    36,    47,    31,    45,    25,
      63,    24,    63,    52,    52,    59,    59,    52,    24,    23,
      21,    22,     4,     5,    19,    20,     6,     7,     8,     9,
      10,    52,    33,    43,    52,    31,    65,     9,    63,    25,
      33,    33,    33,    54,    55,    56,    56,    57,    57,    57,
      57,    58,    58,    59,    59,    59,    33,    34,    25,     9,
      64,    64,    52,    25,    45,    45,    65,    65,    16,    64,
      45,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    39,    40,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    48,    49,    50,    50,    51,    51,
      51,    52,    53,    53,    54,    54,    55,    55,    55,    56,
      56,    56,    56,    56,    57,    57,    57,    58,    58,    58,
      58,    59,    59,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    62,    62,    63,    63,    63,    64,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     8,     7,     4,
       2,     1,     3,     2,     2,     3,     2,     3,     3,     1,
       1,     1,     1,     1,     2,     3,     4,     3,    11,     7,
       7,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     1,     1,     1,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
      yychar = yylex ();
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
  case 2: /* program: %empty  */
#line 122 "parser.y"
                  {(yyval.node) = NULL;}
#line 1555 "parser.tab.c"
    break;

  case 3: /* program: global_var program  */
#line 123 "parser.y"
                                    {
                    if((yyvsp[0].node) != NULL){
                      (yyval.node) = (yyvsp[0].node);
                    }else {
                      (yyval.node) = NULL;
                    }
                  }
#line 1567 "parser.tab.c"
    break;

  case 4: /* program: func program  */
#line 131 "parser.y"
                              {
                    if((yyvsp[0].node) != NULL)
                      add_child((yyvsp[-1].node),(yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                    arvore = (void*) (yyval.node);
                    }
#line 1578 "parser.tab.c"
    break;

  case 5: /* global_var: var_decl ','  */
#line 141 "parser.y"
                              {
                    (yyval.node) = NULL;
                    }
#line 1586 "parser.tab.c"
    break;

  case 6: /* func: header comm_block cleanup_table  */
#line 148 "parser.y"
                                                 {
                    add_child((yyvsp[-2].node), (yyvsp[-1].node));
                    (yyval.node) = (yyvsp[-2].node);
                    }
#line 1595 "parser.tab.c"
    break;

  case 7: /* header: '(' new_table par_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR  */
#line 154 "parser.y"
                                                                         {
                //add_child($7,$2);
                update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                (yyval.node) = (yyvsp[0].node);

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, (yyvsp[0].node)->lex_val->tk_value, FUNCTION, (yyvsp[-2].filler));

                }
#line 1609 "parser.tab.c"
    break;

  case 8: /* header: '(' new_table ')' TK_OC_OR type '/' TK_IDENTIFICADOR  */
#line 164 "parser.y"
                                                                   {
                update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                (yyval.node) = (yyvsp[0].node);

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, (yyvsp[0].node)->lex_val->tk_value, FUNCTION, (yyvsp[-2].filler));
                }
#line 1621 "parser.tab.c"
    break;

  case 9: /* par_list: par_list ';' type TK_IDENTIFICADOR  */
#line 173 "parser.y"
                                               {
                //add_child($1,$4);
                (yyval.node) = (yyvsp[-3].node);
                parser_declare_identifier(tableStackHead->table, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER, (yyvsp[-1].filler));
            }
#line 1631 "parser.tab.c"
    break;

  case 10: /* par_list: type TK_IDENTIFICADOR  */
#line 179 "parser.y"
                                    {
                (yyval.node) = (yyvsp[0].node);
                parser_declare_identifier(tableStackHead->table, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER, (yyvsp[-1].filler));
            }
#line 1640 "parser.tab.c"
    break;

  case 11: /* arg_list: exp  */
#line 185 "parser.y"
                     {
                    node_stack_push(&head,(yyvsp[0].node));
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1649 "parser.tab.c"
    break;

  case 12: /* arg_list: arg_list ';' exp  */
#line 189 "parser.y"
                                   {
                    add_child(node_stack_pop(&head), (yyvsp[0].node));
                    node_stack_push(&head, (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-2].node);
                    }
#line 1659 "parser.tab.c"
    break;

  case 13: /* ret_comm: TK_PR_RETURN exp  */
#line 196 "parser.y"
                                   {
                    update_label((yyvsp[-1].node),"return");
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1669 "parser.tab.c"
    break;

  case 14: /* comm_block: '{' '}'  */
#line 205 "parser.y"
                          {
                    (yyval.node) = NULL;
                    }
#line 1677 "parser.tab.c"
    break;

  case 15: /* comm_block: '{' comm_lst '}'  */
#line 209 "parser.y"
                                   {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1685 "parser.tab.c"
    break;

  case 16: /* comm_lst: comm ','  */
#line 214 "parser.y"
                         {
                  (yyval.node) = (yyvsp[-1].node);
                  if((yyvsp[-1].node) != NULL){
                    node_stack_push(&head, (yyvsp[-1].node));
                  }
                  }
#line 1696 "parser.tab.c"
    break;

  case 17: /* comm_lst: comm_lst comm ','  */
#line 222 "parser.y"
                                   {// one conflict 
                    if((yyvsp[-1].node) == NULL){//FIX: oof
                      if((yyvsp[-2].node) == NULL){
                        (yyval.node) = NULL;
                      }else
                        (yyval.node) = (yyvsp[-2].node);
                    }else {
                      if((yyvsp[-2].node) == NULL){
                        (yyval.node) = (yyvsp[-1].node);
                        node_stack_push(&head, (yyvsp[-1].node));
                      }else{
                        add_child(node_stack_pop(&head), (yyvsp[-1].node));
                        //add_child($1, $2);
                        node_stack_push(&head, (yyvsp[-1].node));
                        (yyval.node) = (yyvsp[-2].node);
                      }
                    }
                  }
#line 1719 "parser.tab.c"
    break;

  case 18: /* comm: new_table comm_block cleanup_table  */
#line 244 "parser.y"
                                                  {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1727 "parser.tab.c"
    break;

  case 19: /* comm: var_decl  */
#line 248 "parser.y"
                           {
                     (yyval.node) = NULL;
                    }
#line 1735 "parser.tab.c"
    break;

  case 20: /* comm: attrib_comm  */
#line 252 "parser.y"
                                {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1743 "parser.tab.c"
    break;

  case 21: /* comm: func_call  */
#line 256 "parser.y"
                           {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1751 "parser.tab.c"
    break;

  case 22: /* comm: ret_comm  */
#line 260 "parser.y"
                          {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1759 "parser.tab.c"
    break;

  case 23: /* comm: flux_ctrl  */
#line 264 "parser.y"
                           {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1767 "parser.tab.c"
    break;

  case 24: /* var_decl: type id_list  */
#line 269 "parser.y"
                               {
                                //printf("IDs entered\n");
                                (yyval.node) = NULL;
                                do{
                                    //printf("idStackHead = %s\n", idStackHead->current_id);

                                    // create table entry from ID and insert it to table on top of stack
                                    parser_declare_identifier(tableStackHead->table, idStackHead->current_id, IDENTIFIER, (yyvsp[-1].filler));

                                    struct id_stack *nextHead = idStackHead->next_id;

                                    free(idStackHead->current_id);
                                    free(idStackHead);

                                    idStackHead = nextHead;
                                }
                                while(idStackHead->next_id != NULL);
                                }
#line 1790 "parser.tab.c"
    break;

  case 25: /* attrib_comm: TK_IDENTIFICADOR '=' exp  */
#line 289 "parser.y"
                                                {
                      add_child((yyvsp[-1].node),(yyvsp[-2].node));
                      add_child((yyvsp[-1].node),(yyvsp[0].node));
                      update_label((yyvsp[-1].node),"=");
                      (yyval.node) = (yyvsp[-1].node);
                      parser_identifier_check(tableStackHead, (yyvsp[-2].node)->lex_val->tk_value, IDENTIFIER);
                      }
#line 1802 "parser.tab.c"
    break;

  case 26: /* func_call: TK_IDENTIFICADOR '(' arg_list ')'  */
#line 298 "parser.y"
                                                    {
                      add_child((yyvsp[-3].node),(yyvsp[-1].node));
                      char *funcName = calloc(
                        1,sizeof(char) * (strlen(
                          (yyvsp[-3].node)->lex_val->tk_value) + 5 * sizeof(
                            char)));
                      strcpy(funcName, "call ");
                      strcat(funcName, (yyvsp[-3].node)->lex_val->tk_value);
                      update_label((yyvsp[-3].node),funcName); (yyval.node) = (yyvsp[-3].node);
                      parser_identifier_check(tableStackHead, (yyvsp[-3].node)->lex_val->tk_value, FUNCTION);
                      }
#line 1818 "parser.tab.c"
    break;

  case 27: /* func_call: TK_IDENTIFICADOR '(' ')'  */
#line 310 "parser.y"
                                           {
                      (yyval.node) = (yyvsp[-2].node);
                      parser_identifier_check(tableStackHead, (yyvsp[-2].node)->lex_val->tk_value, FUNCTION);
                      }
#line 1827 "parser.tab.c"
    break;

  case 28: /* flux_ctrl: TK_PR_IF '(' exp ')' new_table comm_block cleanup_table TK_PR_ELSE new_table comm_block cleanup_table  */
#line 316 "parser.y"
                                                                                                                     {
                  update_label((yyvsp[-10].node),"if");
                  add_child((yyvsp[-10].node),(yyvsp[-8].node));
                  if((yyvsp[-5].node) != NULL) {
                    add_child((yyvsp[-10].node),(yyvsp[-5].node));
                    node_stack_pop(&head);
                  }
                  if((yyvsp[-1].node) != NULL) {
                    add_child((yyvsp[-10].node),(yyvsp[-1].node));
                    node_stack_pop(&head);
                  }
                  (yyval.node) = (yyvsp[-10].node);
                }
#line 1845 "parser.tab.c"
    break;

  case 29: /* flux_ctrl: TK_PR_IF '(' exp ')' new_table comm_block cleanup_table  */
#line 330 "parser.y"
                                                                         {
                  update_label((yyvsp[-6].node),"if");
                  add_child((yyvsp[-6].node),(yyvsp[-4].node));
                  if((yyvsp[-1].node) != NULL) {
                    add_child((yyvsp[-6].node),(yyvsp[-1].node));
                    node_stack_pop(&head);
                  };
                  (yyval.node) = (yyvsp[-6].node);
                }
#line 1859 "parser.tab.c"
    break;

  case 30: /* flux_ctrl: TK_PR_WHILE '(' exp ')' new_table comm_block cleanup_table  */
#line 340 "parser.y"
                                                                            {
                  update_label((yyvsp[-6].node),"while");
                  add_child((yyvsp[-6].node),(yyvsp[-4].node));
                  if((yyvsp[-1].node) != NULL) {
                    add_child((yyvsp[-6].node),(yyvsp[-1].node));
                    node_stack_pop(&head);
                  };
                  (yyval.node) = (yyvsp[-6].node);
                }
#line 1873 "parser.tab.c"
    break;

  case 31: /* exp: or_exp  */
#line 353 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1881 "parser.tab.c"
    break;

  case 32: /* or_exp: or_exp TK_OC_OR and_exp  */
#line 358 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"|");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1892 "parser.tab.c"
    break;

  case 33: /* or_exp: and_exp  */
#line 365 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1900 "parser.tab.c"
    break;

  case 34: /* and_exp: and_exp TK_OC_AND eq_exp  */
#line 370 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"&");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1911 "parser.tab.c"
    break;

  case 35: /* and_exp: eq_exp  */
#line 377 "parser.y"
                        {
                      (yyval.node) = (yyvsp[0].node);
                      }
#line 1919 "parser.tab.c"
    break;

  case 36: /* eq_exp: eq_exp TK_OC_EQ comp_exp  */
#line 382 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"==");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1930 "parser.tab.c"
    break;

  case 37: /* eq_exp: eq_exp TK_OC_NE comp_exp  */
#line 389 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"!=");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1941 "parser.tab.c"
    break;

  case 38: /* eq_exp: comp_exp  */
#line 396 "parser.y"
                          {(yyval.node) = (yyvsp[0].node);}
#line 1947 "parser.tab.c"
    break;

  case 39: /* comp_exp: comp_exp '<' sum_exp  */
#line 399 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"<");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1958 "parser.tab.c"
    break;

  case 40: /* comp_exp: comp_exp '>' sum_exp  */
#line 406 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),">");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1969 "parser.tab.c"
    break;

  case 41: /* comp_exp: comp_exp TK_OC_LE sum_exp  */
#line 413 "parser.y"
                                           {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"<=");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1980 "parser.tab.c"
    break;

  case 42: /* comp_exp: comp_exp TK_OC_GE sum_exp  */
#line 420 "parser.y"
                                           {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),">=");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1991 "parser.tab.c"
    break;

  case 43: /* comp_exp: sum_exp  */
#line 427 "parser.y"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1997 "parser.tab.c"
    break;

  case 44: /* sum_exp: sum_exp '+' mult_exp  */
#line 430 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"+");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2008 "parser.tab.c"
    break;

  case 45: /* sum_exp: sum_exp '-' mult_exp  */
#line 437 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"-");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2019 "parser.tab.c"
    break;

  case 46: /* sum_exp: mult_exp  */
#line 444 "parser.y"
                          {
                      (yyval.node) = (yyvsp[0].node);
                      }
#line 2027 "parser.tab.c"
    break;

  case 47: /* mult_exp: mult_exp '*' un_exp  */
#line 449 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"*");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2038 "parser.tab.c"
    break;

  case 48: /* mult_exp: mult_exp '/' un_exp  */
#line 456 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"/");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2049 "parser.tab.c"
    break;

  case 49: /* mult_exp: mult_exp '%' un_exp  */
#line 463 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"%");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2060 "parser.tab.c"
    break;

  case 50: /* mult_exp: un_exp  */
#line 470 "parser.y"
                        {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2068 "parser.tab.c"
    break;

  case 51: /* un_exp: '-' un_exp  */
#line 475 "parser.y"
                            {
                    add_child((yyvsp[-1].node), (yyvsp[0].node));
                    update_label((yyvsp[-1].node),"-");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2078 "parser.tab.c"
    break;

  case 52: /* un_exp: '!' un_exp  */
#line 481 "parser.y"
                            {add_child((yyvsp[-1].node), (yyvsp[0].node));
                    update_label((yyvsp[-1].node),"!");
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2087 "parser.tab.c"
    break;

  case 53: /* un_exp: operand  */
#line 486 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2095 "parser.tab.c"
    break;

  case 54: /* operand: TK_IDENTIFICADOR  */
#line 491 "parser.y"
                                  {
                    parser_identifier_check(tableStackHead, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER);
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2104 "parser.tab.c"
    break;

  case 55: /* operand: lit  */
#line 496 "parser.y"
                     {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2112 "parser.tab.c"
    break;

  case 56: /* operand: func_call  */
#line 500 "parser.y"
                            {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2120 "parser.tab.c"
    break;

  case 57: /* operand: '(' exp ')'  */
#line 504 "parser.y"
                             {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2128 "parser.tab.c"
    break;

  case 58: /* id_list: TK_IDENTIFICADOR  */
#line 511 "parser.y"
                                   {
                    update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                    (yyval.node) = (yyvsp[0].node);

                    //printf("Entering id to stack %s\n", $1->lex_val->tk_value);
                    struct id_stack *idStackEntry = malloc(sizeof(struct id_stack));
                    idStackEntry->current_id = strdup((yyvsp[0].node)->lex_val->tk_value);
                    idStackEntry->next_id = idStackHead;
                    idStackHead = idStackEntry;
                    }
#line 2143 "parser.tab.c"
    break;

  case 59: /* id_list: id_list ';' TK_IDENTIFICADOR  */
#line 522 "parser.y"
                                               {
                    update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                    add_child((yyvsp[-2].node), (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-2].node);

                    //printf("Entering id to stack %s\n", $3->lex_val->tk_value);
                    struct id_stack *idStackEntry = malloc(sizeof(struct id_stack));
                    idStackEntry->current_id = strdup((yyvsp[0].node)->lex_val->tk_value);
                    idStackEntry->next_id = idStackHead;
                    idStackHead = idStackEntry;
                    }
#line 2159 "parser.tab.c"
    break;

  case 60: /* lit: TK_LIT_INT  */
#line 535 "parser.y"
                            {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2167 "parser.tab.c"
    break;

  case 61: /* lit: TK_LIT_FLOAT  */
#line 539 "parser.y"
                              {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2175 "parser.tab.c"
    break;

  case 62: /* lit: TK_LIT_FALSE  */
#line 543 "parser.y"
                              {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2183 "parser.tab.c"
    break;

  case 63: /* lit: TK_LIT_TRUE  */
#line 547 "parser.y"
                             {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2191 "parser.tab.c"
    break;

  case 64: /* type: TK_PR_INT  */
#line 553 "parser.y"
                            {
                    (yyval.filler) = INT;
                    }
#line 2199 "parser.tab.c"
    break;

  case 65: /* type: TK_PR_FLOAT  */
#line 557 "parser.y"
                             {
                    (yyval.filler) = FLOAT;
                    }
#line 2207 "parser.tab.c"
    break;

  case 66: /* type: TK_PR_BOOL  */
#line 561 "parser.y"
                            {
                    (yyval.filler) = BOOL;
                    }
#line 2215 "parser.tab.c"
    break;

  case 67: /* new_table: %empty  */
#line 566 "parser.y"
           { // initialize a new table and push it to stack
                    symbol_table *newTable;
                    initialize_symbol_table(&newTable);
                    table_stack_push(&tableStackHead, newTable);
                }
#line 2225 "parser.tab.c"
    break;

  case 68: /* cleanup_table: %empty  */
#line 572 "parser.y"
                { // pop and free table
                    free_symbol_table(table_stack_pop(&tableStackHead));
                }
#line 2233 "parser.tab.c"
    break;


#line 2237 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 575 "parser.y"


void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
}

