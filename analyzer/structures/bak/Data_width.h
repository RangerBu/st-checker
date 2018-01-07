#ifndef DATA_WIDTH_H
#define DATA_WIDTH_H

#include <string>
#include <sstream>
#include <iostream>

class Data_width
{
    /**
    * public static methods
    */
public:
    static Data_width *get_instance(int _width)
    {
        return new Data_width(_width);
    }

    static Data_width *maximum(Data_width *_a, Data_width *_b)
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
public:
    virtual ~Data_width()
    {

    }

    int effective_value(int _value)
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

    int compare_to(Data_width *_a)
    {
        return width - _a->get_width();
    }



    /**
    * getters and setters
    */
    int get_width()
    {
        return width;
    }
    int get_maximum_value()
    {
        return maximum_value;
    }
    int get_minimum_value()
    {
        return minimum_value;
    }

    /**
    * helpers
    */
    std::string format()
    {
        std::stringstream ss;
        ss << "R" << width;
        return ss.str();
    }
    void print(std::ostream &out)
    {
        out << this->format();
    }

    /**
    * private attributes and methods
    */
private:
    int width;
    int maximum_value;
    int minimum_value;

    Data_width(int _width)
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

};

#endif // DATA_WIDTH_H
