%option nounput
%option noyywrap

%{
#include "token.h"
std::string stringContent;
int blockCommentBegin;
int lastTokReturned = 0;

int make_tok(int token_type, int curr_line, std::string text="") {
	lastTokReturned = make_token(token_type, curr_line, text);
	return lastTokReturned;	
}
%}

IDENTIFIER [a-zA-Z][a-zA-Z0-9_]{0,30}
BAD_IDENTIFIER [a-zA-Z][a-zA-Z0-9_]{31,}
BOOLLITERAL true|false 
INTLITERAL [0-9]+
HEX_LITERAL 0[x|X][0-9A-Fa-f]+ 
DBLLITERAL [0-9]+\.[0-9]*
SCIENTIFIC_LITERAL {DBLLITERAL}[eE][+\-]?{INTLITERAL} 
 
%x STRING
%x BLOCK_COMMENT
%x BRACKET_MULTI

%%

void/[^A-Za-z_0-9](.|\n)* {return make_tok(T_VOID, current_line, yytext); }
double/[^A-Za-z_0-9](.|\n)* {return make_tok(T_DOUBLE, current_line); }
bool/[^A-Za-z_0-9](.|\n)* {return make_tok(T_BOOL, current_line, yytext); }
string/[^A-Za-z_0-9](.|\n)* {return make_tok(T_STRING, current_line, yytext); }
class/[^A-Za-z_0-9](.|\n)* {return make_tok(T_CLASS, current_line, yytext); }
interface/[^A-Za-z_0-9](.|\n)* {return make_tok(T_INTERFACE, current_line, yytext); }
int/[^A-Za-z_0-9](.|\n)* {return make_tok(T_INT, current_line, yytext); }
null/[^A-Za-z_0-9](.|\n)* {return make_tok(T_NULL, current_line, yytext); }
this/[^A-Za-z_0-9](.|\n)* {return make_tok(T_THIS, current_line, yytext); }
extends/[^A-Za-z_0-9](.|\n)* {return make_tok(T_EXTENDS, current_line, yytext); }
implements/[^A-Za-z_0-9](.|\n)* {return make_tok(T_IMPLEMENTS, current_line, yytext); }
for/[^A-Za-z_0-9](.|\n)* {return make_tok(T_FOR, current_line, yytext); }
while/[^A-Za-z_0-9](.|\n)* {return make_tok(T_WHILE, current_line, yytext); }
if/[^A-Za-z_0-9](.|\n)* {return make_tok(T_IF, current_line, yytext); }
else/[^A-Za-z_0-9](.|\n)* {return make_tok(T_ELSE, current_line, yytext); }
return/[^A-Za-z_0-9](.|\n)* {return make_tok(T_RETURN, current_line, yytext); }
break/[^A-Za-z_0-9](.|\n)* {return make_tok(T_BREAK, current_line, yytext); }
NewArray/[^A-Za-z_0-9](.|\n)* {return make_tok(T_NEWARRAY, current_line, yytext); }
New/[^A-Za-z_0-9](.|\n)* {return make_tok(T_NEW, current_line, yytext); }
Print/[^A-Za-z_0-9](.|\n)* {return make_tok(T_PRINT, current_line, yytext); }
ReadInteger/[^A-Za-z_0-9](.|\n)* {return make_tok(T_READINTEGER, current_line, yytext); }
ReadLine/[^A-Za-z_0-9](.|\n)* {return make_tok(T_READLINE, current_line, yytext); }

{BOOLLITERAL} {return make_tok(T_BOOLLITERAL, current_line, yytext); }
{INTLITERAL} {return make_tok(T_INTLITERAL, current_line, yytext); }
{HEX_LITERAL} {return make_tok(T_INTLITERAL, current_line, yytext); }
{DBLLITERAL} {return make_tok(T_DBLLITERAL, current_line, yytext); }
{SCIENTIFIC_LITERAL} {return make_tok(T_DBLLITERAL, current_line, yytext); }
{IDENTIFIER}/[[:space:]]+{IDENTIFIER} { return make_tok(T_TYPEIDENTIFIER, current_line, yytext); }
{IDENTIFIER}/[[:space:]]*\[[[:space:]]*\] { return make_tok(T_TYPEIDENTIFIER, current_line, yytext); }
{IDENTIFIER} {return make_tok(T_IDENTIFIER, current_line, yytext); }

\" { BEGIN(STRING); }
<STRING>\n { lex_error("missing \" at end of string literal"); }
<STRING>\" { BEGIN(INITIAL); return make_tok(T_STRINGLITERAL, current_line, '"' + stringContent + '"'); }
<STRING>[^\n"]* { stringContent = yytext; } 

\/\* { BEGIN(BLOCK_COMMENT); blockCommentBegin = current_line; }
<BLOCK_COMMENT>. { }
<BLOCK_COMMENT>\*\/ { BEGIN(INITIAL); }
<BLOCK_COMMENT><<EOF>> { lex_error("unclosed block comment beginning on line %d", blockCommentBegin); }

<BLOCK_COMMENT,INITIAL,BRACKET_MULTI>\n { current_line++; }

[+\-*/%\\<>=!;,\.()\{\}\[\]] { return make_tok(yytext[0], current_line, ""); }

\<\= { return make_tok(T_LE, current_line); }
\>\= { return make_tok(T_GE, current_line); }
\=\= { return make_tok(T_EQ, current_line); }
\!\= { return make_tok(T_NEQ, current_line); }
\&\& { return make_tok(T_AND, current_line); }
\|\| { return make_tok(T_OR, current_line); }

\[[[:space:]]*\] {return make_tok(T_ARRAY, current_line); };

<INITIAL>\/\/.* { }
<INITIAL,BRACKET_MULTI>[[:blank:]] { }

{BAD_IDENTIFIER} { lex_error("identifier %s too long", yytext); } 
. { lex_error("unrecognized character %s", yytext); }
