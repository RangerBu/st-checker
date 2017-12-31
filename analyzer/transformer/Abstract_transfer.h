#ifndef ABSTRACT_TRANSFER_H
#define ABSTRACT_TRANSFER_H

#include <iostream>

#include "absyntax/absyntax.hh"

#include "../domain/Value_set.h"


class Abstract_transfer{

public:
    Abstract_transfer();
    virtual ~Abstract_transfer();

    // all inherited class must implement this function
    virtual Value_set *Transform(symbol_c *, Value_set *)=0;

    /**
    * helpers for inherited classes
    */
protected:
    bool is_number(std::string);
    bool is_bool(std::string);
    bool is_byte(std::string);

    int to_number(std::string);
    bool to_bool(std::string);

};

#endif // ABSTRACT_TRANSFER_H
