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
#line 1 "main.y" /* yacc.c:339  */

    #include "common.h"
    #include <cassert>
    extern TreeNode* root;
    int yylex();
    extern void yyerror(const char*);
    extern int lineno, level, error;
    extern FILE* yyout;
    extern map<string, stack<idAttr>> identifierTable;
    extern map<string, vector<functionAttr>> functionTable;
    extern int checkRange(string id, int level);
    TreeNode* addOperatorNode(TreeNode* t1, TreeNode* t2, OperatorType op, int lineno);
    bool checkFor(TreeNode* t1, TreeNode* t2);
    bool checkForCon(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkWhile(TreeNode* t1, TreeNode* t2);
    bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3);
    bool checkAsg(TreeNode* t1, bool i);
    void setType(TreeNode* &idlist, TreeNode* type, bool ifConst);
    string getValueOfId(TreeNode* n);
    bool setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId);
    int assignId(TreeNode* &id, TreeNode* expr);
    bool checkFuncCall(TreeNode* id, TreeNode* param);
    void generateFuncTable(string funcName, TreeNode* parameterList, TreeNode* returnType);

#line 91 "main.tab.cpp" /* yacc.c:339  */

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
   by #include "main.tab.h".  */
#ifndef YY_YY_MAIN_TAB_H_INCLUDED
# define YY_YY_MAIN_TAB_H_INCLUDED
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
    ASG = 258,
    ADDASG = 259,
    MINASG = 260,
    MULASG = 261,
    DIVASG = 262,
    MODASG = 263,
    ADDASGO = 264,
    MINASGO = 265,
    DOT = 266,
    REF = 267,
    POI = 268,
    NOT = 269,
    ADD = 270,
    MIN = 271,
    MUL = 272,
    DIV = 273,
    MOD = 274,
    EQU = 275,
    GT = 276,
    LT = 277,
    GTQ = 278,
    LTQ = 279,
    NEQ = 280,
    AND = 281,
    OR = 282,
    LBRACE = 283,
    RBRACE = 284,
    LPAREN = 285,
    RPAREN = 286,
    ID = 287,
    INTEGER = 288,
    MAIN = 289,
    DEC = 290,
    OCT = 291,
    HEX = 292,
    CHAR = 293,
    BOOL = 294,
    STRING = 295,
    T_BOOL = 296,
    T_INT = 297,
    T_CHAR = 298,
    T_STRING = 299,
    T_VOID = 300,
    CONST = 301,
    STRUCT = 302,
    IF = 303,
    ELSE = 304,
    WHILE = 305,
    FOR = 306,
    RETURN = 307,
    CONTINUE = 308,
    BREAK = 309,
    PRINTF = 310,
    SCANF = 311,
    SEMICOLON = 312,
    COMMA = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MAIN_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 201 "main.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   422

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

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
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    58,    59,    63,    64,    65,    66,    67,
      68,    69,    73,    74,    75,    79,    93,    97,   109,   119,
     130,   144,   148,   151,   159,   162,   166,   169,   174,   183,
     191,   200,   210,   211,   215,   216,   217,   218,   219,   223,
     234,   248,   259,   273,   287,   295,   313,   314,   315,   316,
     319,   321,   334,   346,   358,   370,   382,   394,   406,   418,
     430,   442,   454,   466,   477,   488,   499,   513,   521,   529,
     537,   545,   553,   561,   569,   577,   585,   593,   601,   609,
     617,   632,   633,   646,   659,   660,   667,   668,   669
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASG", "ADDASG", "MINASG", "MULASG",
  "DIVASG", "MODASG", "ADDASGO", "MINASGO", "DOT", "REF", "POI", "NOT",
  "ADD", "MIN", "MUL", "DIV", "MOD", "EQU", "GT", "LT", "GTQ", "LTQ",
  "NEQ", "AND", "OR", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "ID",
  "INTEGER", "MAIN", "DEC", "OCT", "HEX", "CHAR", "BOOL", "STRING",
  "T_BOOL", "T_INT", "T_CHAR", "T_STRING", "T_VOID", "CONST", "STRUCT",
  "IF", "ELSE", "WHILE", "FOR", "RETURN", "CONTINUE", "BREAK", "PRINTF",
  "SCANF", "SEMICOLON", "COMMA", "$accept", "program", "statements",
  "statement", "function", "functionDefi", "functionDecl", "functionCall",
  "paramList", "scanfIdlist", "printfIdlist", "idlist", "declaration",
  "type", "loop", "forcon", "control", "jump", "assignment", "expr", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF -91

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-91)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     221,   -16,   -13,   320,   -91,   -91,   -91,   -91,   -91,    73,
      29,    32,    40,   282,   -91,   -91,    67,    75,   -91,   131,
     221,   -91,   -91,   -91,   -17,    78,    80,   104,   -91,   -91,
      82,    83,   -91,   -91,   271,   271,   271,   271,   271,   271,
     -91,   -91,   282,   111,   282,   282,   247,   282,   282,   282,
     282,   282,   -91,   -91,   -91,   -91,   364,   107,   108,   -91,
     -91,   -91,   -91,   -91,    11,   124,    95,   -91,   -91,   412,
     -91,   364,   -91,   364,   -91,   364,   -91,   364,   -91,   364,
     -91,   364,    12,   364,   151,    95,   316,   334,   412,   106,
     111,   145,   118,   -91,   -91,   103,   103,   349,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,    35,   121,   282,   147,   152,   148,   -91,   282,   158,
     160,   282,   171,   282,   -91,   103,   103,   -91,   -91,   -91,
     110,   110,   110,   110,   110,   110,   389,   377,   -91,   170,
      61,   191,    76,   364,   -91,   176,   204,   364,   221,   221,
      10,   221,    27,   -91,   -91,   183,   185,   -91,   196,   221,
     282,    56,   114,    53,   141,    53,   -91,   -91,   197,   168,
     364,   179,   -91,   -91,   -91,   -91,   -91,   -91,     8,   221,
     -91,   195,   -91
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    34,    35,    36,    37,    38,     0,
       0,     0,     0,    49,    47,    46,     0,     0,     5,     0,
       2,     3,    11,    14,     0,     0,     0,     0,     9,    10,
       0,     0,    63,    64,    50,    50,    50,    50,    50,    50,
      65,    66,    23,     0,     0,     0,    50,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    48,     0,     0,     1,
       4,    12,    13,     6,    31,     0,    32,     8,     7,    85,
      51,    57,    52,    58,    53,    59,    54,    60,    55,    61,
      56,    62,     0,    22,    31,    33,     0,     0,     0,     0,
       0,     0,     0,    83,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,    84,    67,    68,    69,    70,    71,
      79,    74,    76,    75,    77,    78,    72,    73,    18,     0,
       0,     0,     0,    30,    16,     0,    29,    21,     0,     0,
       0,     0,     0,    27,    19,     0,     0,    17,     0,     0,
       0,     0,     0,    50,     0,    50,    26,    25,     0,     0,
      28,    44,    40,    41,    39,    42,    24,    15,     0,     0,
      43,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -90,   -20,   -91,   -91,   -91,   -91,   -91,   -91,
     -91,   189,   187,    46,   -91,   -91,    57,   -91,   -33,   -27
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    82,   142,
     140,    66,    26,    27,    28,    91,    29,    30,    31,    56
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      60,    70,    72,    74,    76,    78,    80,    71,    73,    75,
      77,    79,    81,    92,   113,    83,    32,    86,    87,    33,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   179,   114,
      61,   117,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,    43,    10,    44,   161,   162,
      45,   164,     1,     2,   138,     1,     2,   163,    46,   169,
     118,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   165,    88,   143,   171,     3,   181,
     154,   147,    90,   139,   150,    57,   152,     4,     5,     6,
       7,     8,     9,    58,    10,   157,    11,    12,    13,    14,
      15,    16,    17,    18,     4,     5,     6,     7,     8,   155,
     100,   101,   102,     1,     2,    98,    99,   100,   101,   102,
     173,    59,   175,   170,   158,    62,    64,    63,    65,    67,
      68,    60,    60,    84,    60,   172,     3,   111,   112,    60,
       1,     2,   115,   116,   113,     4,     5,     6,     7,     8,
       9,    60,    10,   121,    11,    12,    13,    14,    15,    16,
      17,    18,   174,     3,   122,   123,   144,     1,     2,   141,
     146,   145,     4,     5,     6,     7,     8,     9,   148,    10,
     149,    11,    12,    13,    14,    15,    16,    17,    18,   177,
       3,   151,   153,   156,     1,     2,   159,   160,   168,     4,
       5,     6,     7,     8,     9,   166,    10,   167,    11,    12,
      13,    14,    15,    16,    17,    18,   182,     3,   178,   176,
       1,     2,    85,    89,     0,   180,     4,     5,     6,     7,
       8,     9,     0,    10,     0,    11,    12,    13,    14,    15,
      16,    17,    18,     3,     0,     0,     1,     2,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,     0,    10,
       0,    11,    12,    13,    14,    15,    16,    17,    18,    88,
       1,     2,     0,    47,     0,    48,    49,    50,     4,     5,
       6,     7,     8,     9,    47,     0,    48,    49,    50,    51,
       0,     0,     0,    69,    53,     0,     0,     0,     0,    54,
      51,    55,     0,     0,    52,    53,     0,     0,     0,     0,
      54,     0,    55,    34,    35,    36,    37,    38,    39,    40,
      41,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,   119,     0,     0,    42,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,   120,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,   124,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    34,    35,    36,    37,    38,
      39,    40,    41
};

