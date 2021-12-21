#include <fstream>
#include <algorithm>
#include "parsetree.h"
#include "semantics.h"
#include "codegen.h"
#include "decafc.h"


// prototypes:
extern FILE *yyin;
int yylex(); // this is only needed for the --lex option I think.
void main_lex();
void main_tree();
void main_sem();
void main_gen();

// Globals controlling behavior:
bool semantic_checks = false;
bool IN_FUNC = false;
s_class * current_classy = nullptr;

// type to represent the user's choice: lexical analysis, tree generation,
// semantic checks, code generation.
enum action {LEX, TREE, SEM, GEN};

// CITE: https://docs.microsoft.com/en-us/troubleshoot/cpp/
//               declare-pointers-to-functions
// DESC: How to declare an array of pointers to functions
void (*functions[])() = {main_lex, main_tree, main_sem, main_gen};

void usage(char **argv, int code = 1)
{
   std::cerr << "Usage: " << argv[0] << " [options] file" << std::endl;
   std::cerr << "Options:" << std::endl <<
"  --help                   Display this usage information" << std::endl <<
"  --lex                    Display the tokens" << std::endl <<
"  --tree                   Show a traversal of the parse tree" << std::endl <<
"  --sem                    Perform semantic checks" << std::endl <<
"  --gen (default)          Generate JVM assembly code" << std::endl;
   std::cerr << "At most one of --lex, --tree, --sem, or --gen may be given."
             << std::endl;
   exit(code);
}

int main(int argc, char **argv)
{
   action act = GEN;
   bool act_given = false;
   std::string filename = "";
   if (argc < 2) usage(argv);

   // process command line arguments
   for (int i = 1; i < argc; i++)
   {
      std::string arg = argv[i];

      // if you give an action, it has to be legit.
      if (   arg.size() >= 2 && arg.substr(0,2) == "--"
          && arg != "--help" && arg != "--lex" && arg != "--tree"
          && arg != "--sem" && arg != "--gen")
      {
         usage(argv);
      } // You can only give one action option. if (act_given && (   arg == "--lex" || arg == "--tree"
                        || arg == "--sem" || arg == "--geb"))
      {
         usage(argv);
      }
      if (arg == "--help") usage(argv, 0);
      else if (arg == "--lex") act = LEX, act_given = true;
      else if (arg == "--tree") act = TREE, act_given = true;
      else if (arg == "--sem") act = SEM, act_given = true;
      else if (arg == "--gen") act_given = true;
      else act_given = true, filename = arg;
   }

   // error if a filename wasn't given
   if (filename == "") usage(argv);

   // open the file, error if couldn't open.
   yyin = fopen(filename.c_str(), "r");
   if (!yyin)
   {
      std::cout << filename
           << ": no such file or file can't be opened for reading."
           << std::endl;
      exit(1);
   }

   // determine the program_name from the filename
   // (for code generation)
   size_t pos = filename.find_last_of('.');
   program_name = pos == std::string::npos ? filename : filename.substr(0 ,pos);
   size_t file_slash = program_name.find_last_of('/');
   if (file_slash != std::string::npos)
      program_name = program_name.substr(file_slash+1); 

   // do the chosen function
   functions[act]();
}

void main_lex()
{
   current_line = 1;
   while (yylex())
   {
      std::cout << *mytok << std::endl;
      delete mytok;
   }
}

void main_tree()
{
   current_line = 1;
   yyparse();
   traverse_tree(top);
}

s_type* base_type(s_type* type) 
{
    s_arraytype * test = dynamic_cast<s_arraytype *>(type);
    if (!test)
        return type;
    return base_type(test->content_type);
}


