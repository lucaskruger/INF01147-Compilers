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
#include "../include/iloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_UNDECLARED 10
#define ERR_DECLARED 11
#define ERR_VARIABLE 20
#define ERR_FUNCTION 21

entry_type scanner_data_type;

void parser_declare_identifier(symbol_table *table, char* identifier, entry_nature nature, entry_type data_type);
symbol_table_entry *parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature);
entry_type type_inference(node_t *op1, node_t *op2);

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
        fprintf (stderr,"Line %d: ERROR (%d): Variable %s already declared in this scope.\n", get_line_number(), ERR_DECLARED, identifier);
        exit(ERR_DECLARED);
    }

    scanner_data_type = data_type;

    symbol_table_entry newEntry = create_table_entry(identifier, get_line_number(), nature, data_type, NULL);
    insert_symbol_table(table, newEntry);

    /*print_symbol_table(table);
    printf("\n");*/
}

// checks for ERR_UNDECLARED, ERR_VARIABLE or ERR_FUNCTION on a variable, ignores last two errors if expected_nature is -1. Returns the checked entry if it's valid
symbol_table_entry *parser_identifier_check(table_stack *table, char* identifier, entry_nature expected_nature){

    symbol_table_entry *searched_entry = search_table_stack(&table, identifier);

    if(searched_entry == NULL){
        fprintf (stderr,"Line %d: ERROR (%d): Undeclared identifier %s.\n", get_line_number(), ERR_UNDECLARED, identifier);
        exit(ERR_UNDECLARED);
    } else if(expected_nature != -1){
        if(expected_nature == FUNCTION && searched_entry->nature == IDENTIFIER){
            fprintf (stderr,"Line %d: ERROR (%d): Variable identifier %s used as function.\n", get_line_number(), ERR_VARIABLE, identifier);
            exit(ERR_VARIABLE);
        }
        if(expected_nature == IDENTIFIER && searched_entry->nature == FUNCTION){
            fprintf (stderr,"Line %d: ERROR (%d): Function identifier %s used as variable.\n", get_line_number(), ERR_FUNCTION, identifier);
            exit(ERR_FUNCTION);
        }
    }

    return searched_entry;
}

// returns an entry type based on the type_inference rules defined in the assignment
entry_type type_inference(node_t *op1, node_t *op2){

    entry_type t1 = op1->data_type;
    entry_type t2 = op2->data_type;

    if(t1 == t2){
        return t1;
    }

    if((t1 == FLOAT || t2 == FLOAT) && (t1 == INT || t2 == INT)){
        return FLOAT;
    }

    if((t1 == BOOL || t2 == BOOL) && (t1 == INT || t2 == INT)){
        return INT;
    }

    if((t1 == FLOAT || t2 == FLOAT) && (t1 == BOOL || t2 == BOOL)){
        return FLOAT;
    }
}

symbol_table globalTable = {
    .entry = {
        .identifier = NULL
    },
    .next_entry = NULL,
    .next_offset = 0
};

table_stack symbolTableStack = {
   .table = &globalTable,
   .prev_table = NULL,
};
table_stack *tableStackHead = &symbolTableStack;
table_stack *tableStackBase = &symbolTableStack;

node_s *head = NULL;

struct id_stack idStack = { .current_id = NULL, .next_id = NULL };
struct id_stack *idStackHead = &idStack;