static const yytype_int16 yycheck[] =
{
      20,    34,    35,    36,    37,    38,    39,    34,    35,    36,
      37,    38,    39,    46,     3,    42,    32,    44,    45,    32,
      47,    48,    49,    50,    51,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    30,    28,
      57,    29,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     9,    48,    28,   148,   149,
      28,   151,     9,    10,    29,     9,    10,    57,    28,   159,
      58,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,    57,    32,   113,    31,    32,   179,
      29,   118,    46,    58,   121,    28,   123,    41,    42,    43,
      44,    45,    46,    28,    48,    29,    50,    51,    52,    53,
      54,    55,    56,    57,    41,    42,    43,    44,    45,    58,
      17,    18,    19,     9,    10,    15,    16,    17,    18,    19,
     163,     0,   165,   160,    58,    57,    32,    57,    34,    57,
      57,   161,   162,    32,   164,    31,    32,    40,    40,   169,
       9,    10,    28,    58,     3,    41,    42,    43,    44,    45,
      46,   181,    48,    57,    50,    51,    52,    53,    54,    55,
      56,    57,    31,    32,    29,    57,    29,     9,    10,    58,
      32,    29,    41,    42,    43,    44,    45,    46,    30,    48,
      30,    50,    51,    52,    53,    54,    55,    56,    57,    31,
      32,    30,    32,    12,     9,    10,    30,     3,    12,    41,
      42,    43,    44,    45,    46,    32,    48,    32,    50,    51,
      52,    53,    54,    55,    56,    57,    31,    32,    49,    32,
       9,    10,    43,    46,    -1,   178,    41,    42,    43,    44,
      45,    46,    -1,    48,    -1,    50,    51,    52,    53,    54,
      55,    56,    57,    32,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    -1,    48,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    32,
       9,    10,    -1,    12,    -1,    14,    15,    16,    41,    42,
      43,    44,    45,    46,    12,    -1,    14,    15,    16,    28,
      -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    38,
      28,    40,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      38,    -1,    40,     3,     4,     5,     6,     7,     8,     9,
      10,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    -1,    -1,    28,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    29,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    29,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     3,     4,     5,     6,     7,
       8,     9,    10
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    32,    41,    42,    43,    44,    45,    46,
      48,    50,    51,    52,    53,    54,    55,    56,    57,    60,
      61,    62,    63,    64,    65,    66,    71,    72,    73,    75,
      76,    77,    32,    32,     3,     4,     5,     6,     7,     8,
       9,    10,    28,    72,    28,    28,    28,    12,    14,    15,
      16,    28,    32,    33,    38,    40,    78,    28,    28,     0,
      62,    57,    57,    57,    32,    34,    70,    57,    57,    32,
      77,    78,    77,    78,    77,    78,    77,    78,    77,    78,
      77,    78,    67,    78,    32,    70,    78,    78,    32,    71,
      72,    74,    77,    78,    78,    78,    78,    78,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    40,    40,     3,    28,    28,    58,    29,    58,    29,
      29,    57,    29,    57,    29,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    29,    58,
      69,    58,    68,    78,    29,    29,    32,    78,    30,    30,
      78,    30,    78,    32,    29,    58,    12,    29,    58,    30,
       3,    61,    61,    57,    61,    57,    32,    32,    12,    61,
      78,    31,    31,    77,    31,    77,    32,    31,    49,    30,
      75,    61,    31
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    64,    65,    66,    66,    66,
      66,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    70,    71,    71,    72,    72,    72,    72,    72,    73,
      73,    74,    74,    75,    75,    75,    76,    76,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     2,     1,
       1,     1,     2,     2,     1,     7,     4,     5,     4,     5,
       4,     3,     1,     0,     4,     3,     3,     2,     5,     3,
       3,     1,     2,     3,     1,     1,     1,     1,     1,     7,
       7,     5,     5,     9,     7,    11,     1,     1,     2,     1,
       0,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     3,     1,     1,     1,     1
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
#line 54 "main.y" /* yacc.c:1646  */
    { root = new TreeNode(0, NODE_Prog); root->addChild((yyvsp[0])); }
#line 1450 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 58 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1456 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 59 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); (yyval)->addSibling((yyvsp[0])); }
#line 1462 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 63 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_SKIP); }
#line 1468 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 64 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1474 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 65 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1480 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 66 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1486 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 67 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1492 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 68 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1498 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 69 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1504 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 73 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->addChild((yyvsp[-1])); }
#line 1510 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 74 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1516 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 75 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1522 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 79 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                                        node->setFunctionType(FUNC_DEFI);
                                                        node->setDeclType((yyvsp[-6])->getDeclType());
                                                        node->setIdentifier((string)"main");
                                                        (yyvsp[-6])->setFunctionType(FUNC_TYPE);
                                                        node->addChild((yyvsp[-6]));
                                                        // $6->setFunctionType(FUNC_BODY);
                                                        node->addChild((yyvsp[-1]));
                                                        generateFuncTable((string)"main", nullptr, (yyvsp[-6]));
                                                        (yyval) = node;
                                                    }
