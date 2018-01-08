#include "Value_set.h"

Bits_vector_1 *Bits_vector_1::BV1_ELEM_TOP = 0;

Bits_vector_1 *Bits_vector_1::BV1_ELEM_BOT = 0;

Bits_vector_8 *Bits_vector_8::BV8_ELEM_TOP = 0;

Bits_vector_8 *Bits_vector_8::BV8_ELEM_BOT = 0;



/**
* public methods
*/

Value_set::Value_set()
{
}
Value_set::Value_set(std::vector<key> _vars_list)
{
    int len = _vars_list.size();
    for (int i=0; i<len; i++)
    {
        insert_var(_vars_list[i]);
    }
}
Value_set::Value_set(Value_set *_vs0)
{
    std::map<key, bool_value> t_bool_vars = _vs0->get_bool_vars();
    std::map<key, bool_value>::iterator it1 = t_bool_vars.begin();
    for (; it1 != t_bool_vars.end(); ++it1)
    {
        insert_bool_var(it1->first, it1->second);
    }
    std::map<key, byte_value> t_byte_vars = _vs0->get_byte_vars();
    std::map<key, byte_value>::iterator it2 = t_byte_vars.begin();
    for (; it2 != t_byte_vars.end(); ++it2)
    {
        insert_byte_var(it2->first, it2->second);
    }
    std::map<key, int_value> t_int_vars = _vs0->get_int_vars();
    std::map<key, int_value>::iterator it3 = t_int_vars.begin();
    for (; it3 != t_int_vars.end(); ++it3)
    {
        insert_int_var(it3->first, it3->second);
    }

}
Value_set::~Value_set()
{
}

void Value_set::insert_var(key _var)
{
    std::string str_type = _var->get_str_type();

    if (str_type.compare(Var::TYPE_INT) == 0)
    {
        insert_int_var(_var, Strided_interval::get_bot());
    }
    else if (str_type.compare(Var::TYPE_BOOL) == 0)
    {
        insert_bool_var(_var, Bits_vector_1::get_bot());
    }
    else if (str_type.compare(Var::TYPE_BYTE) == 0)
    {
        insert_byte_var(_var, Bits_vector_8::get_bot());
    }
    else
    {
        std::cout << "Passed an wrong type variable in Value_set::insert_var()" << std::endl;
    }
}
void Value_set::insert_bool_var(key _var, bool_value _value)
{
    bool_vars[_var] = _value;

    if (contains_var(_var) == 0)
    {
        vars_list.push_back(_var);
    }
}
void Value_set::insert_byte_var(key _var, byte_value _value)
{
    byte_vars[_var] = _value;
    if (contains_var(_var) == 0)
    {
        vars_list.push_back(_var);
    }
}
void Value_set::insert_int_var(key _var, int_value _value)
{
    int_vars[_var] = _value;
    if (contains_var(_var) == 0)
    {
        vars_list.push_back(_var);
    }
}
void Value_set::update_bool_var(key _var, bool_value _value)
{
    if (bool_vars.find(_var) == bool_vars.end())
    {
        std::cout << "There is no bool variable " << _var->get_str_name() << " in this value-set!" << std::endl;
    }
    else
    {
        bool_vars[_var] = _value;
    }
}
void Value_set::update_byte_var(key _var, byte_value _value)
{
    if (byte_vars.find(_var) == byte_vars.end())
    {
         std::cout << "There is no byte variable " << _var->get_str_name() << " in this value-set!" << std::endl;
         return;
    }
    else
    {
        byte_vars[_var] = _value;
    }
}
void Value_set::update_int_var(key _var, int_value _value)
{
    if (int_vars.find(_var) == int_vars.end())
    {
         std::cout << "There is no int variable " << _var->get_str_name() << " in this value-set!" << std::endl;
         return;
    }
    else
    {
        int_vars[_var] = _value;
    }
}
bool_value Value_set::get_bool_value(key _var)
{
    if (bool_vars.find(_var) == bool_vars.end())
    {
        std::cout << "There is no bool variable " << _var->get_str_name() << " in this value-set!" << std::endl;
        return 0;
    }
    else
    {
        return bool_vars[_var];
    }
}
byte_value Value_set::get_byte_value(key _var)
{
    if (byte_vars.find(_var) == byte_vars.end())
    {
         std::cout << "There is no byte variable " << _var->get_str_name() << " in this value-set!" << std::endl;
         return 0;
    }
    else
    {
        return byte_vars[_var];
    }
}
int_value Value_set::get_int_value(key _var)
{
    if (int_vars.find(_var) == int_vars.end())
    {
        std::cout << "There is no int variable " << _var->get_str_name() << " in this value-set!" << std::endl;
        return 0;
    }
    else
    {
        return int_vars[_var];
    }
}

