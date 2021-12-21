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
#line 42 "decaf.y"

#include "parsetree.h"
#include <vector>
#include <assert.h>
#define YYSTYPE parse_tree *

int yylex();
std::map<std::string, s_class *> extenders = {};
std::map<std::string, std::vector<s_class *>> implementers = {};
extern bool semantic_checks; // defined in the compiler main file.
int variable_num = 0;

/* We need this to see syntax errors. */
int yyerror(char const *s)
{
   std::cout << "line " << current_line << ": ";
   std::cout << s << std::endl;
   // exit at the first error.
   exit(1);
}

s_type * make_type(parse_tree * tree) {
	if (tree->description == "primtype") {
		// return new s_prim(tree->children[0]->tok->text);
		if (tree->children[0]->tok->text != "")
			return new s_prim(tree->children[0]->tok->text);
		else if (tree->children[0]->tok->type == 261)
			return new s_prim("int");
		else if (tree->children[0]->tok->type == 262)
			return new s_prim("double");
		else if (tree->children[0]->tok->type == 263)
			return new s_prim("bool");
		else if (tree->children[0]->tok->type == 264)
			return new s_prim("string");

		return nullptr;
	}
	// else if 
	else if (tree->description == "arraytype") {
		return new s_arraytype(make_type(tree->children[0]));
	}
	else if (tree->description == "usertype")
		return new s_usertype(tree->children[0]->tok->text);
	else
		std::cerr << "we have failed you" << std::endl;

	return nullptr;
}

void remove_dup_interface(s_class * classy, std::string ident){
	std::vector<s_interface *> interfaces = classy->interfaces;
	auto it = interfaces.begin();	
	while (it != interfaces.end()){
		if ((*it)->name == ident)
			it = interfaces.erase(it);
		else
			it++;
	}	
	classy->interfaces = interfaces;
}


