#include <iostream>
#include <cstdarg>
#include <fstream>
#include "codegen.h"

std::ostream *gout;
std::string program_name;
size_t curr_label = 1;
size_t current_loop_exit_label = 0;

void codegen_error(char const * fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   vfprintf(stderr, fmt, args);
   std::cout << std::endl;
   va_end(args);
   exit(1);
}

std::string get_java_type(std::string type)
{   
//  //std::clog << "****************************" << type << std::endl;
    if (type.length() > 2 and type.substr(type.length()-2,2) == "[]")
    return "[" + get_java_type(type.substr(0, type.length()-2)); 

    if (type == "int")
        return "I";
    else if (type == "string")
        return "Ljava/lang/String;";
    else if (type == "bool")
        return "Z";
    else if (type == "double")
        return "D";
    else if (type == "void")
        return "V";
    else
    return "L" + type + ";";
    //std::clog << "Type generation broke" << std::endl;
    return "";
}

std::string get_singleton_type(std::string type) 
{
    std::string dtype = get_java_type(type);
    if (dtype == "D") return "d";
    else if (dtype == "I" or dtype == "Z") return "i";
    else return "a";
}

s_var * get_var(parse_tree * tree)
{
    symtab * scope = tree->scope;
    return dynamic_cast<s_var *>(scope->lookup(tree->children[1]->tok->text));
}

void output_label(size_t val) 
{
    (*gout) << "L" << val << ":" << std::endl;
}


void gen_ineq(int op, parse_tree* tree)
{
    s_type * left_type = tree->children[0]->type;
    s_type * right_type = tree->children[2]->type;
    std::string d_type; 
    if (!left_type || !right_type)
        d_type = "a";
    else
        d_type = get_singleton_type(left_type->name);

    if (d_type == "d") {
        (*gout) << "   dcmpg" <<std::endl << "   iconst_0" << std::endl;
        d_type = "i";
    }
    
    if (left_type and right_type and left_type->name == "string" and right_type->name == "string") {
        (*gout) << "   invokevirtual         java/lang/String/equals(Ljava/lang/Object;)Z" << std::endl;
        return;
    }

    size_t first_label = curr_label++;
    size_t second_label = curr_label++;
    //std::clog << "***in gen_ineq" << std::endl;
    //std::clog << op << std::endl;
    if (op == '<')
        (*gout) << "   if_" << d_type << "cmplt            ";
    else if (op == '>')
        (*gout) << "   if_" << d_type << "cmpgt            ";
    else if (op == 288)
        (*gout) << "   if_" << d_type << "cmple            ";
    else if (op == 289)
        (*gout) << "   if_" << d_type << "cmpge            ";
    else if (op == 290)
        (*gout) << "   if_" << d_type << "cmpeq            ";
    else if (op == 291)
        (*gout) << "   if_" << d_type << "cmpne            ";
    else if (op == 292)
        (*gout) << "   iand" << std::endl << "   ifne            ";
    else if (op == 293)
        (*gout) << "   ior" << std::endl  << "   ifne            ";

    (*gout) << "L" <<first_label << std::endl
            << "   iconst_0" << std::endl
            << "   goto                 L" << second_label << std::endl
            <<"L"<< first_label << ":" << std::endl
            << "   iconst_1" << std::endl
            << "L"<<second_label << ":" << std::endl;
}

void gen_binop(parse_tree * tree) 
{
    gen_expr(tree->children[0]);
    gen_expr(tree->children[2]);
    std::string d_type = get_singleton_type(tree->type->name);
    int op = tree->children[1]->tok->type;

    if (op == '+')
        (*gout) << "   " << d_type + "add" << std::endl;
    else if (op == '-')
        (*gout) << "   " << d_type + "sub" << std::endl;
    else if (op == '*')
        (*gout) << "   " << d_type + "mul" << std::endl;
    else if (op == '%')
        (*gout) << "   " << d_type + "rem" << std::endl;
    else if (op == '<' || op == '>' || (op <= 293 && op >= 288))
        gen_ineq(op, tree);
}

void gen_uop(parse_tree * tree)
{
    gen_expr(tree->children[1]);
    if (tree->children[0]->tok->type == '!'){
        (*gout) << "iconst_1" << std::endl;
        (*gout) << "ixor" << std::endl;
    } else {
        (*gout) << "   " << get_singleton_type(tree->type->name) << "neg" << std::endl;
    }
}

