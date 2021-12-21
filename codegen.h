// codegen.h
#ifndef CODEGEN_H
#define CODEGEN_H

#include "parsetree.h"

void gen_binop(parse_tree *tree);
void gen_expr(parse_tree *tree);
void gen_assign(parse_tree *tree);
void gen_global_var(parse_tree *tree);
void gen_preamble();
void gen_global_variable(parse_tree *tree);
void gen_main_boilerplate();
void gen_main_block(parse_tree * tree, std::string super_name);
void gen_main_program(parse_tree *tree);
void gen_stmt(parse_tree *tree);
void gen_stmt_block(parse_tree *tree);

void codegen_error(char const *fmt, ...);

/* *** Global variables *** */

extern std::ostream *gout;  // the file I'm writing to right now.
extern std::string program_name; // the name of the program. Good idea

#endif
