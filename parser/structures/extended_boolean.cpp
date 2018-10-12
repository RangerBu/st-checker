//
// Created by Samson on 2018/5/30.
//

#include "extended_boolean.h"

Extended_boolean::Extended_boolean(std::string _str_value)
{
    str_value = _str_value;
}

Extended_boolean::~Extended_boolean()
{
}

Abstract_value* Extended_boolean::get_top()
{
    return TOP;
}

bool Extended_boolean::equal(Abstract_value *_other)
{
    return this == _other;
}


Extended_boolean *Extended_boolean::TOP = new Extended_boolean("T_B");
Extended_boolean *Extended_boolean::TRUE = new Extended_boolean("TRUE");
Extended_boolean *Extended_boolean::FALSE = new Extended_boolean("FALSE");