#line 184 "parser.tab.c"

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
  YYSYMBOL_42_1 = 42,                      /* $@1  */
  YYSYMBOL_43_2 = 43,                      /* $@2  */
  YYSYMBOL_par_list = 44,                  /* par_list  */
  YYSYMBOL_45_3 = 45,                      /* $@3  */
  YYSYMBOL_46_4 = 46,                      /* $@4  */
  YYSYMBOL_arg_list = 47,                  /* arg_list  */
  YYSYMBOL_ret_comm = 48,                  /* ret_comm  */
  YYSYMBOL_comm_block = 49,                /* comm_block  */
  YYSYMBOL_comm_lst = 50,                  /* comm_lst  */
  YYSYMBOL_comm = 51,                      /* comm  */
  YYSYMBOL_var_decl = 52,                  /* var_decl  */
  YYSYMBOL_53_5 = 53,                      /* $@5  */
  YYSYMBOL_attrib_comm = 54,               /* attrib_comm  */
  YYSYMBOL_func_call = 55,                 /* func_call  */
  YYSYMBOL_flux_ctrl = 56,                 /* flux_ctrl  */
  YYSYMBOL_exp = 57,                       /* exp  */
  YYSYMBOL_or_exp = 58,                    /* or_exp  */
  YYSYMBOL_and_exp = 59,                   /* and_exp  */
  YYSYMBOL_eq_exp = 60,                    /* eq_exp  */
  YYSYMBOL_comp_exp = 61,                  /* comp_exp  */
  YYSYMBOL_sum_exp = 62,                   /* sum_exp  */
  YYSYMBOL_mult_exp = 63,                  /* mult_exp  */
  YYSYMBOL_un_exp = 64,                    /* un_exp  */
  YYSYMBOL_operand = 65,                   /* operand  */
  YYSYMBOL_id_list = 66,                   /* id_list  */
  YYSYMBOL_lit = 67,                       /* lit  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_new_table = 69,                 /* new_table  */
  YYSYMBOL_cleanup_table = 70              /* cleanup_table  */
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
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

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
       0,   155,   155,   156,   164,   175,   182,   188,   188,   198,
     198,   207,   207,   213,   213,   219,   223,   230,   239,   243,
     248,   256,   280,   284,   288,   292,   296,   300,   305,   305,
     325,   349,   361,   367,   424,   460,   507,   512,   527,   532,
     547,   552,   567,   582,   585,   600,   615,   630,   645,   648,
     663,   678,   683,   698,   713,   721,   726,   739,   751,   756,
     783,   793,   797,   804,   815,   828,   833,   838,   843,   850,
     854,   858,   863,   869
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
  "$accept", "program", "global_var", "func", "header", "$@1", "$@2",
  "par_list", "$@3", "$@4", "arg_list", "ret_comm", "comm_block",
  "comm_lst", "comm", "var_decl", "$@5", "attrib_comm", "func_call",
  "flux_ctrl", "exp", "or_exp", "and_exp", "eq_exp", "comp_exp", "sum_exp",
  "mult_exp", "un_exp", "operand", "id_list", "lit", "type", "new_table",
  "cleanup_table", YY_NULLPTR
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
       0,   -65,   -65,   -65,   -65,    25,     0,     0,   -14,    47,
     -65,    16,   -65,   -65,   -65,    33,   -65,   -65,     6,    32,
     -24,   -65,    68,    72,    48,     2,   -65,   -65,    69,    77,
     -65,   -65,   -65,   -65,   -14,   -65,   -65,    75,     3,    88,
       3,    85,    48,    48,    48,    48,    79,   -65,   -65,   -65,
     -65,    48,   -65,   -65,    89,    91,    -2,    22,    61,    87,
     -65,   -65,   -65,    48,    11,   -65,    84,   -65,   -65,    92,
     -65,     3,   -65,   -65,    83,    90,   -65,   -65,    93,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,   -65,   -65,    55,   -65,   -65,   -65,   -65,   109,
     -65,    94,   -65,   -65,   -65,    91,    -2,    22,    22,    61,
      61,    61,    61,    87,    87,   -65,   -65,   -65,   -65,    48,
      95,   112,   -65,   -14,   -14,   -65,   -65,    97,   -65,   -65,
     -65,   108,   -65,   -65,   -14,   -65,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    69,    70,    71,    72,     0,     2,     2,     0,     0,
      28,     0,     1,     3,     4,    72,    73,     5,     0,     0,
       0,    13,     0,     0,     0,     0,    18,    26,    72,     0,
      23,    24,    25,    27,     0,     6,    63,    29,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    65,    66,    67,
      68,     0,    61,    17,    36,    38,    40,    43,    48,    51,
      55,    58,    60,     0,     0,    19,     0,    20,    73,     0,
       9,     0,    11,    14,     0,     0,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    32,     0,    15,    21,    22,    64,     0,
       7,     0,    72,    72,    62,    37,    39,    41,    42,    44,
      45,    46,    47,    49,    50,    52,    53,    54,    31,     0,
       0,     0,    12,     0,     0,    16,    10,     0,    73,    73,
       8,    34,    35,    72,     0,    73,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,    86,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -33,   -65,    99,    42,   -65,   -65,    57,   -65,
     -40,   -65,    46,    50,    21,   -23,    19,   -37,   -65,   -65,
     -65,    -5,    -4,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   121,    99,    20,   101,    41,
      94,    27,    16,    28,    29,     9,    18,    31,    52,    33,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    37,
      62,    10,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      11,    68,    74,    75,    97,    63,    21,    76,    77,    39,
      40,    78,     1,     2,     3,     1,     2,     3,    44,    81,
      82,    15,    45,    92,    95,    12,    83,    84,     1,     2,
       3,    36,     4,    70,    64,    72,    46,    47,    48,    49,
      50,    85,    86,    51,    93,     1,     2,     3,    22,    19,
      23,    24,   115,   116,   117,    44,    38,    30,    25,    45,
     109,   110,   111,   112,   131,   132,   100,    87,    88,    26,
      30,   136,    32,    46,    47,    48,    49,    50,    17,   125,
      51,     1,     2,     3,    22,    32,    23,    24,   118,   119,
     128,   129,    13,    14,    25,    89,    90,    91,   123,   124,
      42,   135,   107,   108,    43,    65,   113,   114,    67,    69,
      73,    64,    71,    79,    80,    96,   102,    98,   120,   122,
     126,   127,   130,   103,   133,   105,   104,    66,     0,   134,
     106
};

