#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <string>
#include <map>
#include <vector>

/* *** semantic_assert ***
Given a boolean condition, a format string, and other parameters,
test the condition. If true, return with no effect.
Otherwise, output the line number and
pass the format string and other parameters to
fprintf (on stderr), output a newline, and exit the compiler.
*/
void semantic_assert(bool condition, char const *fmt, ...);


/* Part I - data structures for ascribing semantics to program elements */

struct semantics
{
   // Top level abstract class
   virtual std::string to_string() const = 0;  // to be implemented by subclass
};

// Kinds of semantics in programs.

// types -- this is likely abstract as well.
//    (subclasses would be primitive, nonprimitive (programmer-defined classes)
//     and placeholders, for types mentioned but not yet defined.)
//
struct s_type: public semantics
{
   std::string name;  // does every type have a name? In Decaf, I think so.
   s_type(std::string name);
};

struct s_arraytype: public s_type
{
   s_type *content_type;
   s_arraytype(s_type *);
   std::string to_string() const;
};


// Room here for s_type subclass declarations, including placeholder.
// ..........

// Needed forward declarations
struct s_class;
struct s_interface;

struct s_prim: public s_type
{
   virtual std::string to_string() const;
   s_prim(std::string name);
};

// variables & parameters
struct s_var: public semantics
{
   std::string name;
   s_type * type;
   s_class * classy = nullptr;
   int num = -1;
   s_var(std::string name, s_type *type);
   std::string to_string() const;

};


// Prototypes and functions. Functions are a subclass of Prototype because they
// also have a body, local variables, might belong to a class.


struct s_prototype: public semantics
{
   // parameter list
   std::vector<s_var *> params;

   // return type (nullptr == void)
   s_type *return_type;
   std::string to_string() const;
};

struct s_function: public s_prototype
{

   // class it belongs to, if any:
   s_class * owner_class;

   // list of local variables
   std::vector<s_var *> locals;
   std::string to_string() const;
   size_t num_locals;
};

// user types (classes & interfaces)

struct s_usertype:public s_type
{
   bool defined; // false when this type is a placeholder for something
                 // that should be defined later; true otherwise
   s_usertype(std::string);
   std::string to_string() const;

};

// classes
struct s_class: public s_usertype
{
   // map of function name to s_function
   std::map<std::string, s_function *> function_map;

   // link to superclass (nullptr = does not extend something)
   s_class *superclass;

   // vector of interfaces
   std::vector<s_interface *> interfaces;

	std::vector<s_var *> attrs;

   s_class(std::string);
};

// interfaces
struct s_interface: public s_usertype
{
   // map of function name to prototype
   std::map<std::string, s_prototype *> prototype_map;
   s_interface(std::string);

};


/* ---------- PART II,  symbol table (declaration scope) -------------------*/

// symbol table
// used for representing different variable scopes
// These are nested, e.g. global scope contains class
// scope, contains function scope, contains function block scope,
// contains control construct scope.
/* Valid example:

int x;

class c
{
   boolean x = true;
   void m1()
   {
      if (x) println("ok");
   }
   void m2(double x)
   {
      c x;
      m1();
      if (x == null)
      {
         // at this point at runtime there are five variables
         // named x. Which one is in scope here?
         int x = 5;
         println(x);
      }
   }
}
*/

struct symtab
{
   // VARIABLES
private:
   // a pointer to the scope that contains this one.
   symtab *outer;
   // a name that is unique to each created symbol table.
   std::string name;

public:
   // a table associating a string to a semantics
   std::map<std::string, semantics *> table;

   // constructor
   symtab(symtab *outer);

   // GETTERS:

   // name getter
   std::string to_string() const;

   // looks for a value associated with string in table, returning it
   // if found, otherwise returning nullptr.
   semantics *lookup_local(std::string) const ;

   // recursive lookup function. if not found here,
   // proceed to the outer scope, if any.
   semantics *lookup(std::string) const;

   // MODIFIERS:

   // Pre: key is not found locally.
   void add(std::string key, semantics *value);

   // Pre: key is found locally.
   void replace(std::string key, semantics *value);

   friend symtab *close_scope();
};

/**** Variables ***/

extern std::vector<s_var *> variables;
extern symtab *current_scope;
extern symtab *top_scope;
// These will be used later, perhaps
extern s_class *current_class;
extern s_interface *current_interface;
extern s_function *current_function;
extern s_prototype *current_prototype;
extern s_prim *semantics_int_type;
extern s_prim *semantics_double_type;
extern s_prim *semantics_bool_type;
extern s_prim *semantics_string_type;

/*** Functions ***/

// makes a new scope inside current_scope and
// sets current_scope to the newly created symbol table.
void open_scope();

// leaves the current scope (sets current_scope to its outer);
// and returns the scope that was current.
symtab *close_scope();

// issues a semantic error and exits.
void semantic_error(std::string const & msg);


#endif
