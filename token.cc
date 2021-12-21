#include <cstdarg>
#include "token.h"

// Define: Global variables for the current line and
// most recently constructed token.
int current_line;
token *mytok;

// the following needs to match the order of the tokens declared at
// the top of the .y grammar file.
std::string token_name_array[] =
{ "VOID", "INT", "DOUBLE", "BOOL", "STRING", "CLASS", "INTERFACE", "NULL", "THIS",
"EXTENDS", "IMPLEMENTS", "FOR", "WHILE", "IF", "ELSE", "RETURN", "BREAK", "NEW",
"NEWARRAY", "PRINT", "READINTEGER", "READLINE", "IDENTIFIER", "TYPEIDENTIFIER",
"BOOLLITERAL", "INTLITERAL", "DBLLITERAL", "STRINGLITERAL",
"LE", "GE", "EQ", "NEQ", "AND", "OR", "ARRAY"
};

void lex_error(const char * fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   std::cerr << "line " << current_line << ": lexical error, ";
   vfprintf(stderr, fmt, args);
   std::cerr << std::endl;
   va_end(args);
   exit(1);
}

std::string token_type_name(int type)
{
   // returns a readable name for a given token type
   if (type >= 260)
      return token_name_array[type - 260];
   else
      return std::string(1, (char) type);
}


/****************************************************************************/

std::string token::to_string() const
{
   return token_type_name(type)
          + " " + (text == "" ? "" : text + " ") + "(ln."
          + std::to_string(lineno) + ")";
}

token::token(int type, int lineno, std::string text)
   : type(type), lineno(lineno), text(text) {}

token::~token() {}


int make_token(int type, int lineno, std::string text)
{
   mytok = new token(type, lineno, text);
   return type;
}


std::ostream & operator<<(std::ostream & ostr, const token & tok)
{
   ostr << "token{" << tok.to_string() << "}";
   return ostr;
}