static const yytype_int16 yycheck[] =
{
       4,    34,    42,    43,    68,     3,    11,    44,    45,    33,
      34,    51,    12,    13,    14,    12,    13,    14,     7,    21,
      22,    35,    11,    63,    64,     0,     4,     5,    12,    13,
      14,    25,    32,    38,    32,    40,    25,    26,    27,    28,
      29,    19,    20,    32,    33,    12,    13,    14,    15,    33,
      17,    18,    89,    90,    91,     7,    24,    15,    25,    11,
      83,    84,    85,    86,   128,   129,    71,     6,     7,    36,
      28,   135,    15,    25,    26,    27,    28,    29,    31,   119,
      32,    12,    13,    14,    15,    28,    17,    18,    33,    34,
     123,   124,     6,     7,    25,     8,     9,    10,   102,   103,
      32,   134,    81,    82,    32,    36,    87,    88,    31,    34,
      25,    32,    24,    24,    23,    31,    33,    25,     9,    25,
      25,     9,    25,    33,    16,    79,    33,    28,    -1,   133,
      80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    14,    32,    38,    39,    40,    41,    52,
      68,    69,     0,    38,    38,    35,    49,    31,    53,    33,
      44,    68,    15,    17,    18,    25,    36,    48,    50,    51,
      52,    54,    55,    56,    69,    70,    25,    66,    24,    33,
      34,    46,    32,    32,     7,    11,    25,    26,    27,    28,
      29,    32,    55,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    67,     3,    32,    36,    51,    31,    49,    34,
      68,    24,    68,    25,    57,    57,    64,    64,    57,    24,
      23,    21,    22,     4,     5,    19,    20,     6,     7,     8,
       9,    10,    57,    33,    47,    57,    31,    70,    25,    43,
      68,    45,    33,    33,    33,    59,    60,    61,    61,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    33,    34,
       9,    42,    25,    69,    69,    57,    25,     9,    49,    49,
      25,    70,    70,    16,    69,    49,    70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    39,    40,    42,    41,    43,
      41,    45,    44,    46,    44,    47,    47,    48,    49,    49,
      50,    50,    51,    51,    51,    51,    51,    51,    53,    52,
      54,    55,    55,    56,    56,    56,    57,    58,    58,    59,
      59,    60,    60,    60,    61,    61,    61,    61,    61,    62,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    65,
      65,    65,    65,    66,    66,    67,    67,    67,    67,    68,
      68,    68,    69,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     0,     9,     0,
       8,     0,     5,     0,     3,     1,     3,     2,     2,     3,
       2,     3,     3,     1,     1,     1,     1,     1,     0,     3,
       3,     4,     3,    11,     7,     7,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     1,     1,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     0
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
#line 155 "parser.y"
                  {(yyval.node) = NULL;}
#line 1601 "parser.tab.c"
    break;

  case 3: /* program: global_var program  */
#line 156 "parser.y"
                                    {
                    if((yyvsp[0].node) != NULL){
                      (yyval.node) = (yyvsp[0].node);
                    }else {
                      (yyval.node) = NULL;
                    }
                  }
#line 1613 "parser.tab.c"
    break;

  case 4: /* program: func program  */
#line 164 "parser.y"
                              {
                    if((yyvsp[0].node) != NULL){
                      add_child((yyvsp[-1].node),(yyvsp[0].node));
                    }
                    (yyval.node) = (yyvsp[-1].node);
                    arvore = (void*) (yyval.node);
                    }
#line 1625 "parser.tab.c"
    break;

  case 5: /* global_var: var_decl ','  */
#line 175 "parser.y"
                              {
                    (yyval.node) = NULL;
                    }
#line 1633 "parser.tab.c"
    break;

  case 6: /* func: header comm_block cleanup_table  */
#line 182 "parser.y"
                                                 {
                    add_child((yyvsp[-2].node), (yyvsp[-1].node));
                    (yyval.node) = (yyvsp[-2].node);
                    }
#line 1642 "parser.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 188 "parser.y"
                                                    {scanner_data_type = (yyvsp[0].filler);}
#line 1648 "parser.tab.c"
    break;

  case 8: /* header: '(' new_table par_list ')' TK_OC_OR type $@1 '/' TK_IDENTIFICADOR  */
#line 188 "parser.y"
                                                                                                   {
                //add_child($7,$2);
                update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                (yyval.node) = (yyvsp[0].node);

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, (yyvsp[0].node)->lex_val->tk_value, FUNCTION, (yyvsp[-3].filler));

                }
