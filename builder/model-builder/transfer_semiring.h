#ifndef ABSTRACT_EFFECT
#define ABSTRACT_EFFECT

#include <vector>

#include "wali/SemElem.hpp"

#include "abstract_new_value.h"

class Transfer_semiring : public wali::SemElem
{
    /**
    * public methods
    */
public:
    Transfer_semiring(Abstract_new_value *);
    virtual ~Transfer_semiring();


    /**
    * inherited from SemElem
    */
    wali::sem_elem_t one() const;
    wali::sem_elem_t zero() const;

    wali::sem_elem_t extend(SemElem *);
    wali::sem_elem_t combine(SemElem *);

    bool equal(SemElem *) const;
    std::ostream& print(std::ostream& out) const;


    /**
    * getters and setters
    */
    Abstract_new_value *get_value();
    void set_value(Abstract_new_value *);

    /**
    * private attributes
    */
private:
    Abstract_new_value *value;

    /**
    * static attributes
    */
    static wali::sem_elem_t ELEM_ONE;
    static wali::sem_elem_t ELEM_ZERO;

};

#endif // ABSTRACT_EFFECT
