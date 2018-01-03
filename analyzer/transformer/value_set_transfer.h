#ifndef Value_set_transfer_H
#define Value_set_transfer_H

#include <iostream>
#include <string>

#include "absyntax/absyntax.hh"

#include "../domain/Value_set.h"


class Value_set_transfer{
    /**
    * public static attributes
    */
public:
    static Value_set_transfer *get_bot();
    static Value_set_transfer *get_identity();

public:
    Value_set_transfer();
    virtual ~Value_set_transfer();

    // all inherited class must implement this function
    virtual Value_set *Transform(Value_set *);
    virtual std::string format();

    /**
    * helper methods
    */
    bool equals(Value_set_transfer *);

    /**
    * helpers for inherited classes
    */
protected:
    bool is_number(std::string);
    bool is_bool(std::string);
    bool is_byte(std::string);

    int to_number(std::string);
    bool to_bool(std::string);

    /**
    * private attributes
    */
private:
    static Value_set_transfer *ELEM_BOT;
    static Value_set_transfer *ELEM_IDENTITY;

};

#endif // Value_set_transfer_H
