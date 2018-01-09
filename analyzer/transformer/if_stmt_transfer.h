#ifndef IF_STMT_TRANSFER
#define IF_STMT_TRANSFER

#include <string>

#include "value_set_transfer.h"
#include "../domain/value_set.h"

class If_stmt_transfer : public Abstract_value_set_transfer
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    If_stmt_transfer(symbol_c *);

    /*
    * de-constructor
    */
    virtual ~If_stmt_transfer();


    /**
    * external visible methods
    */
    Value_set *op_transform(Value_set *);


    /**
    * getters and setters
    */
    Var *get_left_var();

    Var *get_right_var1();

    std::string get_str_left_var();

    std::string get_str_right_var1();

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
    * left_var op right_var1
    */
    Var *left_var;

    Var *right_var1;

    std::string str_left_var;

    std::string str_right_var1;

    std::string str_op;

    symbol_c *statement;
};

#endif // IF_STMT_TRANSFER
