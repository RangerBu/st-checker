#ifndef BITS_VECTOR_H
#define BITS_VECTOR_H

#include <vector>
#include <iostream>

#include "../../analyzer/structures/Boolean4.h"

typedef Boolean4* Bit;

class Bits_vector{

    /**
    * public methods
    */
public:
    // default: 1 bit
    Bits_vector();
    Bits_vector(int);
    virtual ~Bits_vector();

    void insert_element(int, Bit);
    Bit get_element(int);

    Bits_vector *And(Bits_vector *);
    Bits_vector *Or(Bits_vector *);
    Bits_vector *Not();
    Bits_vector *Xor(Bits_vector *);
    Bits_vector *Join(Bits_vector *);

    /**
    * getters and setters
    */
    int get_bits();
    Bit *get_values();

    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);
    bool equals(Bits_vector *);


    /**
    * private attributes and methods
    */
private:
    int bits;
    // default value of each bit is FALSE
    Bit *values;



};


#endif // BITS_VECTOR_H
