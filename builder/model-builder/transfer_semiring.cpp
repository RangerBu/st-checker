#include "transfer_semiring.h"

/**
* methods only used in this file
*/
Abstract_value *_extend(Abstract_value *_first, Abstract_value *_second)
{

    Abstract_value *ret = Abstract_value::get_instance(_second);

    std::vector<Abstract_value*> update_list;

    std::queue<Abstract_value *> work_queue;
    work_queue.push(ret);
    Abstract_value *v = 0;
    while(work_queue.size() > 0)
    {
        v = work_queue.front(); work_queue.pop();

        if (v->get_extend_pre() == 0)
        {
            update_list.push_back(v);
        }
        else
        {
            work_queue.push(v->get_extend_pre());
        }
    }

    Abstract_value *first = Abstract_value::get_instance(_first);
    for (int i=0; i<update_list.size(); i++)
    {
        update_list[i]->set_extend_pre(first);
    }
    return ret;
}

Abstract_value *_combine(Abstract_value *_first, Abstract_value *_second)
{
    Abstract_value *ret = Abstract_value::get_instance(_first);

    ret->set_combine_pre(Abstract_value::get_instance(_second));

    return ret;
}


/**
* public methods
*/
/*
* constructor
*/
Transfer_semiring::Transfer_semiring(Abstract_value *_value)
{
    value = _value;
}

/*
* de-constructor
*/
Transfer_semiring::~Transfer_semiring()
{

}


/**
* inherited methods from SemElem
*/
wali::sem_elem_t Transfer_semiring::one() const
{
    if (ELEM_ONE == 0)
    {
        ELEM_ONE = new Transfer_semiring(Abstract_value::get_instance(Abstract_value_set_transfer::get_bot()));
    }
    return ELEM_ONE;
}

wali::sem_elem_t Transfer_semiring::zero() const
{
    if (ELEM_ZERO == 0)
    {
        ELEM_ZERO = new Transfer_semiring(Abstract_value::get_instance(Abstract_value_set_transfer::get_identity()));
    }
    return ELEM_ZERO;
}

wali::sem_elem_t Transfer_semiring::extend(SemElem *_other)
{
    if (_other->equal(zero().get_ptr()))
    {
        return this;
    }

    if (this->equal(zero().get_ptr()))
    {
        return _other;
    }

    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    return new Transfer_semiring(_extend(value, other->get_value()));
}

wali::sem_elem_t Transfer_semiring::combine(SemElem *_other)
{
    if (_other->equal(one().get_ptr()))
    {
        return this;
    }

    if (this->equal(one().get_ptr()))
    {
        return _other;
    }

    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    return new Transfer_semiring(_combine(value, other->get_value()));
}


/**
* getters and setters
*/
Abstract_value *Transfer_semiring::get_value()
{
    return value;
}


/**
* helpers - inherited methods from SemElem
*/
bool Transfer_semiring::equal(SemElem *_other) const
{
    Transfer_semiring *other = static_cast<Transfer_semiring *>(_other);

    return value->equal(other->get_value());
}

std::ostream& Transfer_semiring::print(std::ostream& _out) const
{
    return _out << value;
}


/**
* helpers
*/
bool Transfer_semiring::equal(Transfer_semiring *_other)
{
    return value->equal(_other->get_value());
}

std::ostream &Transfer_semiring::print(std::ostream &_out)
{

}


/**
* helpers - debug only
*/
std::string Transfer_semiring::to_string()
{
    return ("transfer_semiring with value:" + value->to_string());
}


/**
* private static attributes
*/
wali::sem_elem_t Transfer_semiring::ELEM_ONE = 0;
wali::sem_elem_t Transfer_semiring::ELEM_ZERO = 0;
