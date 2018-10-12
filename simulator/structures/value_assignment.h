//
// Created by Samson on 2018/6/1.
//

#ifndef VERIFY_ST_PROGRAMS_VALUE_ASSIGNMENT_H
#define VERIFY_ST_PROGRAMS_VALUE_ASSIGNMENT_H

#include <vector>
#include <map>

#include "../../parser/structures/variable.h"
#include "../../parser/structures/abstract_value.h"
#include "../../parser/structures/pou.h"

class Value_assignment
{
public:
    Value_assignment(POU *_pou);

    virtual ~Value_assignment();

    bool equal(Value_assignment *_other);

    friend std::ostream &operator<<(std::ostream &_out, Value_assignment &_value_assignment);

    /**
     * getters and setters
     */
    std::vector<Variable *> get_v_variable_list();

    std::map<Variable *, Abstract_value *> get_m_variable_to_value();

    std::vector<Variable *> get_v_input_variable_list();

    std::vector<Variable *> get_v_output_variable_list();

    std::vector<Variable *> get_v_internal_variable_list();

    std::vector<Variable *> get_v_temp_variable_list();

    std::vector<Variable *> get_v_global_variable_list();


private:
    // ���б������б�
    std::vector<Variable *> v_variable_list;

    // ���б�����ǰ�ĸ�ֵ
    std::map<Variable *, Abstract_value *> m_variable_to_value;

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
};


#endif //VERIFY_ST_PROGRAMS_VALUE_ASSIGNMENT_H
