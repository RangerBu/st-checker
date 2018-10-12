#ifndef BITS_VECTOR_H
#define BITS_VECTOR_H

#include <vector>
#include <string>
#include <sstream>

#include "abstract_data.h"
#include "../../analyzer/structures/boolean4.h"

typedef Boolean4* bit;

class Bits_vector : public Abstract_data
{
    /**
    * public static methods
    */
public:
    /*
    * get top instance
    */
    static Bits_vector *get_top(int);

    /*
    * get bot instance
    */
    static Bits_vector *get_bot(int);

    /*
    * get instance with length _n, and default value (bot instance of boolean4)
    */
    static Bits_vector *get_instance(int);

    /*
    * get instance with length _n, and initial value _value
    */
    static Bits_vector *get_instance(int, bit *);

    /*
    * get instance with length _n, and initial value _value
    */
    static Bits_vector *get_instance(int, std::string);

    static Bits_vector *get_instance(Bits_vector *);


    /**
    * public methods
    */
    Bits_vector();
    virtual ~Bits_vector();


    /**
    * operations
    */
    virtual Bits_vector *op_and(Bits_vector *);

    virtual Bits_vector *op_or(Bits_vector *);

    virtual Bits_vector *op_not();

    virtual Bits_vector *op_xor(Bits_vector *);

    virtual Bits_vector *op_union(Bits_vector *);

    virtual Bits_vector *op_intersect(Bits_vector *);


    /**
    * getters and setters
    */
    int get_length();

    void set_length(int);

    bit *get_values();

    void set_values(bit *);


    /**
    * inherited methods (helpers)
    */
    bool equal(Abstract_data *);

    std::ostream &print(std::ostream &);

    /*
    * access bit value by index
    */
    bit get_element_at(int);

    /*
    * set bit value by index
    */
    void set_element_at(int, bit);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * protected attributes
    */
protected:
    /*
    * length of the bits-vector
    */
    int length;

    /*
    * the value of each bit
    */
    bit *values;


private:
    /**
    * private methods
    */
    /*
    * create an instance with length _lenght using this constructor
    */
    Bits_vector(int);

    /*
    * create an instance with length _length and default value _bit at each bit
    */
    Bits_vector(int, bit);


    /**
    * private static attributes
    */
    /*
    * the top instance
    */
    static Bits_vector *BV_ELEM_TOP;

    /*
    * the bot instance
    */
    static Bits_vector *BV_ELEM_BOT;
};


#endif // BITS_VECTOR_H
