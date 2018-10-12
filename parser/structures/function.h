//
// Created by Samson on 2018/5/29.
//

#ifndef VERIFY_ST_PROGRAMS_FUNCTION_H
#define VERIFY_ST_PROGRAMS_FUNCTION_H

#include <string>

#include "pou.h"

class Function : public POU
{
public:
    Function(symbol_c *_symbol);

    virtual ~Function();

    /**
     * getters and setters
     */
    std::string get_str_function_type();

private:
    std::string str_function_type;
};


#endif //VERIFY_ST_PROGRAMS_FUNCTION_H
