//
// Created by Samson on 2018/6/1.
//

#include "configuration.h"

Configuration::Configuration()
{

}

Configuration::~Configuration()
{

}

bool Configuration::equal(Configuration *_other)
{
    /**
     * 补充：
     * 1. value_assignment的定义，及equal方法
     * 2. stack_symbol的定义，及equal方法
     */
    bool flag = true;

    for (int i = 0; i < gamma.size(); ++i)
    {

    }

    return pc->equal(_other->get_pc()) && sigma->equal(_other->get_sigma());
}

/**
* getters and setters
*/
Vertex* Configuration::get_pc()
{
    return pc;
}

Value_assignment* Configuration::get_sigma()
{
    return sigma;
}

std::stack<Stack_symbol *> Configuration::get_gamma()
{
    return gamma;
}