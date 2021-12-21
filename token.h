#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

// Next three lines borrow parts of the parser's definitions
// for use by the lexer. Most important are the T_ definitions
// for each token type, which come from y.tab.h
struct parse_tree;
#define YYSTYPE parse_tree *
#include "y.tab.h"

// lex error, in the spirit of printf("%s\n", );
void lex_error(const char * fmt, ...);





// return a readable name for a given token type;
std::string token_type_name(int type);

// token struct
struct token
{
   int type;
   int lineno;
   std::string text;
   virtual std::string to_string() const;
   token(int type, int lineno, std::string text="");
   virtual ~token();
};

// sets the global mytok to a
// dynamically allocated instance of the appropriate
// sort of token, and returns the given type.
// This simplifies the lexer enough to make it worthwhile.
int make_token(int type, int lineno, std::string text="");

// and overload the output operator
std::ostream & operator<<(std::ostream & ostr, const token & tok);

// Declare: Global variables for the current line and
// most recently constructed token.
extern token *mytok;
extern int current_line;

#endif
