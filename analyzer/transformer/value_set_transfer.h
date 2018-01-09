#ifndef ABSTRACT_VALUE_SET_TRANSFER_H
#define ABSTRACT_VALUE_SET_TRANSFER_H

#include <string>

#include "absyntax/absyntax.hh"

#include "../domain/value_set.h"

class Abstract_value_set_transfer
{
    /**
    * public static methods
    */
public :
    static Abstract_value_set_transfer *get_bot();

    static Abstract_value_set_transfer *get_identity();


    /**
    * public methods
    */
    Abstract_value_set_transfer();

    virtual ~Abstract_value_set_transfer();


    /**
    * external visible methods
    */
    virtual Value_set *op_transform(Value_set *);


    /**
    * helpers
    */
    virtual bool equal(Abstract_value_set_transfer *);

    virtual std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    virtual std::string to_string();


    /**
    * helpers for inherited classes
    */
    bool is_number(std::string);

    bool is_bool(std::string);

    bool is_byte(std::string);

    int to_number(std::string);

    bool to_bool(std::string);


    /**
    * private static attributes
    */
private:
    static Abstract_value_set_transfer *ELEM_BOT;

    static Abstract_value_set_transfer *ELEM_IDENTITY;


    /**
    * private attributes
    */
};

#endif // ABSTRACT_VALUE_SET_TRANSFER_H
