#ifndef BITS_VECTOR_1_H
#define BITS_VECTOR_1_H

#include "bits_vector.h"

class Bits_vector_1 : public Bits_vector
{
    /**
    * public static methods
    */
public:
    /*
    * get top instance
    */
    static Bits_vector_1 *get_top()
    {
        if (BV1_ELEM_TOP == 0)
        {
            BV1_ELEM_TOP = new Bits_vector_1();
            BV1_ELEM_TOP->set_element_at(0, Boolean4::get_top());
        }
        return BV1_ELEM_TOP;
    }

    /*
    * get bot instance
    */
    static Bits_vector_1 *get_bot()
    {
        if (BV1_ELEM_BOT == 0)
        {
            BV1_ELEM_BOT = new Bits_vector_1();
        }
        return BV1_ELEM_BOT;
    }

    /*
    * get instance by boolean value
    */
    static Bits_vector_1 *get_instance(bool _value)
    {
            Bits_vector_1 *ret = new Bits_vector_1();
        ret->set_element_at(0, Boolean4::get_instance(_value));

        return ret;
    }

    static Bits_vector_1 *get_instance(std::string _value)
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

    static Bits_vector_1 *get_instance(Bits_vector_1 *_other)
    {
        Bits_vector_1 *ret = new Bits_vector_1();
        ret->set_element_at(0, _other->get_element_at(0));
        return ret;
    }


    /**
    * public methods
    */
    virtual ~Bits_vector_1()
    {

    }


    /**
    * private methods and static attributes
    */
private:
    /*
    * constructor
    */
    Bits_vector_1()
    {
        length = 1;
        values = new bit[length];
        set_element_at(0, Boolean4::get_bot());
    }

    static Bits_vector_1 *BV1_ELEM_TOP;

    static Bits_vector_1 *BV1_ELEM_BOT;
};

typedef Bits_vector_1* bool_value;

#endif // BITS_VECTOR_1_H