void gen_call_identifier(parse_tree * tree) 
{
    s_function * func = dynamic_cast<s_function *>(tree->scope->lookup(tree->children[0]->tok->text));
    if (!func->owner_class){
        for (size_t i = 0; i < tree->children[1]->children.size(); i++)
            gen_expr(tree->children[1]->children[i]);
        (*gout) << "   invokestatic         " << program_name << "_/" << tree->children[0]->tok->text << "("; 
    }
    else {
        (*gout) << "   aload_0" << std::endl;
        for (size_t i = 0; i < tree->children[1]->children.size(); i++)
            gen_expr(tree->children[1]->children[i]);
    (*gout) << "   invokevirtual        " << func->owner_class->name 
            << "/" << tree->children[0]->tok->text << "(";
    }

    for (size_t i = 0; i < func->params.size(); i++)
        (*gout) << get_java_type(func->params[i]->type->name);

    (*gout) << ")" << (func->return_type ? get_java_type(func->return_type->name) : "V") << std::endl;

}

s_prototype * get_function(s_class * classy, s_interface * inter, std::string func_ident)
{
    if (classy){
        for (auto it = classy->function_map.begin(); it != classy->function_map.end(); it++) 
            if (it->first == func_ident)
                return it->second;      

        if (classy->superclass)
            return get_function(classy->superclass, nullptr, func_ident);
    }
    else  if (inter) {
        for (auto it = inter->prototype_map.begin(); it != inter->prototype_map.end(); it++) 
            if (it->first == func_ident)
                return it->second;      
    }

    codegen_error("COULD NOT FIND FUNC OR PROTO FOR: %s", func_ident.c_str());
    return nullptr;

}


void gen_call_fieldaccess(parse_tree * tree)
{
    std::string object_type_name = tree->children[0]->children[0]->type->name;
    //std::clog << "in gen fieldaccess" << std::endl;   
    if (object_type_name[object_type_name.length() - 1] == ']' 
      && tree->children[0]->children[1]->tok->text == "length"){
        gen_expr(tree->children[0]->children[0]);
        (*gout) << "  arraylength" << std::endl; 
        return;
    }
    
    s_interface * inter = dynamic_cast<s_interface *>(top_scope->lookup(object_type_name));
    gen_expr(tree->children[0]->children[0]);
    
    // Generate arguments
    for (size_t i = 0; i < tree->children[1]->children.size(); i++)
        gen_expr(tree->children[1]->children[i]);

    // Create the function call
    (*gout) << "   invoke" << (inter ? "interface      " : "virtual        ") << object_type_name << "/"
        << tree->children[0]->children[1]->tok->text << "(";
    int count = 1;
    s_class * classy = dynamic_cast<s_class *>(top_scope->lookup(object_type_name));
    s_prototype * proto = get_function(classy, inter, tree->children[0]->children[1]->tok->text);
    for (size_t i = 0; i < proto->params.size(); i++){
        std::string jtype = get_java_type(proto->params[i]->type->name);
        count += jtype == "D" ? 2 : 1;
        (*gout) << jtype;
    }

    (*gout) << ")" << (proto->return_type ? get_java_type(proto->return_type->name) : "V") << " " << (inter ? std::to_string(count) : "") << std::endl;
    
}

void gen_call(parse_tree * tree) {
    if (tree->children[0]->tok && tree->children[0]->tok->type == 282)  //Is it an Identifier?
        gen_call_identifier(tree);
    else  // It is a field access!
        gen_call_fieldaccess(tree);
}

void gen_aref(parse_tree * tree) 
{
    gen_expr(tree->children[0]);
    gen_expr(tree->children[1]);
    std::string dtype = get_singleton_type(tree->type->name);
    (*gout) << "   " << dtype << "aload" << std::endl; 
}

void gen_fieldaccess(parse_tree * tree) 
{
    gen_expr(tree->children[0]);
    (*gout) << "   getfield " <<  "            " 
          << tree->children[0]->type->name << "/" 
          << tree->children[1]->tok->text << " " 
          << get_java_type(tree->type->name) << std::endl;
}

void gen_INTLITERAL(parse_tree * tree) 
{
    int value = std::stoi(tree->tok->text);
    if (value < 6)
        (*gout) << "   iconst_" << value << std::endl;
    else 
        (*gout) << "   ldc                  " << value << std::endl;
}

