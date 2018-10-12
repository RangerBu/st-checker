//
// Created by Samson on 2018/6/1.
//

#ifndef VERIFY_ST_PROGRAMS_ASSIGNMENT_H
#define VERIFY_ST_PROGRAMS_ASSIGNMENT_H

#include <stack>
#include <map>

#include "../../parser/structures/vertex.h"
#include "stack_symbol.h"
#include "value_assignment.h"

class Configuration
{
public:
    Configuration();

    virtual ~Configuration();

    bool equal(Configuration *_other);

    /**
     * getters and setters
     */
    Vertex *get_pc();

    Value_assignment *get_sigma();

    std::stack<Stack_symbol *> get_gamma();

private:
    // 当前节点
    Vertex *pc;

    // 当前变量的赋值
    Value_assignment *sigma;

    // 运行时栈
    std::stack<Stack_symbol *> gamma;

};


#endif //VERIFY_ST_PROGRAMS_ASSIGNMENT_H
