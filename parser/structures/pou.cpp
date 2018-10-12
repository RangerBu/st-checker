//
// Created by Samson on 2018/5/29.
//

#include "pou.h"

std::string POU::get_str_pou_name()
{
    return str_pou_name;
}

symbol_c* POU::get_symbol()
{
    return symbol;
}

var_declarations_list_c* POU::get_variable_declarations_list()
{
    return var_declarations_list;
}

statement_list_c* POU::get_statement_list()
{
    return statement_list;
}

std::vector<Variable *> POU::get_variable_list()
{
    return v_variable_list;
}

std::map<Variable *, Abstract_value *> POU::get_m_assignment()
{
    return m_assignment;
}

CFG* POU::get_cfg()
{
    return cfg;
}

std::vector<Variable *> POU::get_v_input_variable_list()
{
    return v_input_variable_list;
}

std::vector<Variable *> POU::get_v_output_variable_list()
{
    return v_output_variable_list;
}

std::vector<Variable *> POU::get_v_internal_variable_list()
{
    return v_internal_variable_list;
}

std::vector<Variable *> POU::get_v_temp_variable_list()
{
    return v_temp_variable_list;
}

std::vector<Variable *> POU::get_v_global_variable_list()
{
    return v_global_variable_list;
}