#line 1538 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 97 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                    node->setFunctionType(FUNC_CALL);
                                    TreeNode* id = new TreeNode(lineno, NODE_Func);
                                    id->setFunctionType(FUNC_ID);
                                    id->setIdentifier((string)"scanf");
                                    node->setIdentifier((string)"scanf");
                                    node->addChild(id);
                                    node->addChild((yyvsp[-2]));
                                    node->addChild((yyvsp[-1]));
                                    (yyval) = node;
                                    
                                }
#line 1555 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 109 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                    node->setFunctionType(FUNC_CALL);
                                    TreeNode* id = new TreeNode(lineno, NODE_Func);
                                    id->setFunctionType(FUNC_ID);
                                    id->setIdentifier((string)"printf");
                                    node->setIdentifier((string)"printf");
                                    node->addChild(id);
                                    node->addChild((yyvsp[-1]));
                                    (yyval) = node;
                                }
#line 1570 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 119 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = new TreeNode(lineno, NODE_Func);
                                                node->setFunctionType(FUNC_CALL);
                                                TreeNode* id = new TreeNode(lineno, NODE_Func);
                                                id->setFunctionType(FUNC_ID);
                                                id->setIdentifier((string)"printf");
                                                node->setIdentifier((string)"printf");
                                                node->addChild(id);
                                                node->addChild((yyvsp[-2]));
                                                node->addChild((yyvsp[-1]));
                                                (yyval) = node;
                                            }
