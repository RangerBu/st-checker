#ifndef ASSIGN_STMT_TRANSFER_H
#define ASSIGN_STMT_TRANSFER_H

#include <string>
#include <iostream>

#include "Abstract_transfer.h"
#include "../domain/Var.h"
#include "../structures/Strided_interval.h"
#include "../structures/Bits_vector_8.h"

class Assign_stmt_transfer : public Abstract_transfer
{

public:
    Assign_stmt_transfer();
    Assign_stmt_transfer(symbol_c *);
    virtual ~Assign_stmt_transfer();

    Value_set *Transform(symbol_c *, Value_set *);
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
};


#endif // ASSIGN_STMT_TRANSFER_H