#line 134 "decaf.tab.c"

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
    YYUNDEF = 295,                 /* "invalid token"  */
    T_VOID = 260,                  /* "void"  */
    T_INT = 261,                   /* "int"  */
    T_DOUBLE = 262,                /* "double"  */
    T_BOOL = 263,                  /* "bool"  */
    T_STRING = 264,                /* "string"  */
    T_CLASS = 265,                 /* "class"  */
    T_INTERFACE = 266,             /* "interface"  */
    T_NULL = 267,                  /* "null"  */
    T_THIS = 268,                  /* "this"  */
    T_EXTENDS = 269,               /* "extends"  */
    T_IMPLEMENTS = 270,            /* "implements"  */
    T_FOR = 271,                   /* "for"  */
    T_WHILE = 272,                 /* "while"  */
    T_IF = 273,                    /* "if"  */
    T_ELSE = 274,                  /* "else"  */
    T_RETURN = 275,                /* "return"  */
    T_BREAK = 276,                 /* "break"  */
    T_NEW = 277,                   /* "New"  */
    T_NEWARRAY = 278,              /* "NewArray"  */
    T_PRINT = 279,                 /* "Print"  */
    T_READINTEGER = 280,           /* "ReadInteger"  */
    T_READLINE = 281,              /* "ReadLine"  */
    T_IDENTIFIER = 282,            /* T_IDENTIFIER  */
    T_TYPEIDENTIFIER = 283,        /* T_TYPEIDENTIFIER  */
    T_BOOLLITERAL = 284,           /* T_BOOLLITERAL  */
    T_INTLITERAL = 285,            /* T_INTLITERAL  */
    T_DBLLITERAL = 286,            /* T_DBLLITERAL  */
    T_STRINGLITERAL = 287,         /* T_STRINGLITERAL  */
    T_LE = 288,                    /* "<="  */
    T_GE = 289,                    /* ">="  */
    T_EQ = 290,                    /* "=="  */
    T_NEQ = 291,                   /* "!="  */
    T_AND = 292,                   /* "&&"  */
    T_OR = 293,                    /* "||"  */
    T_ARRAY = 294                  /* "[]"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_VOID = 3,                     /* "void"  */
  YYSYMBOL_T_INT = 4,                      /* "int"  */
  YYSYMBOL_T_DOUBLE = 5,                   /* "double"  */
  YYSYMBOL_T_BOOL = 6,                     /* "bool"  */
  YYSYMBOL_T_STRING = 7,                   /* "string"  */
  YYSYMBOL_T_CLASS = 8,                    /* "class"  */
  YYSYMBOL_T_INTERFACE = 9,                /* "interface"  */
  YYSYMBOL_T_NULL = 10,                    /* "null"  */
  YYSYMBOL_T_THIS = 11,                    /* "this"  */
  YYSYMBOL_T_EXTENDS = 12,                 /* "extends"  */
  YYSYMBOL_T_IMPLEMENTS = 13,              /* "implements"  */
  YYSYMBOL_T_FOR = 14,                     /* "for"  */
  YYSYMBOL_T_WHILE = 15,                   /* "while"  */
  YYSYMBOL_T_IF = 16,                      /* "if"  */
  YYSYMBOL_T_ELSE = 17,                    /* "else"  */
  YYSYMBOL_T_RETURN = 18,                  /* "return"  */
  YYSYMBOL_T_BREAK = 19,                   /* "break"  */
  YYSYMBOL_T_NEW = 20,                     /* "New"  */
  YYSYMBOL_T_NEWARRAY = 21,                /* "NewArray"  */
  YYSYMBOL_T_PRINT = 22,                   /* "Print"  */
  YYSYMBOL_T_READINTEGER = 23,             /* "ReadInteger"  */
  YYSYMBOL_T_READLINE = 24,                /* "ReadLine"  */
  YYSYMBOL_T_IDENTIFIER = 25,              /* T_IDENTIFIER  */
  YYSYMBOL_T_TYPEIDENTIFIER = 26,          /* T_TYPEIDENTIFIER  */
  YYSYMBOL_T_BOOLLITERAL = 27,             /* T_BOOLLITERAL  */
  YYSYMBOL_T_INTLITERAL = 28,              /* T_INTLITERAL  */
  YYSYMBOL_T_DBLLITERAL = 29,              /* T_DBLLITERAL  */
  YYSYMBOL_T_STRINGLITERAL = 30,           /* T_STRINGLITERAL  */
  YYSYMBOL_T_LE = 31,                      /* "<="  */
  YYSYMBOL_T_GE = 32,                      /* ">="  */
  YYSYMBOL_T_EQ = 33,                      /* "=="  */
  YYSYMBOL_T_NEQ = 34,                     /* "!="  */
  YYSYMBOL_T_AND = 35,                     /* "&&"  */
  YYSYMBOL_T_OR = 36,                      /* "||"  */
  YYSYMBOL_T_ARRAY = 37,                   /* "[]"  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* ')'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_46_ = 46,                       /* '.'  */
  YYSYMBOL_47_ = 47,                       /* '='  */
  YYSYMBOL_48_ = 48,                       /* '<'  */
  YYSYMBOL_49_ = 49,                       /* '>'  */
  YYSYMBOL_50_ = 50,                       /* '%'  */
  YYSYMBOL_51_ = 51,                       /* '*'  */
  YYSYMBOL_52_ = 52,                       /* '/'  */
  YYSYMBOL_53_ = 53,                       /* '!'  */
  YYSYMBOL_54_ = 54,                       /* '+'  */
  YYSYMBOL_55_ = 55,                       /* '-'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_pgm = 57,                       /* pgm  */
  YYSYMBOL_program = 58,                   /* program  */
  YYSYMBOL_decl = 59,                      /* decl  */
  YYSYMBOL_function_decl = 60,             /* function_decl  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_62_2 = 62,                      /* $@2  */
  YYSYMBOL_63_3 = 63,                      /* $@3  */
  YYSYMBOL_64_4 = 64,                      /* $@4  */
  YYSYMBOL_formals = 65,                   /* formals  */
  YYSYMBOL_stmt_block = 66,                /* stmt_block  */
  YYSYMBOL_67_5 = 67,                      /* $@5  */
  YYSYMBOL_68_6 = 68,                      /* $@6  */
  YYSYMBOL_variable_decl_func = 69,        /* variable_decl_func  */
  YYSYMBOL_variable_decl = 70,             /* variable_decl  */
  YYSYMBOL_variable = 71,                  /* variable  */
  YYSYMBOL_type = 72,                      /* type  */
  YYSYMBOL_primtype = 73,                  /* primtype  */
  YYSYMBOL_arraytype = 74,                 /* arraytype  */
  YYSYMBOL_usertype = 75,                  /* usertype  */
  YYSYMBOL_class_decl = 76,                /* class_decl  */
  YYSYMBOL_77_7 = 77,                      /* $@7  */
  YYSYMBOL_78_8 = 78,                      /* $@8  */
  YYSYMBOL_79_9 = 79,                      /* $@9  */
  YYSYMBOL_80_10 = 80,                     /* $@10  */
  YYSYMBOL_extends_decl = 81,              /* extends_decl  */
  YYSYMBOL_implements_decl = 82,           /* implements_decl  */
  YYSYMBOL_field = 83,                     /* field  */
  YYSYMBOL_interface_decl = 84,            /* interface_decl  */
  YYSYMBOL_85_11 = 85,                     /* $@11  */
  YYSYMBOL_86_12 = 86,                     /* $@12  */
  YYSYMBOL_prototypes = 87,                /* prototypes  */
  YYSYMBOL_prototype = 88,                 /* prototype  */
  YYSYMBOL_89_13 = 89,                     /* $@13  */
  YYSYMBOL_90_14 = 90,                     /* $@14  */
  YYSYMBOL_stmts = 91,                     /* stmts  */
  YYSYMBOL_stmt = 92,                      /* stmt  */
  YYSYMBOL_lvalue = 93,                    /* lvalue  */
  YYSYMBOL_aref = 94,                      /* aref  */
  YYSYMBOL_matched_stmt = 95,              /* matched_stmt  */
  YYSYMBOL_unmatched_stmt = 96,            /* unmatched_stmt  */
  YYSYMBOL_common_if = 97,                 /* common_if  */
  YYSYMBOL_matched_if = 98,                /* matched_if  */
  YYSYMBOL_unmatched_if = 99,              /* unmatched_if  */
  YYSYMBOL_common_while = 100,             /* common_while  */
  YYSYMBOL_matched_while = 101,            /* matched_while  */
  YYSYMBOL_unmatched_while = 102,          /* unmatched_while  */
  YYSYMBOL_matched_for = 103,              /* matched_for  */
  YYSYMBOL_unmatched_for = 104,            /* unmatched_for  */
  YYSYMBOL_print_stmt = 105,               /* print_stmt  */
  YYSYMBOL_break_stmt = 106,               /* break_stmt  */
  YYSYMBOL_return_stmt = 107,              /* return_stmt  */
  YYSYMBOL_nullactuals = 108,              /* nullactuals  */
  YYSYMBOL_actuals = 109,                  /* actuals  */
  YYSYMBOL_level_one = 110,                /* level_one  */
  YYSYMBOL_level_two = 111,                /* level_two  */
  YYSYMBOL_level_three = 112,              /* level_three  */
  YYSYMBOL_level_four = 113,               /* level_four  */
  YYSYMBOL_level_five = 114,               /* level_five  */
  YYSYMBOL_level_six = 115,                /* level_six  */
  YYSYMBOL_level_seven = 116,              /* level_seven  */
  YYSYMBOL_level_eight = 117,              /* level_eight  */
  YYSYMBOL_level_nine = 118,               /* level_nine  */
  YYSYMBOL_level_ten = 119,                /* level_ten  */
  YYSYMBOL_ident_type = 120,               /* ident_type  */
  YYSYMBOL_call = 121,                     /* call  */
  YYSYMBOL_fieldaccess = 122,              /* fieldaccess  */
  YYSYMBOL_level_one_ops = 123,            /* level_one_ops  */
  YYSYMBOL_level_two_ops = 124,            /* level_two_ops  */
  YYSYMBOL_level_three_ops = 125,          /* level_three_ops  */
  YYSYMBOL_level_four_ops = 126,           /* level_four_ops  */
  YYSYMBOL_level_five_ops = 127,           /* level_five_ops  */
  YYSYMBOL_level_six_ops = 128,            /* level_six_ops  */
  YYSYMBOL_level_seven_ops = 129,          /* level_seven_ops  */
  YYSYMBOL_level_eight_ops = 130,          /* level_eight_ops  */
  YYSYMBOL_excl_rule = 131,                /* excl_rule  */
  YYSYMBOL_plus_rule = 132,                /* plus_rule  */
  YYSYMBOL_minus_rule = 133,               /* minus_rule  */
  YYSYMBOL_expr = 134,                     /* expr  */
  YYSYMBOL_nullable_expr = 135,            /* nullable_expr  */
  YYSYMBOL_constants = 136,                /* constants  */
  YYSYMBOL_intliteral = 137,               /* intliteral  */
  YYSYMBOL_doubleliteral = 138,            /* doubleliteral  */
  YYSYMBOL_stringliteral = 139,            /* stringliteral  */
  YYSYMBOL_boolliteral = 140,              /* boolliteral  */
  YYSYMBOL_identifier = 141,               /* identifier  */
  YYSYMBOL_typeidentifier = 142,           /* typeidentifier  */
  YYSYMBOL_void = 143,                     /* void  */
  YYSYMBOL_interface = 144,                /* interface  */
  YYSYMBOL_class = 145,                    /* class  */
  YYSYMBOL_extends = 146,                  /* extends  */
  YYSYMBOL_implements = 147,               /* implements  */
  YYSYMBOL_print = 148,                    /* print  */
  YYSYMBOL_break = 149,                    /* break  */
  YYSYMBOL_return = 150,                   /* return  */
  YYSYMBOL_eq = 151,                       /* eq  */
  YYSYMBOL_neq = 152,                      /* neq  */
  YYSYMBOL_le = 153,                       /* le  */
  YYSYMBOL_ge = 154,                       /* ge  */
  YYSYMBOL_and = 155,                      /* and  */
  YYSYMBOL_or = 156,                       /* or  */
  YYSYMBOL_readint = 157,                  /* readint  */
  YYSYMBOL_readline = 158,                 /* readline  */
  YYSYMBOL_new = 159,                      /* new  */
  YYSYMBOL_newarray = 160,                 /* newarray  */
  YYSYMBOL_integer = 161,                  /* integer  */
  YYSYMBOL_double = 162,                   /* double  */
  YYSYMBOL_string = 163,                   /* string  */
  YYSYMBOL_bool = 164,                     /* bool  */
  YYSYMBOL_this = 165,                     /* this  */
  YYSYMBOL_null = 166,                     /* null  */
  YYSYMBOL_array = 167                     /* array  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   302

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  112
/* YYNRULES -- Number of rules.  */
#define YYNRULES  183
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  277

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
       2,     2,     2,    53,     2,     2,     2,    50,     2,     2,
      38,    39,    51,    54,    40,    55,    46,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      48,    47,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   118,   119,   121,   121,   121,   121,   124,
     125,   124,   152,   153,   152,   176,   177,   178,   180,   180,
     180,   183,   184,   187,   188,   214,   214,   214,   216,   217,
     218,   219,   221,   223,   227,   228,   226,   294,   295,   293,
     316,   317,   318,   320,   321,   322,   324,   325,   326,   334,
     335,   333,   359,   360,   362,   362,   381,   381,   402,   403,
     405,   405,   407,   407,   407,   408,   410,   411,   412,   413,
     414,   415,   416,   417,   419,   420,   421,   423,   425,   426,
     427,   429,   430,   431,   433,   434,   436,   437,   438,   439,
     441,   442,   443,   445,   446,   448,   450,   452,   454,   456,
     458,   460,   462,   464,   466,   468,   470,   472,   474,   476,
     478,   480,   480,   482,   482,   482,   482,   482,   482,   483,
     484,   485,   487,   487,   489,   490,   492,   494,   495,   496,
     497,   497,   498,   498,   498,   499,   500,   500,   501,   502,
     503,   504,   504,   505,   506,   507,   509,   511,   511,   513,
     513,   513,   513,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546
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
  "\"end of file\"", "error", "\"invalid token\"", "\"void\"", "\"int\"",
  "\"double\"", "\"bool\"", "\"string\"", "\"class\"", "\"interface\"",
  "\"null\"", "\"this\"", "\"extends\"", "\"implements\"", "\"for\"",
  "\"while\"", "\"if\"", "\"else\"", "\"return\"", "\"break\"", "\"New\"",
  "\"NewArray\"", "\"Print\"", "\"ReadInteger\"", "\"ReadLine\"",
  "T_IDENTIFIER", "T_TYPEIDENTIFIER", "T_BOOLLITERAL", "T_INTLITERAL",
  "T_DBLLITERAL", "T_STRINGLITERAL", "\"<=\"", "\">=\"", "\"==\"",
  "\"!=\"", "\"&&\"", "\"||\"", "\"[]\"", "'('", "')'", "','", "'{'",
  "'}'", "';'", "'['", "']'", "'.'", "'='", "'<'", "'>'", "'%'", "'*'",
  "'/'", "'!'", "'+'", "'-'", "$accept", "pgm", "program", "decl",
  "function_decl", "$@1", "$@2", "$@3", "$@4", "formals", "stmt_block",
  "$@5", "$@6", "variable_decl_func", "variable_decl", "variable", "type",
  "primtype", "arraytype", "usertype", "class_decl", "$@7", "$@8", "$@9",
  "$@10", "extends_decl", "implements_decl", "field", "interface_decl",
  "$@11", "$@12", "prototypes", "prototype", "$@13", "$@14", "stmts",
  "stmt", "lvalue", "aref", "matched_stmt", "unmatched_stmt", "common_if",
  "matched_if", "unmatched_if", "common_while", "matched_while",
  "unmatched_while", "matched_for", "unmatched_for", "print_stmt",
  "break_stmt", "return_stmt", "nullactuals", "actuals", "level_one",
  "level_two", "level_three", "level_four", "level_five", "level_six",
  "level_seven", "level_eight", "level_nine", "level_ten", "ident_type",
  "call", "fieldaccess", "level_one_ops", "level_two_ops",
  "level_three_ops", "level_four_ops", "level_five_ops", "level_six_ops",
  "level_seven_ops", "level_eight_ops", "excl_rule", "plus_rule",
  "minus_rule", "expr", "nullable_expr", "constants", "intliteral",
  "doubleliteral", "stringliteral", "boolliteral", "identifier",
  "typeidentifier", "void", "interface", "class", "extends", "implements",
  "print", "break", "return", "eq", "neq", "le", "ge", "and", "or",
  "readint", "readline", "new", "newarray", "integer", "double", "string",
  "bool", "this", "null", "array", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-169)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     276,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,    20,
     276,  -169,  -169,  -169,   -16,    -4,  -169,  -169,  -169,  -169,
    -169,  -169,     4,     4,    -2,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,     9,  -169,  -169,  -169,    42,    42,
    -169,  -169,    35,  -169,    48,    -2,    48,    57,    76,  -169,
    -169,    47,     4,  -169,  -169,    47,  -169,  -169,    68,     4,
      82,  -169,    89,   200,   223,  -169,    -4,  -169,     4,  -169,
    -169,  -169,    90,    92,    -4,    90,  -169,  -169,  -169,   206,
     218,  -169,  -169,  -169,  -169,  -169,    95,    98,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,    11,   229,   252,
    -169,    97,    94,   100,  -169,  -169,   102,   107,   109,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
      15,  -169,  -169,  -169,  -169,  -169,   101,  -169,  -169,  -169,
     143,  -169,  -169,   143,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,   113,   116,  -169,    13,   222,    33,  -169,   110,
     111,  -169,   122,    15,  -169,  -169,  -169,   126,  -169,  -169,
    -169,  -169,  -169,   136,   139,   135,   165,   141,   142,   144,
     145,  -169,  -169,  -169,  -169,    15,    15,    15,   148,  -169,
    -169,    15,  -169,   174,  -169,  -169,  -169,    15,  -169,  -169,
      15,  -169,  -169,  -169,    15,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,    15,    15,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,    15,     4,    15,    15,  -169,  -169,  -169,    15,    15,
    -169,  -169,   154,   160,   161,     4,    15,   159,   176,   177,
    -169,   113,   143,   116,  -169,  -169,    34,    33,  -169,  -169,
     172,    51,  -169,    53,    66,  -169,  -169,  -169,  -169,   180,
     191,    15,  -169,  -169,  -169,  -169,  -169,  -169,    15,  -169,
     194,    15,  -169,   268,   195,  -169,  -169,  -169,   203,   202,
    -169,    15,  -169,   204,   143,  -169,  -169
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   159,   177,   178,   180,   179,   161,   160,   158,     0,
       2,     3,     6,     5,     0,     0,    25,    26,    27,     7,
       8,    33,     0,     0,     0,    28,    29,    31,    30,     1,
       4,    23,   157,   183,    12,    32,     9,    49,    40,    40,
      13,    10,     0,   162,    43,     0,    43,     0,     0,    52,
     163,    37,     0,    41,    42,    34,    15,    15,     0,     0,
       0,    44,     0,     0,     0,    50,     0,    53,     0,    45,
      46,    46,     0,    17,     0,     0,    51,    54,    56,     0,
       0,    18,    14,    16,    24,    11,     0,     0,    38,    48,
      47,    35,    21,    15,    15,    39,    36,    58,     0,     0,
      22,   147,     0,     0,   182,   181,     0,     0,     0,   166,
     165,   175,   176,   164,   173,   174,   156,   153,   154,   155,
       0,    19,   143,   145,    73,    59,   113,    64,    60,    61,
     147,    70,    74,   147,    72,    76,    71,    75,    66,    67,
      68,   146,    96,    98,   100,   102,   104,   106,   108,   110,
     112,   118,    63,     0,   142,   141,   148,     0,   111,   149,
     150,   151,   152,    62,     0,     0,     0,     0,     0,     0,
       0,   116,   117,    55,    57,   147,     0,     0,     0,    20,
     127,     0,    79,    60,    82,    83,   172,     0,   128,   171,
       0,   129,   167,   168,     0,   130,   131,   169,   170,   134,
     135,   144,     0,     0,   136,   137,   132,   133,   138,   139,
     140,     0,     0,     0,    90,   113,   109,    69,    90,     0,
      87,    88,     0,     0,     0,     0,     0,     0,     0,     0,
     121,    95,   147,    97,    99,   101,   103,   105,   107,   126,
       0,     0,    91,     0,     0,    93,    89,   114,   115,     0,
       0,     0,    81,    77,    78,    80,    65,   124,     0,   125,
       0,     0,   120,     0,     0,    92,    86,    94,   122,     0,
     123,   147,   119,     0,   147,    84,    85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,  -169,   232,    49,  -169,  -169,  -169,  -169,   -43,
     -53,  -169,  -169,  -169,     2,   -32,     0,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,   207,   199,   179,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,   117,  -125,  -169,  -128,
    -132,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,    43,  -169,  -169,    70,    77,    75,    72,    65,
      83,  -147,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -138,  -117,  -168,
    -169,  -169,  -169,  -169,  -169,   -11,   -15,   211,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     9,    10,    11,    12,    41,    48,    40,    47,    63,
     124,    92,   179,    97,    13,    14,    74,    16,    17,    18,
      19,    62,    96,    60,    95,    44,    51,    79,    20,    42,
      76,    58,    67,    86,    87,   101,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   241,   244,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   269,   151,   152,   181,   187,   190,
     194,   202,   203,   211,   153,   154,   204,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    21,    22,    23,    24,
      45,    52,   164,   165,   166,   195,   196,   206,   207,   191,
     188,   167,   168,   169,   170,    25,    26,    27,    28,   171,
     172,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,   185,   183,   178,    34,   184,   216,   227,   205,    39,
      15,    36,    37,    38,    64,     2,     3,     4,     5,    82,
      29,    32,    85,    32,     8,   104,   105,    31,   215,    32,
      54,    73,    73,    33,    53,   111,   112,     8,   114,   115,
      32,    61,   116,   117,   118,   119,   192,   193,    69,   222,
      98,    99,   -24,   120,    43,    77,   215,    78,    66,   228,
     229,    50,   215,    84,   238,   215,    73,    73,   122,   215,
     123,     1,     2,     3,     4,     5,    49,   215,   215,    15,
      15,    90,    90,   208,   209,   210,   215,    59,   201,   123,
     257,   258,   259,   258,     8,    56,   240,   242,   205,   100,
     255,   242,   245,   273,   254,   260,   261,   104,   105,   250,
      65,   106,   107,   108,    57,   109,   110,   111,   112,   113,
     114,   115,    32,    70,   116,   117,   118,   119,    89,    89,
      71,    81,    83,    93,   264,   120,    94,   173,    81,   121,
     175,   265,   276,   174,   267,   176,   275,   177,   180,   186,
     122,   189,   123,   104,   105,   213,   212,   106,   107,   108,
     214,   109,   110,   111,   112,   113,   114,   115,    32,   217,
     116,   117,   118,   119,   218,   104,   105,   219,   220,   223,
     224,   120,   225,   226,    81,   111,   112,   230,   114,   115,
      32,   232,   116,   117,   118,   119,   122,   246,   123,   247,
     248,   239,   251,   120,     2,     3,     4,     5,   221,     1,
       2,     3,     4,     5,   249,   252,   253,   256,   122,   262,
     123,     1,     2,     3,     4,     5,     8,     2,     3,     4,
       5,   263,     8,     2,     3,     4,     5,   266,   271,    72,
      33,   272,    30,   274,     8,    55,    46,   182,    88,     8,
      80,   231,   270,   197,   198,     8,     2,     3,     4,     5,
      91,   243,    75,   268,   233,   234,   235,   236,   102,    68,
     199,   200,     2,     3,     4,     5,   201,   123,     8,     1,
       2,     3,     4,     5,     6,     7,   237,     0,     0,     0,
       0,   103,     0,    32,     8,     0,     0,     0,     0,     0,
       0,     0,     8
};

