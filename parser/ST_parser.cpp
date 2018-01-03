#include "ST_parser.h"


/**
* static methods
*/
std::string ST_parser::parse(symbol_c *_symbol)
{
    AbsyntaxVisitor *v = new AbsyntaxVisitor();
    v->init_str_statement();
    _symbol->accept(*v);
    std::string ret = v->get_str_statement();
    delete v;
    return ret;
}

/**
* public methods
*/
ST_parser::ST_parser()
{
    file_name = "in.txt";
    init();
}
ST_parser::ST_parser(std::string _file_name)
{
    file_name = _file_name;
    init();
}
ST_parser::~ST_parser()
{

}

/**
* getters and setters
*/
program_declaration_c *ST_parser::get_prog()
{
    return prog;
}
var_declarations_list_c *ST_parser::get_vars()
{
    return vars;
}
statement_list_c *ST_parser::get_stmts_list()
{
    return stmts_list;
}

/**
* helpers
*/
void ST_parser::init()
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
    stage1_2(this->file_name.c_str(), &tree_root);
    prog = (program_declaration_c *)((library_c *)tree_root)->get_element(1775);
    vars = (var_declarations_list_c *) prog->var_declarations;
    stmts_list = (statement_list_c *) prog->function_block_body;

}


/**
* others
*/
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