#line 1586 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 130 "main.y" /* yacc.c:1646  */
    { TreeNode* node = new TreeNode(lineno, NODE_Stmt);
                                node->setFunctionType(FUNC_CALL);
                                node->setIdentifier((yyvsp[-3])->getIdentifier());
                                if(checkFuncCall((yyvsp[-3]), (yyvsp[-1]))){
                                    node->addChild((yyvsp[-3]));
                                    node->addChild((yyvsp[-1]));
                                    (yyval) = node;
                                } else {
                                    yyerror("check function call failed!\n");
                                }
                            }
#line 1602 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 144 "main.y" /* yacc.c:1646  */
    {   (yyvsp[0])->setFunctionType(FUNC_PARAM);
                            (yyval) = (yyvsp[-2]);
                            (yyval)->addSibling((yyvsp[0]));
                        }
#line 1611 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 148 "main.y" /* yacc.c:1646  */
    {   (yyvsp[0])->setFunctionType(FUNC_PARAM);
            (yyval) = (yyvsp[0]); 
        }
#line 1619 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 151 "main.y" /* yacc.c:1646  */
    {  TreeNode* node = new TreeNode(lineno, NODE_Func);
        node->setFunctionType(FUNC_PARAM);
        node->setDeclType(D_VOID);
        (yyval) = node;
    }
#line 1629 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 159 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[-3]);
                                (yyval)->addSibling((yyvsp[0]));
                            }
#line 1637 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 162 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[0]); }
#line 1643 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 166 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[-2]);
                            (yyval)->addSibling((yyvsp[0]));
                        }
#line 1651 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 169 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[0]);
            }
#line 1658 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 174 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[-4]); 
                                assignId((yyvsp[-2]), (yyvsp[0]));
                                (yyvsp[-2])->addChild((yyvsp[0]));
                                (yyval)->addSibling((yyvsp[-2]));
                                if (setEntryOfId((yyvsp[-2])->getIdentifier(), level, (yyvsp[-2])->getDeclType(), getValueOfId((yyvsp[0])), (yyvsp[-2])->getNodeId())){
                                    string msg = (string)"Line@" + to_string((yyvsp[-2])->getLineno()) + (string)" Node@" + to_string((yyvsp[-2])->getNodeId()) + (string)": " + (yyvsp[-2])->getIdentifier() + (string)" ID : redefined.";yyerror(msg.c_str());
                                    (yyvsp[-2])->setIsAlive(false);
                                }
                            }
#line 1672 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 183 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[-2]); 
                        (yyval)->addSibling((yyvsp[0]));
                        if (setEntryOfId((yyvsp[0])->getIdentifier(), level, (yyvsp[0])->getDeclType(), getValueOfId(nullptr), (yyvsp[0])->getNodeId())){
                            string msg = (string)"Line@" + to_string((yyvsp[0])->getLineno()) + (string)" Node@" + to_string((yyvsp[0])->getNodeId()) + (string)": " + (yyvsp[0])->getIdentifier() + (string)" ID : redefined.";
                            yyerror(msg.c_str());
                            (yyvsp[0])->setIsAlive(false);
                        }
                    }
#line 1685 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 191 "main.y" /* yacc.c:1646  */
    {   assignId((yyvsp[-2]), (yyvsp[0]));
                    (yyvsp[-2])->addChild((yyvsp[0]));
                    (yyval) = (yyvsp[-2]);
                    if (setEntryOfId((yyvsp[-2])->getIdentifier(), level, (yyvsp[-2])->getDeclType(), getValueOfId((yyvsp[0])), (yyvsp[-2])->getNodeId())){
                        string msg = (string)"Line@" + to_string((yyvsp[-2])->getLineno()) + (string)" Node@" + to_string((yyvsp[-2])->getNodeId()) + (string)": " + (yyvsp[-2])->getIdentifier() + (string)" ID : redefined.";
                        yyerror(msg.c_str());
                        (yyvsp[-2])->setIsAlive(false);
                    }
                }
#line 1699 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 200 "main.y" /* yacc.c:1646  */
    {   (yyval) = (yyvsp[0]);
                    if (setEntryOfId((yyvsp[0])->getIdentifier(), level, (yyvsp[0])->getDeclType(), getValueOfId(nullptr), (yyvsp[0])->getNodeId())){
                        string msg = (string)"Line@" + to_string((yyvsp[0])->getLineno()) + (string)" Node@" + to_string((yyvsp[0])->getNodeId()) + (string)": " + (yyvsp[0])->getIdentifier() + (string)" ID : redefined.";
                        yyerror(msg.c_str());
                        (yyvsp[0])->setIsAlive(false);
                    }
                }
#line 1711 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 210 "main.y" /* yacc.c:1646  */
    {   setType((yyvsp[0]), (yyvsp[-1]), 0); (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_DECL); (yyval)->addChild((yyvsp[-1])); (yyval)->addChild((yyvsp[0])); }
#line 1717 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 211 "main.y" /* yacc.c:1646  */
    {   setType((yyvsp[0]), (yyvsp[-1]), 1); (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_DECL); (yyval)->addChild((yyvsp[-1])); (yyval)->addChild((yyvsp[0])); }
