/* These are the tokens.
   By convention (in CS 310) they have numbers starting with 260. Take care that
   this list exactly matches the array of strings declared in token.cc. These tokens are only used for multi-character tokens. Single-character tokens
   map to their characters directly.
*/
%token T_VOID 260 "void"
%token T_INT 261 "int"
%token T_DOUBLE 262 "double"
%token T_BOOL 263 "bool"
%token T_STRING 264 "string"
%token T_CLASS 265 "class"
%token T_INTERFACE 266 "interface"
%token T_NULL 267 "null"
%token T_THIS 268 "this"
%token T_EXTENDS 269 "extends"
%token T_IMPLEMENTS 270 "implements"
%token T_FOR 271 "for"
%token T_WHILE 272 "while"
%token T_IF 273 "if"
%token T_ELSE 274 "else"
%token T_RETURN 275 "return"
%token T_BREAK 276 "break"
%token T_NEW 277 "New"
%token T_NEWARRAY 278 "NewArray"
%token T_PRINT 279 "Print"
%token T_READINTEGER 280 "ReadInteger"
%token T_READLINE 281 "ReadLine"
%token T_IDENTIFIER 282  
%token T_TYPEIDENTIFIER 283
%token T_BOOLLITERAL 284
%token T_INTLITERAL 285
%token T_DBLLITERAL 286
%token T_STRINGLITERAL 287
%token T_LE 288 "<="
%token T_GE 289 ">="
%token T_EQ 290 "=="
%token T_NEQ 291 "!="
%token T_AND 292 "&&" 
%token T_OR 293  "||"
%token T_ARRAY 294 "[]"

%{
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

%}

%define parse.error verbose

%%

/* Debugging hint: if you want to test part of the grammar in isolation,
* change this line rather than using the %start directive from yacc/bison.
* (Crucially, this line sets the "top" variable.)
*/
pgm: program { top = $$ = $1; }

/* Language grammar follows:
*/

program: decl { $$ = new parse_tree("program", 1, $decl); }
| program decl { $1 -> add_child($decl); $$ = $1; }

decl: variable_decl | function_decl | class_decl | interface_decl

