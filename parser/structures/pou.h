//
// Created by Samson on 2018/5/29.
//

#ifndef VERIFY_ST_PROGRAMS_POU_H
#define VERIFY_ST_PROGRAMS_POU_H

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "absyntax/absyntax.hh"

#include "variable.h"
#include "abstract_value.h"
#include "cfg.h"

class POU
{
public:

    /**
     * getters and setters
     */
    std::string get_str_pou_name();

    symbol_c *get_symbol();

    var_declarations_list_c *get_variable_declarations_list();

    statement_list_c *get_statement_list();

    std::vector<Variable *> get_variable_list();

    std::map<Variable *, Abstract_value *> get_m_assignment();

    CFG *get_cfg();

    std::vector<Variable *> get_v_input_variable_list();

    std::vector<Variable *> get_v_output_variable_list();

    std::vector<Variable *> get_v_internal_variable_list();

    std::vector<Variable *> get_v_temp_variable_list();

    std::vector<Variable *> get_v_global_variable_list();

    /**
     * helpers
     */


protected:
    // POU的名字
    std::string str_pou_name;

    // POU对应的语法树对象
    symbol_c *symbol;

    // 声明部分的语法树结构
    var_declarations_list_c *var_declarations_list;

    // 主体部分的语法树结构
    statement_list_c *statement_list;

    // 声明部分包含的变量
    std::vector<Variable *> v_variable_list;

    // 变量的值
    std::map<Variable *, Abstract_value *> m_assignment;

    // 输入变量
    std::vector<Variable *> v_input_variable_list;

    // 输出变量
    std::vector<Variable *> v_output_variable_list;

    // 内部变量
    std::vector<Variable *> v_internal_variable_list;

    // 临时变量
    std::vector<Variable *> v_temp_variable_list;

    // 全局变量
    std::vector<Variable *> v_global_variable_list;

    // body部分对应的CFG
    CFG *cfg;
};


#endif //VERIFY_ST_PROGRAMS_POU_H
