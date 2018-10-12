//
// Created by Samson on 2018/5/30.
//

#include <sstream>

#include "variable.h"

std::string Variable::VARIABLE_TYPE_INT = "INT";

std::string Variable::VARIABLE_TYPE_BOOL = "BOOL";

Variable::Variable(std::string _str_variable_name, std::string _str_variable_type) :
        str_variable_name(_str_variable_name), str_variable_type(_str_variable_type)
{

}

Variable::~Variable()
{

}

bool Variable::equal(Variable *_other)
{
    return str_variable_name.compare(_other->get_str_variable_name()) == 0 && str_variable_type.compare(_other->get_str_variable_type()) == 0;
}

std::string Variable::get_str_variable_name()
{
    return str_variable_name;
}

std::string Variable::get_str_variable_type()
{
    return str_variable_type;
}

std::ostream &operator<<(std::ostream &_out, Variable &_variable)
{
    std::stringstream ss;
    ss << "[" << _variable.str_variable_name << "(" << _variable.str_variable_type << ")]";

    return _out << ss.str();
}