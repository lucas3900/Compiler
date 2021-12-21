#include <iostream>  // temporary
#include <cassert>
#include <cstdarg>
#include "semantics.h"
#include "token.h"

/* *** variables *** */

std::vector<s_var *> variables = {}; 
symtab *top_scope = nullptr;
symtab *current_scope = nullptr;
s_function *current_function;
s_interface *current_interface;
s_class *current_class;
s_prototype *current_prototype;

void semantic_assert(bool condition, char const * fmt, ...)
{
   if (condition) return;
   std::cerr << "line " << current_line << ": semantic error, ";
   va_list args;
   va_start(args, fmt);
   vfprintf(stderr, fmt, args);
   std::cerr << std::endl;
   va_end(args);
   exit(1);
}

/* *** semantics constructors and instance methods *** */

s_var::s_var(std::string name, s_type *type) : name(name), type(type) {}

std::string s_var::to_string() const
{
   return name;
}

s_type::s_type(std::string name) : name(name) {}

s_arraytype::s_arraytype(s_type * content_type) :
   s_type(content_type->name+"[]"), content_type(content_type) {}

std::string s_arraytype::to_string() const
{
    return name;
}

std::string s_function::to_string() const
{
    return "FuNcTiOn";
}

std::string s_prototype::to_string() const
{
    return "PrOtOtYpE";
}

s_prim::s_prim(std::string name) : s_type(name) {}

std::string s_prim::to_string() const
{
   return name;
}

std::string s_usertype::to_string() const
{
   return "usertype:"+name;
}

s_usertype::s_usertype(std::string name) : s_type(name) { defined = false; }

s_class::s_class(std::string name) : s_usertype(name)
{
   defined = true;
   superclass = nullptr;
}

s_interface::s_interface(std::string name) :s_usertype(name)
{
   defined = true;
}


/* *** Global types builtin. *** */
s_prim *semantics_int_type = new s_prim("int");
s_prim *semantics_double_type = new s_prim("double");
s_prim *semantics_bool_type = new s_prim("bool");
s_prim *semantics_string_type = new s_prim("string");

/* *** symtab *** */

symtab::symtab(symtab *outer) : outer(outer)
{
   static int seq = 1;
   name = "symtab-" + std::to_string(seq++);
}

std::string symtab::to_string() const
{
   return name;
}

semantics *symtab::lookup_local(std::string key) const
{
   // p has type iterator to map of string and semantics*.
   // auto is much easier here. Thank you C++11.
   auto p = table.find(key);
   return p == table.end() ? nullptr : p->second;
}

semantics *symtab::lookup(std::string key) const
{
   semantics *p = lookup_local(key);
   return     p ? p :
          outer ? outer->lookup(key) :
                  nullptr;
}

void symtab::add(std::string key, semantics *value)
{
   assert(!lookup_local(key));
   table[key] = value;
}

void symtab::replace(std::string key, semantics *value)
{
   assert(lookup_local(key));
   table[key] = value;
}

/* *** functions *** */

void open_scope()
{
   current_scope = new symtab(current_scope);
}

symtab *close_scope()
{
   symtab *old = current_scope;
   current_scope = current_scope->outer;
   return old;
}
