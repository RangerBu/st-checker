#include "value_set_semiring.h"

/**
* public methods
*/
/*
* constructor
*/
Value_set_semiring::Value_set_semiring(Abstract_value_set_transfer *_transfer)
{
    transfer = _transfer;
}

/*
* de-constructor
*/
Value_set_semiring::~Value_set_semiring()
{

}


/**
* inherited methods from SemElem
*/
wali::sem_elem_t Value_set_semiring::one() const
{
    if (ELEM_ONE == 0)
    {
        ELEM_ONE = new Value_set_semiring(Abstract_value_set_transfer::get_identity());
    }
    return ELEM_ONE;
}

wali::sem_elem_t Value_set_semiring::zero() const
{
    if (ELEM_ZERO == 0)
    {
        ELEM_ZERO = new Value_set_semiring(Abstract_value_set_transfer::get_bot());
    }
    return ELEM_ZERO;
}

wali::sem_elem_t Value_set_semiring::extend(SemElem *_other)
{

}

wali::sem_elem_t Value_set_semiring::combine(SemElem *_other)
{

}


/**
* getters and setters
*/
Value_set *Value_set_semiring::get_value()
{
    return value;
}

void Value_set_semiring::set_value(Value_set *_value)
{
    value = _value;
}

Abstract_value_set_transfer *Value_set_semiring::get_transfer()
{
    return transfer;
}


/**
* helpers - inherited methods from SemElem
*/
bool Value_set_semiring::equal(SemElem *_other) const
{
    Value_set_semiring *other = static_cast<Value_set_semiring *>(_other);

    return value->equal(other->get_value()) && transfer->equal(other->get_transfer());
}

std::ostream &Value_set_semiring::print(std::ostream &_out) const
{
    if (value != 0)
    {
        value->print(_out);
    }
    else
    {
        std::cerr << "The value has not been initialized in Value_set_semiring::print() const!" << std::endl;
        exit(0);
    }
    return _out;
}


/**
* helpers
*/
bool Value_set_semiring::equal(Value_set_semiring *_other)
{
    return value->equal(_other->get_value()) && transfer->equal(_other->get_transfer());
}

std::ostream &Value_set_semiring::print_dot(std::ostream &_out)
{

}


/**
* helpers - debug only
*/
std::string Value_set_semiring::to_string()
{
    return value->to_string();
}


/**
* private static attributes
*/
wali::sem_elem_t Value_set_semiring::ELEM_ONE = 0;

wali::sem_elem_t Value_set_semiring::ELEM_ZERO = 0;

