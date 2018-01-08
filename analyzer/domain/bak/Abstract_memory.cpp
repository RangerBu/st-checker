#include "Abstract_memory.h"

/**
* public methods
*/

Abstract_memory::Abstract_memory()
{
}
Abstract_memory::Abstract_memory(std::vector<Var *> _vars)
{
    int len = _vars.size();
    for (int i=0; i<len; i++)
    {
        vars.push_back(_vars[i]);
    }
    init_memory();
}
Abstract_memory::~Abstract_memory()
{
}
void Abstract_memory::set_value(Var *_v, Value_set *_vs)
{
    std::string key = _v->format();
    values[key] = _vs;
}
Value_set *Abstract_memory::get_value(Var *_v)
{
    std::string key = _v->format();
    std::map<std::string, Value_set *>::iterator it;

    it = values.find(key);
    if (it != values.end())
    {
        return values[key];
    }
    return 0;
}

/**
* helpers
*/
std::string Abstract_memory::format()
{
    std::stringstream o;
    o << "(";
    int len = vars.size();
    for (int i = 0; i<len; i++)
    {
        o << vars[i]->get_str_name() << ":" << values[vars[i]->format()]->format();
        if (i < len-1)
        {
            o << ", ";
        }
        else
        {
            o << ")";
        }
    }
    return o.str();
}
void Abstract_memory::print(std::ostream &out)
{
    out << this->format();
}

/**
* private attributes and methods
*/
void Abstract_memory::init_memory()
{
    int len = vars.size();

    for (int i=0; i<len; i++)
    {
        std::string key = vars[i]->format();
        Value_set *value = 0;

        switch(vars[i]->get_type())
        {
        case (Var::INT_T):
            {
                value = Strided_interval::get_bot();

                break;
            }
        case (Var::BOOL_T):
            {
                value = Bits_vector_1::get_bot();
                break;
            }
        case (Var::BYTE_T):
            {
                value = Bits_vector_8::get_bot();
                break;
            }
        }
        values[key] = value;
    }
}
