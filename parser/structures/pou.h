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
    // POU������
    std::string str_pou_name;

    // POU��Ӧ���﷨������
    symbol_c *symbol;

    // �������ֵ��﷨���ṹ
    var_declarations_list_c *var_declarations_list;

    // ���岿�ֵ��﷨���ṹ
    statement_list_c *statement_list;

    // �������ְ����ı���
    std::vector<Variable *> v_variable_list;

    // ������ֵ
    std::map<Variable *, Abstract_value *> m_assignment;

    // �������
    std::vector<Variable *> v_input_variable_list;

    // �������
    std::vector<Variable *> v_output_variable_list;

    // �ڲ�����
    std::vector<Variable *> v_internal_variable_list;

    // ��ʱ����
    std::vector<Variable *> v_temp_variable_list;

    // ȫ�ֱ���
    std::vector<Variable *> v_global_variable_list;

    // body���ֶ�Ӧ��CFG
    CFG *cfg;
};


#endif //VERIFY_ST_PROGRAMS_POU_H
