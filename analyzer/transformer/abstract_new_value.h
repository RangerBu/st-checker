#ifndef ABSTRACT_NEW_VALUE_H
#define ABSTRACT_NEW_VALUE_H

#include "../domain/Value_set.h"

class Abstract_new_value
{
    /**
    * public attributes
    */
public:
    Abstract_new_value();
    Abstract_new_value(key, std::string, key);

    ~Abstract_new_value();

    /**
    * private attributes
    */
private:
    key left_var;
    int_value left_si;
    bool_value left_bv1;
    byte_value left_bv8;

    key right_var;
    int_value right_si;
    bool_value right_bv1;
    byte_value right_bv8;

    std::string op;
};

#endif // ABSTRACT_NEW_VALUE_H
