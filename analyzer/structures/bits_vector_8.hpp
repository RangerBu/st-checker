#ifndef BITS_VECTOR_8_H
#define BITS_VECTOR_8_H

#include "bits_vector.h"

class Bits_vector_8 : public Bits_vector
{
    /**
    * public static methods
    */
public:
    /*
    * get top instance
    */
    static Bits_vector_8 *get_top()
    {
        if (BV8_ELEM_TOP == 0)
        {
            BV8_ELEM_TOP = new Bits_vector_8();
            for (int i=0; i<8; i++)
            {
                BV8_ELEM_TOP->set_element_at(i, Boolean4::get_top());
            }
        }
        return BV8_ELEM_TOP;
    }

    /*
    * get bot instance
    */
    static Bits_vector_8 *get_bot()
    {
        if (BV8_ELEM_BOT == 0)
        {
            BV8_ELEM_BOT = new Bits_vector_8();
            for (int i=0; i<8; i++)
            {
                BV8_ELEM_BOT->set_element_at(i, Boolean4::get_bot());
            }
        }
        return BV8_ELEM_BOT;
    }

    /*
    * get instance by boolean value
    */
    static Bits_vector_8 *get_instance(bool _value)
    {
        Bits_vector_8 *ret = new Bits_vector_8();

        for (int i=0; i<8; i++)
        {
            ret->set_element_at(i, Boolean4::get_instance(_value));
        }
        return ret;
    }

    /*
    * get instance with initial value _value
    */
    static Bits_vector_8 *get_instance(std::string _value)
    {
        Bits_vector_8 *ret = new Bits_vector_8();
        for (int i=0; i<8; i++)
        {
            if (_value[i] == '0')
            {
                ret->set_element_at(i, Boolean4::get_instance(false));
            }
            else if (_value[i] == '1')
            {
                ret->set_element_at(i, Boolean4::get_instance(true));
            }
            else if (_value[i] == '_')
            {
                ret->set_element_at(i, Boolean4::get_bot());
            }
            else if (_value[i] == '*')
            {
                ret->set_element_at(i, Boolean4::get_top());
            }
        }
        return ret;
    }


    /**
    * public methods
    */
    virtual ~Bits_vector_8()
    {
    }


    /**
    * private methods and static attributes
    */
private:
    /*
    * constructor
    */
    Bits_vector_8()
    {
        length = 8;
        values = new bit[length];
        for (int i=0; i<8; i++)
        {
            set_element_at(i, Boolean4::get_bot());
        }
    }

    static Bits_vector_8 *BV8_ELEM_TOP;

    static Bits_vector_8 *BV8_ELEM_BOT;
};


#endif // BITS_VECTOR_8_H