#line 1723 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 215 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Type); (yyval)->setDeclType(D_BOOL); }
#line 1729 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 216 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Type); (yyval)->setDeclType(D_INT); }
#line 1735 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 217 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Type); (yyval)->setDeclType(D_CHAR); }
#line 1741 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 218 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Type); (yyval)->setDeclType(D_STRING); }
#line 1747 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 219 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Type); (yyval)->setDeclType(D_VOID); }
#line 1753 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 223 "main.y" /* yacc.c:1646  */
    {   if(checkFor((yyvsp[-4]), (yyvsp[-1]))) {
                                                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                            (yyval)->addChild((yyvsp[-4]));
                                                            (yyval)->addChild((yyvsp[-1]));
                                                            (yyval)->setStatementType(STMT_FOR);
                                                            (yyval)->typeCheck();
                                                        } else {
                                                            string msg = (string)"Line@" + to_string(lineno) + (string)" For : Not syntactically defined.";
                                                            yyerror(msg.c_str());
                                                        }                                                      
                                                    }
#line 1769 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 234 "main.y" /* yacc.c:1646  */
    {   if(checkWhile((yyvsp[-4]), (yyvsp[-1]))) {
                                                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                            (yyval)->addChild((yyvsp[-4]));
                                                            (yyval)->addChild((yyvsp[-1]));
                                                            (yyval)->setStatementType(STMT_WHILE);
                                                            (yyval)->typeCheck();
                                                        } else {
                                                            string msg = (string)"Line@" + to_string(lineno) + (string)" While : Not syntactically defined.";
                                                            yyerror(msg.c_str());
                                                        }
                                                    }
#line 1785 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 248 "main.y" /* yacc.c:1646  */
    { if(checkForCon((yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]))) {
                                                        (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                        (yyval)->setStatementType(STMT_FORCON);
                                                        (yyval)->addChild((yyvsp[-4]));
                                                        (yyval)->addChild((yyvsp[-2]));
                                                        (yyval)->addChild((yyvsp[0]));
                                                    } else {
                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                        yyerror(msg.c_str());
                                                    }
                                                }
#line 1801 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 259 "main.y" /* yacc.c:1646  */
    { if(checkForCon((yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]))) {
                                                        (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                        (yyval)->setStatementType(STMT_FORCON);
                                                        (yyval)->addChild((yyvsp[-4]));
                                                        (yyval)->addChild((yyvsp[-2]));
                                                        (yyval)->addChild((yyvsp[0]));
                                                    } else {
                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" ForCon : Not syntactically defined.";
                                                        yyerror(msg.c_str());
                                                    }
                                                }
#line 1817 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 273 "main.y" /* yacc.c:1646  */
    {   if(checkIf((yyvsp[-6]), (yyvsp[-3]), NULL)) {
                                                                        (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                                        (yyval)->addChild((yyvsp[-6]));
                                                                        (yyval)->addChild((yyvsp[-3]));
                                                                        TreeNode* elseNode = new TreeNode(lineno, NODE_ELSE);
                                                                        (yyval)->addChild(elseNode);
                                                                        (yyval)->addChild((yyvsp[0]));
                                                                        (yyval)->setStatementType(STMT_IF);
                                                                        (yyval)->typeCheck();
                                                                    } else {
                                                                        string msg = (string)"Line@" + to_string(lineno) + (string)" If : Not syntactically defined.";
                                                                        yyerror(msg.c_str());
                                                                    }
                                                                }
#line 1836 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 287 "main.y" /* yacc.c:1646  */
    {   if(checkIf((yyvsp[-4]), (yyvsp[-1]), NULL)) {
                                                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                            (yyval)->addChild((yyvsp[-4]));
                                                            (yyval)->addChild((yyvsp[-1]));
                                                            (yyval)->setStatementType(STMT_IF);
                                                            (yyval)->typeCheck();
                                                        }
                                                    }
#line 1849 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 295 "main.y" /* yacc.c:1646  */
    {   if(checkIf((yyvsp[-8]), (yyvsp[-5]), (yyvsp[-1]))) {
                                                                                        (yyval) = new TreeNode(lineno, NODE_Stmt);
                                                                                        (yyval)->addChild((yyvsp[-8]));
                                                                                        (yyval)->addChild((yyvsp[-5]));
                                                                                        TreeNode* elseNode = new TreeNode(lineno, NODE_ELSE);
                                                                                        (yyval)->addChild(elseNode);
                                                                                        (yyval)->addChild((yyvsp[-1]));
                                                                                        (yyval)->setStatementType(STMT_IF);
                                                                                        (yyval)->typeCheck();
                                                                                    } 
                                                                                    // else {
                                                                                    //     string msg = (string)"Line@" + to_string(lineno) + (string)" If : Not syntactically defined.";
                                                                                    //     yyerror(msg.c_str());
                                                                                    // }
                                                                                }
#line 1869 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 313 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_BREAK); }
#line 1875 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 314 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_CONTINUE); }
#line 1881 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 315 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_RETURN); (yyval)->addChild((yyvsp[0])); }
#line 1887 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 316 "main.y" /* yacc.c:1646  */
    { (yyval) = new TreeNode(lineno, NODE_Stmt); (yyval)->setStatementType(STMT_RETURN); }
#line 1893 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 321 "main.y" /* yacc.c:1646  */
    {
                        if (checkAsg((yyvsp[-2]), 0)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1911 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 334 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ADDASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1928 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 346 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MINASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1945 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 358 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MULASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1962 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 370 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(DIVASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1979 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 382 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MODASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 1996 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 394 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 0)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2013 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 406 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ADDASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2030 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 418 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MINASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2047 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 430 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MULASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2064 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 442 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(DIVASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2081 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 454 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-2]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MODASIG);
                            (yyval)->addChild((yyvsp[-2]));
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2098 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 466 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[0]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ADDASIGO);
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2114 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 477 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[0]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MINASIGO);
                            (yyval)->addChild((yyvsp[0]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2130 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 488 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-1]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(ADDASIGO);
                            (yyval)->addChild((yyvsp[-1]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2146 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 499 "main.y" /* yacc.c:1646  */
    {   if(checkAsg((yyvsp[-1]), 1)) {
                            (yyval) = new TreeNode(lineno, NODE_Stmt);
                            (yyval)->setStatementType(STMT_ASIG);
                            (yyval)->setAssignmentType(MINASIGO);
                            (yyval)->addChild((yyvsp[-1]));
                            (yyval)->typeCheck();
                        } else {
                            // string msg = (string)"Line@" + to_string(lineno) + (string)" Assignment : Identifier undefined.";
                            // yyerror(msg.c_str());
                        }
                    }
#line 2162 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 513 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_ADD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    } else {
                        (yyval) = node;
                    }
                    
                }
#line 2175 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 521 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_MIN, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    } else {
                        (yyval) = node;
                    }
                    
                }
