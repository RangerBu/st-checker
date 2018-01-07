#ifndef ASSIGN_STMT_TRANSFER_H
#define ASSIGN_STMT_TRANSFER_H

#include <string>
#include <iostream>

#include "value_set_transfer.h"
#include "../domain/Var.h"
#include "../structures/Strided_interval.h"
#include "../structures/bits_vector_8.hpp"

class Assign_stmt_transfer : public Value_set_transfer
{

public:
    Assign_stmt_transfer(symbol_c *);
    virtual ~Assign_stmt_transfer();

//    Value_set *Transform(symbol_c *, Value_set *);
    Value_set *Transform(Value_set *);
    std::string format();

    /**
    * private attributes
    */
private:
    // left_var = right_var1 op right_var2
    Var *left_var;
    Var *right_var1;
    Var *right_var2;

    std::string op;
    std::string str_left_var;
    std::string str_right_var1;
    std::string str_right_var2;

    symbol_c *statement;
};


#endif // ASSIGN_STMT_TRANSFER_H
