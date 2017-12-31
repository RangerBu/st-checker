#include "Bits_vector_1.h"

/**
* static methods
*/

Bits_vector_1 *Bits_vector_1::get_top()
{
    if(ELEM_TOP == 0)
    {
        ELEM_TOP = new Bits_vector_1();
        ELEM_TOP->insert_element(0, Boolean4::MAYBE);
    }
    return ELEM_TOP;
}
Bits_vector_1 *Bits_vector_1::get_bot()
{
    if (ELEM_BOT == 0)
    {
        ELEM_BOT = new Bits_vector_1();
    }
    return ELEM_BOT;
}
Bits_vector_1 *Bits_vector_1::get_instance(bool _value)
{
    Bits_vector_1 *ret = new Bits_vector_1();
    if (_value)
    {
        ret->insert_element(0, Boolean4::TRUE);
    }
    else
    {
        ret->insert_element(0, Boolean4::FALSE);
    }
    return ret;
}
Bits_vector_1 *Bits_vector_1::get_instance(std::string _value)
{
    Bits_vector_1 *ret = new Bits_vector_1();
    if (_value.compare("0") == 0 || _value.compare("FALSE") == 0)
    {
        ret->insert_element(0, Boolean4::FALSE);
    }
    else if (_value.compare("1") == 0 || _value.compare("TRUE") == 0)
    {
        ret->insert_element(0, Boolean4::TRUE);
    }
    else if (_value.compare("_") == 0 || _value.compare("BOT") == 0)
    {
        ret->insert_element(0, Boolean4::BOT);
    }
    else if (_value.compare("*") == 0 || _value.compare("MAYBE") == 0)
    {
        ret->insert_element(0, Boolean4::MAYBE);
    }
    return ret;
}

/**
* private static attributes
*/
Bits_vector_1 *Bits_vector_1::ELEM_BOT = 0;
Bits_vector_1 *Bits_vector_1::ELEM_TOP = 0;

/**
* public methods
*/
Bits_vector_1::Bits_vector_1():Bits_vector(1)
{
}
Bits_vector_1::~Bits_vector_1()
{
}