#line 2188 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 529 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_MUL, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2201 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 537 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_DIV, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2214 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 545 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_MOD, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2227 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 553 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_AND, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2240 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 561 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_OR, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2253 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 569 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_GT, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2266 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 577 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_GTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2279 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 585 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_LT, lineno); 
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2292 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 593 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_LTQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2305 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 601 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_NEQ, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2318 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 609 "main.y" /* yacc.c:1646  */
    {   TreeNode* node = addOperatorNode((yyvsp[-2]), (yyvsp[0]), OP_EQU, lineno);
                    if (node == nullptr) {
                        yyerror("expr is not variable type");
                    }
                    else {
                        (yyval) = node;
                    }
                }
#line 2331 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 617 "main.y" /* yacc.c:1646  */
    { if((yyvsp[0])->getNodeType() == NODE_Var || (yyvsp[0])->getNodeType() == NODE_ConstVar 
                    || (yyvsp[0])->getNodeType() == NODE_Const || (yyvsp[0])->getNodeType() == NODE_Op) {
                    if ((yyvsp[0])->getDeclType() != D_STRING) {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setStatementType(STMT_EXPR);
                        node->setOperatorType(OP_NOT);
                        node->setDeclType((yyvsp[0])->getDeclType());
                        node->addChild((yyvsp[0]));
                        (yyval) = node;
                    }
                  } else {
                      string msg = (string)"Line@ " + to_string(lineno) + (string)" Node@" + to_string((yyvsp[0])->getNodeType()) + (string)"Type error : NOT operation" ;
                      yyerror(msg.c_str());
                  }
                }
#line 2351 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 632 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]);}
#line 2357 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 633 "main.y" /* yacc.c:1646  */
    { if(((yyvsp[0])->getNodeType() == NODE_Var || (yyvsp[0])->getNodeType() == NODE_ConstVar  || (yyvsp[0])->getNodeType() == NODE_Const) && (yyvsp[0])->getDeclType() == D_INT) {
                    int value = (yyvsp[0])->getIntValue();
                    TreeNode* node = new TreeNode(lineno, NODE_Op);
                    node->setStatementType(STMT_EXPR);
                    node->setOperatorType(OP_MIN);
                    node->setDeclType((yyvsp[0])->getDeclType());
                    node->setIntValue(-value);
                    node->addChild((yyvsp[0]));
                    (yyval) = node;
                  } else {
                      yyerror("UMINUS Type error, this node is not an integer.");
                  }
                }
#line 2375 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 646 "main.y" /* yacc.c:1646  */
    { if((yyvsp[0])->getNodeType() == NODE_Var || (yyvsp[0])->getNodeType() == NODE_ConstVar) {
                    if ((yyvsp[-1])->getIdentifier() != "") {
                        TreeNode* node = new TreeNode(lineno, NODE_Op);
                        node->setStatementType(STMT_EXPR);
                        node->setOperatorType(OP_REF);
                        node->setDeclType((yyvsp[0])->getDeclType());
                        node->addChild((yyvsp[0]));
                        (yyval) = node;
                    }
                  } else {
                      yyerror("REF Type error, this node is not an identifier.");
                  }
                }
#line 2393 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 659 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 2399 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 660 "main.y" /* yacc.c:1646  */
    {    if(identifierTable.find((yyvsp[0])->getIdentifier()) == identifierTable.end()) {
                string msg = (string)"Line@" + to_string((yyvsp[0])->getLineno()) + (string)" Node@" + to_string((yyvsp[0])->getNodeId()) + (string)": " + (yyvsp[0])->getIdentifier() + (string)" NODE_Var/ConstVar : ID not defined.";
                yyerror(msg.c_str());
            }
            (yyval) = (yyvsp[0]);
            
        }
