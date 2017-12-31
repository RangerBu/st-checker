#include "Bits_vector_8.h"

/**
* static methods
*/
Bits_vector_8 *Bits_vector_8::get_top()
{
    if (ELEM_TOP==0)
    {
        ELEM_TOP = new Bits_vector_8();
        for (int i=0; i<8; i++)
        {
            ELEM_TOP->insert_element(i, Boolean4::MAYBE);
        }
    }
    return ELEM_TOP;
}
Bits_vector_8 *Bits_vector_8::get_bot()
{
    if (ELEM_BOT == 0)
    {
        ELEM_BOT = new Bits_vector_8();
    }
    return ELEM_BOT;
}
Bits_vector_8 *Bits_vector_8::get_instance()
{
    return new Bits_vector_8();
}
Bits_vector_8 *Bits_vector_8::get_instance(std::string _value)
{
    if (_value.length() < 8)
    {
        std::cout << "Unmatched length!" << std::endl;
        return 0;
    }
    else
    {
        Bits_vector_8 *ret = new Bits_vector_8();
        for (int i=0; i<8; i++)
        {
            if (_value[i] == '0')
            {
                ret->insert_element(i, Boolean4::FALSE);
            }
            else
            {
                ret->insert_element(i, Boolean4::TRUE);
            }
        }
        return ret;
    }
}


/**
* public methods
*/
Bits_vector_8::~Bits_vector_8()
{
}

/**
* private attributes and methods
*/
Bits_vector_8 *Bits_vector_8::ELEM_BOT = 0;
Bits_vector_8 *Bits_vector_8::ELEM_TOP = 0;
Bits_vector_8::Bits_vector_8():Bits_vector(8)
{
}
