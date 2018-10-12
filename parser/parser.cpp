//
// Created by Samson on 2018/5/29.
//

#include <cstdarg>
#include <fstream>

#include "main.hh"
#include "stage1_2/stage1_2.hh"

#include "parser.h"
#include "structures/function.h"
#include "../debug_helper.h"

runtime_options_t runtime_options;

void error_exit(const char *file_name, int line_no, const char *errmsg, ...) {
    va_list argptr;
    va_start(argptr, errmsg); /* second argument is last fixed pamater of error_exit() */

    fprintf(stderr, "\nInternal compiler error in file %s at line %d", file_name, line_no);
    if (errmsg != NULL) {
        fprintf(stderr, ": ");
        vfprintf(stderr, errmsg, argptr);
    } else {
        fprintf(stderr, ".");
    }
    fprintf(stderr, "\n");
    va_end(argptr);

    exit(EXIT_FAILURE);
}

Parser::Parser(std::string _file_path) : file_path(_file_path)
{
    runtime_options.pre_parsing             = false; /* allow use of forward references (run pre-parsing phase before the definitive parsing phase that builds the AST) */
    runtime_options.safe_extensions         = false; /* allow use of SAFExxx datatypes */
    runtime_options.full_token_loc          = false; /* error messages specify full token location */
    runtime_options.conversion_functions    = false; /* Create a conversion function for derived datatype */
    runtime_options.nested_comments         = false; /* Allow the use of nested comments. */
    runtime_options.ref_standard_extensions = false; /* Allow the use of REFerences (keywords REF_TO, REF, DREF, ^, NULL). */
    runtime_options.ref_nonstand_extensions = false; /* Allow the use of non-standard extensions to REF_TO datatypes: REF_TO ANY, and REF_TO in struct elements! */
    runtime_options.nonliteral_in_array_size= false; /* Allow the use of constant non-literals when specifying size of arrays (ARRAY [1..max] OF INT) */
    runtime_options.includedir              = NULL;  /* Include directory, where included files will be searched for... */
    /* Default values for the command line options... */
    runtime_options.relaxed_datatype_model  = false; /* by default use the strict datatype equivalence model */

    symbol_c *tree_root;
    stage1_2(this->file_path.c_str(), &tree_root);

//    program_declaration_c * program_ = (program_declaration_c *)((library_c *)tree_root)->get_element(1776);

//    Program program((program_declaration_c *)((library_c *)tree_root)->get_element(1776));

    library_c * pou_list = (library_c *)tree_root;

    for (int i = 1775; i < pou_list->n; ++i)
    {
        std::string str_cname = pou_list->get_element(i)->absyntax_cname();

        if (str_cname.compare("program_declaration_c") == 0) {

            program = new Program(pou_list->get_element(i));
            v_pou_list.push_back(program);

        } else if (str_cname.compare("function_declaration_c") == 0)
        {
            v_pou_list.push_back(new Function(pou_list->get_element(i)));

        } else if (str_cname.compare("function_block_declaration_c") == 0)
        {

        } else {
            Debug_helper::print_debug_info(__FILE__, __LINE__, "´íÎóµÄPOUÀàÐÍ£¡");
            exit(233);
        }
    }
}

Parser::~Parser()
{

}

Program* Parser::get_program()
{
    return program;
}

std::vector<POU *> Parser::get_v_pou_list()
{
    return v_pou_list;
}