#line 2411 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 667 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2417 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 668 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2423 "main.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 669 "main.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2429 "main.tab.cpp" /* yacc.c:1646  */
    break;


#line 2433 "main.tab.cpp" /* yacc.c:1646  */
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
#line 673 "main.y" /* yacc.c:1906  */


TreeNode* addOperatorNode(TreeNode* t1, TreeNode* t2, OperatorType op, int lineno)
{
    TreeNode* node = nullptr;
    if ((t1->getNodeType() == NODE_Const || t1->getNodeType() == NODE_Var || t1->getNodeType() == NODE_ConstVar) &&
        (t2->getNodeType() == NODE_Const || t2->getNodeType() == NODE_Var || t2->getNodeType() == NODE_ConstVar)) {
        node = new TreeNode(lineno, NODE_Op);
        node->setDeclType(t1->getDeclType());
        node->setStatementType(STMT_EXPR);
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
        if (node->typeCheck() == false) { error++; }
        
    } else if(t1->getStatementType() == STMT_EXPR || t2->getStatementType() == STMT_EXPR) {
        node = new TreeNode(lineno, NODE_Op);
        node->setStatementType(STMT_EXPR);
        node->setDeclType(t1->getDeclType());
        node->setOperatorType(op);
        node->addChild(t1);
        node->addChild(t2);
        if (node->typeCheck() == false) { error++; }
    }
    return node;
}

bool checkFor(TreeNode* t1, TreeNode* t2)
{
    // if((t1->getNodeType() != NODE_Stmt && t1->getNodeType() != NODE_Func) || (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func)) {
    //     return false;
    // }
    if(t1->getNodeType() != NODE_Stmt || (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func)) {
        return false;
    }
    return true;
}

bool checkForCon(TreeNode* t1, TreeNode* t2, TreeNode* t3){
    if(t1->getStatementType() != STMT_ASIG && t1->getStatementType() != STMT_DECL) {
        return false;
    }
    if(t3->getStatementType() != STMT_ASIG || t3->getNodeType() != NODE_Stmt) {
        return false;
    }
    // if(t1->getStatementType() == STMT_ASIG) {
    //     // id should be declared before. checked in ASIG    
    // }
    if (t2->getNodeType() == NODE_Stmt){

    }
    if(t2->getOperatorType() != OP_EQU && t2->getOperatorType() != OP_NEQ &&
        t2->getOperatorType() != OP_GT && t2->getOperatorType() != OP_GTQ &&
        t2->getOperatorType() != OP_LT && t2->getOperatorType() != OP_LTQ) {
            // cout << "check comparison" << endl;
            return false;
    }
    if(t1->getStatementType() == STMT_DECL) {
        TreeNode* node = t1->getChild();
        while(node != nullptr) {
            if (node->getNodeType() == NODE_Var){
                if(identifierTable.find(node->getIdentifier()) != identifierTable.end()) {
                    stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
                    idAttr attr = s.top();
                    attr.level += 1;
                    s.pop();
                    s.push(attr);
                    identifierTable[node->getIdentifier()] = s;
                }
            }
            node = node->getSibling();
        }
    }
    

    return true;
}

bool checkWhile(TreeNode* t1, TreeNode* t2)
{
    if(t2->getNodeType() != NODE_Stmt) {
        string msg = (string)"Node@" + to_string(t2->getNodeId()) + (string)" NODE_While: unexpected type for while body.";
        yyerror(msg.c_str());
        return false;
    }
    return true;
}

bool checkIf(TreeNode* t1, TreeNode* t2, TreeNode* t3)
{
    if (t2->getNodeType() != NODE_Stmt && t2->getNodeType() != NODE_Func) {
        string msg = (string)"Line@" + to_string(t2->getLineno()) + (string)" Node@" + to_string(t2->getNodeId()) + (string)" NODE_If: unexpected type for true statements";
        yyerror(msg.c_str());
        return false;
    }
    if (t3 != NULL && t3->getNodeType() != NODE_Stmt && t3->getNodeType() != NODE_Func) {
        string msg = (string)"Line@" + to_string(t2->getLineno()) + (string)" Node@" + to_string(t3->getNodeId()) + (string)" NODE_If: unexpected type for false statements";
        yyerror(msg.c_str());
        return false;
    }
    return true;
}

bool checkAsg(TreeNode* t1, bool i)
{
    assert (t1 != nullptr);
    // if (t1->getNodeType() != NODE_Var) {
    //     string msg = (string)"variable should be a left value instead of" + TreeNode::nodeType2String(t1->getNodeType());
    //     yyerror(msg.c_str());
    //     return false;
    // }
    // if (i) {
    //     if (t1->getDeclType() != D_INT) {
    //         return false;
    //     }
    // }
    // id check
    int res = checkRange(t1->getIdentifier(), level);
    if(res == -1){
        string msg = (string)"Line@" + to_string(t1->getLineno()) + (string)" Node@" + to_string(t1->getNodeId()) + (string)": " + t1->getIdentifier() + (string)" Assignment : Identifier undefined.";
        yyerror(msg.c_str());
        return false;
    }
    // if (identifierTable.find(t1->getIdentifier()) == identifierTable.end()) {
    //     return false;
    // } else {
    //     stack<idAttr> s = identifierTable.find(t1->getIdentifier())->second;
    //     // cout << "checkAsg" << endl;
    //     if (s.size() == 0) {
    //         return false;
    //     }
    // }
    return true;
}

