#include "transfer_semiring.h"

Transfer_semiring::Transfer_semiring(Abstract_new_value *_value)
{
    value = _value;
}
Transfer_semiring::~Transfer_semiring()
{
}

wali::sem_elem_t Transfer_semiring::one() const
{
    if (ELEM_ONE == 0)
    {
        ELEM_ONE = new Transfer_semiring(new Abstract_new_value(Value_set_transfer::get_bot()));
    }
    return ELEM_ONE;
}
wali::sem_elem_t Transfer_semiring::zero() const
{
    if (ELEM_ZERO == 0)
    {
        ELEM_ZERO = new Transfer_semiring(new Abstract_new_value(Value_set_transfer::get_identity()));
    }
    return ELEM_ZERO;
}
wali::sem_elem_t Transfer_semiring::extend(SemElem *_other)
{
    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    value->insert_post(other->get_value());
    other->get_value()->insert_pre(value);

    return new Transfer_semiring(other->get_value());
}
wali::sem_elem_t Transfer_semiring::combine(SemElem *_other)
{
    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    Abstract_new_value *new_value = new Abstract_new_value(Value_set_transfer::get_identity());

    value->insert_post(new_value);
    other->get_value()->insert_post(new_value);

    new_value->insert_pre(value);
    new_value->insert_pre(other->get_value());

    return new Transfer_semiring(new_value);
}


bool Transfer_semiring::equal(SemElem *_other) const
{
    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    return value->equals(other->get_value());
}
std::ostream& Transfer_semiring::print(std::ostream& _out) const
{
    return _out << value;
}

/**
* getters and setters
*/
Abstract_new_value *Transfer_semiring::get_value()
{
    return value;
}
void Transfer_semiring::set_value(Abstract_new_value *_value)
{
    value = _value;
}

/**
* private static attributes
*/
wali::sem_elem_t Transfer_semiring::ELEM_ONE = 0;
wali::sem_elem_t Transfer_semiring::ELEM_ZERO = 0;
