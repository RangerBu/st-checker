//
// Created by Samson on 2018/5/29.
//

#include <sstream>

#include "program.h"
#include "interval.h"
#include "extended_boolean.h"
#include "../utils.h"
#include "../../debug_helper.h"

Program::Program(symbol_c *_symbol)
{
    symbol = _symbol;

    program_declaration_c *prog = (program_declaration_c *)symbol;

    str_pou_name = prog->program_type_name->token->value;

    var_declarations_list = (var_declarations_list_c *) prog->var_declarations;

    statement_list = (statement_list_c *) prog->function_block_body;

    // �����������֣��õ������б�
    for (int i = 0; i < var_declarations_list->n; ++i)
    {
        std::string str_cname = var_declarations_list->get_element(i)->absyntax_cname();

        if (str_cname.compare("input_declarations_c") == 0)
        {
            // �������
            input_declaration_list_c *input_declaration_list = (input_declaration_list_c *) ((input_declarations_c *)var_declarations_list->get_element(i))->input_declaration_list;

            /**
             * VAR_INPUT
             * IN, IN1 : INT;
             * IN2 : INT := 10;
             * END_VAR
             */
            // input_declaration_list->n Ϊ����
            for (int j = 0; j < input_declaration_list->n; ++j)
            {
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)input_declaration_list->get_element(j);

                // �������б�
                var1_list_c *var1_list = (var1_list_c *) var1_init_decl->var1_list;


                // ��ʼֵ��������������
                simple_spec_init_c *simple_spec_init = (simple_spec_init_c *) var1_init_decl->spec_init;

                // ��������
                std::string str_type = simple_spec_init->simple_specification->absyntax_cname();


                for (int k = 0; k < var1_list->n; ++k)
                {
                    std::string str_variable_name = var1_list->get_element(k)->token->value;

                    Variable *variable = 0;

                    if (str_type.compare("int_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_INT);

                        v_input_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        // ���ó�ʼֵ��Ĭ������Ϊ[0, 0]�� Boolean��Ϊfalse
                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;
                            int initial_value = utils::to_number(str_initial_value);

                            m_assignment[variable] = new Interval(initial_value, initial_value);

                        } else {
                            m_assignment[variable] = new Interval(0, 0);
                        }

                    } else if (str_type.compare("bool_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_BOOL);

                        v_input_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;

                            if (str_initial_value.compare("TRUE") == 0)
                            {
                                m_assignment[variable] = Extended_boolean::TRUE;
                            } else {
                                m_assignment[variable] = Extended_boolean::FALSE;
                            }
                        } else {
                            m_assignment[variable] = Extended_boolean::FALSE;
                        }

                    } else {
                        Debug_helper::print_debug_info(__FILE__, __LINE__, "Ŀǰ�в�֧�ֵ��������ͣ�");
                        exit(233);
                    }
                }
            }
        } else if (str_cname.compare("output_declarations_c") == 0)
        {
            // �������
            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *) ((output_declarations_c *) var_declarations_list->get_element(i))->var_init_decl_list;

            for (int j = 0; j < var_init_decl_list->n; ++j)
            {
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list->get_element(j);

                // �������б�
                var1_list_c *var1_list = (var1_list_c *) var1_init_decl->var1_list;


                // ��ʼֵ��������������
                simple_spec_init_c *simple_spec_init = (simple_spec_init_c *) var1_init_decl->spec_init;

                // ��������
                std::string str_type = simple_spec_init->simple_specification->absyntax_cname();


                for (int k = 0; k < var1_list->n; ++k)
                {
                    std::string str_variable_name = var1_list->get_element(k)->token->value;

                    Variable *variable = 0;

                    if (str_type.compare("int_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_INT);

                        v_output_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        // ���ó�ʼֵ��Ĭ������Ϊ[0, 0]�� Boolean��Ϊfalse
                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;
                            int initial_value = utils::to_number(str_initial_value);

                            m_assignment[variable] = new Interval(initial_value, initial_value);

                        } else {
                            m_assignment[variable] = new Interval(0, 0);
                        }

                    } else if (str_type.compare("bool_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_BOOL);

                        v_output_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;

                            if (str_initial_value.compare("TRUE") == 0)
                            {
                                m_assignment[variable] = Extended_boolean::TRUE;
                            } else {
                                m_assignment[variable] = Extended_boolean::FALSE;
                            }
                        } else {
                            m_assignment[variable] = Extended_boolean::FALSE;
                        }

                    } else {
                        Debug_helper::print_debug_info(__FILE__, __LINE__, "Ŀǰ�в�֧�ֵ��������ͣ�");
                        exit(233);
                    }
                }
            }
        } else if (str_cname.compare("var_declarations_c") == 0)
        {
            // �ڲ�����
            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *) ((var_declarations_c *) var_declarations_list->get_element(i))->var_init_decl_list;

            for (int j = 0; j < var_init_decl_list->n; ++j)
            {
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list->get_element(j);

                // �������б�
                var1_list_c *var1_list = (var1_list_c *) var1_init_decl->var1_list;


                // ��ʼֵ��������������
                simple_spec_init_c *simple_spec_init = (simple_spec_init_c *) var1_init_decl->spec_init;

                // ��������
                std::string str_type = simple_spec_init->simple_specification->absyntax_cname();


                for (int k = 0; k < var1_list->n; ++k)
                {
                    std::string str_variable_name = var1_list->get_element(k)->token->value;

                    Variable *variable = 0;

                    if (str_type.compare("int_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_INT);

                        v_internal_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        // ���ó�ʼֵ��Ĭ������Ϊ[0, 0]�� Boolean��Ϊfalse
                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;
                            int initial_value = utils::to_number(str_initial_value);

                            m_assignment[variable] = new Interval(initial_value, initial_value);

                        } else {
                            m_assignment[variable] = new Interval(0, 0);
                        }

                    } else if (str_type.compare("bool_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_BOOL);

                        v_internal_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;

                            if (str_initial_value.compare("TRUE") == 0)
                            {
                                m_assignment[variable] = Extended_boolean::TRUE;
                            } else {
                                m_assignment[variable] = Extended_boolean::FALSE;
                            }
                        } else {
                            m_assignment[variable] = Extended_boolean::FALSE;
                        }

                    } else {
                        Debug_helper::print_debug_info(__FILE__, __LINE__, "Ŀǰ�в�֧�ֵ��������ͣ�");
                        exit(233);
                    }
                }
            }
        } else if (str_cname.compare("temp_var_decls_c") == 0)
        {
            // �ֲ�����
            //
            temp_var_decls_list_c * temp_var_decls_list = (temp_var_decls_list_c *)((temp_var_decls_c *) var_declarations_list->get_element(i))->var_decl_list;

            for (int j = 0; j < temp_var_decls_list->n; ++j)
            {
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)temp_var_decls_list->get_element(j);

                // �������б�
                var1_list_c *var1_list = (var1_list_c *) var1_init_decl->var1_list;


                // ��ʼֵ��������������
                simple_spec_init_c *simple_spec_init = (simple_spec_init_c *) var1_init_decl->spec_init;

                // ��������
                std::string str_type = simple_spec_init->simple_specification->absyntax_cname();


                for (int k = 0; k < var1_list->n; ++k)
                {
                    std::string str_variable_name = var1_list->get_element(k)->token->value;

                    Variable *variable = 0;

                    if (str_type.compare("int_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_INT);

                        v_temp_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        // ���ó�ʼֵ��Ĭ������Ϊ[0, 0]�� Boolean��Ϊfalse
                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;
                            int initial_value = utils::to_number(str_initial_value);

                            m_assignment[variable] = new Interval(initial_value, initial_value);

                        } else {
                            m_assignment[variable] = new Interval(0, 0);
                        }

                    } else if (str_type.compare("bool_type_name_c") == 0)
                    {
                        variable = new Variable(str_variable_name, Variable::VARIABLE_TYPE_BOOL);

                        v_temp_variable_list.push_back(variable);
                        v_variable_list.push_back(variable);

                        if (simple_spec_init->constant != 0)
                        {
                            // ��ʼֵ
                            std::string str_initial_value = simple_spec_init->constant->token->value;

                            if (str_initial_value.compare("TRUE") == 0)
                            {
                                m_assignment[variable] = Extended_boolean::TRUE;
                            } else {
                                m_assignment[variable] = Extended_boolean::FALSE;
                            }
                        } else {
                            m_assignment[variable] = Extended_boolean::FALSE;
                        }

                    } else {
                        Debug_helper::print_debug_info(__FILE__, __LINE__, "Ŀǰ�в�֧�ֵ��������ͣ�");
                        exit(233);
                    }
                }
            }

        } else if (str_cname.compare("global_var_declarations_c") == 0)
        {
            // ȫ�ֱ���
        }
    }

    // �������岿�ֵõ�CFG
    cfg = new CFG(str_pou_name, statement_list);


}

Program::~Program()
{
}
