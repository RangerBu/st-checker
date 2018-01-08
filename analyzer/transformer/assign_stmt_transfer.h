#ifndef ASSIGN_STMT_TRANSFER_H
#define ASSIGN_STMT_TRANSFER_H

#include <string>
#include <iostream>

#include "value_set_transfer.h"
#include "../domain/var.h"
#include "../structures/strided_interval.h"
#include "../structures/bits_vector_8.hpp"

class Assign_stmt_transfer : public Abstract_value_set_transfer
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Assign_stmt_transfer(symbol_c *);

    virtual ~Assign_stmt_transfer();


    /**
    * external visible methods - inherited methods
    */
    Value_set *op_transform(Value_set *);


    /**
    * getters and setters
    */
    std::string get_str_left_var();

    Var *get_left_var();

    std::string get_str_right_var1();

    Var *get_right_var1();

    std::string get_str_right_var2();

    Var *get_right_var2();

    std::string get_str_op();

    symbol_c *get_statement();


    /**
    * helpers - inherited methods
    */
    bool equal(Abstract_value_set_transfer *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    /*
    * left_var = right_var1 op right_var2
    */
    Var *left_var;

    Var *right_var1;

    Var *right_var2;

    std::string str_op;

    std::string str_left_var;

    std::string str_right_var1;

    std::string str_right_var2;

    symbol_c *statement;
};


#endif // ASSIGN_STMT_TRANSFER_H
