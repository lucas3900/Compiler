#include "parsetree.h"
#include "semantics.h"

#include <cstdarg> // needed for variadic function definition

// Global variables:
parse_tree *top;  // store the top of the parse tree

// constructing a parse tree with 0 or more children
parse_tree::parse_tree(std::string description,
                       size_t num_children, ...)
   : description(description), tok(nullptr), scope(current_scope),
     type(nullptr)
{
   va_list args;
   va_start(args, num_children);
   for (size_t i = 0; i < num_children; i++)
   {
      add_child(va_arg(args, parse_tree *));
   }
}

parse_tree::parse_tree(token *tokp)
   : tok(tokp), scope(current_scope), type(nullptr)
     // ,sem(nullptr), type(nullptr)
{
}

void parse_tree::add_child(parse_tree *tree)
{
   children.push_back(tree);
}

std::string parse_tree::to_string() const
{
   std::string answer = local_to_string();
   if (!tok) // nonterminal
   {
      answer = "(" + answer;
      for (parse_tree *tree : children)
      {
         answer += !tree ? " NULL" : " " + tree->to_string();
      }
      answer += ")";
   }
   return answer;
}

std::string parse_tree::local_to_string() const
{
   std::string answer;
   if (tok)
   {
      answer =  tok->to_string();
   }
   else // nonterminal
   {
      answer = description;
      if (scope)
      {
         answer += " [scope: " + scope->to_string() + "]";
      }
      if (type)
      {
         answer += " [type: " + type->to_string() + "]";
      }
   }
   return answer;
}


/* helper functions */

std::string base26(int x)
{
   char buf[2];
   buf[1] = 0;
   if (x<26)
   {
      buf[0] = std::string("abcdefghijklmnopqrstuvwxyz")[x];
      return std::string(buf);
   }
   return base26(x/26) + base26(x % 26);
}

std::string seq2str(int seq, int depth)
{
   // TODO: There's something very off-by-one about this.
   // depth 1: A, B, C, D....
   // depth 2: 1, 2, 3, 4....
   // depth 3: a, b, c, d....
   // depth 4: 1, 2, 3, 4....
   char buf[100];
   int d = (depth - 1) % 4;
   if (d == 1 || d == 3) {
     sprintf(buf, "%d", seq);
     return std::string(buf);
   }
   std::string let = base26(seq-1);
   if (d==0) {
      std::string bob = "";
      for (auto i = let.begin(); i!=let.end(); i++)
         bob += toupper(*i);
      let = bob;
   }
   return let;
}

void traverse_tree(parse_tree *tree, int depth, int seq)
{
   // tree is a possibly null tree, but output always occurs
   for (int i=0;i<depth;i++)
   {
      std::cout << "  ";
   }
   if (seq)
   {
      std::cout << seq2str(seq, depth) << " ";
   }
   if (!tree)
   {
      std::cout << "NULL" << std::endl;
      return;
   }
   std::cout << tree->local_to_string() << std::endl;
   if (tree->tok)
   {
      return;
   }
   // must be nonterminal...
   for (size_t i=0;i<tree->children.size();i++)
   {
      traverse_tree(tree->children[i], depth+1, i+1);
   }
}
