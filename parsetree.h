#ifndef PARSETREE_H
#define PARSETREE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>  // this wasn't necessary before??
#include "token.h"
#include "semantics.h"

  /* prototype for yyerror, needed on my linux laptop */
int yyerror(const char * s);


struct parse_tree
{
   // VARIABLES:
   /* exactly one of these two are used.  */
   std::string description;
   token *tok;   // terminal when tok is not nullptr.

   /* used in all non-terminals: */
   symtab *scope;  // the current_scope when tree was created

   /* sometimes used: */
   // semantics *sem; // used for declarations
   s_type *type;  // used for expressions
   std::vector<parse_tree *> children;

   // constructing a non-terminal, with zero or more
   // children, all of which better be parse_tree *.
   // Oh, and if you screw up the calling convention here
   // by giving an incorrect num_children parameter,
   // there will be hell to pay.
   parse_tree(std::string description, size_t num_children = 0, ...);

   // construct a terminal parse tree with a token.
   parse_tree(token *tok);

   // add a child to this parse tree.
   void add_child(parse_tree *tree);


   // convert to a string for printing. Just this node.
   std::string local_to_string() const;

   // convert to a string for printing, inclding children recursively.
   std::string to_string() const;

   s_var * variable = nullptr;

};

extern parse_tree *top;  // store the top of the parse tree

// A more in-depth traversal that prints to stdout.
void traverse_tree(parse_tree *tree, int depth=0, int seq=0);

#endif
