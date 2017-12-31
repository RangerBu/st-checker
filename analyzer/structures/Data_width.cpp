#include "Data_width.h"

/**
* public static methods
*/
Data_width *Data_width::get_instance(int _width)
{
    return new Data_width(_width);
}

Data_width *Data_width::maximum(Data_width *_a, Data_width *_b)
{
    if (_a->compare_to(_b) < 0)
    {
        return _b;
    }
    else
    {
        return _a;
    }
}

/**
* public methods
*/

Data_width::~Data_width()
{
}

int Data_width::effective_value(int _value)
{
    int high_bit_mask = 1 << (width - 1);
    if (width == 1)
    {
        return _value & high_bit_mask;
    }
    else
    {
        return -(_value & high_bit_mask) + (_value & (high_bit_mask - 1));
    }
}

int Data_width::compare_to(Data_width *_a)
{
    return width - _a->get_width();
}

/**
* getters and setters
*/
int Data_width::get_width()
{
    return width;
}
int Data_width::get_maximum_value()
{
    return maximum_value;
}
int Data_width::get_minimum_value()
{
    return minimum_value;
}

/**
* helpers
*/
std::string Data_width::format()
{
    std::stringstream ss;
    ss << "R" << width;
    return ss.str();
}
void Data_width::print(std::ostream &out)
{
    out << this->format();
}

/**
* private methods
*/
Data_width::Data_width(int _width)
{
    width = _width;
    if (width == 1)
    {
        minimum_value = 0;
        maximum_value = 1;
    }
    else
    {
        minimum_value = -(1 << (width -1 ));
        maximum_value = -(minimum_value + 1);
    }
}