static const yytype_int16 yycheck[] =
{
       0,   133,   130,   120,    15,   133,   153,   175,   146,    24,
      10,    22,    23,    24,    57,     4,     5,     6,     7,    72,
       0,    25,    75,    25,    26,    10,    11,    43,   153,    25,
      45,    63,    64,    37,    45,    20,    21,    26,    23,    24,
      25,    52,    27,    28,    29,    30,    33,    34,    59,   166,
      93,    94,    43,    38,    12,    66,   181,    68,    58,   176,
     177,    13,   187,    74,   211,   190,    98,    99,    53,   194,
      55,     3,     4,     5,     6,     7,    41,   202,   203,    79,
      80,    79,    80,    50,    51,    52,   211,    40,    54,    55,
      39,    40,    39,    40,    26,    38,   213,   214,   236,    97,
     232,   218,   219,   271,   232,    39,    40,    10,    11,   226,
      42,    14,    15,    16,    38,    18,    19,    20,    21,    22,
      23,    24,    25,    41,    27,    28,    29,    30,    79,    80,
      41,    41,    40,    38,   251,    38,    38,    43,    41,    42,
      38,   258,   274,    43,   261,    38,   274,    38,    47,    36,
      53,    35,    55,    10,    11,    44,    46,    14,    15,    16,
      38,    18,    19,    20,    21,    22,    23,    24,    25,    43,
      27,    28,    29,    30,    38,    10,    11,    38,    43,    38,
      38,    38,    38,    38,    41,    20,    21,    39,    23,    24,
      25,    17,    27,    28,    29,    30,    53,    43,    55,    39,
      39,   212,    43,    38,     4,     5,     6,     7,    43,     3,
       4,     5,     6,     7,   225,    39,    39,    45,    53,    39,
      55,     3,     4,     5,     6,     7,    26,     4,     5,     6,
       7,    40,    26,     4,     5,     6,     7,    43,    43,    39,
      37,    39,    10,    39,    26,    46,    39,   130,    42,    26,
      71,   181,   263,    31,    32,    26,     4,     5,     6,     7,
      42,   218,    39,   263,   187,   190,   194,   202,    39,    58,
      48,    49,     4,     5,     6,     7,    54,    55,    26,     3,
       4,     5,     6,     7,     8,     9,   203,    -1,    -1,    -1,
      -1,    39,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    26,    57,
      58,    59,    60,    70,    71,    72,    73,    74,    75,    76,
      84,   142,   143,   144,   145,   161,   162,   163,   164,     0,
      59,    43,    25,    37,   141,   167,   141,   141,   141,   142,
      63,    61,    85,    12,    81,   146,    81,    64,    62,    41,
      13,    82,   147,   141,   142,    82,    38,    38,    87,    40,
      79,   141,    77,    65,    65,    42,    72,    88,   143,   141,
      41,    41,    39,    71,    72,    39,    86,   141,   141,    83,
      83,    41,    66,    40,   141,    66,    89,    90,    42,    60,
      70,    42,    67,    38,    38,    80,    78,    69,    65,    65,
      70,    91,    39,    39,    10,    11,    14,    15,    16,    18,
      19,    20,    21,    22,    23,    24,    27,    28,    29,    30,
      38,    42,    53,    55,    66,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   121,   122,   130,   131,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   148,   149,   150,   157,   158,   159,
     160,   165,   166,    43,    43,    38,    38,    38,   134,    68,
      47,   123,    92,    95,    95,    96,    36,   124,   156,    35,
     125,   155,    33,    34,   126,   151,   152,    31,    32,    48,
      49,    54,   127,   128,   132,   133,   153,   154,    50,    51,
      52,   129,    46,    44,    38,    93,   117,    43,    38,    38,
      43,    43,   134,    38,    38,    38,    38,   135,   134,   134,
      39,   111,    17,   112,   113,   114,   115,   116,   117,   141,
     134,   108,   134,   108,   109,   134,    43,    39,    39,   141,
     134,    43,    39,    39,    95,    96,    45,    39,    40,    39,
      39,    40,    39,    40,   134,   134,    43,   134,    72,   120,
     141,    43,    39,   135,    39,    95,    96
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    61,
      62,    60,    63,    64,    60,    65,    65,    65,    67,    68,
      66,    69,    69,    70,    71,    72,    72,    72,    73,    73,
      73,    73,    74,    75,    77,    78,    76,    79,    80,    76,
      81,    81,    81,    82,    82,    82,    83,    83,    83,    85,
      86,    84,    87,    87,    89,    88,    90,    88,    91,    91,
      92,    92,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    98,    99,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   123,   124,   125,
     126,   126,   127,   127,   127,   127,   128,   128,   129,   129,
     129,   130,   130,   131,   132,   133,   134,   135,   135,   136,
     136,   136,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     0,
       0,     8,     0,     0,     8,     0,     3,     2,     0,     0,
       6,     0,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     0,     0,     9,     0,     0,     9,
       0,     2,     2,     0,     2,     3,     0,     2,     2,     0,
       0,     7,     0,     2,     0,     7,     0,     7,     0,     2,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     2,
       4,     4,     2,     2,     9,     9,     5,     2,     2,     3,
       0,     1,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     2,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     6,
       4,     3,     1,     1,     4,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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
  case 2: /* pgm: program  */
#line 113 "decaf.y"
             { top = yyval = yyvsp[0]; }
#line 1864 "decaf.tab.c"
    break;

  case 3: /* program: decl  */
#line 118 "decaf.y"
              { yyval = new parse_tree("program", 1, yyvsp[0]); }
#line 1870 "decaf.tab.c"
    break;

  case 4: /* program: program decl  */
#line 119 "decaf.y"
               { yyvsp[-1] -> add_child(yyvsp[0]); yyval = yyvsp[-1]; }
#line 1876 "decaf.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 124 "decaf.y"
                               { open_scope(); }
#line 1882 "decaf.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 125 "decaf.y"
  { current_function = new s_function; variable_num = current_class ? 1 : 0; }
#line 1888 "decaf.tab.c"
    break;

  case 11: /* function_decl: void identifier $@1 $@2 '(' formals ')' stmt_block  */
#line 127 "decaf.y"
{ 	
  std::string ident = yyvsp[-6]->tok->text;
  semantic_assert(!current_scope->lookup_local(ident),
          "\"%s\" is aleady defined",
          ident.c_str());
    
  for (size_t i = 0; i < yyvsp[-2]->children.size(); i++) {
    std::string identParam = yyvsp[-2]->children[i]->children[1]->tok->text;
    current_function->params.push_back(
      dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
  }

  current_function->owner_class = current_class;
  current_function->return_type = nullptr;

  current_function->owner_class = current_class;
  yyval = new parse_tree("functiondecl", 4, yyvsp[-7], yyvsp[-6], yyvsp[-2], yyvsp[0]); 
  close_scope();
    current_function->num_locals = variable_num;
  if (current_scope->lookup_local(ident))
    current_scope->replace(ident, current_function);
  else
    current_scope->add(ident, current_function);
  current_function = nullptr;
}
#line 1918 "decaf.tab.c"
    break;

  case 12: /* $@3: %empty  */
#line 152 "decaf.y"
                  { open_scope(); }
#line 1924 "decaf.tab.c"
    break;

  case 13: /* $@4: %empty  */
#line 153 "decaf.y"
  { current_function = new s_function; variable_num = current_class ? 1 : 0; }
#line 1930 "decaf.tab.c"
    break;

  case 14: /* function_decl: type identifier $@3 $@4 '(' formals ')' stmt_block  */
#line 155 "decaf.y"
{	
  std::string ident = yyvsp[-6]->tok->text;
  semantic_assert(!current_scope->lookup_local(ident),
          "\"%s\" is aleady defined",
          ident.c_str());
    
  for (size_t i = 0; i < yyvsp[-2]->children.size(); i++) {
    std::string identParam = yyvsp[-2]->children[i]->children[1]->tok->text;
    current_function->params.push_back(
      dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
  }
  current_function->owner_class = current_class;
  current_function->return_type = make_type(yyvsp[-7]);

  yyval = new parse_tree("functiondecl", 4, yyvsp[-7], yyvsp[-6], yyvsp[-2], yyvsp[0]); 
  close_scope();
    current_function->num_locals = variable_num;
  current_scope->add(ident, current_function);
  current_function = nullptr;
}
#line 1955 "decaf.tab.c"
    break;

  case 15: /* formals: %empty  */
#line 176 "decaf.y"
         { yyval = new parse_tree("formals"); }
#line 1961 "decaf.tab.c"
    break;

  case 16: /* formals: formals variable ','  */
#line 177 "decaf.y"
                           {yyvsp[-2]->add_child(yyvsp[-1]); yyval = yyvsp[-2]; }
#line 1967 "decaf.tab.c"
    break;

  case 17: /* formals: formals variable  */
#line 178 "decaf.y"
                       { yyvsp[-1]->add_child(yyvsp[0]); yyval = yyvsp[-1]; }
#line 1973 "decaf.tab.c"
    break;

  case 18: /* $@5: %empty  */
#line 180 "decaf.y"
                { open_scope(); }
#line 1979 "decaf.tab.c"
    break;

  case 19: /* $@6: %empty  */
#line 180 "decaf.y"
                                                                {close_scope(); }
#line 1985 "decaf.tab.c"
    break;

  case 20: /* stmt_block: '{' $@5 variable_decl_func stmts '}' $@6  */
#line 181 "decaf.y"
        { yyval = new parse_tree("stmtblock", 2, yyvsp[-3], yyvsp[-2]); }
#line 1991 "decaf.tab.c"
    break;

  case 21: /* variable_decl_func: %empty  */
#line 183 "decaf.y"
                    { yyval = new parse_tree("vardecls"); }
#line 1997 "decaf.tab.c"
    break;

  case 22: /* variable_decl_func: variable_decl_func variable_decl  */
#line 184 "decaf.y"
                                       { yyvsp[-1]->add_child(yyvsp[0]); yyval = yyvsp[-1]; }
#line 2003 "decaf.tab.c"
    break;

  case 23: /* variable_decl: variable ';'  */
#line 187 "decaf.y"
                            { yyval = yyvsp[-1]; }
#line 2009 "decaf.tab.c"
    break;

  case 24: /* variable: type identifier  */
#line 189 "decaf.y"
{ 
	std::string ident = yyvsp[0]->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());

	s_type * type = make_type(yyvsp[-1]);
	s_var * variable = new s_var(ident, type);
	variable->classy = current_class; //Adding this so variable can look up the name of the class they exist in.

	if (current_function) {
		variable->num = variable_num++;
        if (type->name == "double")
           variable_num++;
		current_function->locals.push_back(variable);
	}
	
	if (current_class && !current_function)
		current_class->attrs.push_back(variable);
			
	variables.push_back(variable);
	current_scope->add(ident, variable);
	yyval = new parse_tree("variable", 2, yyvsp[-1], yyvsp[0]);  
}
#line 2038 "decaf.tab.c"
    break;

  case 28: /* primtype: integer  */
#line 216 "decaf.y"
                  { yyval = new parse_tree("primtype", 1, yyvsp[0]); }
#line 2044 "decaf.tab.c"
    break;

  case 29: /* primtype: double  */
#line 217 "decaf.y"
         { yyval = new parse_tree("primtype", 1, yyvsp[0]); }
#line 2050 "decaf.tab.c"
    break;

  case 30: /* primtype: bool  */
#line 218 "decaf.y"
       { yyval = new parse_tree("primtype", 1, yyvsp[0]); }
#line 2056 "decaf.tab.c"
    break;

  case 31: /* primtype: string  */
#line 219 "decaf.y"
         { yyval = new parse_tree("primtype", 1, yyvsp[0]); }
#line 2062 "decaf.tab.c"
    break;

  case 32: /* arraytype: type array  */
#line 221 "decaf.y"
                      { yyval = new parse_tree("arraytype", 1, yyvsp[-1]); }
#line 2068 "decaf.tab.c"
    break;

  case 33: /* usertype: typeidentifier  */
#line 223 "decaf.y"
                          { yyval = new parse_tree("usertype", 1, yyvsp[0]); }
#line 2074 "decaf.tab.c"
    break;

  case 34: /* $@7: %empty  */
#line 227 "decaf.y"
                        {open_scope(); current_class = new s_class(yyvsp[-2]->tok->text);}
#line 2080 "decaf.tab.c"
    break;

  case 35: /* $@8: %empty  */
#line 228 "decaf.y"
                                      {close_scope(); }
#line 2086 "decaf.tab.c"
    break;

  case 36: /* class_decl: class typeidentifier extends_decl implements_decl $@7 '{' field '}' $@8  */
#line 229 "decaf.y"
{
	assert (current_scope == top_scope);	
	std::string ident = yyvsp[-7]->tok->text;
    
    if (yyvsp[-5]){ 
        std::vector<parse_tree *> children = yyvsp[-5]->children;
        for (size_t i = 0; i < children.size(); i++){   
            std::string implements_ident = yyvsp[-5]->children[i]->tok->text;
            semantics * interface = current_scope->lookup_local(implements_ident);
            if (interface) { 
				s_interface * temp = dynamic_cast<s_interface*>(interface);
				semantic_assert(temp,
						"Implementing a non-interface: \"%s\"",
						implements_ident.c_str());
                current_class->interfaces.push_back(temp);
			} else {
                s_interface * temp = new s_interface(implements_ident);
                temp->defined = false;
                current_scope->add(implements_ident, temp);
                current_class->interfaces.push_back(temp);
				auto it = implementers.find(implements_ident);
				if (it == implementers.end()){
					std::vector<s_class *> vec = {current_class};
					implementers.insert({implements_ident, vec});
				} else 
					implementers[implements_ident].push_back(current_class);
            }
        }
    }

    if (yyvsp[-6]) {
        std::string super_class_ident = yyvsp[-6]->children[0]->tok->text;
        semantics * super_class = current_scope->lookup_local(super_class_ident);
        if (super_class){
			s_class * temp = dynamic_cast<s_class*>(super_class);	
			semantic_assert(temp,
						"Extending a non-class: \"%s\"",
						super_class_ident.c_str());
            current_class->superclass = temp;
		} else {
            s_class * temp = new s_class(super_class_ident);
            temp->defined = false;
            current_scope->add(super_class_ident, temp);
            current_class->superclass = temp;
			extenders.insert(std::pair<std::string, s_class *>(super_class_ident, current_class));
        }
    }
	semantics * exists = current_scope->lookup_local(ident);
	if (exists 
		&& !dynamic_cast<s_class *>(exists)->defined){
		current_scope->replace(ident, current_class);
		auto it = extenders.find(ident);
		if (!(it == extenders.end()))
			it->second->superclass = current_class;
	} else {
		semantic_assert(!exists,
						"\"%s\" is aleady defined",
						ident.c_str());
		current_scope->add(ident, current_class);
	}

	yyval = new parse_tree("class", 4, yyvsp[-7], yyvsp[-6], yyvsp[-5], yyvsp[-2]); 
	current_class = nullptr;
}
#line 2155 "decaf.tab.c"
    break;

  case 37: /* $@9: %empty  */
#line 294 "decaf.y"
        {open_scope(); current_class = new s_class(yyvsp[-2]->tok->text);}
#line 2161 "decaf.tab.c"
    break;

  case 38: /* $@10: %empty  */
#line 295 "decaf.y"
                      {close_scope(); }
#line 2167 "decaf.tab.c"
    break;

  case 39: /* class_decl: class identifier extends_decl implements_decl $@9 '{' field '}' $@10  */
#line 296 "decaf.y"
{
	assert (current_scope == top_scope);	
	std::string ident = yyvsp[-7]->tok->text;

	semantics * temp = current_scope->lookup_local(ident);

	if (temp && !dynamic_cast<s_class *>(temp)->defined){
		current_scope->replace(ident, current_class);
	}
	else {
		semantic_assert(!current_scope->lookup_local(ident),
						"\"%s\" is aleady defined",
						ident.c_str());
		current_scope->add(ident, current_class);
	}

	yyval = new parse_tree("class", 4, yyvsp[-7], yyvsp[-6], yyvsp[-5], yyvsp[-2]); 
	current_class = nullptr;
}
#line 2191 "decaf.tab.c"
    break;

  case 40: /* extends_decl: %empty  */
#line 316 "decaf.y"
              {yyval = nullptr; }
#line 2197 "decaf.tab.c"
    break;

  case 41: /* extends_decl: extends identifier  */
#line 317 "decaf.y"
                     {yyval = new parse_tree("extends", 1, yyvsp[0]); }
#line 2203 "decaf.tab.c"
    break;

  case 42: /* extends_decl: extends typeidentifier  */
#line 318 "decaf.y"
                         {yyval = new parse_tree("extends", 1, yyvsp[0]); }
#line 2209 "decaf.tab.c"
    break;

  case 43: /* implements_decl: %empty  */
#line 320 "decaf.y"
                 {yyval = nullptr; }
#line 2215 "decaf.tab.c"
    break;

  case 44: /* implements_decl: implements identifier  */
#line 321 "decaf.y"
                        { yyval = new parse_tree("implements", 1, yyvsp[0]); }
#line 2221 "decaf.tab.c"
    break;

  case 45: /* implements_decl: implements_decl ',' identifier  */
#line 322 "decaf.y"
                                     {yyvsp[-2]->add_child(yyvsp[0]); yyval = yyvsp[-2]; }
#line 2227 "decaf.tab.c"
    break;

  case 46: /* field: %empty  */
#line 324 "decaf.y"
        {yyval = new parse_tree("fields"); }
#line 2233 "decaf.tab.c"
    break;

  case 47: /* field: field variable_decl  */
#line 325 "decaf.y"
                          {yyvsp[-1]->add_child(yyvsp[0]); yyval =  yyvsp[-1]; }
#line 2239 "decaf.tab.c"
    break;

  case 48: /* field: field function_decl  */
#line 327 "decaf.y"
{
    std::string func_text = yyvsp[0]->children[1]->tok->text;
    current_class->function_map.insert(std::pair<std::string, s_function *>(func_text, dynamic_cast<s_function *>(current_scope->lookup_local(func_text))));
    yyvsp[-1]->add_child(yyvsp[0]); yyval =  yyvsp[-1]; 
}
#line 2249 "decaf.tab.c"
    break;

  case 49: /* $@11: %empty  */
#line 334 "decaf.y"
  {open_scope(); current_interface = new s_interface(yyvsp[0]->tok->text);}
#line 2255 "decaf.tab.c"
    break;

  case 50: /* $@12: %empty  */
#line 335 "decaf.y"
                     {close_scope(); }
#line 2261 "decaf.tab.c"
    break;

  case 51: /* interface_decl: interface identifier $@11 '{' prototypes '}' $@12  */
#line 336 "decaf.y"
{ 
	assert (current_scope == top_scope);	
	std::string ident = yyvsp[-5]->tok->text;
	if (current_scope->lookup_local(ident) && !dynamic_cast<s_interface *>(current_scope->lookup_local(ident))->defined) {
		current_scope->replace(ident, current_interface);
		auto it = implementers.find(ident);
		if (!(it == implementers.end())){
			std::vector<s_class *> classes = it->second;
			for (size_t i = 0; i < classes.size(); i++) {
				remove_dup_interface(classes[i], current_interface->name);
				classes[i]->interfaces.push_back(current_interface);
			}
		}
	} else {
		semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());
		current_scope->add(ident, current_interface);
	}
	yyval = new parse_tree("interface", 2, yyvsp[-5], yyvsp[-2]); 
	current_interface = nullptr;
}
#line 2288 "decaf.tab.c"
    break;

  case 52: /* prototypes: %empty  */
#line 359 "decaf.y"
             {yyval = new parse_tree("prototypes"); }
#line 2294 "decaf.tab.c"
    break;

  case 53: /* prototypes: prototypes prototype  */
#line 360 "decaf.y"
                           { yyvsp[-1]-> add_child(yyvsp[0]); yyval = yyvsp[-1]; }
#line 2300 "decaf.tab.c"
    break;

  case 54: /* $@13: %empty  */
#line 362 "decaf.y"
                            {open_scope(); }
#line 2306 "decaf.tab.c"
    break;

  case 55: /* prototype: type identifier $@13 '(' formals ')' ';'  */
#line 363 "decaf.y"
{
	current_prototype = new s_prototype; 
	yyval = new parse_tree("prototype", 3, yyvsp[-6], yyvsp[-5], yyvsp[-2]); 
	current_prototype->return_type=make_type(yyvsp[-6]);
	for (size_t i = 0; i < yyvsp[-2]->children.size(); i++) {
		std::string identParam = yyvsp[-2]->children[i]->children[1]->tok->text;
		current_prototype->params.push_back(
			dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
	}
	current_interface->prototype_map.insert({yyvsp[-5]->tok->text, current_prototype});
	close_scope();
	std::string ident = yyvsp[-5]->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());
	current_scope->add(ident, current_prototype);
	current_prototype = nullptr;
}
#line 2329 "decaf.tab.c"
    break;

  case 56: /* $@14: %empty  */
#line 381 "decaf.y"
                  {open_scope(); }
#line 2335 "decaf.tab.c"
    break;

  case 57: /* prototype: void identifier $@14 '(' formals ')' ';'  */
#line 382 "decaf.y"
{
	current_prototype = new s_prototype; 
	yyval = new parse_tree("prototype", 3, yyvsp[-6], yyvsp[-5], yyvsp[-2]); 
	current_prototype->return_type=nullptr;
	for (size_t i = 0; i < yyvsp[-2]->children.size(); i++) {
		std::string identParam = yyvsp[-2]->children[i]->children[1]->tok->text;
		current_prototype->params.push_back(
			dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
	}
	current_interface->prototype_map.insert({yyvsp[-5]->tok->text, current_prototype});
	current_prototype = nullptr;
	close_scope();
	std::string ident = yyvsp[-5]->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());
	current_scope->add(ident, current_prototype);
	current_prototype = nullptr;
}
#line 2359 "decaf.tab.c"
    break;

  case 58: /* stmts: %empty  */
#line 402 "decaf.y"
       { yyval = new parse_tree("stmts"); }
#line 2365 "decaf.tab.c"
    break;

  case 59: /* stmts: stmts stmt  */
#line 403 "decaf.y"
                 { yyvsp[-1]-> add_child(yyvsp[0]); yyval = yyvsp[-1]; }
#line 2371 "decaf.tab.c"
    break;

  case 65: /* aref: level_ten '[' expr ']'  */
#line 408 "decaf.y"
                              {yyval = new parse_tree("aref", 2, yyvsp[-3], yyvsp[-1]); }
#line 2377 "decaf.tab.c"
    break;

  case 77: /* common_if: "if" '(' expr ')'  */
#line 423 "decaf.y"
                             { yyval = yyvsp[-1]; }
#line 2383 "decaf.tab.c"
    break;

  case 78: /* matched_if: common_if matched_stmt "else" matched_stmt  */
#line 425 "decaf.y"
                                                                 {yyval = new parse_tree("if", 3, yyvsp[-3], yyvsp[-2], yyvsp[0]); }
#line 2389 "decaf.tab.c"
    break;

  case 79: /* unmatched_if: common_if stmt  */
#line 426 "decaf.y"
                             {yyval = new parse_tree("if", 3, yyvsp[-1], yyvsp[0], nullptr); }
#line 2395 "decaf.tab.c"
    break;

  case 80: /* unmatched_if: common_if matched_stmt "else" unmatched_stmt  */
#line 427 "decaf.y"
                                               {yyval = new parse_tree("if", 3, yyvsp[-3], yyvsp[-2], yyvsp[0]); }
#line 2401 "decaf.tab.c"
    break;

  case 81: /* common_while: "while" '(' expr ')'  */
#line 429 "decaf.y"
                                   { yyval = yyvsp[-1];}
#line 2407 "decaf.tab.c"
    break;

  case 82: /* matched_while: common_while matched_stmt  */
#line 430 "decaf.y"
                                         { yyval = new parse_tree("while", 2, yyvsp[-1], yyvsp[0]); }
#line 2413 "decaf.tab.c"
    break;

  case 83: /* unmatched_while: common_while unmatched_stmt  */
#line 431 "decaf.y"
                                             { yyval = new parse_tree("while", 2, yyvsp[-1], yyvsp[0]); }
#line 2419 "decaf.tab.c"
    break;

  case 84: /* matched_for: "for" '(' nullable_expr ';' expr ';' nullable_expr ')' matched_stmt  */
#line 433 "decaf.y"
                                                                                            { yyval = new parse_tree("for", 4, yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 2425 "decaf.tab.c"
    break;

  case 85: /* unmatched_for: "for" '(' nullable_expr ';' expr ';' nullable_expr ')' unmatched_stmt  */
#line 434 "decaf.y"
                                                                                                { yyval = new parse_tree("for", 4, yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]); }
#line 2431 "decaf.tab.c"
    break;

  case 86: /* print_stmt: print '(' actuals ')' ';'  */
#line 436 "decaf.y"
                                      {yyval = new parse_tree("print", 2, yyvsp[-4], yyvsp[-2]); }
#line 2437 "decaf.tab.c"
    break;

  case 87: /* break_stmt: break ';'  */
#line 437 "decaf.y"
                      { yyval = new parse_tree("break", 1, yyvsp[-1]); }
#line 2443 "decaf.tab.c"
    break;

  case 88: /* return_stmt: return ';'  */
#line 438 "decaf.y"
                        { yyval = new parse_tree("return", 1, yyvsp[-1]); }
#line 2449 "decaf.tab.c"
    break;

  case 89: /* return_stmt: return expr ';'  */
#line 439 "decaf.y"
                  { yyval = new parse_tree("return", 2, yyvsp[-2], yyvsp[-1]); }
#line 2455 "decaf.tab.c"
    break;

  case 90: /* nullactuals: %empty  */
#line 441 "decaf.y"
             {yyval = new parse_tree("actuals"); }
#line 2461 "decaf.tab.c"
    break;

  case 91: /* nullactuals: expr  */
#line 442 "decaf.y"
       {yyval = new parse_tree("actuals", 1, yyvsp[0]); }
#line 2467 "decaf.tab.c"
    break;

  case 92: /* nullactuals: nullactuals ',' expr  */
#line 443 "decaf.y"
                           {yyvsp[-2]->add_child(yyvsp[0]); yyval = yyvsp[-2]; }
#line 2473 "decaf.tab.c"
    break;

  case 93: /* actuals: expr  */
#line 445 "decaf.y"
              {yyval = new parse_tree("actuals", 1, yyvsp[0]); }
#line 2479 "decaf.tab.c"
    break;

  case 94: /* actuals: actuals ',' expr  */
#line 446 "decaf.y"
                       {yyvsp[-2]->add_child(yyvsp[0]); yyval = yyvsp[-2]; }
#line 2485 "decaf.tab.c"
    break;

  case 95: /* level_one: lvalue level_one_ops level_two  */
#line 449 "decaf.y"
        { yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 2491 "decaf.tab.c"
    break;

  case 97: /* level_two: level_two level_two_ops level_three  */
#line 453 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2497 "decaf.tab.c"
    break;

  case 99: /* level_three: level_three level_three_ops level_four  */
#line 457 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2503 "decaf.tab.c"
    break;

  case 101: /* level_four: level_five level_four_ops level_five  */
#line 461 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2509 "decaf.tab.c"
    break;

  case 103: /* level_five: level_six level_five_ops level_six  */
#line 465 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2515 "decaf.tab.c"
    break;

  case 105: /* level_six: level_six level_six_ops level_seven  */
#line 469 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2521 "decaf.tab.c"
    break;

  case 107: /* level_seven: level_seven level_seven_ops level_eight  */
#line 473 "decaf.y"
        {yyval = new parse_tree("binop", 3, yyvsp[-2], yyvsp[-1], yyvsp[0]); }
#line 2527 "decaf.tab.c"
    break;

  case 109: /* level_eight: level_eight_ops level_eight  */
#line 477 "decaf.y"
        { yyval = new parse_tree("uop", 2, yyvsp[-1], yyvsp[0]); }
#line 2533 "decaf.tab.c"
    break;

  case 119: /* level_ten: newarray '(' expr ',' ident_type ')'  */
#line 483 "decaf.y"
                                       { yyval = new parse_tree("newarray", 2, yyvsp[-3], yyvsp[-1]); }
#line 2539 "decaf.tab.c"
    break;

  case 120: /* level_ten: new '(' identifier ')'  */
#line 484 "decaf.y"
                         { yyval = new parse_tree("new", 1, yyvsp[-1]); }
#line 2545 "decaf.tab.c"
    break;

  case 121: /* level_ten: '(' expr ')'  */
#line 485 "decaf.y"
               {yyval = yyvsp[-1];}
#line 2551 "decaf.tab.c"
    break;

  case 124: /* call: fieldaccess '(' nullactuals ')'  */
#line 489 "decaf.y"
                                      { yyval = new parse_tree("call", 2, yyvsp[-3], yyvsp[-1]); }
#line 2557 "decaf.tab.c"
    break;

  case 125: /* call: identifier '(' nullactuals ')'  */
#line 490 "decaf.y"
                                 { yyval = new parse_tree("call", 2, yyvsp[-3], yyvsp[-1]); }
#line 2563 "decaf.tab.c"
    break;

  case 126: /* fieldaccess: level_nine '.' identifier  */
#line 492 "decaf.y"
                                           {yyval = new parse_tree("fieldaccess", 2, yyvsp[-2], yyvsp[0]); }
#line 2569 "decaf.tab.c"
    break;

  case 127: /* level_one_ops: '='  */
#line 494 "decaf.y"
                   {yyval = new parse_tree(mytok); }
#line 2575 "decaf.tab.c"
    break;

  case 134: /* level_five_ops: '<'  */
#line 498 "decaf.y"
                               { yyval = new parse_tree(mytok); }
#line 2581 "decaf.tab.c"
    break;

  case 135: /* level_five_ops: '>'  */
#line 499 "decaf.y"
      { yyval = new parse_tree(mytok); }
#line 2587 "decaf.tab.c"
    break;

  case 138: /* level_seven_ops: '%'  */
#line 501 "decaf.y"
                     {yyval = new parse_tree(mytok); }
#line 2593 "decaf.tab.c"
    break;

  case 139: /* level_seven_ops: '*'  */
#line 502 "decaf.y"
      {yyval = new parse_tree(mytok); }
#line 2599 "decaf.tab.c"
    break;

  case 140: /* level_seven_ops: '/'  */
#line 503 "decaf.y"
      {yyval = new parse_tree(mytok); }
#line 2605 "decaf.tab.c"
    break;

  case 143: /* excl_rule: '!'  */
#line 505 "decaf.y"
               {yyval = new parse_tree(mytok); }
#line 2611 "decaf.tab.c"
    break;

  case 144: /* plus_rule: '+'  */
#line 506 "decaf.y"
               { yyval = new parse_tree(mytok); }
#line 2617 "decaf.tab.c"
    break;

  case 145: /* minus_rule: '-'  */
#line 507 "decaf.y"
                { yyval = new parse_tree(mytok); }
#line 2623 "decaf.tab.c"
    break;

  case 147: /* nullable_expr: %empty  */
#line 511 "decaf.y"
               {yyval = nullptr; }
#line 2629 "decaf.tab.c"
    break;

  case 153: /* intliteral: T_INTLITERAL  */
#line 516 "decaf.y"
                         { yyval = new parse_tree(mytok); }
#line 2635 "decaf.tab.c"
    break;

  case 154: /* doubleliteral: T_DBLLITERAL  */
#line 517 "decaf.y"
                            { yyval = new parse_tree(mytok); }
#line 2641 "decaf.tab.c"
    break;

  case 155: /* stringliteral: T_STRINGLITERAL  */
#line 518 "decaf.y"
                               {yyval = new parse_tree(mytok); }
#line 2647 "decaf.tab.c"
    break;

  case 156: /* boolliteral: T_BOOLLITERAL  */
#line 519 "decaf.y"
                           {yyval = new parse_tree(mytok); }
#line 2653 "decaf.tab.c"
    break;

  case 157: /* identifier: T_IDENTIFIER  */
#line 520 "decaf.y"
                         { yyval = new parse_tree(mytok); }
#line 2659 "decaf.tab.c"
    break;

  case 158: /* typeidentifier: T_TYPEIDENTIFIER  */
#line 521 "decaf.y"
                                 { yyval = new parse_tree(mytok); }
#line 2665 "decaf.tab.c"
    break;

  case 159: /* void: "void"  */
#line 522 "decaf.y"
             {yyval = new parse_tree(mytok); }
#line 2671 "decaf.tab.c"
    break;

  case 160: /* interface: "interface"  */
#line 523 "decaf.y"
                       { yyval = new parse_tree(mytok); }
#line 2677 "decaf.tab.c"
    break;

  case 161: /* class: "class"  */
#line 524 "decaf.y"
               { yyval = new parse_tree(mytok); }
#line 2683 "decaf.tab.c"
    break;

  case 162: /* extends: "extends"  */
#line 525 "decaf.y"
                   {yyval = new parse_tree(mytok); }
#line 2689 "decaf.tab.c"
    break;

  case 163: /* implements: "implements"  */
#line 526 "decaf.y"
                         {yyval = new parse_tree(mytok); }
#line 2695 "decaf.tab.c"
    break;

  case 164: /* print: "Print"  */
#line 527 "decaf.y"
               { yyval = new parse_tree(mytok); }
#line 2701 "decaf.tab.c"
    break;

  case 165: /* break: "break"  */
#line 528 "decaf.y"
               {yyval = new parse_tree(mytok); }
#line 2707 "decaf.tab.c"
    break;

  case 166: /* return: "return"  */
#line 529 "decaf.y"
                 {yyval = new parse_tree(mytok); }
#line 2713 "decaf.tab.c"
    break;

  case 167: /* eq: "=="  */
#line 530 "decaf.y"
         {yyval = new parse_tree(mytok); }
#line 2719 "decaf.tab.c"
    break;

  case 168: /* neq: "!="  */
#line 531 "decaf.y"
           {yyval = new parse_tree(mytok); }
#line 2725 "decaf.tab.c"
    break;

  case 169: /* le: "<="  */
#line 532 "decaf.y"
         {yyval = new parse_tree(mytok); }
#line 2731 "decaf.tab.c"
    break;

  case 170: /* ge: ">="  */
#line 533 "decaf.y"
         {yyval = new parse_tree(mytok); }
#line 2737 "decaf.tab.c"
    break;

  case 171: /* and: "&&"  */
#line 534 "decaf.y"
           {yyval = new parse_tree(mytok); }
#line 2743 "decaf.tab.c"
    break;

  case 172: /* or: "||"  */
#line 535 "decaf.y"
         {yyval = new parse_tree(mytok); }
#line 2749 "decaf.tab.c"
    break;

  case 173: /* readint: "ReadInteger"  */
#line 536 "decaf.y"
                       {yyval = new parse_tree(mytok); }
#line 2755 "decaf.tab.c"
    break;

  case 174: /* readline: "ReadLine"  */
#line 537 "decaf.y"
                     {yyval = new parse_tree(mytok); }
#line 2761 "decaf.tab.c"
    break;

  case 175: /* new: "New"  */
#line 538 "decaf.y"
           {yyval = new parse_tree(mytok); }
#line 2767 "decaf.tab.c"
    break;

  case 176: /* newarray: "NewArray"  */
#line 539 "decaf.y"
                     {yyval = new parse_tree(mytok); }
#line 2773 "decaf.tab.c"
    break;

  case 177: /* integer: "int"  */
#line 540 "decaf.y"
               {yyval = new parse_tree(mytok); }
#line 2779 "decaf.tab.c"
    break;

  case 178: /* double: "double"  */
#line 541 "decaf.y"
                 {yyval = new parse_tree(mytok); }
#line 2785 "decaf.tab.c"
    break;

  case 179: /* string: "string"  */
#line 542 "decaf.y"
                 {yyval = new parse_tree(mytok); }
#line 2791 "decaf.tab.c"
    break;

  case 180: /* bool: "bool"  */
#line 543 "decaf.y"
             {yyval = new parse_tree(mytok); }
#line 2797 "decaf.tab.c"
    break;

  case 181: /* this: "this"  */
#line 544 "decaf.y"
             {yyval = new parse_tree(mytok); }
#line 2803 "decaf.tab.c"
    break;

  case 182: /* null: "null"  */
#line 545 "decaf.y"
              {yyval = new parse_tree(mytok); }
#line 2809 "decaf.tab.c"
    break;

  case 183: /* array: "[]"  */
#line 546 "decaf.y"
               {yyval = new parse_tree(mytok); }
#line 2815 "decaf.tab.c"
    break;


#line 2819 "decaf.tab.c"

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

#line 548 "decaf.y"

