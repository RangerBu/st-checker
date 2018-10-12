//
// Created by Samson on 2018/6/1.
//

#ifndef VERIFY_ST_PROGRAMS_STACK_SYMBOL_H
#define VERIFY_ST_PROGRAMS_STACK_SYMBOL_H

#include <string>
#include <map>
#include <iostream>

#include "../../parser/structures/vertex.h"
#include "../../parser/structures/variable.h"
#include "value_assignment.h"


class Stack_symbol
{
public:
    Stack_symbol(std::string _str_pou_name, Vertex *_return_site, std::map<Variable *, Variable *> _m_eta, Value_assignment *_sigma);

    virtual ~Stack_symbol();

    bool equal(Stack_symbol *_other);

    friend std::ostream &operator<<(std::ostream &_out, Stack_symbol &_stack_symbol);

    /**
     * getters and setters
     */
    std::string get_str_pou_name();

    Vertex *get_return_site();

    std::map<Variable *, Variable *> get_m_eta();

    Value_assignment *get_sigma();

private:
    // ��ǰ����ִ�е�POU������
    std::string str_pou_name;

    // ���÷���ʱ�Ľڵ�
    Vertex *return_site;

    // ���÷���ʱ����Ҫ���ĵı�������������
    std::map<Variable *, Variable *> m_eta;

    // ���÷���ʱ����Ҫ�ָ���������
    Value_assignment *sigma;
};


#endif //VERIFY_ST_PROGRAMS_STACK_SYMBOL_H