#line 1662 "parser.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 198 "parser.y"
                                              {scanner_data_type = (yyvsp[0].filler);}
#line 1668 "parser.tab.c"
    break;

  case 10: /* header: '(' new_table ')' TK_OC_OR type $@2 '/' TK_IDENTIFICADOR  */
#line 198 "parser.y"
                                                                                             {
                update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                (yyval.node) = (yyvsp[0].node);

                symbol_table *baseTable = table_stack_base(&tableStackHead);
                parser_declare_identifier(baseTable, (yyvsp[0].node)->lex_val->tk_value, FUNCTION, (yyvsp[-3].filler));
                }
#line 1680 "parser.tab.c"
    break;

  case 11: /* $@3: %empty  */
#line 207 "parser.y"
                              {scanner_data_type = (yyvsp[0].filler);}
#line 1686 "parser.tab.c"
    break;

  case 12: /* par_list: par_list ';' type $@3 TK_IDENTIFICADOR  */
#line 207 "parser.y"
                                                                         {
                //add_child($1,$4);
                (yyval.node) = (yyvsp[-4].node);
                parser_declare_identifier(tableStackHead->table, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER, (yyvsp[-2].filler));
            }
#line 1696 "parser.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 213 "parser.y"
                   {scanner_data_type = (yyvsp[0].filler);}
#line 1702 "parser.tab.c"
    break;

  case 14: /* par_list: type $@4 TK_IDENTIFICADOR  */
#line 213 "parser.y"
                                                              {
                (yyval.node) = (yyvsp[0].node);
                parser_declare_identifier(tableStackHead->table, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER, (yyvsp[-2].filler));
            }
#line 1711 "parser.tab.c"
    break;

  case 15: /* arg_list: exp  */
