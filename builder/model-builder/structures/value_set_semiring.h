#ifndef VALUE_SET_SEMIRING_H
#define VALUE_SET_SEMIRING_H

#include "wali/SemElem.hpp"

#include "../../../analyzer/transformer/value_set_transfer.h"

class Value_set_semiring : public wali::SemElem
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Value_set_semiring(Abstract_value_set_transfer *);

    Value_set_semiring(Abstract_value_set_transfer *, Value_set *);

    Value_set_semiring();

    /*
    * de-constructor
    */
    virtual ~Value_set_semiring();


    /**
    * inherited methods from SemElem
    */
    wali::sem_elem_t one() const;

    wali::sem_elem_t zero() const;

    wali::sem_elem_t extend(SemElem *);

    wali::sem_elem_t combine(SemElem *);


    /**
    * getters and setters
    */
    Value_set *get_value();

    void set_value(Value_set *);

    Abstract_value_set_transfer *get_transfer();


    /**
    * helpers - inherited methods from SemElem
    */
    bool equal(SemElem *) const;

    std::ostream& print(std::ostream& out) const;


    /**
    * helpers
    */
    bool equal(Value_set_semiring *);

    std::ostream &print_dot(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    Value_set *value;

    bool is_reached;

    Abstract_value_set_transfer *transfer;


    /**
    * private static attributes
    */

    static wali::sem_elem_t ELEM_ONE;

    static wali::sem_elem_t ELEM_ZERO;
};

#endif // VALUE_SET_SEMIRING_H
