//
// Created by Samson on 2018/5/30.
//

#include <sstream>

#include "interval.h"

Interval::Interval(int _lower, int _upper) : lower(_lower), upper(_upper)
{
    std::stringstream ss;
    ss << "[" << lower << ", " << upper << "]";

    str_value = ss.str();
}

Interval::~Interval()
{
}

Abstract_value *Interval::get_top()
{
    return new Interval(MIN, MAX);
}

bool Interval::equal(Abstract_value *_other)
{
    Interval *other = static_cast<Interval *>(_other);

    return lower == other->get_lower() && upper == other->get_upper();
}

/**
 * getters and setters
 */

int Interval::get_lower()
{
    return lower;
}
int Interval::get_upper()
{
    return upper;
}
