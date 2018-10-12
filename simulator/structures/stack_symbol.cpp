//
// Created by Samson on 2018/6/1.
//

#include "stack_symbol.h"

Stack_symbol::Stack_symbol(std::string _str_pou_name, Vertex *_return_site, std::map<Variable *, Variable *> _m_eta,
                           Value_assignment *_sigma) :
        str_pou_name(_str_pou_name), return_site(_return_site), m_eta(_m_eta), sigma(_sigma)
{
}

Stack_symbol::~Stack_symbol()
{
}

bool Stack_symbol::equal(Stack_symbol *_other)
{
    bool flag = true;

    if (m_eta.size() != _other->get_m_eta().size())
    {
        flag = false;
    } else {
        std::map<Variable *, Variable *> other_m_eta = _other->get_m_eta();
        for (std::map<Variable *, Variable *>::iterator it = m_eta.begin(); it != m_eta.end() ; ++it)
        {
            if (!(m_eta[it->first]->equal(other_m_eta[it->first])))
            {
                flag = false;
                break;
            }
        }
    }

    return str_pou_name.compare(_other->get_str_pou_name()) == 0 && return_site->equal(_other->get_return_site())
            && flag && sigma->equal(_other->get_sigma());
}
std::ostream &operator<<(std::ostream &_out, Stack_symbol &_stack_symbol)
{
    _out << "(" << _stack_symbol.str_pou_name << ", " << *_stack_symbol.return_site << ", \n";
    _out << "{ ";
    for (std::map<Variable *, Variable *>::iterator it = _stack_symbol.m_eta.begin(); it != _stack_symbol.m_eta.end() ; ++it)
    {
        _out << *(it->first) << " : " << *(_stack_symbol.m_eta[it->second]) << "; ";
    }
    _out << "}\n";
}

std::string Stack_symbol::get_str_pou_name()
{
    return str_pou_name;
}

Vertex* Stack_symbol::get_return_site()
{
    return return_site;
}

std::map<Variable *, Variable *> Stack_symbol::get_m_eta()
{
    return m_eta;
}

Value_assignment* Stack_symbol::get_sigma()
{
    return sigma;
}