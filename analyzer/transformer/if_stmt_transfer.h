#ifndef IF_STMT_TRANSFER
#define IF_STMT_TRANSFER

#include <string>

#include "Abstract_transfer.h"
#include "../domain/Value_set.h"

class If_stmt_transfer : public Abstract_transfer
{
    /**
    * public methods
    */
public:
    If_stmt_transfer();
    virtual ~If_stmt_transfer();

    Value_set *Transform(symbol_c *, Value_set *);

    /**
    * private attributes
    */
private:
    std::string op;
    std::string str_left_var, str_right_var;

    key left_var, right_var;


};

#endif // IF_STMT_TRANSFER
