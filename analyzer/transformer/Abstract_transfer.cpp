#include "Abstract_transfer.h"

Abstract_transfer::Abstract_transfer()
{
}
Abstract_transfer::~Abstract_transfer()
{
}


/**
* helpers for inherited classes
*/
bool Abstract_transfer::is_number(std::string _str)
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
bool Abstract_transfer::is_bool(std::string _str)
{
    return _str.compare("FALSE") == 0 || _str.compare("TRUE") == 0;
}
bool Abstract_transfer::is_byte(std::string _str)
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

int Abstract_transfer::to_number(std::string _str)
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
bool Abstract_transfer::to_bool(std::string _str)
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