void gen_DBLLITERAL(parse_tree * tree) 
{
    double value = std::stod(tree->tok->text);
    if (value == 0.0)
        (*gout) << "   dconst_0";
    else if (value == 1.0)
        (*gout) << "   dconst_1";
    else
        (*gout) << "   ldc2_w                " << tree->tok->text;
    (*gout) << std::endl;
}

void gen_STRINGLITERAL(parse_tree * tree) 
{
    (*gout) << "    ldc                   " << tree->tok->text << std::endl;
}

void gen_BOOLLITERAL(parse_tree * tree) 
{
    (*gout) << "    iconst_" << (tree->tok->text == "true" ? 1 : 0) << std::endl;
}

void gen_IDENTIFIER(parse_tree * tree) 
{
    s_var * var = tree->variable;
    if (var->num >= 0){
        (*gout) << "   " << get_singleton_type(var->type->name) 
            << "load                " << var->num << std::endl;
    } else {
        std::string name = var->classy ? var->classy->name : (program_name + "_");
        if (var->classy) (*gout) << "   aload_0" << std::endl;
        (*gout) << "   get" << (var->classy ? "field " : "static") <<  "            " 
            << name << "/" << var->name << " " << get_java_type(var->type->name) << std::endl;; 
    }
}

void gen_THIS(parse_tree * tree) 
{
    (*gout) << "   aload_0" << std::endl;
}


void gen_scanner(std::string scanner_type)
{
    (*gout) <<
       "   new                   java/util/Scanner" << std::endl <<
       "   dup" << std::endl <<     
       "   getstatic             java/lang/System/in Ljava/io/InputStream;"  <<   std::endl <<
       "   invokespecial         java/util/Scanner/<init>(Ljava/io/InputStream;)V" << std::endl <<
       "   invokevirtual         " << scanner_type << std::endl;
    // who needs to close scanners
}

void gen_READINT(parse_tree * tree) 
{
    gen_scanner("java/util/Scanner/nextInt()I");
}

void gen_READLINE(parse_tree * tree) 
{
    gen_scanner("java/util/Scanner/nextLine()Ljava/lang/String;");
}

void gen_new(parse_tree * tree) 
{
    (*gout) << "   new                  " << tree->children[0]->tok->text << std::endl
        << "   dup" << std::endl
        << "   invokespecial        " << tree->children[0]->tok->text << "/<init>()V" << std::endl;
}

void gen_null(parse_tree * tree) 
{
    (*gout) << "   aconst_null" << std::endl;
}

s_type * make_type_codegen(parse_tree * tree) 
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
        return new s_arraytype(make_type_codegen(tree->children[0]));
    }
    else if (tree->description == "usertype")
        return new s_usertype(tree->children[0]->tok->text);
    else if (tree->tok && tree->tok->type == 282)
        return new s_usertype(tree->tok->text);
    else // void returns nullpty
        return nullptr;
}

std::string get_array_java_type(s_type * type) 
{
    s_arraytype * arr = dynamic_cast<s_arraytype *>(type);
    if (arr) return "[" + get_array_java_type(arr->content_type);
        return get_java_type(type->name);
    
}

void gen_newarray(parse_tree * tree) 
{
    gen_expr(tree->children[0]);
    std::string type;
    std::string prefix;
    
    // Is it a primtype?
    if (tree->children[1]->description == "primtype" 
        && tree->children[1]->children[0]->tok->type != 264){
        int t = tree->children[1]->children[0]->tok->type;
        if (t == 262)
            type = "double";
        else if (t == 261)
            type = "int";
        else if (t == 263)
            type = "bool";
        else 
            codegen_error("BAD ARRAY TYPE");
        prefix = "";
    }
    // Is is a userdefined object?
    else if (tree->children[1]->description == "usertype"){
        type = tree->children[1]->children[0]->tok->text;
        prefix = "a";
    } else {
        type = get_array_java_type(make_type_codegen(tree->children[1]));
        prefix = "a";
    }   
    (*gout) << "   " << prefix << "newarray            " << (prefix.length() ? "" : " ") << type << std::endl;
}

