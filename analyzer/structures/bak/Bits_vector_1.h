#ifndef BITS_VECTOR_1_H
#define BITS_VECTOR_1_H

#include "bits_vector.h"

class Bits_vector_1 : public Bits_vector{

    /**
    * static attributes
    */
public:
    static Bits_vector_1 *get_top();
    static Bits_vector_1 *get_bot();
    static Bits_vector_1 *get_instance(bool);
    static Bits_vector_1 *get_instance(std::string);

private:
    static Bits_vector_1 *ELEM_TOP;
    static Bits_vector_1 *ELEM_BOT;


public:
    Bits_vector_1();
    ~Bits_vector_1();

};
#endif // BITS_VECTOR_1_H
