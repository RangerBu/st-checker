#ifndef STRIDED_INTERVAL_H
#define STRIDED_INTERVAL_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>

#include "boolean4.h"


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


class Strided_interval
{
    /**
    * public static methods
    */
public:
    static Strided_interval *get_top();
    static Strided_interval *get_bot();
    static Strided_interval *get_singleton_set(int);
    static Strided_interval *get_interval(int, int);
    static Strided_interval *get_strided_interval(int, int, int);
    static Strided_interval *get_strided_interval(std::vector<int> );

    /**
    * private static attributes and methods
    */
private:
    static Strided_interval *ELEM_TOP;
    static Strided_interval *ELEM_BOT;
    static Data_width *width;
    static int gcd(int, int);
    static int* extended_gcd(int, int);
    static unsigned min_or(unsigned, unsigned, unsigned, unsigned);
    static unsigned max_or(unsigned, unsigned, unsigned, unsigned);
    static int min_or_signed(int, int, int, int);
    static int max_or_signed(int, int, int, int);

    /**
    * public methods
    */
public:
    virtual ~Strided_interval();

    Strided_interval *Add(int);
    Strided_interval *Add(Strided_interval *);
    Strided_interval *Sub(int);
    Strided_interval *Sub(Strided_interval *);
    Strided_interval *Union(Strided_interval *);
    Strided_interval *Intersect(Strided_interval *);
    Strided_interval *remove_lower_bound();
    Strided_interval *remove_upper_bound();
    Strided_interval *Negate();
    Strided_interval *Or(Strided_interval *);
    Strided_interval *Not();
    Strided_interval *And(Strided_interval *);
    Strided_interval *Xor(Strided_interval *);
    Boolean4 *Compare(Strided_interval *);
    Boolean4 *Smaller(Strided_interval *);
    Strided_interval *Except(Strided_interval *);
    Strided_interval *Widen(Strided_interval *);
    Strided_interval *Extend();
    Strided_interval *sign_extend();
    Boolean4 *Greater(Strided_interval *);
    Boolean4 *greater_or_equal(Strided_interval *);
    Boolean4 *smaller_or_equal(Strided_interval *);
    int shared_suffix_mask();
    int shared_prefix_mask();

    std::vector<int> si_to_array();

    /**
    * getters and setters
    */
    int get_stride();
    void set_stride(int);
    int get_lower();
    void set_lower(int);
    int get_upper();
    void set_upper(int);


    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);
    bool equals(Strided_interval *);

    bool is_singleton_set();
    bool is_top();
    bool is_bot();
    bool is_zero();
    bool is_one();
    bool is_interval();
    bool contains(int);
    bool contains(Strided_interval *);
    bool is_lower_bound_minimal();
    bool is_upper_bound_maximal();


    /**
    * private attributes and methods
    */
private:
    int stride;
    int lower, upper;

    Strided_interval(int, int, int);

};

#endif // STRIDED_INTERVAL_H
