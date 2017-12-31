#include "utils.h"

utils::utils()
{
    //ctor
}

utils::~utils()
{
    //dtor
}

std::string &utils::trim(std::string &_str)
{
    if (_str.empty())
    {
        return _str;
    }
    _str.erase(0, _str.find_first_not_of(" "));
    _str.erase(_str.find_last_not_of(" ") + 1);
    return _str;
}
int utils::gcd(int a, int b)
{
    if (a == 0 && b == 0)
    {
        return 0;
    }
    else if (a == 0)
    {
        return b;
    }
    else if (b == 0)
    {
        return a;
    }
    int r = a % b;
    while (r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
int utils::extend_euclidean(int a, int b, int &x, int &y)
{
    int old_x, old_y, r, old_r, q, tmp;
    x = 0; y = 1; r = b;
    old_x = 1; old_y = 0; old_r = a;

    while(r!=0)
    {
         q = old_r / r;

        tmp = old_r;
        old_r = r;
        r = tmp - q * r;

        tmp = old_x;
        old_x = x;
        x = tmp - q * x;

        tmp = old_y;
        old_y = y;
        y = tmp - q * y;
    }
    x = old_x;
    y = old_y;
    return old_r;
}
