//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_INTERVAL_H
#define VERIFY_ST_PROGRAMS_INTERVAL_H

#include "abstract_value.h"

class Interval : public Abstract_value
{
public:
    Interval(int _lower, int _upper);

    virtual ~Interval();

    Abstract_value *get_top();

    bool equal(Abstract_value *_other);

    /**
     * getters and setters
     */
    int get_lower();

    int get_upper();

private:
    int lower, upper;

    const int MAX = (1 << 15) - 1;
    const int MIN = -(1 << 15);

};


#endif //VERIFY_ST_PROGRAMS_INTERVAL_H
