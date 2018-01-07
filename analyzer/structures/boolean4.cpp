#include "boolean4.h"

#include <sstream>

/**
* static methods
*/

Boolean4 *Boolean4::get_instance(int _value)
{
    if (_value > 0)
    {
        return ELEM_TRUE;
    }
    else
    {
        return ELEM_FALSE;
    }
}

Boolean4 *Boolean4::get_instance(bool _value)
{
    if (_value)
    {
        return ELEM_TRUE;
    }
    else
    {
        return ELEM_FALSE;
    }
}

Boolean4 *Boolean4::get_top()
{
    return ELEM_TOP;
}

Boolean4 *Boolean4::get_bot()
{
    return ELEM_BOT;
}

Boolean4 *Boolean4::get_false()
{
    return ELEM_FALSE;
}

Boolean4 *Boolean4::get_true()
{
    return ELEM_TRUE;
}

/**
* pubic methods
*/
/*
* de-constructor
*/
Boolean4::~Boolean4()
{

}


/**
* operations
*/
Boolean4 *Boolean4::op_and(Boolean4 *_other)
{
    if (this == ELEM_FALSE)
    {
        return ELEM_FALSE;
    }
    else if (this == ELEM_TOP)
    {
        if (_other == ELEM_FALSE)
        {
            return ELEM_FALSE;
        }
        else
        {
            return ELEM_TOP;
        }
    }
    else if (this == ELEM_BOT)
    {
        if (_other == ELEM_FALSE)
        {
            return ELEM_FALSE;
        }
        else if (_other == ELEM_TOP)
        {
            return ELEM_TOP;
        }
        else
        {
            return ELEM_BOT;
        }
    }
    else
    {
        return _other;
    }
}
Boolean4 *Boolean4::op_or(Boolean4 *_other)
{
    if (this == ELEM_TRUE)
    {
        return ELEM_TRUE;
    }
    else if (this == ELEM_TOP)
    {
        if (_other == ELEM_TRUE)
        {
            return ELEM_TRUE;
        }
        else
        {
            return ELEM_TOP;
        }
    }
    else if (this == ELEM_BOT)
    {
        if (_other == ELEM_TRUE)
        {
            return ELEM_TRUE;
        }
        else if (_other == ELEM_TOP)
        {
            return ELEM_TOP;
        }
        else
        {
            return ELEM_BOT;
        }
    }
    else
    {
        return _other;
    }
}
Boolean4 *Boolean4::op_not()
{
    if (this == ELEM_TRUE)
    {
        return ELEM_FALSE;
    }
    else if (this == ELEM_TOP)
    {
        return ELEM_TOP;
    }
    else if (this == ELEM_BOT)
    {
        return ELEM_BOT;
    }
    else
    {
        return ELEM_TRUE;
    }
}
Boolean4 *Boolean4::op_xor(Boolean4 *_other)
{
    if (this == ELEM_BOT)
    {
        return ELEM_BOT;
    }
    else if (this == ELEM_TRUE)
    {
        return _other->op_not();
    }
    else if (this == ELEM_FALSE)
    {
        return _other;
    }
    else
    {
        if (_other == ELEM_BOT)
        {
            return ELEM_BOT;
        }
        else
        {
            return ELEM_TOP;
        }
    }
}
Boolean4 *Boolean4::op_union(Boolean4 *_other)
{
    if (this == ELEM_BOT)
    {
        return _other;
    }
    if (_other == ELEM_BOT)
    {
        return this;
    }

    if (this == ELEM_FALSE)
    {
        return _other->op_and(ELEM_TOP);
    }
    else if (this == ELEM_TOP)
    {
        return ELEM_TOP;
    }
    else
    {
        return _other->op_or(ELEM_TOP);
    }
}


/**
* inherited methods
*/
bool Boolean4::equal(Abstract_data *_other)
{
    return this == (Boolean4 *)_other;
}

std::ostream &Boolean4::print(std::ostream &_out)
{
    if (this == ELEM_TRUE)
    {
        _out << "1";
    }
    else if (this == ELEM_FALSE)
    {
        _out << "0";
    }
    else if (this == ELEM_TOP)
    {
        _out << "*";
    }
    else if (this == ELEM_BOT)
    {
        _out << "_";
    }
    return _out;
}


/**
* helpers - debug only
*/
std::string Boolean4::to_string()
{
    std::stringstream _out;
    if (this == ELEM_TRUE)
    {
        _out << "1";
    }
    else if (this == ELEM_FALSE)
    {
        _out << "0";
    }
    else if (this == ELEM_TOP)
    {
        _out << "*";
    }
    else if (this == ELEM_BOT)
    {
        _out << "_";
    }
    return _out.str();
}


/**
* private attributes and methods
*/
/*
* initiate top, bot, false and true element
*/
Boolean4 *Boolean4::ELEM_TOP = new Boolean4();

Boolean4 *Boolean4::ELEM_BOT = new Boolean4();

Boolean4 *Boolean4::ELEM_FALSE = new Boolean4();

Boolean4 *Boolean4::ELEM_TRUE = new Boolean4();

Boolean4::Boolean4()
{

}