// functions
function_decl: void identifier { open_scope(); } 
  { current_function = new s_function; variable_num = current_class ? 1 : 0; } 
  '(' formals ')'  stmt_block  
{ 	
  std::string ident = $identifier->tok->text;
  semantic_assert(!current_scope->lookup_local(ident),
          "\"%s\" is aleady defined",
          ident.c_str());
    
  for (size_t i = 0; i < $formals->children.size(); i++) {
    std::string identParam = $formals->children[i]->children[1]->tok->text;
    current_function->params.push_back(
      dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
  }

  current_function->owner_class = current_class;
  current_function->return_type = nullptr;

  current_function->owner_class = current_class;
  $$ = new parse_tree("functiondecl", 4, $void, $identifier, $formals, $stmt_block); 
  close_scope();
    current_function->num_locals = variable_num;
  if (current_scope->lookup_local(ident))
    current_scope->replace(ident, current_function);
  else
    current_scope->add(ident, current_function);
  current_function = nullptr;
}
| type identifier { open_scope(); }
  { current_function = new s_function; variable_num = current_class ? 1 : 0; } 
  '(' formals ')' stmt_block 
{	
  std::string ident = $identifier->tok->text;
  semantic_assert(!current_scope->lookup_local(ident),
          "\"%s\" is aleady defined",
          ident.c_str());
    
  for (size_t i = 0; i < $formals->children.size(); i++) {
    std::string identParam = $formals->children[i]->children[1]->tok->text;
    current_function->params.push_back(
      dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
  }
  current_function->owner_class = current_class;
  current_function->return_type = make_type($type);

  $$ = new parse_tree("functiondecl", 4, $type, $identifier, $formals, $stmt_block); 
  close_scope();
    current_function->num_locals = variable_num;
  current_scope->add(ident, current_function);
  current_function = nullptr;
}

formals: { $$ = new parse_tree("formals"); } 
| formals[in] variable ',' {$in->add_child($variable); $$ = $in; }
| formals[in] variable { $in->add_child($variable); $$ = $in; }

stmt_block: '{' { open_scope(); } variable_decl_func stmts  '}' {close_scope(); }
	{ $$ = new parse_tree("stmtblock", 2, $variable_decl_func, $stmts); }

variable_decl_func: { $$ = new parse_tree("vardecls"); }
| variable_decl_func[in] variable_decl { $in->add_child($variable_decl); $$ = $in; }

// variables
variable_decl: variable ';' { $$ = $variable; }
variable: type identifier 
{ 
	std::string ident = $identifier->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());

	s_type * type = make_type($type);
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
	$$ = new parse_tree("variable", 2, $type, $identifier);  
}

type: primtype | arraytype | usertype

primtype: integer { $$ = new parse_tree("primtype", 1, $1); }
| double { $$ = new parse_tree("primtype", 1, $1); }
| bool { $$ = new parse_tree("primtype", 1, $1); }
| string { $$ = new parse_tree("primtype", 1, $1); } 

arraytype: type array { $$ = new parse_tree("arraytype", 1, $type); }

usertype:  typeidentifier { $$ = new parse_tree("usertype", 1, $1); }

// class
class_decl: class typeidentifier extends_decl implements_decl 
			{open_scope(); current_class = new s_class($typeidentifier->tok->text);}
			'{' field '}' {close_scope(); } 
{
	assert (current_scope == top_scope);	
	std::string ident = $typeidentifier->tok->text;
    
    if ($implements_decl){ 
        std::vector<parse_tree *> children = $implements_decl->children;
        for (size_t i = 0; i < children.size(); i++){   
            std::string implements_ident = $implements_decl->children[i]->tok->text;
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

    if ($extends_decl) {
        std::string super_class_ident = $extends_decl->children[0]->tok->text;
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

	$$ = new parse_tree("class", 4, $typeidentifier, $extends_decl, $implements_decl, $field); 
	current_class = nullptr;
}
| class identifier extends_decl implements_decl 
	{open_scope(); current_class = new s_class($identifier->tok->text);} 
	'{' field '}' {close_scope(); }
{
	assert (current_scope == top_scope);	
	std::string ident = $identifier->tok->text;

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

	$$ = new parse_tree("class", 4, $identifier, $extends_decl, $implements_decl, $field); 
	current_class = nullptr;
}

extends_decl: {$$ = nullptr; }
| extends identifier {$$ = new parse_tree("extends", 1, $identifier); }
| extends typeidentifier {$$ = new parse_tree("extends", 1, $typeidentifier); }

implements_decl: {$$ = nullptr; }
| implements identifier { $$ = new parse_tree("implements", 1, $identifier); }
| implements_decl[in] ',' identifier {$in->add_child($identifier); $$ = $1; }

field : {$$ = new parse_tree("fields"); }
| field[in] variable_decl {$in->add_child($variable_decl); $$ =  $1; }
| field[in] function_decl 
{
    std::string func_text = $function_decl->children[1]->tok->text;
    current_class->function_map.insert(std::pair<std::string, s_function *>(func_text, dynamic_cast<s_function *>(current_scope->lookup_local(func_text))));
    $in->add_child($function_decl); $$ =  $1; 
}

interface_decl: interface identifier 
  {open_scope(); current_interface = new s_interface($identifier->tok->text);} 
  '{' prototypes '}' {close_scope(); }
{ 
	assert (current_scope == top_scope);	
	std::string ident = $identifier->tok->text;
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
	$$ = new parse_tree("interface", 2, $identifier, $prototypes); 
	current_interface = nullptr;
}

prototypes:  {$$ = new parse_tree("prototypes"); }
| prototypes[in] prototype { $[in]-> add_child($prototype); $$ = $[in]; }

prototype: type identifier {open_scope(); }'(' formals ')' ';' 
{
	current_prototype = new s_prototype; 
	$$ = new parse_tree("prototype", 3, $type, $identifier, $formals); 
	current_prototype->return_type=make_type($type);
	for (size_t i = 0; i < $formals->children.size(); i++) {
		std::string identParam = $formals->children[i]->children[1]->tok->text;
		current_prototype->params.push_back(
			dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
	}
	current_interface->prototype_map.insert({$identifier->tok->text, current_prototype});
	close_scope();
	std::string ident = $identifier->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());
	current_scope->add(ident, current_prototype);
	current_prototype = nullptr;
}
| void identifier {open_scope(); }'(' formals ')' ';' 
{
	current_prototype = new s_prototype; 
	$$ = new parse_tree("prototype", 3, $void, $identifier, $formals); 
	current_prototype->return_type=nullptr;
	for (size_t i = 0; i < $formals->children.size(); i++) {
		std::string identParam = $formals->children[i]->children[1]->tok->text;
		current_prototype->params.push_back(
			dynamic_cast<s_var *>(current_scope->lookup_local(identParam)));
	}
	current_interface->prototype_map.insert({$identifier->tok->text, current_prototype});
	current_prototype = nullptr;
	close_scope();
	std::string ident = $identifier->tok->text;
	semantic_assert(!current_scope->lookup_local(ident),
					"\"%s\" is aleady defined",
					ident.c_str());
	current_scope->add(ident, current_prototype);
	current_prototype = nullptr;
}

stmts: { $$ = new parse_tree("stmts"); } 
| stmts[in] stmt { $in-> add_child($stmt); $$ = $in; }

stmt: matched_stmt | unmatched_stmt 

lvalue: identifier | fieldaccess | aref
aref:  level_ten '[' expr ']' {$$ = new parse_tree("aref", 2, $level_ten, $expr); }

matched_stmt: print_stmt 
| break_stmt 
| return_stmt 
| nullable_expr ';'
| matched_if
| matched_for
| matched_while
| stmt_block

unmatched_stmt: unmatched_if
| unmatched_for
| unmatched_while

common_if: "if" '(' expr ')' { $$ = $expr; }

matched_if: common_if matched_stmt[one] "else" matched_stmt[two] {$$ = new parse_tree("if", 3, $common_if, $one, $two); }
unmatched_if: common_if stmt {$$ = new parse_tree("if", 3, $common_if, $stmt, nullptr); }
| common_if matched_stmt "else" unmatched_stmt {$$ = new parse_tree("if", 3, $common_if, $matched_stmt, $unmatched_stmt); }

common_while: "while" '(' expr ')' { $$ = $expr;}
matched_while: common_while matched_stmt { $$ = new parse_tree("while", 2, $common_while, $matched_stmt); }
unmatched_while: common_while unmatched_stmt { $$ = new parse_tree("while", 2, $common_while, $unmatched_stmt); }

matched_for: "for" '(' nullable_expr[one] ';' expr ';'  nullable_expr[two] ')' matched_stmt { $$ = new parse_tree("for", 4, $one, $expr, $two, $matched_stmt); }
unmatched_for: "for" '(' nullable_expr[one] ';' expr ';'  nullable_expr[two] ')' unmatched_stmt { $$ = new parse_tree("for", 4, $one, $expr, $two, $unmatched_stmt); }

print_stmt: print '(' actuals ')' ';' {$$ = new parse_tree("print", 2, $print, $actuals); }
break_stmt: break ';' { $$ = new parse_tree("break", 1, $break); }
return_stmt: return ';' { $$ = new parse_tree("return", 1, $return); }
| return expr ';' { $$ = new parse_tree("return", 2, $return, $expr); }

nullactuals: {$$ = new parse_tree("actuals"); }
| expr {$$ = new parse_tree("actuals", 1, $expr); }
| nullactuals[in] ',' expr {$[in]->add_child($expr); $$ = $in; }

actuals: expr {$$ = new parse_tree("actuals", 1, $expr); }
| actuals[in] ',' expr {$[in]->add_child($expr); $$ = $in; }

level_one: lvalue level_one_ops level_two
	{ $$ = new parse_tree("binop", 3, $lvalue, $level_one_ops, $level_two);}
| level_two

level_two: level_two[in] level_two_ops level_three 
	{$$ = new parse_tree("binop", 3, $in, $level_two_ops, $level_three); } 
| level_three

level_three: level_three[in] level_three_ops level_four 
	{$$ = new parse_tree("binop", 3, $in, $level_three_ops, $level_four); } 
| level_four

level_four: level_five[one] level_four_ops level_five[two]
	{$$ = new parse_tree("binop", 3, $one, $level_four_ops, $two); } 
| level_five

level_five: level_six[one] level_five_ops level_six[two]
	{$$ = new parse_tree("binop", 3, $one, $level_five_ops, $two); } 
| level_six

level_six: level_six[in] level_six_ops level_seven
	{$$ = new parse_tree("binop", 3, $in, $level_six_ops, $level_seven); }
| level_seven

level_seven: level_seven[in] level_seven_ops level_eight
	{$$ = new parse_tree("binop", 3, $in, $level_seven_ops, $level_eight); } 
| level_eight

level_eight: level_eight_ops level_eight[in] 
	{ $$ = new parse_tree("uop", 2, $level_eight_ops, $in); }
| level_nine

level_nine: constants | level_ten

level_ten: lvalue | readint '(' ')' | readline '(' ')' | this | null | call
| newarray '(' expr ',' ident_type ')' { $$ = new parse_tree("newarray", 2, $expr, $ident_type); } 
| new '(' identifier ')' { $$ = new parse_tree("new", 1, $identifier); }
| '(' expr ')' {$$ = $expr;} 

ident_type: type | identifier

call: fieldaccess '(' nullactuals ')' { $$ = new parse_tree("call", 2, $fieldaccess, $nullactuals); }
| identifier '(' nullactuals ')' { $$ = new parse_tree("call", 2, $identifier, $nullactuals); }

fieldaccess: level_nine[in] '.' identifier {$$ = new parse_tree("fieldaccess", 2, $in, $identifier); }

level_one_ops: '=' {$$ = new parse_tree(mytok); } 
level_two_ops: or 
level_three_ops: and 
level_four_ops: eq | neq
level_five_ops:  le | ge | '<' { $$ = new parse_tree(mytok); }
| '>' { $$ = new parse_tree(mytok); }
level_six_ops: plus_rule | minus_rule
level_seven_ops: '%' {$$ = new parse_tree(mytok); }
| '*' {$$ = new parse_tree(mytok); }
| '/' {$$ = new parse_tree(mytok); }
level_eight_ops: minus_rule | excl_rule
excl_rule: '!' {$$ = new parse_tree(mytok); }
plus_rule: '+' { $$ = new parse_tree(mytok); }
minus_rule: '-' { $$ = new parse_tree(mytok); }

expr: level_one

nullable_expr: {$$ = nullptr; } | expr

constants: intliteral | doubleliteral | stringliteral | boolliteral 

/* terminal-building productions below */
intliteral: T_INTLITERAL { $$ = new parse_tree(mytok); }
doubleliteral: T_DBLLITERAL { $$ = new parse_tree(mytok); }
stringliteral: T_STRINGLITERAL {$$ = new parse_tree(mytok); }
boolliteral: T_BOOLLITERAL {$$ = new parse_tree(mytok); }
identifier: T_IDENTIFIER { $$ = new parse_tree(mytok); }
typeidentifier: T_TYPEIDENTIFIER { $$ = new parse_tree(mytok); } 
void: T_VOID {$$ = new parse_tree(mytok); }
interface: T_INTERFACE { $$ = new parse_tree(mytok); }
class: T_CLASS { $$ = new parse_tree(mytok); }
extends: T_EXTENDS {$$ = new parse_tree(mytok); }
implements: T_IMPLEMENTS {$$ = new parse_tree(mytok); }
print: T_PRINT { $$ = new parse_tree(mytok); }
break: T_BREAK {$$ = new parse_tree(mytok); }
return: T_RETURN {$$ = new parse_tree(mytok); }
eq: T_EQ {$$ = new parse_tree(mytok); }
neq: T_NEQ {$$ = new parse_tree(mytok); }
le: T_LE {$$ = new parse_tree(mytok); }
ge: T_GE {$$ = new parse_tree(mytok); }
and: T_AND {$$ = new parse_tree(mytok); }
or: T_OR {$$ = new parse_tree(mytok); }
readint: T_READINTEGER {$$ = new parse_tree(mytok); }
readline: T_READLINE {$$ = new parse_tree(mytok); }
new: T_NEW {$$ = new parse_tree(mytok); }
newarray: T_NEWARRAY {$$ = new parse_tree(mytok); }
integer: T_INT {$$ = new parse_tree(mytok); }
double: T_DOUBLE {$$ = new parse_tree(mytok); } 
string: T_STRING {$$ = new parse_tree(mytok); }
bool: T_BOOL {$$ = new parse_tree(mytok); }
this: T_THIS {$$ = new parse_tree(mytok); }
null: T_NULL  {$$ = new parse_tree(mytok); }
array: T_ARRAY {$$ = new parse_tree(mytok); }

%%