void setType(TreeNode* &idlist, TreeNode* type, bool ifConst) {
    if(ifConst){
        // iterate nodes to set type and const
        // cout << "ifConst here" << endl;
        TreeNode* node = idlist;
        assert (node != nullptr);
        node->setNodeType(NODE_ConstVar);
        node->setStatementType(STMT_DECL);
        node->setDeclType(type->getDeclType());
        stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
        while(!s.empty()) {
            idAttr attr = s.top();
            attr.isConst = true;
            s.pop();
            s.push(attr);
        }
        identifierTable[node->getIdentifier()] = s;
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_ConstVar);
            node->setDeclType(type->getDeclType());
            node->setStatementType(STMT_DECL);
            stack<idAttr> s = identifierTable.find(node->getIdentifier())->second;
        while(!s.empty()) {
            idAttr attr = s.top();
            attr.isConst = true;
            s.pop();
            s.push(attr);
        }
        identifierTable[node->getIdentifier()] = s;
        }
    } else {
        TreeNode* node = idlist;
        assert (node != nullptr);
        node->setNodeType(NODE_Var);
        node->setStatementType(STMT_DECL);
        node->setDeclType(type->getDeclType());
        while ((node = node->getSibling()) != nullptr) {
            node->setNodeType(NODE_Var);
            node->setStatementType(STMT_DECL);
            node->setDeclType(type->getDeclType());
        }
    }
}

string getValueOfId(TreeNode* n) {
    if (n == nullptr){
        string res = to_string(0);
        return res;
    }
    switch(n->getDeclType()){
        case D_BOOL:
            return to_string((int)n->getBoolValue());
        case D_INT:
            return to_string(n->getIntValue());
        case D_CHAR:{
            string res(1, n->getCharValue());
            return res;
        }
        case D_STRING:{
            return n->getStringValue();
        }
        default:
            return (string)"";
    }
}

bool setEntryOfId(string identifier, int level, DeclType type, string value, int nodeId){
    // cout << identifier << " declared in level " << level << endl;
    idAttr attr;
    attr.level = level;
    attr.type = type;
    // type check
    attr.value = value;
    attr.id = nodeId;
    bool redefined = false;
    stack<idAttr> s, tmp;
    if(identifierTable.find(identifier) != identifierTable.end()) {
        s = (identifierTable.find(identifier)->second);
        tmp = (identifierTable.find(identifier)->second);
    }
    while (!tmp.empty()) {
        if(tmp.top().level == level){
            redefined = true;
            break;
        }
        tmp.pop();
    }
    if(redefined){
        return true;
    } else{
        s.push(attr);
        identifierTable[identifier] = s;
        return false;
    }
}

int assignId(TreeNode* &id, TreeNode* expr){
    id->setDeclType(expr->getDeclType());
    switch(id->getDeclType()){
        case D_BOOL:
        {
            id->setBoolValue(expr->getBoolValue());
            break;
        }
        case D_CHAR:
        {
            id->setCharValue(expr->getCharValue());
            break;
        }
        case D_INT:
        {
            id->setIntValue(expr->getIntValue());
            break;
        }
        case D_STRING:
        {
            id->setStringValue(expr->getStringValue());
            break;
        }
        default:
            break;
    }
    return 0;
    
}

bool checkFuncCall(TreeNode* id, TreeNode* param){
    // cout << "checkFuncCall" << endl;
    if (identifierTable.find(id->getIdentifier()) == identifierTable.end()) {
        if (id->getIdentifier() != (string)"scanf" && id->getIdentifier() != (string)"printf") {
            return false;
        }
    }
    if (id->getFunctionType() != FUNC_ID) {
        return false;
    }
    if (param->getFunctionType() != FUNC_PARAM) {
        return false;
    }
    return true;
}

bool compareFuncAttr(functionAttr a1, functionAttr a2) {
    if (a1.returnValue != a2.returnValue) {
        return false;
    }
    if (a1.parameterList.size() != a2.parameterList.size()) {
        return false;
    }
    for(int i = 0; i < a1.parameterList.size(); i++) {
        if (a1.parameterList[i] != a2.parameterList[i]) {
            return false;
        }
    }
    return true;
}

void generateFuncTable(string funcName, TreeNode* parameterList, TreeNode* returnType){
    functionAttr attr;
    attr.returnValue = returnType->getDeclType();
    bool flagEqual = false;
    if (parameterList != nullptr) {
        attr.parameterList.push_back(parameterList->getDeclType());
        TreeNode* node = parameterList->getSibling();
        flagEqual = false;
        while(node != nullptr) {
            attr.parameterList.push_back(node->getDeclType());
            node = node->getSibling();
        }
    }
    
    if (functionTable.find(funcName) != functionTable.end()) {
        vector<functionAttr> v = functionTable.find(funcName)->second;
        for(vector<functionAttr>::iterator it=v.begin(); it!=v.end();it++){
            if(compareFuncAttr(*it, attr)) {
                flagEqual = true;
                break;
            }
        }
        if (!flagEqual) {
            v.push_back(attr);
            functionTable[funcName] = v;
        }
    } 
    else { 
        vector<functionAttr> v;
        v.push_back(attr);
        functionTable[funcName] = v;
    }
}


