#ifndef IF_STMT_TRANSFER
#define IF_STMT_TRANSFER

#include <string>

#include "value_set_transfer.h"
#include "../domain/Value_set.h"

class If_stmt_transfer : public Value_set_transfer
{
    /**
    * public methods
    */
public:
    If_stmt_transfer(symbol_c *);
    virtual ~If_stmt_transfer();

    Value_set *Transform(Value_set *);
    std::string format();

    /**
    * private attributes
    */
private:
    std::string op;
    std::string str_left_var, str_right_var;

    key left_var, right_var;

    symbol_c *statement;


};

#endif // IF_STMT_TRANSFER
