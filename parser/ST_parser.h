#ifndef ST_PARSER_H
#define ST_PARSER_H

#include <string>
#include <stdarg.h>
#include <cstdlib>

#include "absyntax/absyntax.hh"
#include "main.hh"
#include "absyntax_utils/absyntax_utils.hh"
#include "stage1_2/stage1_2.hh"

#include "Absyntax_visitor.h"
#include "Absyntax_visitor_weight.h"
#include "../analyzer/transformer/Abstract_transfer.h"

class ST_parser{

/**
* static methods
*/

public:
    static std::string parse(symbol_c *);
    static void parse_weight(symbol_c *, Abstract_transfer *);

public:
    ST_parser();
    ST_parser(std::string);
    virtual ~ST_parser();

    /**
    * getters and setters
    */
    program_declaration_c *get_prog();
    var_declarations_list_c *get_vars();
    statement_list_c *get_stmts_list();

    /**
    * helpers
    */
    void init();

private:
    std::string file_name;

    program_declaration_c *prog;
    var_declarations_list_c *vars;
    statement_list_c *stmts_list;


};

#endif // ST_PARSER_H
