//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_ABSTRACT_VALUE_H
#define VERIFY_ST_PROGRAMS_ABSTRACT_VALUE_H

#include <string>

class Abstract_value
{
public:

    virtual Abstract_value *get_top()=0;

    virtual bool equal(Abstract_value *_other)=0;

    std::string get_str_value();

protected:
    std::string str_value;
};


#endif //VERIFY_ST_PROGRAMS_ABSTRACT_VALUE_H