void gen_expr(parse_tree * tree) 
{
    std::string desc = tree -> description;
    int t = tree->tok ? tree->tok->type : 0;

    //std::clog << "Generating code for expr: " << desc << "T: " << t<< std::endl;
    if (desc == "binop")                gen_binop(tree);
    else if (desc == "uop")             gen_uop(tree);
    else if (desc == "call")            gen_call(tree);
    else if (desc == "aref")            gen_aref(tree);
    else if (desc == "fieldaccess")         gen_fieldaccess(tree);
    else if (desc == "newarray")            gen_newarray(tree);
    else if (desc == "INTLITERAL" || t == 285)  gen_INTLITERAL(tree);
    else if (desc == "DBLLITERAL" || t == 286)  gen_DBLLITERAL(tree);
    else if (desc == "STRINGLITERAL" || t == 287)   gen_STRINGLITERAL(tree);
    else if (desc == "BOOLLITERAL" || t == 284)     gen_BOOLLITERAL(tree);
    else if (desc == "IDENTIFIER" || t == 282)  gen_IDENTIFIER(tree);
    else if (desc == "THIS" || t==268)      gen_THIS(tree);
    else if (desc == "READLINE"|| t == 281)     gen_READLINE(tree);
    else if (desc == "READINT" || t == 280)     gen_READINT(tree);
    else if (desc == "new"     || t == 277)     gen_new(tree);
    else if (desc == "null"    || t == 267)     gen_null(tree);
    else
        codegen_error("Exper failed to parse with tok: %i, and %s as desc.", t, desc.c_str());
    //std::clog << "Exiting code for expr: " << desc << "T: " << t<< std::endl;
}

void gen_assign_ident(parse_tree * tree)
{
    s_var * var = tree->children[0]->variable;
    if (var->num >= 0){
        gen_expr(tree->children[2]);
        (*gout) << "   " << get_singleton_type(var->type->name) << "store               " << var->num << std::endl;
    }
    else {
        std::string name = var->classy ? var->classy->name : (program_name + "_");
        if (var->classy) (*gout) << "   aload_0" << std::endl;
        gen_expr(tree->children[2]);
        (*gout) << "   put" << (var->classy ? "field " : "static") 
            <<  "            " << name << "/" << var->name << " " << get_java_type(var->type->name) << std::endl;; 
    }
}

void gen_assign_fieldaccess(parse_tree * tree)
{
    gen_expr(tree->children[0]->children[0]);
    gen_expr(tree->children[2]);
    (*gout) << "   putfield             " << tree->children[0]->children[0]->type->name
        << "/" << tree->children[0]->children[1]->tok->text << " " 
        << get_java_type(tree->children[2]->type->name) << std::endl;
}

void gen_assign_aref(parse_tree * tree) 
{
    parse_tree * aref = tree->children[0];
    parse_tree * value = tree->children[2];

    gen_expr(aref->children[0]);
    gen_expr(aref->children[1]);
    gen_expr(value);
    
    std::string dtype = get_singleton_type(value->type->name);

    (*gout) << "   " << dtype << "astore" << std::endl;
}

void gen_assign_stmt(parse_tree * tree)
{
    std::string desc = tree->children[0]->description;
    int t = tree->children[0]->tok ? tree->children[0]->tok->type : 0;
    if (desc == "IDENTIFIER" || t == 282) gen_assign_ident(tree);
    else if (desc == "fieldaccess") gen_assign_fieldaccess(tree);
    else if (desc == "aref") gen_assign_aref(tree);
    else codegen_error("A non supported l value has broken through!");
}

void gen_if_stmt(parse_tree * tree)
{
    size_t else_begin = curr_label++;
    size_t else_end = curr_label++;
    // push expression value on stack
    gen_expr(tree->children[0]);

    // generate if instruction
    (*gout) << "   ifeq                 L" << else_begin << std::endl;

    // generate if block
    gen_stmt(tree->children[1]);

    // goto end of if
    (*gout) << "   goto                 L" << else_end << std::endl;
    output_label(else_begin);

    // generate else block
    gen_stmt(tree->children[2]);    
    output_label(else_end);
}

void gen_while_stmt(parse_tree * tree)
{
    size_t while_begin = curr_label++;
    size_t while_end = curr_label++;
    size_t old_loop = current_loop_exit_label;
    current_loop_exit_label = while_end;
    output_label(while_begin);
    gen_expr(tree->children[0]);
    (*gout) << "   ifeq                  L" << while_end << std::endl;
    gen_stmt(tree->children[1]);    
    (*gout) << "   goto                  L" << while_begin << std::endl;
    output_label(while_end);
    current_loop_exit_label = old_loop; //Set the exit point back to the original
}

