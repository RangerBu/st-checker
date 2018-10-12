//
// Created by Samson on 2018/5/30.
//

#include <cstring>

#include "utils.h"

std::string& utils::trim(std::string &_str)
{
    if (_str.empty())
    {
        return _str;
    }
    _str.erase(0, _str.find_first_not_of(" "));
    _str.erase(_str.find_last_not_of(" ") + 1);
    return _str;
}

bool utils::is_number(std::string _str)
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

int utils::to_number(std::string _str)
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

char* utils::append(char *_ch1, char *_ch2)
{
    char *ret = (char *)malloc(strlen(_ch1) + strlen(_ch2) + 1);

    for (int i = 0; _ch1[i] != '\0' ; ++i)
    {
        ret[i] = _ch1[i];
    }

    for (int j = 0; _ch2[j] != '\0'; ++j)
    {
        ret[j + strlen(_ch1)] = _ch2[j];
    }

    ret[strlen(_ch1) + strlen(_ch2)] = '\0';

    return ret;
}