s_type * make_type_pass_two(parse_tree * tree) 
{
    if (tree->description == "primtype") {
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
    else if (tree->description == "arraytype") {
        return new s_arraytype(make_type_pass_two(tree->children[0]));
    }
    else if (tree->description == "usertype")
        return new s_usertype(tree->children[0]->tok->text);
    else if (tree->tok && tree->tok->type == 282)
        return new s_usertype(tree->tok->text);
    else // void returns nullpty
        return nullptr;
}

bool no_class_cycle(s_class * classy, std::string & start) 
{
    s_class * super_class = classy->superclass;
    if (super_class) {
        if (super_class->name == start)
            return false;
        return no_class_cycle(super_class, start);
    }

    return true;
}

bool equal_params(std::vector<s_var *> params_1, std::vector<s_var *> params_2) 
{
    if (params_1.size() != params_2.size())
        return false;
    for (size_t i = 0; i < params_1.size(); i++)
        if (!(params_1[i]->type->name == params_2[i]->type->name))
            return false;

    return true;
}

bool equal_return_types(s_type* type_1, s_type* type_2)
{
    if (!type_1 && !type_2)
        return true;
    else if ((!type_1 && type_2) || (type_1 && !type_2))
        return false;
    else if (type_1->name != type_2->name)
        return false;
    
    return true;
}

bool implements_interfaces_only(s_class * classy)
{
    std::vector<s_interface *> interfaces = classy->interfaces;
    for (size_t i = 0; i < interfaces.size(); i++){
        if (!dynamic_cast<s_interface *>(top_scope->lookup_local(interfaces[i]->name)))
            return false;
    }   

    return true;        
}

s_function * get_super_class_method(std::string ident, s_class * superclass) 
{
    std::map<std::string, s_function *> methods = superclass->function_map;
    for (auto it = methods.begin(); it != methods.end(); it++)
        if (it->first == ident)
            return it->second;

    s_class * super_superclass = superclass->superclass;
    if (super_superclass)
        return get_super_class_method(ident, super_superclass);

    return nullptr;
}

bool class_implements_interface(s_class * classy)
{
    std::vector<s_interface *> interfaces = classy->interfaces;

    for (size_t i = 0; i < interfaces.size(); i++){
        std::map<std::string, s_prototype *> protos = interfaces[i]->prototype_map; 
        for (auto it = protos.begin(); it != protos.end(); it++) {
            std::string proto_ident = it->first;
            s_prototype * proto = it->second;
                s_function * function = get_super_class_method(proto_ident, classy);
            semantic_assert(function, "Does not impliement interface function %s", proto_ident.c_str());

            if (!(equal_params(proto->params, function->params)
                && equal_return_types(proto->return_type, function->return_type) ))
                return false; //params or return type don't match
        }
    }

    return true;
}

bool invalid_method_override(s_class * classy)
{
    s_class * super_class = classy->superclass;
    std::map<std::string, s_function *> methods = classy->function_map;
    for (auto it = methods.begin(); it != methods.end(); it++) {
        s_function * method = it->second;
        s_function * superclass_method = get_super_class_method(it->first, super_class);
        if (superclass_method) 
            if (!(equal_params(method->params, superclass_method->params)
                && equal_return_types(method->return_type, superclass_method->return_type))) 
                return false; //params or return type don't match
    }
    return true;
}

void sem_post_pass_one()
{
    for (auto it = top_scope->table.begin(); it != top_scope->table.end(); it++) {
        s_class * classy = dynamic_cast<s_class *>(it->second);
        s_interface * interfacey = dynamic_cast<s_interface *>(it->second);
        std::string ident = it->first;
        if (classy) {
            if (classy->superclass){
                semantic_assert(dynamic_cast<s_class *>(top_scope->lookup_local(classy->superclass->name)),
                                "\"%s\" extends an undefined class: \"%s\"",
                                ident.c_str(),  (classy->superclass->name).c_str());
                semantic_assert(no_class_cycle(classy, ident),
                                "Cyclical inheritance with class: \"%s\"",
                                ident.c_str());
                semantic_assert(invalid_method_override(classy),
                                "Invalid Method Override: \"%s\"",
                                ident.c_str());
            }
            semantic_assert(class_implements_interface(classy),
                            "Class fails to implement all interface methods: \"%s\"",
                            ident.c_str());
            semantic_assert(implements_interfaces_only(classy),
                            "Class \"%s\" implements non-interface.",
                            ident.c_str());
        } else if (interfacey) {
            semantic_assert(interfacey->defined,
                            "Undefined interface: \"%s\"",
                            ident.c_str());
        }
    }  

    for (size_t i = 0; i < variables.size(); i++){
        s_var * var = variables[i];
        std::string base = base_type(var->type)->name;
        if (dynamic_cast<s_usertype *>(var->type)){
            semantics * user_type = top_scope->lookup_local(base);
                  semantic_assert(dynamic_cast<s_class *>(user_type)
                            || dynamic_cast<s_interface *>(user_type),
                                          "Undefined User Type: \"%s\"",
                                          base.c_str());
        }
    }
}

// Begins Pass 2 code
s_type* get_expr_type(parse_tree* top);

bool semantic_eq(s_type * left, s_type * right)
{
    if (!(left && right))
        return false;
    
    return left->name == right->name;
}


bool is_compatible(s_type* left, s_type* right)
{   
    if (semantic_eq(left, right))
        return true;

    if (!right) {
      if (dynamic_cast<s_usertype *>(left))
                return true;
        else
            return false;
    }

    if (!dynamic_cast<s_usertype *>(left))
        return false;

    std::string class_name = right->name;
    s_class * classy = dynamic_cast<s_class *>(top_scope->lookup(class_name));
    semantic_assert(classy, "Attempting to assign non-class to class/interface");
    std::vector<s_interface *> interfaces = classy->interfaces;
    for (size_t i = 0; i < interfaces.size(); i++)
        if (interfaces[i]->name == left->name)
            return true;

    if (classy->superclass)
        return is_compatible(left, classy->superclass);

    return false;
}

s_type * parse_binop(parse_tree * ptr, int op)
/* parses and throws errors on binops */
{
    std::vector<int> number_ops = { 43, 45, 42, 47, 37};
    std::vector<int> comparisons = {288, 289, 60, 62};
    std::vector<int> logicals = {292, 293};
    std::vector<int> equality = {290, 291};

    s_type * left_child = get_expr_type(ptr->children[0]);
    s_type * right_child = get_expr_type(ptr->children[2]);
    
    //std::string desc = ptr->children[1]->description;
    if (std::find(number_ops.begin(), number_ops.end(), op) != number_ops.end()) {
        semantic_assert(left_child->name == "int" || left_child->name == "double", 
                        "Math must be done with numbers");
        semantic_assert(semantic_eq(left_child, right_child), "Both sides of binop must be float or int");
        return left_child;
    } else if (std::find(comparisons.begin(), comparisons.end(), op) != comparisons.end()) {
    semantic_assert(left_child->name == "int" || left_child->name == "double", 
            "Math must be done with numbers");
    semantic_assert(semantic_eq(left_child, right_child), "Both sides of binop must be float or int");
    return new s_prim("bool");
    } else if (op == 61){ // assignment
        semantic_assert(is_compatible(left_child, right_child), "Incompatible types with assignment");
        return nullptr;
    } else if (std::find(logicals.begin(), logicals.end(), op) != logicals.end()) {
        semantic_assert(left_child->name == "bool", "Logicals must compare bools");
        semantic_assert(semantic_eq(left_child, right_child), "Both sides of binop must be float or int");
        return new s_prim("bool");
    } else if (std::find(equality.begin(), equality.end(), op) != equality.end()) {
        semantic_assert(is_compatible(left_child, right_child) || is_compatible(right_child, left_child), "Equality must be compatible on at least one side");
        return new s_prim("bool");
    }
    return nullptr;
}

s_type *  parse_uop(parse_tree * ptr, int op)
{
    s_type * child = get_expr_type(ptr->children[1]);
    if (op == 33) // not
        semantic_assert(child->name == "bool", "! must be passed bool");
    else
        semantic_assert(child->name == "double" || child->name == "int", "- must be passed number");
    
    return child;
}


s_var * get_class_attr(s_class * classy, std::string ident)
{
    for (size_t i = 0; i < classy->attrs.size(); i++){
        s_var * attr = classy->attrs[i];
        if (attr->name == ident)
            return attr;
    }
    
    if (classy->superclass)
        return get_class_attr(classy->superclass, ident);

    return nullptr; 
}

s_type * get_fieldaccess_type(parse_tree * ptr)
{
    semantic_assert(current_classy, "Field access must be within class scope");

    s_type * left = get_expr_type(ptr->children[0]);
    s_class * classy = dynamic_cast<s_class *>(top_scope->lookup(left->name));
    semantic_assert(classy, "field access must be on class");

    semantic_assert(is_compatible(current_classy, classy), "Can not access fields of a class that is not the same type or a child type.");

    s_var * var = get_class_attr(classy, ptr->children[1]->tok->text);
    semantic_assert(var, "Not an attribute of the class");

    return var->type;
}

s_type * get_call_type(parse_tree * ptr) 
{
    parse_tree * first_child = ptr->children[0];
    symtab * scope = ptr->scope;
    s_prototype * func;
    std::string func_name;
    std::vector<parse_tree*> actuals = ptr -> children[1]->children;
    
    // If the thing we are calling is a fieldaccess
    if (first_child->description == "fieldaccess") { 
        func_name = first_child->children[1]->tok->text;
        std::string usertype_name = get_expr_type(first_child->children[0])->name;
        s_class * classy = dynamic_cast<s_class *>(top_scope->lookup(usertype_name));
        s_interface * inter = dynamic_cast<s_interface *>(top_scope->lookup(usertype_name));
        s_arraytype * arr = dynamic_cast<s_arraytype *>(get_expr_type(first_child->children[0]));

        if (arr && func_name == "length" && actuals.size() == 0)
            return new s_prim("int");

        semantic_assert(classy || inter,
                        "Not a user Type: \"%s\"",
                        usertype_name.c_str());
        
        if (classy){
            func = get_super_class_method(func_name, classy);
            semantic_assert(func, "\"%s\" has no method: \"%s\"", usertype_name.c_str(), func_name.c_str());

        } else {
            auto func_it = inter->prototype_map.find(func_name);
            semantic_assert(func_it != inter->prototype_map.end(), "No prototype");
            func = func_it->second;
        }

    } else { // else it just a regular function
        func_name = first_child->tok->text; 
        func = dynamic_cast<s_function *>(scope->lookup(func_name));
    }
    semantic_assert(func, "Undefined function %s", func_name.c_str());

    semantic_assert(func->params.size() == actuals.size(), "different number of arguments than func definition");

    for (size_t i = 0; i < actuals.size(); i++){
        semantic_assert(is_compatible(func->params[i]->type, get_expr_type(actuals[i])), 
                       "types does not match in function call");

    }
    return func->return_type ? func->return_type : new s_prim("void");
}

s_type * get_ident_type(parse_tree * ptr)
{
    s_var * var = dynamic_cast<s_var *>(ptr->scope->lookup(ptr->tok->text));
    
    if (!var && current_classy && current_classy->superclass)
        var = get_class_attr(current_classy->superclass, ptr->tok->text);
        
    ptr->variable = var;

    semantic_assert(var && var->type, "Undefined Variable: \"%s\"", ptr->tok->text.c_str());
    return var->type;
}

s_type * get_expr_type(parse_tree * top) 
{
    if (!top) 
        return nullptr;
    top->type = get_expr_type_helper(top);
    return top->type;
}

s_type * get_expr_type_helper(parse_tree * top)
{
    std::string desc = top->description;
    // 284  bool 285 int 286 dbl 287 string
    if (desc == "binop") 
        return parse_binop(top, top->children[1]->tok->type);
    else if (desc == "uop")
        return parse_uop(top, top->children[0]->tok->type);
    else if (top->tok){ 
        int terminal = top->tok->type;
        if (terminal == 285)
            return new s_prim("int");
        else if (terminal == 286)
            return new s_prim("double");
        else if (terminal == 287)
            return new s_prim("string");
        else if (terminal == 284)
            return new s_prim("bool");
        else if (terminal == 282 || terminal == 283) // ident
            return get_ident_type(top);
        else if (terminal == 280) // readint
            return new s_prim("int");
        else if (terminal == 281) // readline
            return new s_prim("string");
        else if (terminal == 268) {// this
            semantic_assert(current_classy, "This used outside class context");
            return current_classy;
        }
    }   else if (desc == "new") { // new
        s_class * classy = dynamic_cast<s_class * >(top_scope->lookup(top->children[0]->tok->text));
        semantic_assert(classy, "New must take a class");
        return classy;
    } else if (desc == "newarray") { // newarray
        if (top->children[1]->tok and top->children[1]->tok->type == 282) {
            top->children[1] = new parse_tree("usertype", 1, top->children[1]);
            top->children[1]->scope = top->scope;
        }
        s_type * typey = make_type_pass_two(top->children[1]);
        s_type * typey2 = dynamic_cast<s_type * >(top_scope->lookup(base_type(typey)->name));
        semantic_assert(!dynamic_cast<s_interface *>(typey2),
                        "New Array cannot take an interface");  
        semantic_assert(get_expr_type(top->children[0])->name == "int",
                        "Size of array must be int");
        return new s_arraytype(typey);
    }
    // Function calls 
    else if (desc == "call")
        return get_call_type(top);
    else if (desc == "fieldaccess")
        return get_fieldaccess_type(top);
    else if (desc == "aref") {
        s_arraytype * arr = dynamic_cast<s_arraytype *>(get_expr_type(top->children[0]));   
        semantic_assert(arr, "Trying to index a non arraytype");
        semantic_assert(get_expr_type(top->children[1])->name == "int", "Array index must be of type int");
        
        return arr->content_type;
    }
        
    return nullptr;
}

void parse_function(parse_tree * ptr) 
{
    IN_FUNC = true;
        s_type * return_type = make_type_pass_two(ptr->children[0]);
        parse_stmt(ptr->children[3], return_type);
    if (return_type) {
        return_type = dynamic_cast<s_type *>(top_scope->lookup(base_type(return_type)->name));
        semantic_assert(return_type, "Return Type not defined");
        semantic_assert(!dynamic_cast<s_interface *>(return_type), "Can't return interface");
    }
    IN_FUNC = false;
}

void parse_while(parse_tree * ptr, s_type * return_type)
{
    s_type * cond = get_expr_type(ptr->children[0]);
    semantic_assert(cond && cond->name == "bool",
                    "while loop condition must be bool");
    parse_stmt(ptr->children[1], return_type, true);
}

void parse_for(parse_tree * ptr, s_type * return_type)
{
    s_type * cond = get_expr_type(ptr->children[1]);
    semantic_assert(cond && cond->name == "bool",
                    "for loop condition must be bool");
    
    get_expr_type(ptr->children[0]);
    get_expr_type(ptr->children[2]);
    parse_stmt(ptr->children[3], return_type, true);
}

void parse_if(parse_tree * ptr, s_type * return_type, bool in_loop)
{
    s_type * cond = get_expr_type(ptr->children[0]);
    semantic_assert(cond && cond->name == "bool",
                    "if condition must be bool");
    
    parse_stmt(ptr->children[1], return_type, in_loop);
    parse_stmt(ptr->children[2], return_type, in_loop);
}

void parse_stmt(parse_tree * ptr, s_type * return_type, bool in_loop)
{
    if (!ptr) return;
    std::string desc = ptr->description;
    if (desc == "binop")
        ptr->type = parse_binop(ptr, ptr->children[1]->tok->type);
    else if (desc == "uop")
        ptr->type = parse_uop(ptr, ptr->children[0]->tok->type);
    else if (desc == "for")
        parse_for(ptr, return_type);
    else if (desc == "while")
        parse_while(ptr, return_type);
    else if (desc == "if")
        parse_if(ptr, return_type, in_loop);
    else if (desc == "return"){
        semantic_assert(IN_FUNC, "Return only allowed in function");
        if (ptr->children.size() == 2)
            semantic_assert(semantic_eq(return_type, get_expr_type(ptr->children[1])), 
                            "Incompatible return type");
        else
            semantic_assert(!return_type, "Must return value from non void function");
    }
    else if (desc == "stmtblock") // do we want to loop over all chilren no matter or just stmt_block
        for (size_t i = 0; i < ptr->children[1]->children.size(); i++)
            parse_stmt(ptr->children[1]->children[i], return_type, in_loop);
    else if (desc == "break")
        semantic_assert(in_loop, "Break Not allowed outside of loop");
    else if (desc == "print"){
        std::vector<parse_tree *> actuals = ptr->children[1]->children;
        for (size_t i = 0; i < actuals.size(); i++){
            s_type * arg = get_expr_type(actuals[i]);
            semantic_assert(arg && (arg->name == "int" || arg->name == "string" || arg->name == "bool" || arg->name == "double"),
                            "You can only print an int, double, bool, or string");
        }
    }
    else
        get_expr_type(ptr);
}

void sem_pass_two(parse_tree * top)
{
    semantic_assert(top->description == "program",
                   "Can't be an empty file");
    bool got_main = false;

    for (size_t i = 0; i < top->children.size(); i++){
        parse_tree * child = top->children[i];
        std::string child_desc = child->description;
        if (child_desc == "functiondecl")
        {
            if (child->children[1]->tok->text == "main" && 
                child->children[0]->tok &&
                child->children[0]->tok->type == 260 &&
                child->children[2]->children.size() == 0)
                got_main = true;

            parse_function(child);
        }
        else if (child_desc == "class") {
            current_classy = dynamic_cast<s_class *>(top_scope->lookup(child->children[0]->tok->text));
            for (size_t x = 0; x < child->children[3]->children.size(); x++)
                if (child->children[3]->children[x]->description == "functiondecl")
                    parse_function(child->children[3]->children[x]);
            current_classy = nullptr;
        }
    // nothing to do for interfaces or variables
        else if (child_desc == "interface"){}
        else if (child_desc == "variable"){}
        else
            semantic_assert(false, "Bad Global thing");

    }
    semantic_assert(got_main, "You must add a void main function with no paramenters");
}

void main_sem()
{
   semantic_checks = true;
   current_line = 1;
   current_scope = nullptr;
   open_scope();

   // add in primive types
   current_scope->add("double", semantics_double_type);
   current_scope->add("int", semantics_int_type);
   current_scope->add("bool", semantics_bool_type);
   current_scope->add("string", semantics_string_type);
   open_scope();  // this would allow redefinition of built-ins.
   top_scope = current_scope;

   yyparse();
   sem_post_pass_one();
   sem_pass_two(top);
   traverse_tree(top);
}


void main_gen()
{
   main_sem();
   std::string fname = program_name + ".j";
   gout = new std::ofstream(fname.c_str());
   if (!*gout)
   {
      std::cerr << "Can't open " << fname << " for writing" << std::endl;
      exit(1);
   }
   gen_preamble();
   gen_main_block(top, "java/lang/Object");
   gen_main_boilerplate();

   delete gout;
}