void gen_for_stmt(parse_tree * tree)
{
    size_t for_begin = curr_label++;
    size_t for_end = curr_label++;
    size_t old_loop = current_loop_exit_label;
    gen_stmt(tree->children[0]); //pre for stmt
    current_loop_exit_label = for_end; //Set the exit point for a break
    output_label(for_begin);
    gen_expr(tree->children[1]); //condition
    (*gout) << "   ifeq                 L" << for_end << std::endl;
    gen_stmt(tree->children[3]); //body
    gen_stmt(tree->children[2]); //post body stmt
    (*gout) << "   goto                 L" << for_begin << std::endl;
    output_label(for_end);
    current_loop_exit_label = old_loop; //Set the exit point back to the original
}

void gen_return_stmt(parse_tree * tree)
{
    if (tree->children.size() == 2){
        gen_expr(tree->children[1]);
        (*gout) << "   " << get_singleton_type(tree->children[1]->type->name) << "return" << std::endl;
    }
    else
        (*gout) << "   return" << std::endl;
    //std::clog << "Exiting return" << std::endl;
}

void gen_break_stmt(parse_tree * tree)
{
    (*gout) << "   goto                 L" << current_loop_exit_label << std::endl;
}

void gen_print_stmt(parse_tree * tree)
{   
    std::vector<parse_tree *> childs = tree->children[1]->children;
    for(size_t i = 0; i < childs.size(); i++){
        (*gout) << "   getstatic            java/lang/System/out Ljava/io/PrintStream;" << std::endl;
        gen_expr(childs[i]);
        (*gout) << "   invokevirtual        java/io/PrintStream/print(" << get_java_type(childs[i]->type->name) << ")V" << std::endl;
    }
    (*gout) << "   getstatic            java/lang/System/out Ljava/io/PrintStream;" << std::endl;
    (*gout) << "   ldc                  \"\"" << std::endl;
    (*gout) << "   invokevirtual        java/io/PrintStream/println(Ljava/lang/String;)V" << std::endl;
}

void gen_stmt(parse_tree * tree)
{   
    if (!tree)
        return;

    std::string desc = tree->description;
    //std::clog << "generating code for stmt: " << desc << std::endl;
    if      (desc == "if")
        gen_if_stmt(tree);
    else if (desc == "while")
        gen_while_stmt(tree);
    else if (desc == "for")
        gen_for_stmt(tree);
    else if (desc == "return")
        gen_return_stmt(tree);
    else if (desc == "break")
        gen_break_stmt(tree);
    else if (desc == "binop" && tree->children[1]->tok->type == 61) 
        gen_assign_stmt(tree);
    else if (desc == "print")
        gen_print_stmt(tree);
    else if (desc == "stmtblock")
        gen_stmt_block(tree);
    else {
        //std::clog << "In dropped gen_expr" << std::endl;
        gen_expr(tree);
        // The following conditionally pops anything left on the stack to clean up.
        if (tree->type && tree->type->name != "void") {
            (*gout) << "   pop" << std::endl;
            if (tree->type->name == "double")
                (*gout) << "   pop" << std::endl;
        }
    }
}

void gen_stmt_block(parse_tree * tree) 
{   
    if (!tree)
        return;

    for (size_t i = 0; i < tree->children[1]->children.size(); i++)
        gen_stmt(tree->children[1]->children[i]);
}

void gen_global_var(parse_tree * tree) {
    s_var * var = get_var(tree);
    std::string type = var->type->name;
    std::string ident = tree->children[1]->tok->text;
    (*gout) << ".field          "
            << (var->classy ? "": "static ")
            << ident
            << " "
            << get_java_type(type)
            << std::endl;
}