// maybe it can be implemented as follows
Value_set *Value_set::Union(Value_set *_other)
{
    if (bool_vars.size() != _other->get_bool_vars().size())
    {
        std::cout << "Two mismatched operands!" << std::endl;
        return 0;
    }
    Value_set *ret = new Value_set();
    std::map<key, bool_value>::iterator it1 = bool_vars.begin();
    for (; it1!=bool_vars.end(); ++it1)
    {
        bool_value tmp = _other->get_bool_value(it1->first);
        if (tmp == 0)
        {
            std::cout << "There is no int variable " << it1->first->get_str_name() << " in the second value-set!" << std::endl;
            return 0;
        }
        if (it1->second->equal(tmp))
        {
            ret->insert_bool_var(it1->first, it1->second);
        }
        else
        {
            ret->insert_bool_var(it1->first, (bool_value)it1->second->op_union(tmp));
        }
    }
    std::map<key, byte_value>::iterator it2 = byte_vars.begin();
    for (; it2 != byte_vars.end(); ++it2)
    {
        byte_value tmp = _other->get_byte_value(it2->first);
        if (tmp == 0)
        {
            std::cout << "There is no int variable " << it2->first->get_str_name() << " in the second value-set!" << std::endl;
            return 0;
        }
        if (it2->second->equal(tmp))
        {
            ret->insert_byte_var(it2->first, it2->second);
        }
        else
        {
            ret->insert_byte_var(it2->first, (byte_value)it2->second->op_union(tmp));
        }
    }
    std::map<key, int_value>::iterator it3 = int_vars.begin();
    for (; it3 != int_vars.end(); ++it3)
    {
        int_value tmp = _other->get_int_value(it3->first);
        if (tmp == 0)
        {
            std::cout << "There is no int variable " << it3->first->get_str_name() << " in the second value-set!" << std::endl;
            return 0;
        }
        if (it3->second->equal(tmp))
        {
            ret->insert_int_var(it3->first, tmp);
        }
        else
        {
            ret->insert_int_var(it3->first, it3->second->op_union(tmp));
        }
    }
    return ret;
}
key Value_set::contains_var(key _var)
{
    for (int i=0; i<vars_list.size(); i++)
    {
        if (vars_list[i]->equal(_var))
        {
            return vars_list[i];
        }
    }
    return 0;
}
key Value_set::contains_var(std::string _var_name)
{
    for (int i=0; i<vars_list.size(); i++)
    {
        if (vars_list[i]->get_str_name().compare(_var_name) == 0)
        {
            return vars_list[i];
        }
    }
    return 0;
}


/**
* getters and setters
*/
std::map<key, bool_value> Value_set::get_bool_vars()
{
    return bool_vars;
}
std::map<key, byte_value> Value_set::get_byte_vars()
{
    return byte_vars;
}
std::map<key, int_value> Value_set::get_int_vars()
{
    return int_vars;
}


/**
* helpers
*/
std::string Value_set::format()
{
    std::stringstream ss;
    std::map<key, int_value>::iterator it1 = int_vars.begin();
    for (;it1 != int_vars.end(); ++it1)
    {
        ss << it1->first->get_str_name() << "\t" << it1->second->to_string() << "\n";
    }
    std::map<key, bool_value>::iterator it2 = bool_vars.begin();
    for (;it2 != bool_vars.end(); ++it2)
    {
        ss << it2->first->get_str_name() << "\t" << it2->second->to_string() << "\n";
    }
    std::map<key, byte_value>::iterator it3 = byte_vars.begin();
    for (;it3 != byte_vars.end(); ++it3)
    {
        ss << it3->first->get_str_name() << "\t" << it3->second->to_string() << "\n";
    }
    return ss.str();
}
void Value_set::print(std::ostream &out)
{
    out << format();
}
bool Value_set::equals(Value_set *_other)
{
    if (int_vars.size() != _other->get_int_vars().size())
    {
        return false;
    }
    std::map<key, bool_value>::iterator it1 = bool_vars.begin();
    for (; it1 != bool_vars.end(); ++it1)
    {
        bool_value tmp = _other->get_bool_value(it1->first);
        if (tmp == 0)
        {
            return false;
        }
        if (!it1->second->equal(tmp))
        {
            return false;
        }
    }
    std::map<key, byte_value>::iterator it2 = byte_vars.begin();
    for (; it2 != byte_vars.end(); ++it2)
    {
        byte_value tmp = _other->get_byte_value(it2->first);
        if (tmp == 0)
        {
            return false;
        }
        if (!it2->second->equal(tmp))
        {
            return false;
        }
    }
    std::map<key, int_value>::iterator it3 = int_vars.begin();
    for (; it3 != int_vars.end(); ++it3)
    {
        int_value tmp = _other->get_int_value(it3->first);
        if (tmp == 0)
        {
            return false;
        }
        if (!it3->second->equal(tmp))
        {
            return false;
        }
    }
    return true;
}



/**
* private methods
*/
bool Value_set::is_top()
{
    std::map<key, bool_value>::iterator it1 = bool_vars.begin();
    for (; it1 != bool_vars.end(); ++it1)
    {
        if (!it1->second->equal(Bits_vector_1::get_top()))
        {
            return false;
        }
    }
    std::map<key, byte_value>::iterator it2 = byte_vars.begin();
    for (; it2 != byte_vars.end(); ++it2)
    {
        if (!it2->second->equal(Bits_vector_8::get_top()))
        {
            return false;
        }
    }
    std::map<key, int_value>::iterator it3 = int_vars.begin();
    for (; it3 != int_vars.end(); ++it3)
    {
        if (!it3->second->equal(Strided_interval::get_top()))
        {
            return false;
        }
    }
    return true;
}
bool Value_set::is_bot()
{
    std::map<key, bool_value>::iterator it1 = bool_vars.begin();
    for (; it1 != bool_vars.end(); ++it1)
    {
        if (!it1->second->equal(Bits_vector_1::get_bot()))
        {
            return false;
        }
    }
    std::map<key, byte_value>::iterator it2 = byte_vars.begin();
    for (; it2 != byte_vars.end(); ++it2)
    {
        if (!it2->second->equal(Bits_vector_8::get_bot()))
        {
            return false;
        }
    }
    std::map<key, int_value>::iterator it3 = int_vars.begin();
    for (; it3 != int_vars.end(); ++it3)
    {
        if (!it3->second->equal(Strided_interval::get_bot()))
        {
            return false;
        }
    }
    return true;
}
