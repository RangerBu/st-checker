#ifndef STRIDED_INTERVAL_H
#define STRIDED_INTERVAL_H

#include <sstream>
#include <vector>
#include <set>

#include "abstract_data.h"
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


class Strided_interval : public Abstract_data
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

    static Strided_interval *get_strided_interval(Strided_interval *);

    static Data_width *get_width();


    /**
    * public methods
    */
    virtual ~Strided_interval();


    /**
    * operations
    */
    Strided_interval *op_add(int);

    Strided_interval *op_add(Strided_interval *);

    Strided_interval *op_sub(int);

    Strided_interval *op_sub(Strided_interval *);

    Strided_interval *op_union(Strided_interval *);

    Strided_interval *op_intersect(Strided_interval *);

    Strided_interval *op_negate();

    Strided_interval *op_or(Strided_interval *);

    Strided_interval *op_not();

    Strided_interval *op_and(Strided_interval *);

    Strided_interval *op_xor(Strided_interval *);

    Strided_interval *op_except(Strided_interval *);

    Strided_interval *op_widen(Strided_interval *);

    Strided_interval *op_extend();

    Strided_interval *op_sign_extend();

    Boolean4 *op_compare(Strided_interval *);

    Boolean4 *op_smaller(Strided_interval *);

    Boolean4 *op_greater(Strided_interval *);

    Boolean4 *op_greater_or_equal(Strided_interval *);

    Boolean4 *op_smaller_or_equal(Strided_interval *);

    std::vector<int> si_to_array();

    Strided_interval *remove_lower_bound();

    Strided_interval *remove_upper_bound();


    /**
    * getters and setters
    */
    int get_lower();

    void set_lower(int);

    int get_upper();

    void set_upper(int);

    int get_stride();

    void set_stride(int);


    /**
    * inherited methods (helpers)
    */
    bool equal(Abstract_data *);

    std::ostream &print(std::ostream &);

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

    int shared_suffix_mask();

    int shared_prefix_mask();


    /**
    * helpers - debug only
    */
    std::string to_string();



    /**
    * private attributes and methods
    */
private:
    int lower, upper, stride;

    Strided_interval(int, int, int);


    /**
    * private static attributes
    */
    static Strided_interval *ELEM_TOP;

    static Strided_interval *ELEM_BOT;

    static Data_width *WIDTH;
};

typedef Strided_interval * int_value;

#endif // STRIDED_INTERVAL_H