void gen_function(parse_tree * tree)
{
    std::string func_name = tree->children[1]->tok->text;
    s_function * func = dynamic_cast<s_function *>(tree->scope->lookup(func_name));
    (*gout) << std::endl << ".method            "
            << "public " << (func->owner_class ? "" : "static ")
            << func_name
            << "(";

    for (size_t i = 0; i < func->params.size(); i++) {
        (*gout) << get_java_type(func->params[i]->type->name);
    }
    std::string return_type = func->return_type ? get_java_type(func->return_type->name) : "V";

    (*gout) << ")"
            << return_type
            << std::endl
            << "   .limit stack     "
            << "100"
            << std::endl
            << "   .limit locals            "
            << func->num_locals 
            << std::endl;
    gen_stmt_block(tree->children[3]);
    if (return_type == "V") (*gout) << "   return" << std::endl;
    (*gout) << "   nop" << std::endl << ".end method" << std::endl;
}

void gen_class(parse_tree * tree) 
{
    std::ostream * old = gout;
    std::string class_name = tree->children[0]->tok->text;
    s_class * classy = dynamic_cast<s_class *>(tree->scope->lookup(class_name));
    std::string super_name = classy->superclass ? classy->superclass->name : "java/lang/Object";
    gout = new std::ofstream((class_name + ".j").c_str());
    (*gout) << ".source     " << program_name << ".decaf"<< std::endl;
    (*gout) << ".class      public " << class_name << std::endl;
    (*gout) << ".super      " << super_name << std::endl;
    std::vector<s_interface *> inters = classy->interfaces;
    if (inters.size() > 0) (*gout) << std::endl;
    for (size_t i = 0; i < inters.size(); i++)  
        (*gout) << ".implements         " << inters[i]->name << std::endl;
    gen_main_block(tree->children[3], super_name);
    (*gout)  << std::endl << ".method                 public static main([Ljava/lang/String;)V" << std::endl
         << "   .limit stack         0" << std::endl
         << "   .limit locals        1" << std::endl
         << "   invokestatic         "  << class_name << "/main()V"  << std::endl
         << "   return"                 << std::endl
         << ".end method"  << std::endl;
    delete gout;
    gout = old;
}

void gen_interface(parse_tree * tree) 
{
    std::ostream * old = gout;
    std::string name = tree->children[0]->tok->text;
    gout = new std::ofstream((name + ".j").c_str());
    
    (*gout) << ".source     " << program_name << ".decaf"<< std::endl;
    (*gout) << ".interface      abstract " << name << std::endl;
    (*gout) << ".super      java/lang/Object" << std::endl;
    s_interface * inter = dynamic_cast<s_interface *>(tree->scope->lookup(name));
    for (auto it = inter->prototype_map.begin(); it != inter->prototype_map.end(); it++) {
        s_prototype * s_proto = it->second;
        (*gout) << std::endl << ".method               public abstract " << it->first << "(";
        std::vector<s_var *> params = s_proto->params;
        for (size_t x = 0; x < params.size(); x++)
            (*gout) << get_java_type(params[x]->type->name);
        (*gout) << ")" << (s_proto->return_type ? get_java_type(s_proto->return_type->name) : "V") << std::endl
            << ".end method" << std::endl;
    }
    delete gout;
    gout = old;
}


void gen_preamble()
{
    (*gout) << ".source     " << program_name << ".decaf"<< std::endl;
    (*gout) << ".class      public " << program_name << "_" << std::endl;
    (*gout) << ".super      java/lang/Object " << std::endl;
}


void gen_main_boilerplate()
{
    (*gout)  << std::endl << ".method                 public static main([Ljava/lang/String;)V" << std::endl
         << "   .limit stack         0" << std::endl
         << "   .limit locals        1" << std::endl
         << "   invokestatic         " << program_name << "_/main()V"  << std::endl
         << "   return"                  << std::endl
         << ".end method"  << std::endl;
}

void gen_main_block(parse_tree *tree, std::string super_name)
{       
    for (size_t i = 0; i < tree->children.size(); i++) 
        if (tree->children[i]->description == "variable")
            gen_global_var(tree->children[i]);

     (*gout) << std::endl << ".method                 public <init>()V" << std::endl
         << "   .limit stack         1" << std::endl
         << "   .limit locals        1" << std::endl
         << "   aload_0" << std::endl
         << "   invokespecial        " << super_name << "/<init>()V" << std::endl
         << "   return" << std::endl
         << ".end method" << std::endl;

    for (size_t i = 0; i < tree->children.size(); i++) {
        parse_tree * n = tree->children[i];
        if (n->description == "functiondecl")
            gen_function(n);
        else if (n->description == "class")
            gen_class(n);
        else if (n->description == "interface")
            gen_interface(n);
    }
}
