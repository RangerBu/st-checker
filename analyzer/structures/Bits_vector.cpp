#include "Bits_vector.h"

/**
* public methods
*/

Bits_vector::Bits_vector()
{
    bits = 1;
    values = new Bit[bits];
    values[0] = Boolean4::BOT;
}
Bits_vector::Bits_vector(int n)
{
    bits = n;
    values = new Bit[bits];
    for (int i=0; i<n; i++)
    {
        values[i] = Boolean4::BOT;
    }
}
Bits_vector::~Bits_vector()
{
}

void Bits_vector::insert_element(int _idx, Bit _value)
{
    if (_idx < bits && _idx > -1)
    {
        values[_idx] = _value;
    }
    else
    {
        std::cout << "Index out of bounds!" << std::endl;
    }
}
Bit Bits_vector::get_element(int _idx)
{
    if (_idx < bits && _idx > -1)
    {
        return values[_idx];
    }
    else
    {
        std::cout << "Index out of bounds!" << std::endl;
        return 0;
    }
}
Bits_vector *Bits_vector::And(Bits_vector *_other)
{
    if (bits != _other->get_bits())
    {
        std::cout << "Unmatched operands!" << std::endl;
        return 0;
    }
    else
    {
        Bits_vector *ret = new Bits_vector(bits);
        for (int i=0; i<bits; i++)
        {
            ret->insert_element(i, get_element(i)->And(_other->get_element(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::Or(Bits_vector *_other)
{
    if (bits != _other->get_bits())
    {
        std::cout << "Unmatched operands!" << std::endl;
        return 0;
    }
    else
    {
        Bits_vector *ret = new Bits_vector(bits);
        for (int i=0; i<bits; i++)
        {
            ret->insert_element(i, get_element(i)->Or(_other->get_element(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::Not()
{
    Bits_vector *ret = new Bits_vector(bits);
    for (int i=0; i<bits; i++)
    {
        ret->insert_element(i, get_element(i)->Not());
    }
    return ret;
}
Bits_vector *Bits_vector::Xor(Bits_vector *_other)
{
    if (bits != _other->get_bits())
    {
        std::cout << "Unmatched operands!" << std::endl;
        return 0;
    }
    else
    {
        Bits_vector *ret = new Bits_vector(bits);
        for (int i=0; i<bits; i++)
        {
            ret->insert_element(i, get_element(i)->Xor(_other->get_element(i)));
        }
        return ret;
    }
}
Bits_vector *Bits_vector::Join(Bits_vector *_other)
{
    if (bits != _other->get_bits())
    {
        std::cout << "Unmatched size!" << std::endl;
        return 0;
    }
    Bits_vector *ret = new Bits_vector(bits);

    for (int i=0; i<bits; i++)
    {
        ret->insert_element(i, get_element(i)->Join(_other->get_element(i)));
    }
    return ret;
}

/**
* getters and setters
*/
int Bits_vector::get_bits()
{
    return bits;
}
Bit *Bits_vector::get_values()
{
    return values;
}

/**
* helpers
*/
std::string Bits_vector::format()
{
    std::stringstream o;
    o << "[";
    for (int i=0; i<bits; i++)
    {
        std::string tmp;
        if (values[i]->equals(Boolean4::FALSE))
        {
            tmp = "0";
        }
        else if (values[i]->equals(Boolean4::TRUE))
        {
            tmp = "1";
        }
        else if (values[i]->equals(Boolean4::MAYBE))
        {
            tmp = "*";
        }
        else
        {
            tmp = "_";
        }
        o << tmp;
    }
    o << "](" << bits << ")";
    return o.str();
}
void Bits_vector::print(std::ostream &out)
{
    out << this->format();
}
bool Bits_vector::equals(Bits_vector *_other)
{
    if (bits != _other->get_bits())
    {
        return false;
    }
    for (int i=0; i<bits; i++)
    {
        if (!get_element(i)->equals(_other->get_element(i)))
        {
            return false;
        }
    }
    return true;
}

/**
* private attributes and methods
*/
