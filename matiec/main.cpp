#include <iostream>
#include <fstream>

#include <stdarg.h>
#include "main.hh"
#include "absyntax/absyntax.hh"
#include "absyntax_utils/absyntax_utils.hh"
#include "stage1_2/stage1_2.hh"


#include "CFG.h"
#include "str_name_visitor.h"


using namespace std;
runtime_options_t runtime_options;

#define INPUT_FILE "in.txt"
#define DEBUG_LOG "debug.txt"


/**
* forward declaration
*/
void error_exit(const char *file_name, int line_no, const char *errmsg, ...);

int main()
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
    runtime_options.relaxed_datatype_model    = false; /* by default use the strict datatype equivalence model */

    symbol_c *tree_root;
    stage1_2("in.txt", &tree_root);
    ofstream fout(DEBUG_LOG);

    fout.close();
    return 0;
}

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
