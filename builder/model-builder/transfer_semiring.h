#ifndef TRANSFER_SEMIRING_H
#define TRANSFER_SEMIRING_H

#include <queue>

#include "wali/SemElem.hpp"

#include "structures/abstract_value.h"

class Transfer_semiring : public wali::SemElem
{
    /**
    * public methods
    */
public:
    Transfer_semiring(Abstract_value *);

    virtual ~Transfer_semiring();


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
    Abstract_value *get_value();


    /**
    * helpers - inherited methods from SemElem
    */
    bool equal(SemElem *) const;

    std::ostream& print(std::ostream& out) const;


    /**
    * helpers
    */
    bool equal(Transfer_semiring *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    Abstract_value *value;


    /**
    * static attributes
    */
    static wali::sem_elem_t ELEM_ONE;
    static wali::sem_elem_t ELEM_ZERO;

};

#endif // TRANSFER_SEMIRING_H
