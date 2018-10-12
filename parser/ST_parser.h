//
// Created by zero on 1/17/18.
//

#ifndef ST_CHECKER_ST_PARSER_H
#define ST_CHECKER_ST_PARSER_H


#include <string>
#include <stdarg.h>
#include <cstdlib>

#include "../libs/matiec/absyntax/absyntax.hh"
#include "../libs/matiec/main.hh"
#include "../libs/matiec/absyntax_utils/absyntax_utils.hh"
#include "../libs/matiec/stage1_2/stage1_2.hh"

#include "absyntax_visitor.h"

class ST_parser{

/**
* static methods
*/

public:
    static std::string parse(symbol_c *);

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

#endif //ST_CHECKER_ST_PARSER_H
