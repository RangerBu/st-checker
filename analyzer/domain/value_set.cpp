#include "value_set.h"

/**
 * methods used only in this file
 */
bool str_to_bool(std::string _constant)
{
    if (_constant.compare("TRUE") == 0)
    {
        return true;
    }
    else if (_constant.compare("FALSE") == 0)
    {
        return false;
    }
}

int str_to_int(std::string _constant)
{
    int ret = 0;
    int len = _constant.length();
    int i = _constant[0] == '-' ? 1 : 0;
    for ( ; i<len; i++)
    {
        ret += (_constant[i] - '0');
        if (i<len-1)
        {
            ret *= 10;
        }
    }
    if (_constant[0] == '-') ret = -ret;
    return ret;
}


Bits_vector_1 *Bits_vector_1::BV1_ELEM_TOP = 0;

Bits_vector_1 *Bits_vector_1::BV1_ELEM_BOT = 0;

Bits_vector_8 *Bits_vector_8::BV8_ELEM_TOP = 0;

Bits_vector_8 *Bits_vector_8::BV8_ELEM_BOT = 0;

/**
* public methods
*/
/*
* create an instance with variable list _vars_list, the initial value of each variable is \bot
*/
Value_set::Value_set(std::vector<key> _vars_list)
{
    for (int i=0; i<_vars_list.size(); i++)
    {
        insert_var(_vars_list[i]);
    }
}

/*
* create an instance with variable list _vars_list and its length _length, the initial value of each variable is \bot
*/
Value_set::Value_set(int _length, key *_vars_list)
{
    for (int i=0; i<_length; i++)
    {
        insert_var(_vars_list[i]);
    }
}

