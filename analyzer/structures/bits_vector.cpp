#include "bits_vector.h"

/**
* public static methods
*/
/*
* get top instance
*/
Bits_vector *Bits_vector::get_top(int _length)
{
    if (BV_ELEM_TOP == 0)
    {
        BV_ELEM_TOP = new Bits_vector(_length, Boolean4::get_top());
    }
    return BV_ELEM_TOP;
}

/*
* get bot instance
*/
Bits_vector *Bits_vector::get_bot(int _length)
{
    if (BV_ELEM_BOT == 0)
    {
        BV_ELEM_BOT = new Bits_vector(_length);
    }
    return BV_ELEM_BOT;
}

/*
* get instance with length _length, and default value (bot instance of boolean4)
*/
Bits_vector *Bits_vector::get_instance(int _length)
{
    return new Bits_vector(_length);
}

/*
* get instance with length _length, and initial value _values
*/
Bits_vector *Bits_vector::get_instance(int _length, bit *_values)
{
    Bits_vector *ret = get_instance(_length);
    for (int i=0; i<_length; i++)
    {
        ret->set_element_at(i, _values[i]);
    }
    return ret;
}

/*
* get instance with length _n, and initial value _value
*/
Bits_vector *Bits_vector::get_instance(int _length, std::string _value)
{
    if (_length != _value.length())
    {
        std::cerr << "Two operands that are not matched in length in Bits_vector::get_instance!" << std::endl;
        exit(0);
    }
    Bits_vector *ret = get_instance(_length);
    for (int i=0; i<_length; i++)
    {
        if (_value[i] == '1')
        {
            ret->set_element_at(i, Boolean4::get_true());
        }
        else if (_value[i] == '0')
        {
            ret->set_element_at(i, Boolean4::get_false());
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

Bits_vector *Bits_vector::get_instance(Bits_vector *_other)
{
    Bits_vector *ret = Bits_vector::get_instance(_other->get_length());

    for (int i=0; i<ret->get_length(); i++)
    {
        ret->set_element_at(i, _other->get_element_at(i));
    }
    return ret;
}


/**
* public methods
*/
Bits_vector::Bits_vector()
{
    length = 0;
    values = 0;
}
Bits_vector::~Bits_vector()
{

}


/**
* operations
*/
Bits_vector *Bits_vector::op_and(Bits_vector *_other)
{
    if (length != _other->get_length())
    {
        std::cerr << "Two operands that are not matched in length in Bits_vector::op_and!" << std::endl;
        exit(0);
    }
    else
    {
        Bits_vector *ret = Bits_vector::get_instance(length);
        for (int i=0; i<length; i++)
        {
            ret->set_element_at(i, get_element_at(i)->op_and(_other->get_element_at(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::op_or(Bits_vector *_other)
{
    if (length != _other->get_length())
    {
        std::cerr << "Two operands that are not matched in length in Bits_vector::op_or!" << std::endl;
        exit(0);
    }
    else
    {
        Bits_vector *ret = new Bits_vector(length);
        for (int i=0; i<length; i++)
        {
            ret->set_element_at(i, get_element_at(i)->op_or(_other->get_element_at(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::op_not()
{
    Bits_vector *ret = new Bits_vector(length);
    for (int i=0; i<length; i++)
    {
        ret->set_element_at(i, get_element_at(i)->op_not());
    }
    return ret;
}
Bits_vector *Bits_vector::op_xor(Bits_vector *_other)
{
    if (length != _other->get_length())
    {
        std::cerr << "Two operands that are not matched in length in Bits_vector::op_xor!" << std::endl;
        exit(0);
    }
    else
    {
        Bits_vector *ret = new Bits_vector(length);
        for (int i=0; i<length; i++)
        {
            ret->set_element_at(i, get_element_at(i)->op_xor(_other->get_element_at(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::op_union(Bits_vector *_other)
{
    if (length != _other->get_length())
    {
        std::cerr << "Two operands that are not matched in length in Bits_vector::op_union!" << std::endl;
        exit(0);
    }
    Bits_vector *ret = new Bits_vector(length);

    for (int i=0; i<length; i++)
    {
        ret->set_element_at(i, get_element_at(i)->op_union(_other->get_element_at(i)));
    }
    return ret;
}


/**
* getters and setters
*/
int Bits_vector::get_length()
{
    return length;
}

void Bits_vector::set_length(int _length)
{
    length = _length;
}

bit *Bits_vector::get_values()
{
    return values;
}

void Bits_vector::set_values(bit *_values)
{
    values = _values;
}


/**
* inherited methods
*/
bool Bits_vector::equal(Abstract_data *_other)
{
    Bits_vector *other = (Bits_vector *)_other;

    if (length != other->get_length())
    {
        return false;
    }
    else
    {
        for (int i=0; i<length; i++)
        {
            if (!get_element_at(i)->equal(other->get_element_at(i)))
            {
                return false;
            }
        }
        return true;
    }
}

std::ostream &Bits_vector::print(std::ostream &_out)
{
    _out << "[";

    for (int i=0; i<length; i++)
    {
        values[i]->print(_out);
    }
    return _out<< "](" << length << ")";
}

/*
* access bit value by index
*/
bit Bits_vector::get_element_at(int _index)
{
    if (_index > length)
    {
        std::cerr << "The passed _index out of the bound in Bits_vector::get_element_at()!" << std::endl;
        exit(0);
    }
    else
    {
        return values[_index];
    }
}

/*
* set bit value by index
*/
void Bits_vector::set_element_at(int _index, bit _value)
{
    if (_index > length )
    {
        std::cout << length << std::endl;
        std::cerr << "The passed _index out of the bound in Bits_vector::set_element_at()!" << std::endl;
        exit(0);
    }
    else
    {
        values[_index] = _value;
    }
}



/**
* helpers - debug only
*/
std::string Bits_vector::to_string()
{
    std::stringstream ss;
    ss << "[";
    for (int i=0; i<length; i++)
    {
        ss << values[i]->to_string();
    }
    ss << "](" << length << ")";
    return ss.str();
}

/**
* private methods
*/
Bits_vector::Bits_vector(int _length)
{
    length = _length;
    values = new bit[_length];
    for (int i=0; i<_length; i++)
    {
        values[i] = Boolean4::get_bot();
    }
}

Bits_vector::Bits_vector(int _length, bit _value)
{
    length = _length;
    values = new bit[_length];
    for (int i=0; i<length; i++)
    {
        values[i] = _value;
    }
}
/**
* private static attributes
*/
Bits_vector *Bits_vector::BV_ELEM_TOP = 0;

Bits_vector *Bits_vector::BV_ELEM_BOT = 0;
