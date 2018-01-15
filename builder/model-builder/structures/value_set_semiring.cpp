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
    value = 0;
}

Value_set_semiring::Value_set_semiring()
{
    transfer = 0;
    value = 0;
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
    Value_set_semiring *ret = new Value_set_semiring();
    Value_set_semiring *other = static_cast<Value_set_semiring *>(_other);

    if (_other->equal(one().get_ptr()))
    {
        ret->set_value(value);
        if (value == 0) std::cout << "5" << std::endl;
        return ret;
    }

    if (equal(one().get_ptr()))
    {
        ret->set_value(other->get_transfer()->op_transform(value));
        if (ret->get_value() == 0) std::cout << "6" << std::endl;
        return ret;
    }

    if (this->equal(zero().get_ptr()) || _other->equal(zero().get_ptr()))
    {
        return zero();
    }

    if (other->get_transfer() != 0)
    {
        ret->set_value(other->get_transfer()->op_transform(value));
        if (ret->get_value() == 0) std::cout << "7" << std::endl;
        return ret;
    }
    else
    {
        std::cerr << "Extend an element that has no transfer in Value_set_semiring::extend!" << std::endl;
        exit(0);
    }

}

wali::sem_elem_t Value_set_semiring::combine(SemElem *_other)
{
    Value_set_semiring *ret = new Value_set_semiring();
    Value_set_semiring *other = static_cast<Value_set_semiring *>(_other);

    if (_other->equal(zero().get_ptr()))
    {
        return this;
    }

    if (equal(zero().get_ptr()))
    {
        return _other;
    }

    if (equal(_other))
    {
        ret->set_value(value);
        if (value == 0) std::cout << "3" << std::endl;
        return ret;
    }

    ret->set_value(value->op_union(other->get_value()));

    if (ret->get_value() == 0) std::cout << "4" << std::endl;
    return ret;
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

    if (transfer == 0 && other->get_transfer() == 0)
    {
        if (value != 0 && other->get_value() != 0)
        {
            return value->equal(other->value);
        }
        else
        {
            return false;
        }
    }
    else if (transfer != 0 && other->get_transfer() != 0)
    {
        if (value != 0 && other->get_value() != 0)
        {
            return value->equal(other->get_value()) && transfer->equal(other->get_transfer());
        }
        else
        {
            return transfer->equal(other->get_transfer());
        }
    }
    else
    {
        return false;
    }

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