/*
* create an instance using other value-set instance
*/
Value_set::Value_set(Value_set *_other)
{
    std::map<key, value> _vars_map = _other->get_vars_map();

    for (std::map<key, value>::iterator it = _vars_map.begin(); it != _vars_map.end(); ++it)
    {
        if (it->first->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            set_var_value(it->first, Strided_interval::get_strided_interval((int_value) it->second));
        }
        else if (it->first->get_str_type().compare(Var::TYPE_BOOL) == 0)
        {
            set_var_value(it->first, Bits_vector_1::get_instance((bool_value) it->second));
        }
        else if (it->first->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {
            set_var_value(it->first, Bits_vector_8::get_instance((byte_value) it->second));
        }
        else
        {
            std::cerr << "Used an unsupported variable in Value_set::Value_set(Value_set *)!" << std::endl;
            exit(0);
        }
    }
}

/*
* de-constructor
*/
Value_set::~Value_set()
{

}


/**
* external visible methods
*/
void Value_set::set_var_value(key _var, value _value)
{
    if (_var->get_str_type().compare(Var::TYPE_INT) == 0)
    {
        int_vars_map[_var] = (int_value)_value;
    }
    else if (_var->get_str_type().compare(Var::TYPE_BOOL) == 0)
    {
        bool_vars_map[_var] = (bool_value)_value;
    }
    else if (_var->get_str_type().compare(Var::TYPE_BYTE) == 0)
    {
        byte_vars_map[_var] = (byte_value)_value;
    }
    else
    {
        std::cerr << "Passed a wrong type variable in Value_set::set_var_value()!" << std::endl;
        exit(0);
    }

    vars_map[_var] = _value;

    if (contains_var(_var) == 0)
    {
        vars_list.push_back(_var);
    }
}

/*
* get the int_value of key _var, if no such variable in this value-set then exit
*/
int_value Value_set::get_int_value_by(key _var)
{
    std::map<key, int_value>::iterator it = int_vars_map.find(_var);

    if (it != int_vars_map.end())
    {
        return int_vars_map[_var];
    }
    else
    {
        std::cerr << "No such variable in int_vars_map in Value_set::get_int_value!" << std::endl;
        exit(0);
    }
}

/*
* get the bool_value of key _var, if no such variable in this value-set then exit
*/
bool_value Value_set::get_bool_value_by(key _var)
{
    std::map<key, bool_value>::iterator it = bool_vars_map.find(_var);

    if (it != bool_vars_map.end())
    {
        return bool_vars_map[_var];
    }
    else
    {
        std::cerr << "No such variable in bool_vars_map in Value_set::get_bool_value!" << std::endl;
        exit(0);
    }
}

/*
* get the byte_value of key _var, if no such variable in this value-set then exit
*/
byte_value Value_set::get_byte_value_by(key _var)
{
    std::map<key, byte_value>::iterator it = byte_vars_map.find(_var);

    if (it != byte_vars_map.end())
    {
        return byte_vars_map[_var];
    }
    else
    {
        std::cerr << "No such variable in byte_vars_map in Value_set::get_byte_value!" << std::endl;
        exit(0);
    }
}

/*
* whether a key with str_name _str_name contained in vars_list, return the pointer of this var or 0
*/
key Value_set::contains_var(std::string _str_name)
{
    for (int i=0; i<vars_list.size(); i++)
    {
        if (vars_list[i]->get_str_name().compare(_str_name) == 0)
        {
            return vars_list[i];
        }
    }
    return 0;
}

/*
* whether a key contained in vars_list, return 0 if not contained in vars_list
*/
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

void Value_set::insert_var(key _var)
{
    if (contains_var(_var) == 0)
    {
        if (_var->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            if (_var->get_str_constant().length() == 0)
            {
                if (_var->get_str_semantics().compare(Var::SEMANTICS_INPUT) == 0)
                {
                    /*
                     * initialize input variable
                     */
                    int_vars_map[_var] = Strided_interval::get_top();
                }
                else
                {
                    /*
                     * initialize output variable and internal varaible
                     */
                    int_vars_map[_var] = Strided_interval::get_bot();
                }

            }
            else
            {
                int_vars_map[_var] = Strided_interval::get_singleton_set(str_to_int(_var->get_str_constant()));
            }
            vars_map[_var] = int_vars_map[_var];
        }
        else if (_var->get_str_type().compare(Var::TYPE_BOOL) == 0)
        {
            if (_var->get_str_constant().length() == 0)
            {
                if (_var->get_str_semantics().compare(Var::SEMANTICS_INPUT) == 0)
                {
                    /*
                     * initialize input variable
                     */
                    bool_vars_map[_var] = Bits_vector_1::get_top();
                }
                else
                {
                    /*
                     * initialize output variable and internal varaible
                     */
                    bool_vars_map[_var] = Bits_vector_1::get_bot();
                }
            }
            else
            {
                bool_vars_map[_var] = Bits_vector_1::get_instance(str_to_bool(_var->get_str_constant()));
            }
            vars_map[_var] = bool_vars_map[_var];
        }
        else if (_var->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {
            /*
             * add the support for byte variable
             */
            if (_var->get_str_semantics().compare(Var::SEMANTICS_INPUT) == 0)
            {
                /*
                * initialize input byte variable to \top
                */
                byte_vars_map[_var] = Bits_vector_8::get_top();
                vars_map[_var] = byte_vars_map[_var];
            }
            else
            {
                byte_vars_map[_var] = Bits_vector_8::get_bot();
                vars_map[_var] = byte_vars_map[_var];
            }
        }
        else
        {
            std::cerr << "Passed a wrong type variable in Value_set::set_var_value()!" << std::endl;
            exit(0);
        }
        vars_list.push_back(_var);
    }
}


/**
* operations
*/
Value_set *Value_set::op_union(Value_set *_other)
{
    Value_set *ret = new Value_set(vars_list);

    std::map<key, value>::iterator it = vars_map.begin();
    for (; it!=vars_map.end(); ++it)
    {
        if (it->first->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            if (_other->contains_var(it->first))
            {
                ret->set_var_value(it->first, ((int_value)it->second)->op_union(_other->get_int_value_by(it->first)));
            }
            else
            {
                ret->set_var_value(it->first, it->second);
            }
        }
        else if (it->first->get_str_type().compare(Var::TYPE_BOOL) == 0)
        {
            if (_other->contains_var(it->first))
            {
                ret->set_var_value(it->first, ((bool_value)it->second)->op_union(_other->get_bool_value_by(it->first)));
            }
            else
            {
                ret->set_var_value(it->first, it->second);
            }
        }
        else if (it->first->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {
            if (_other->contains_var(it->first))
            {
                ret->set_var_value(it->first, ((byte_value)it->second)->op_union(_other->get_byte_value_by(it->first)));
            }
            else
            {
                ret->set_var_value(it->first, it->second);
            }
        }
        else
        {
            std::cerr << "An unsupported variable in Value_set::op_union!1" << std::endl;
            exit(0);
        }
    }

    std::map<key, value> other_vars_map = _other->get_vars_map();
    for (it=other_vars_map.begin(); it!=other_vars_map.end(); ++it)
    {
        if (!contains_var(it->first))
        {
            ret->set_var_value(it->first, it->second);
        }
    }
    return ret;
}


/**
* getters and setters
*/
std::map<key, value> Value_set::get_vars_map()
{
    return vars_map;
}

std::vector<key> Value_set::get_vars_list()
{
    return vars_list;
}


/**
* helpers
*/
bool Value_set::equal(Value_set *_other)
{
    std::vector<key> other_vars_list = _other->get_vars_list();

    if (vars_list.size() != other_vars_list.size())
    {
        return false;
    }

    for (int i=0; i<vars_list.size(); i++)
    {
        if (vars_list[i]->get_str_type().compare(Var::TYPE_INT) == 0)
        {
            if (_other->get_int_value_by(vars_list[i]) == 0 || !get_int_value_by(vars_list[i])->equal(_other->get_int_value_by(vars_list[i])))
            {
                return false;
            }
        }
        else if (vars_list[i]->get_str_type().compare(Var::TYPE_BOOL) == 0)
        {
            if (_other->get_bool_value_by(vars_list[i]) == 0 || !get_bool_value_by(vars_list[i])->equal(_other->get_bool_value_by(vars_list[i])))
            {
                return false;
            }
        }
        else if (vars_list[i]->get_str_type().compare(Var::TYPE_BYTE) == 0)
        {
            if (_other->get_byte_value_by(vars_list[i]) == 0 || !get_byte_value_by(vars_list[i])->equal(_other->get_byte_value_by(vars_list[i])))
            {
                return false;
            }
        }
        else
        {
            std::cerr << "A wrong variable type in Value_set::equal!" << std::endl;
            exit(0);
        }
    }
    return true;
}

std::ostream &Value_set::print(std::ostream &_out)
{
    std::map<key, value>::iterator it = vars_map.begin();
    for (; it != vars_map.end(); ++it)
    {
        it->second->print(it->first->print(_out)) << "\n";
    }
    return _out;
}


/**
* helpers - debug only
*/
std::string Value_set::to_string()
{
    std::stringstream ss;
    ss.flags(std::ios::left);

    std::map<key, value>::iterator it = vars_map.begin();
    for (; it != vars_map.end(); ++it)
    {
        ss << std::setw(25) << it->first->to_string() << it->second->to_string() << "\n";
    }
    return ss.str();
}
