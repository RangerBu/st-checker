#ifndef STRIDED_INTERVAL_H
#define STRIDED_INTERVAL_H

#define INT_MAX 32767
#define INT_MIN -32768

#include <set>

#include "../../utils/utils.h"
#include "../../analyzer/domain/Value_set.h"

class Strided_interval : public Value_set{
public:
    static Strided_interval *top();
    static Strided_interval *bot();

public:
    Strided_interval();
    Strided_interval(int);
    Strided_interval(int, int, int);
    Strided_interval(Strided_interval *);
    virtual ~Strided_interval();

    // Meet is point-wise union
    Strided_interval *Join(Strided_interval *);

    void Neg();
    void Not();

    Strided_interval *Add(Strided_interval *);
    Strided_interval *Sub(Strided_interval *);
//    Strided_interval *And(Strided_interval *);
//    Strided_interval *Or(Strided_interval *);
//    Strided_interval *Xor(Strided_interval *);
//    Strided_interval *Mul(Strided_interval *);
//    Strided_interval *Div(Strided_interval *);
//    Strided_interval *Shift_left(Strided_interval *);
//    Strided_interval *Shift_right(Strided_interval *);

    Strided_interval *Intersection(Strided_interval *);
    Strided_interval *Delete_element(int);


    /**
    * getters and setters
    */
    int get_stride();
    int get_low();
    int get_high();

    /**
    * helpers
    */
    Strided_interval *operator =(Strided_interval *);
    bool operator ==(Strided_interval *) const;
    bool operator !=(Strided_interval *) const;

    std::string format();
    void print(std::ostream &);


private:
    int stride;
    int low, high;
};

#endif // STRIDED_INTERVAL_H
