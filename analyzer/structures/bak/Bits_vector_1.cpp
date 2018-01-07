#include "Bits_vector_1.h"

/**
* static methods
*/

Bits_vector_1 *Bits_vector_1::get_top()
{
    if(ELEM_TOP == 0)
    {
        ELEM_TOP = new Bits_vector_1();
        ELEM_TOP->set_element_at(0, Boolean4::get_top());
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
        ret->set_element_at(0, Boolean4::get_instance(true));
    }
    else
    {
        ret->set_element_at(0, Boolean4::get_instance(false));
    }
    return ret;
}
Bits_vector_1 *Bits_vector_1::get_instance(std::string _value)
{
    Bits_vector_1 *ret = new Bits_vector_1();
    if (_value.compare("0") == 0 || _value.compare("FALSE") == 0)
    {
        ret->set_element_at(0, Boolean4::get_instance(false));
    }
    else if (_value.compare("1") == 0 || _value.compare("TRUE") == 0)
    {
        ret->set_element_at(0, Boolean4::get_instance(true));
    }
    else if (_value.compare("_") == 0 || _value.compare("BOT") == 0)
    {
        ret->set_element_at(0, Boolean4::get_bot());
    }
    else if (_value.compare("*") == 0 || _value.compare("MAYBE") == 0)
    {
        ret->set_element_at(0, Boolean4::get_top());
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
Bits_vector_1::Bits_vector_1()
{
}
Bits_vector_1::~Bits_vector_1()
{
}
