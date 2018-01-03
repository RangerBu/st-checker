#include "value_set_transfer.h"

/**
* public static attributes
*/

Value_set_transfer *Value_set_transfer::get_bot()
{
    if (ELEM_BOT == 0)
    {
        ELEM_BOT = new Value_set_transfer();
    }
    return ELEM_BOT;
}
Value_set_transfer *Value_set_transfer::get_identity()
{
    if (ELEM_IDENTITY == 0)
    {
        ELEM_IDENTITY = new Value_set_transfer();
    }
    return ELEM_IDENTITY;
}

/**
* public methods
*/
Value_set_transfer::Value_set_transfer()
{
}
Value_set_transfer::~Value_set_transfer()
{
}

Value_set *Value_set_transfer::Transform(Value_set *_vs0)
{
    return 0;
}
std::string Value_set_transfer::format()
{
    if (this == ELEM_BOT)
    {
        return "elem_bot";
    }
    else if (this == ELEM_IDENTITY)
    {
        return "elem_identity";
    }
    return "Value_set_transfer";
}

/**
* helper methods
*/
bool Value_set_transfer::equals(Value_set_transfer *_other)
{
    return format().compare(_other->format()) == 0;
}


/**
* helpers for inherited classes
*/
bool Value_set_transfer::is_number(std::string _str)
{
    int len = _str.length();
    for (int i=0; i<len; i++)
    {
        if (!(_str[i] <= '9' && _str[i] >= '0'))
        {
            return false;
        }
    }
    return true;

}
bool Value_set_transfer::is_bool(std::string _str)
{
    return _str.compare("FALSE") == 0 || _str.compare("TRUE") == 0;
}
bool Value_set_transfer::is_byte(std::string _str)
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

int Value_set_transfer::to_number(std::string _str)
{
    int ret = 0;
    int len = _str.length();
    for (int i=0; i<len; i++)
    {
        ret += (_str[i] - '0');
        if (i<len-1)
        {
            ret *= 10;
        }
    }

    return ret;
}
bool Value_set_transfer::to_bool(std::string _str)
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
Value_set_transfer* Value_set_transfer::ELEM_BOT = 0;
Value_set_transfer* Value_set_transfer::ELEM_IDENTITY = 0;
