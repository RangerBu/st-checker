//
// Created by Samson on 2018/6/1.
//

#include "value_assignment.h"

Value_assignment::Value_assignment(POU *_pou)
{
    v_variable_list = _pou->get_variable_list();

    m_variable_to_value = _pou->get_m_assignment();

    // �������
    v_input_variable_list = _pou->get_v_input_variable_list();

    // �������
    v_output_variable_list = _pou->get_v_output_variable_list();

    // �ڲ�����
    v_internal_variable_list = _pou->get_v_internal_variable_list();

    // �ֲ�����
    v_temp_variable_list = _pou->get_v_temp_variable_list();

    // ȫ�ֱ���
    v_global_variable_list = _pou->get_v_global_variable_list();
}

Value_assignment::~Value_assignment()
{

}

bool Value_assignment::equal(Value_assignment *_other)
{
    for (int i = 0; i < v_variable_list.size(); ++i)
    {
        if (!v_variable_list[i]->equal(_other->get_v_variable_list()[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < v_variable_list.size(); ++i)
    {
        if (!m_variable_to_value[v_variable_list[i]]->equal(_other->get_m_variable_to_value()[v_variable_list[i]]))
        {
            return false;
        }
    }

    /**
     * û�п������롢������ڲ����ֲ���ȫ�ֱ������ϲ�ͬ�����
     * ����Ĭ�ϱ����б�һ���������ǵĵ�ǰ��ȡֵһ����������Value_assignemnt�������
     */

    return true;
}

std::ostream &operator<<(std::ostream &_out, Value_assignment &_value_assignment)
{
    /**
     * �����ʽ��
     * ���� ��ֵ
     * ���� ��ֵ
     */
    for (int i = 0; i < _value_assignment.v_variable_list.size(); ++i)
    {
        _out << *_value_assignment.v_variable_list[i] << " : " << _value_assignment.m_variable_to_value[_value_assignment.v_variable_list[i]]->get_str_value() << std::endl;
    }
    return _out;
}

/**
 * getters and setters
 */
std::vector<Variable *> Value_assignment::get_v_variable_list()
{
    return v_variable_list;
}

std::map<Variable *, Abstract_value *> Value_assignment::get_m_variable_to_value()
{
    return m_variable_to_value;
}

std::vector<Variable *> Value_assignment::get_v_input_variable_list()
{
    return v_input_variable_list;
}

std::vector<Variable *> Value_assignment::get_v_output_variable_list()
{
    return v_output_variable_list;
}

std::vector<Variable *> Value_assignment::get_v_internal_variable_list()
{
    return v_internal_variable_list;
}

std::vector<Variable *> Value_assignment::get_v_temp_variable_list()
{
    return v_temp_variable_list;
}

std::vector<Variable *> Value_assignment::get_v_global_variable_list()
{
    return v_global_variable_list;
}