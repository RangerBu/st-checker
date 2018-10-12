#include "value_set_transfer.h"

Abstract_value_set_transfer *Abstract_value_set_transfer::get_bot()
{
    if (ELEM_BOT == 0)
    {
        ELEM_BOT = new Abstract_value_set_transfer();
    }
    return ELEM_BOT;
}

Abstract_value_set_transfer *Abstract_value_set_transfer::get_identity()
{
    if (ELEM_IDENTITY == 0)
    {
        ELEM_IDENTITY = new Abstract_value_set_transfer();
    }
    return ELEM_IDENTITY;
}


/**
* public methods
*/
/*
* constructor
*/
Abstract_value_set_transfer::Abstract_value_set_transfer()
{

}

/*
* de-constructor
*/
Abstract_value_set_transfer::~Abstract_value_set_transfer()
{

}


/**
* external visible methods
*/
Value_set *Abstract_value_set_transfer::op_transform(Value_set *_vs0)
{
    if (this->equal(Abstract_value_set_transfer::get_bot()))
    {
        return new Value_set(_vs0);
    }
    else if (this->equal(Abstract_value_set_transfer::get_identity()))
    {
        return _vs0;
    }
    else
    {
        std::cerr << "this instance is an instance of inherited class of Abstract_value_set_transfer in Abstract_value_set_transfer::op_transform()!" << std::endl;
        exit(0);
    }
}


/**
* helpers
*/
bool Abstract_value_set_transfer::equal(Abstract_value_set_transfer *_other)
{
    return this == _other;
}

std::ostream &Abstract_value_set_transfer::print(std::ostream &_out)
{
    if (this->equal(Abstract_value_set_transfer::get_bot()))
    {
        return _out << "bot_transfer";
    }
    else if (this->equal(Abstract_value_set_transfer::get_identity()))
    {
        return _out << "identity_transfer";
    }
    else
    {
        std::cerr << "this instance is an instance of inherited class of Abstract_value_set_transfer in Abstract_value_set_transfer::print()!" << std::endl;
        exit(0);
    }
}


/**
* helpers - debug only
*/
std::string Abstract_value_set_transfer::to_string()
{
    if (this->equal(Abstract_value_set_transfer::get_bot()))
    {
        return "bot_transfer";
    }
    else if (this->equal(Abstract_value_set_transfer::get_identity()))
    {
        return "identity_transfer";
    }
    else
    {
        std::cerr << "this instance is an instance of inherited class of Abstract_value_set_transfer in Abstract_value_set_transfer::to_string()!" << std::endl;
        exit(0);
    }
}


/**
* helpers for inherited classes
*/
bool Abstract_value_set_transfer::is_number(std::string _str)
{
    int len = _str.length();
    for (int i=0; i<len; i++)
    {
        if (i==0 && _str[0] == '-') continue;
        if (!(_str[i] <= '9' && _str[i] >= '0'))
        {
            return false;
        }
    }
    return true;

}

bool Abstract_value_set_transfer::is_bool(std::string _str)
{
    return _str.compare("FALSE") == 0 || _str.compare("TRUE") == 0;
}

bool Abstract_value_set_transfer::is_byte(std::string _str)
{
    int len = _str.length();
    for (int i=0; i<len; i++)
    {
        if (!(_str[i] == '0' || _str[i] == '1' || _str[i] == '_' || _str[i] == '*'))
        {
            return false;
        }
    }
    return true;
}

int Abstract_value_set_transfer::to_number(std::string _str)
{
    int ret = 0;
    int len = _str.length();
    int i = _str[0] == '-' ? 1 : 0;
    for ( ; i<len; i++)
    {
        ret += (_str[i] - '0');
        if (i<len-1)
        {
            ret *= 10;
        }
    }
    if (_str[0] == '-') ret = -ret;

    return ret;
}

bool Abstract_value_set_transfer::to_bool(std::string _str)
{
    if (_str.compare("FLASE") == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


/**
* private static attributes
*/
Abstract_value_set_transfer *Abstract_value_set_transfer::ELEM_BOT = 0;

Abstract_value_set_transfer *Abstract_value_set_transfer::ELEM_IDENTITY = 0;
