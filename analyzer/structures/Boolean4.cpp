#include "Boolean4.h"

/**
* pre-declarations
*/
int _and(int a, int b);
int _or(int a, int b);
int _not(int a);
int _xor(int a, int b);
int _join(int a, int b);

/**
* static attributes and methods
*/
Boolean4 *Boolean4::TRUE = new Boolean4(1);
Boolean4 *Boolean4::FALSE = new Boolean4(0);
Boolean4 *Boolean4::MAYBE = new Boolean4(2);
Boolean4 *Boolean4::BOT = new Boolean4(-1);


/**
* public methods
*/
Boolean4::Boolean4(int _value)
{
    value = _value;
}
Boolean4::~Boolean4()
{
}

Boolean4 *Boolean4::And(Boolean4 *_other)
{
    if (equals(Boolean4::FALSE))
    {
        return Boolean4::FALSE;
    }
    else if (equals(Boolean4::MAYBE))
    {
        if (_other->equals(Boolean4::FALSE))
        {
            return Boolean4::FALSE;
        }
        else
        {
            return Boolean4::MAYBE;
        }
    }
    else if (equals(Boolean4::BOT))
    {
        if (_other->equals(Boolean4::FALSE))
        {
            return Boolean4::FALSE;
        }
        else if (_other->equals(Boolean4::MAYBE))
        {
            return Boolean4::MAYBE;
        }
        else
        {
            return Boolean4::BOT;
        }
    }
    else
    {
        return _other;
    }
}
Boolean4 *Boolean4::Or(Boolean4 *_other)
{
    if (equals(Boolean4::TRUE))
    {
        return Boolean4::TRUE;
    }
    else if (equals(Boolean4::MAYBE))
    {
        if (_other->equals(Boolean4::TRUE))
        {
            return Boolean4::TRUE;
        }
        else
        {
            return Boolean4::MAYBE;
        }
    }
    else if (equals(Boolean4::BOT))
    {
        if (_other->equals(Boolean4::TRUE))
        {
            return Boolean4::TRUE;
        }
        else if (_other->equals(Boolean4::MAYBE))
        {
            return Boolean4::MAYBE;
        }
        else
        {
            return Boolean4::BOT;
        }
    }
    else
    {
        return _other;
    }
}
Boolean4 *Boolean4::Not()
{
    if (equals(Boolean4::TRUE))
    {
        return Boolean4::FALSE;
    }
    else if (equals(Boolean4::MAYBE))
    {
        return Boolean4::MAYBE;
    }
    else if (equals(Boolean4::BOT))
    {
        return Boolean4::BOT;
    }
    else
    {
        return Boolean4::TRUE;
    }
}
Boolean4 *Boolean4::Xor(Boolean4 *_other)
{
    if (equals(Boolean4::BOT))
    {
        return Boolean4::BOT;
    }
    else if (equals(Boolean4::TRUE))
    {
        return _other->Not();
    }
    else if (equals(Boolean4::FALSE))
    {
        return _other;
    }
    else
    {
        if (_other->equals(Boolean4::BOT))
        {
            return Boolean4::BOT;
        }
        else
        {
            return Boolean4::MAYBE;
        }
    }
}
Boolean4 *Boolean4::Join(Boolean4 *_other)
{
    if (equals(Boolean4::BOT))
    {
        return _other;
    }
    if (_other->equals(Boolean4::BOT))
    {
        return this;
    }

    if (equals(Boolean4::FALSE))
    {
        return _other->And(Boolean4::MAYBE);
    }
    else if (equals(Boolean4::MAYBE))
    {
        return Boolean4::MAYBE;
    }
    else
    {
        return _other->Or(Boolean4::MAYBE);
    }
}


/**
* getters and setters
*/
int Boolean4::get_value()
{
    return value;
}
void Boolean4::set_value(int _value)
{
    value = _value;
}

/**
* helpers
*/
std::string Boolean4::format()
{
    std::stringstream ss;
    if (equals(Boolean4::FALSE))
    {
        ss << "FALSE";
    }
    else if (equals(Boolean4::TRUE))
    {
        ss << "TRUE";
    }
    else if (equals(Boolean4::MAYBE))
    {
        ss << "MAYBE";
    }
    else
    {
        ss << "BOT";
    }
    return ss.str();
}
void Boolean4::print(std::ostream &out)
{
    out << format();
}
bool Boolean4::equals(Boolean4 *_b)
{
    return value == _b->get_value();
}

/**
* private helpers which are only used in this file
*/