#line 219 "parser.y"
                     {
                    node_stack_push(&head,(yyvsp[0].node));
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1720 "parser.tab.c"
    break;

  case 16: /* arg_list: arg_list ';' exp  */
#line 223 "parser.y"
                                   {
                    add_child(node_stack_pop(&head), (yyvsp[0].node));
                    node_stack_push(&head, (yyvsp[0].node));
                    (yyval.node) = (yyvsp[-2].node);
                    }
#line 1730 "parser.tab.c"
    break;

  case 17: /* ret_comm: TK_PR_RETURN exp  */
#line 230 "parser.y"
                                   {
                    update_label((yyvsp[-1].node),"return");
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1740 "parser.tab.c"
    break;

  case 18: /* comm_block: '{' '}'  */
#line 239 "parser.y"
                          {
                    (yyval.node) = NULL;
                    }
#line 1748 "parser.tab.c"
    break;

  case 19: /* comm_block: '{' comm_lst '}'  */
#line 243 "parser.y"
                                   {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1756 "parser.tab.c"
    break;

  case 20: /* comm_lst: comm ','  */
#line 248 "parser.y"
                         {
                  (yyval.node) = (yyvsp[-1].node);
                  if((yyvsp[-1].node) != NULL){
                    node_stack_push(&head, (yyvsp[-1].node));
                  }
                  }
#line 1767 "parser.tab.c"
    break;

  case 21: /* comm_lst: comm_lst comm ','  */
#line 256 "parser.y"
                                   {// one conflict 
                    if((yyvsp[-1].node) == NULL){//FIX: oof
                      if((yyvsp[-2].node) == NULL){
                        (yyval.node) = NULL;
                      }else
                        (yyval.node) = (yyvsp[-2].node);
                    }else {
                        if((yyvsp[-1].node)->code)
                            printf("%s", (yyvsp[-1].node)->code);
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
#line 1792 "parser.tab.c"
    break;

  case 22: /* comm: new_table comm_block cleanup_table  */
#line 280 "parser.y"
                                                  {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 1800 "parser.tab.c"
    break;

  case 23: /* comm: var_decl  */
#line 284 "parser.y"
                           {
                     (yyval.node) = NULL;
                    }
#line 1808 "parser.tab.c"
    break;

  case 24: /* comm: attrib_comm  */
#line 288 "parser.y"
                                {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1816 "parser.tab.c"
    break;

  case 25: /* comm: func_call  */
#line 292 "parser.y"
                           {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1824 "parser.tab.c"
    break;

  case 26: /* comm: ret_comm  */
#line 296 "parser.y"
                          {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1832 "parser.tab.c"
    break;

  case 27: /* comm: flux_ctrl  */
#line 300 "parser.y"
                           {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 1840 "parser.tab.c"
    break;

  case 28: /* $@5: %empty  */
#line 305 "parser.y"
                       {scanner_data_type = (yyvsp[0].filler);}
#line 1846 "parser.tab.c"
    break;

  case 29: /* var_decl: type $@5 id_list  */
#line 305 "parser.y"
                                                         {
                                //printf("IDs entered\n");
                                (yyval.node) = NULL;
                                do{
                                    //printf("idStackHead = %s\n", idStackHead->current_id);

                                    // create table entry from ID and insert it to table on top of stack
                                    parser_declare_identifier(tableStackHead->table, idStackHead->current_id, IDENTIFIER, (yyvsp[-2].filler));

                                    struct id_stack *nextHead = idStackHead->next_id;

                                    free(idStackHead->current_id);
                                    free(idStackHead);

                                    idStackHead = nextHead;
                                }
                                while(idStackHead->next_id != NULL);
                                }
#line 1869 "parser.tab.c"
    break;

  case 30: /* attrib_comm: TK_IDENTIFICADOR '=' exp  */
#line 325 "parser.y"
                                                {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"=");
                    (yyval.node) = (yyvsp[-1].node);
                    symbol_table_entry *entry = parser_identifier_check(tableStackHead, (yyvsp[-2].node)->lex_val->tk_value, IDENTIFIER);

                    char *scope;
                    int offset = entry->offset;

                    if(offset < tableStackBase->table->next_offset){
                        scope = strdup("rbss");
                    }
                    else{
                        scope = strdup("rfp");
                        offset -= tableStackHead->prev_table->table->next_offset;
                    }

                    iloc_comm *comm = gen_comm(STOREAI, (yyvsp[0].node)->temp, scope, NULL);
                    (yyval.node)->code = concat((yyvsp[0].node)->code, gen_comm_str(comm, int_to_str(offset), NULL, NULL), "\n", NULL);

                    }
#line 1896 "parser.tab.c"
    break;

  case 31: /* func_call: TK_IDENTIFICADOR '(' arg_list ')'  */
#line 349 "parser.y"
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
#line 1912 "parser.tab.c"
    break;

  case 32: /* func_call: TK_IDENTIFICADOR '(' ')'  */
#line 361 "parser.y"
                                           {
                      (yyval.node) = (yyvsp[-2].node);
                      parser_identifier_check(tableStackHead, (yyvsp[-2].node)->lex_val->tk_value, FUNCTION);
                      }
#line 1921 "parser.tab.c"
    break;

  case 33: /* flux_ctrl: TK_PR_IF '(' exp ')' new_table comm_block cleanup_table TK_PR_ELSE new_table comm_block cleanup_table  */
#line 367 "parser.y"
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

                    char *t_label = gen_label();
                    char *f_label = gen_label();
                    char *aux_label = gen_label();

                    iloc_comm *cbr_comm = gen_comm(CBR, (yyvsp[-8].node)->temp, NULL, NULL);
                    char *cbr_code = concat((yyvsp[-8].node)->code, gen_comm_str(cbr_comm, NULL, t_label, f_label), NULL);

                    iloc_comm *jump_aux_comm = gen_comm(JUMPI, NULL, NULL, NULL);
                    char *jump_aux_code = gen_comm_str(jump_aux_comm, NULL, aux_label, NULL);

                    char *code_true;
                    char *code_false;

                    if((yyvsp[-5].node) != NULL){
                        code_true = (yyvsp[-5].node)->code;
                    }else{
                        code_true = strdup("");
                    }

                    if((yyvsp[-1].node) != NULL){
                        code_false = (yyvsp[-1].node)->code;
                    }else{
                        code_false = strdup("");
                    }

                    (yyval.node)->code = concat(cbr_code, "\n",
                                        t_label, ":\tnop\n", code_true, jump_aux_code, "\n",
                                        f_label, ":\tnop\n", code_false,
                                        aux_label, ":\tnop\n", NULL);

                    free(t_label);
                    free(f_label);
                    free(aux_label);

                    free(cbr_comm);
                    free(jump_aux_comm);
                    free(jump_aux_code);

                    free(code_true);
                    free(code_false);
                    
                    
                }
#line 1982 "parser.tab.c"
    break;

  case 34: /* flux_ctrl: TK_PR_IF '(' exp ')' new_table comm_block cleanup_table  */
#line 424 "parser.y"
                                                                         {
                    update_label((yyvsp[-6].node),"if");
                    add_child((yyvsp[-6].node),(yyvsp[-4].node));
                    if((yyvsp[-1].node) != NULL) {
                        add_child((yyvsp[-6].node),(yyvsp[-1].node));
                        node_stack_pop(&head);
                    };
                    (yyval.node) = (yyvsp[-6].node);

                    char *t_label = gen_label();
                    char *f_label = gen_label();


                    iloc_comm *cbr_comm = gen_comm(CBR, (yyvsp[-4].node)->temp, NULL, NULL);
                    char *cbr_code = concat((yyvsp[-4].node)->code, gen_comm_str(cbr_comm, NULL, t_label, f_label), NULL);

                    char *code_true;

                    if((yyvsp[-1].node) != NULL){
                        code_true = (yyvsp[-1].node)->code;
                    }else{
                        code_true = strdup("");
                    }

                    (yyval.node)->code = concat(cbr_code, "\n",
                                        t_label, ":\tnop\n", code_true,
                                        f_label, ":\tnop\n", NULL);

                    free(t_label);
                    free(f_label);

                    free(cbr_comm);
                    
                    free(code_true);
                }
#line 2022 "parser.tab.c"
    break;

  case 35: /* flux_ctrl: TK_PR_WHILE '(' exp ')' new_table comm_block cleanup_table  */
#line 460 "parser.y"
                                                                            {
                    update_label((yyvsp[-6].node),"while");
                    add_child((yyvsp[-6].node),(yyvsp[-4].node));
                    if((yyvsp[-1].node) != NULL) {
                        add_child((yyvsp[-6].node),(yyvsp[-1].node));
                        node_stack_pop(&head);
                    };
                    (yyval.node) = (yyvsp[-6].node);

                    char *t_label = gen_label();
                    char *f_label = gen_label();
                    char *aux_label = gen_label();

                    iloc_comm *cbr_comm = gen_comm(CBR, (yyvsp[-4].node)->temp, NULL, NULL);
                    char *cbr_code = concat((yyvsp[-4].node)->code, gen_comm_str(cbr_comm, NULL, t_label, f_label), NULL);

                    iloc_comm *jump_aux_comm = gen_comm(JUMPI, NULL, NULL, NULL);
                    char *jump_aux_code = gen_comm_str(jump_aux_comm, NULL, aux_label, NULL);

                    char *code_true;

                    if((yyvsp[-1].node) != NULL){
                        code_true = (yyvsp[-1].node)->code;
                    }else{
                        code_true = strdup("");
                    }

                    (yyval.node)->code = concat(aux_label, ":\tnop\n",
                                        cbr_code, "\n",
                                        t_label, ":\tnop\n", code_true, jump_aux_code, "\n",
                                        f_label, ":\tnop\n", NULL);


                    free(t_label);
                    free(f_label);
                    free(aux_label);

                    free(cbr_comm);
                    free(jump_aux_comm);
                    free(jump_aux_code);
                    
                    free(code_true);
                }
#line 2070 "parser.tab.c"
    break;

  case 36: /* exp: or_exp  */
#line 507 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2078 "parser.tab.c"
    break;

  case 37: /* or_exp: or_exp TK_OC_OR and_exp  */
#line 512 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"|");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(OR, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2097 "parser.tab.c"
    break;

  case 38: /* or_exp: and_exp  */
#line 527 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2105 "parser.tab.c"
    break;

  case 39: /* and_exp: and_exp TK_OC_AND eq_exp  */
#line 532 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"&");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(AND, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2124 "parser.tab.c"
    break;

  case 40: /* and_exp: eq_exp  */
#line 547 "parser.y"
                        {
                      (yyval.node) = (yyvsp[0].node);
                      }
#line 2132 "parser.tab.c"
    break;

  case 41: /* eq_exp: eq_exp TK_OC_EQ comp_exp  */
#line 552 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"==");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_EQ, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2151 "parser.tab.c"
    break;

  case 42: /* eq_exp: eq_exp TK_OC_NE comp_exp  */
#line 567 "parser.y"
                                          {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"!=");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_NE, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2170 "parser.tab.c"
    break;

  case 43: /* eq_exp: comp_exp  */
#line 582 "parser.y"
                          {(yyval.node) = (yyvsp[0].node);}
#line 2176 "parser.tab.c"
    break;

  case 44: /* comp_exp: comp_exp '<' sum_exp  */
#line 585 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"<");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_LT, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2195 "parser.tab.c"
    break;

  case 45: /* comp_exp: comp_exp '>' sum_exp  */
#line 600 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),">");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_GT, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2214 "parser.tab.c"
    break;

  case 46: /* comp_exp: comp_exp TK_OC_LE sum_exp  */
#line 615 "parser.y"
                                           {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"<=");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_LE, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2233 "parser.tab.c"
    break;

  case 47: /* comp_exp: comp_exp TK_OC_GE sum_exp  */
#line 630 "parser.y"
                                           {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),">=");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_GE, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2252 "parser.tab.c"
    break;

  case 48: /* comp_exp: sum_exp  */
#line 645 "parser.y"
                         {(yyval.node) = (yyvsp[0].node);}
#line 2258 "parser.tab.c"
    break;

  case 49: /* sum_exp: sum_exp '+' mult_exp  */
#line 648 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"+");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(ADD, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2277 "parser.tab.c"
    break;

  case 50: /* sum_exp: sum_exp '-' mult_exp  */
#line 663 "parser.y"
                                      {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"-");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(SUB, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2296 "parser.tab.c"
    break;

  case 51: /* sum_exp: mult_exp  */
#line 678 "parser.y"
                          {
                      (yyval.node) = (yyvsp[0].node);
                      }
#line 2304 "parser.tab.c"
    break;

  case 52: /* mult_exp: mult_exp '*' un_exp  */
#line 683 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"*");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(MULT, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2323 "parser.tab.c"
    break;

  case 53: /* mult_exp: mult_exp '/' un_exp  */
#line 698 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"/");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(DIV, (yyvsp[-2].node)->temp, (yyvsp[0].node)->temp, (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[-2].node)->code, (yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2342 "parser.tab.c"
    break;

  case 54: /* mult_exp: mult_exp '%' un_exp  */
#line 713 "parser.y"
                                     {
                    add_child((yyvsp[-1].node),(yyvsp[-2].node));
                    add_child((yyvsp[-1].node),(yyvsp[0].node));
                    update_label((yyvsp[-1].node),"%");
                    update_type((yyvsp[-1].node), type_inference((yyvsp[-2].node), (yyvsp[0].node)));
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2354 "parser.tab.c"
    break;

  case 55: /* mult_exp: un_exp  */
#line 721 "parser.y"
                        {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2362 "parser.tab.c"
    break;

  case 56: /* un_exp: '-' un_exp  */
#line 726 "parser.y"
                            {
                    add_child((yyvsp[-1].node), (yyvsp[0].node));
                    update_label((yyvsp[-1].node),"-");
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(MULT, (yyvsp[0].node)->temp, "-1", (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2379 "parser.tab.c"
    break;

  case 57: /* un_exp: '!' un_exp  */
#line 739 "parser.y"
                            {add_child((yyvsp[-1].node), (yyvsp[0].node));
                    update_label((yyvsp[-1].node),"!");
                    (yyval.node) = (yyvsp[-1].node);

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(CMP_EQ, (yyvsp[0].node)->temp, "0", (yyval.node)->temp);
                    (yyval.node)->code = concat((yyvsp[0].node)->code, gen_comm_str(comm, NULL, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2395 "parser.tab.c"
    break;

  case 58: /* un_exp: operand  */
#line 751 "parser.y"
                         {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2403 "parser.tab.c"
    break;

  case 59: /* operand: TK_IDENTIFICADOR  */
#line 756 "parser.y"
                                  {
                    symbol_table_entry *entry = parser_identifier_check(tableStackHead, (yyvsp[0].node)->lex_val->tk_value, IDENTIFIER);
                    update_type((yyvsp[0].node), entry->data_type);

                    (yyval.node) = (yyvsp[0].node);

                    char *scope;
                    int offset = entry->offset; // get offset to calculate the scope

                    if(offset < tableStackBase->table->next_offset){
                        scope = strdup("rbss");
                    }
                    else{
                        scope = strdup("rfp");
                        offset -= tableStackHead->prev_table->table->next_offset; // get offset relative to the current table
                    }

                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(LOADAI, scope, NULL, (yyval.node)->temp);
                    
                    (yyval.node)->code = concat(gen_comm_str(comm, int_to_str(offset), NULL, NULL), "\n", NULL);

                    free(scope);
                    free(comm);
                    }
#line 2434 "parser.tab.c"
    break;

  case 60: /* operand: lit  */
#line 783 "parser.y"
                     {
                    (yyval.node) = (yyvsp[0].node);
                    (yyval.node)->temp = gen_temp();

                    iloc_comm *comm = gen_comm(LOADI, NULL, (yyval.node)->temp, NULL);
                    (yyval.node)->code = concat(gen_comm_str(comm, (yyvsp[0].node)->lex_val->tk_value, NULL, NULL), "\n", NULL);

                    free(comm);
                    }
#line 2448 "parser.tab.c"
    break;

  case 61: /* operand: func_call  */
#line 793 "parser.y"
                            {
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2456 "parser.tab.c"
    break;

  case 62: /* operand: '(' exp ')'  */
#line 797 "parser.y"
                             {
                    (yyval.node) = (yyvsp[-1].node);
                    }
#line 2464 "parser.tab.c"
    break;

  case 63: /* id_list: TK_IDENTIFICADOR  */
#line 804 "parser.y"
                                   {
                    update_label((yyvsp[0].node),(yyvsp[0].node)->lex_val->tk_value);
                    (yyval.node) = (yyvsp[0].node);

                    //printf("Entering id to stack %s\n", $1->lex_val->tk_value);
                    struct id_stack *idStackEntry = malloc(sizeof(struct id_stack));
                    idStackEntry->current_id = strdup((yyvsp[0].node)->lex_val->tk_value);
                    idStackEntry->next_id = idStackHead;
                    idStackHead = idStackEntry;
                    }
#line 2479 "parser.tab.c"
    break;

  case 64: /* id_list: id_list ';' TK_IDENTIFICADOR  */
#line 815 "parser.y"
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
#line 2495 "parser.tab.c"
    break;

  case 65: /* lit: TK_LIT_INT  */
#line 828 "parser.y"
                            {
                    update_type((yyvsp[0].node), INT);
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2504 "parser.tab.c"
    break;

  case 66: /* lit: TK_LIT_FLOAT  */
#line 833 "parser.y"
                              {
                    update_type((yyvsp[0].node), FLOAT);
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2513 "parser.tab.c"
    break;

  case 67: /* lit: TK_LIT_FALSE  */
#line 838 "parser.y"
                              {
                    update_type((yyvsp[0].node), BOOL);
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2522 "parser.tab.c"
    break;

  case 68: /* lit: TK_LIT_TRUE  */
#line 843 "parser.y"
                             {
                    update_type((yyvsp[0].node), BOOL);
                    (yyval.node) = (yyvsp[0].node);
                    }
#line 2531 "parser.tab.c"
    break;

  case 69: /* type: TK_PR_INT  */
#line 850 "parser.y"
                            {
                    (yyval.filler) = INT;
                    }
#line 2539 "parser.tab.c"
    break;

  case 70: /* type: TK_PR_FLOAT  */
#line 854 "parser.y"
                             {
                    (yyval.filler) = FLOAT;
                    }
#line 2547 "parser.tab.c"
    break;

  case 71: /* type: TK_PR_BOOL  */
#line 858 "parser.y"
                            {
                    (yyval.filler) = BOOL;
                    }
#line 2555 "parser.tab.c"
    break;

  case 72: /* new_table: %empty  */
#line 863 "parser.y"
           { // initialize a new table and push it to stack
                    symbol_table *newTable;
                    initialize_symbol_table(&newTable);
                    table_stack_push(&tableStackHead, newTable);
                }
#line 2565 "parser.tab.c"
    break;

  case 73: /* cleanup_table: %empty  */
#line 869 "parser.y"
                { // pop and free table
                    free_symbol_table(table_stack_pop(&tableStackHead));
                }
#line 2573 "parser.tab.c"
    break;


#line 2577 "parser.tab.c"

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

#line 872 "parser.y"


void yyerror (char const *mensagem){
fprintf (stderr, "%s line: %d\n", mensagem, get_line_number());
}

