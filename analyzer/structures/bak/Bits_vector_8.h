#ifndef BITS_VECTOR_8_H
#define BITS_VECTOR_8_H

#include "bits_vector.h"

class Bits_vector_8 : public Bits_vector{

    /**
    * static attributes and methods
    */
public:
    static Bits_vector_8 *get_top();
    static Bits_vector_8 *get_bot();
    static Bits_vector_8 *get_instance();
    static Bits_vector_8 *get_instance(std::string);


public:
    ~Bits_vector_8();

    /**
    * private static attributes and methods
    */
    static Bits_vector_8 *ELEM_TOP;
    static Bits_vector_8 *ELEM_BOT;

private:
    Bits_vector_8();

};

#endif // BITS_VECTOR_1_H
