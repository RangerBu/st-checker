#include "abstract_value.h"

/**
* public static attributes and methods
*/
/*
* count the number of objects created
*/
int Abstract_value::COUNT = 0;

Abstract_value *Abstract_value::get_instance(Abstract_value_set_transfer *_value)
{
    return new Abstract_value(_value);
}

Abstract_value *Abstract_value::get_instance(Abstract_value *_other)
{
    Abstract_value *ret = 0;
    if (_other->get_extend_pre() == 0 && _other->get_combine_pre() == 0)
    {
        ret = new Abstract_value(_other->get_value());
    }
    else if (_other->get_extend_pre() == 0)
    {
        ret = new Abstract_value(_other->get_value());

        ret->set_combine_pre(Abstract_value::get_instance(_other->get_combine_pre()));
    }
    else if (_other->get_combine_pre() == 0)
    {
        ret = new Abstract_value(_other->get_value());

        ret->set_extend_pre(Abstract_value::get_instance(_other->get_extend_pre()));
    }
    else
    {
        ret = new Abstract_value(_other->get_value());

        ret->set_extend_pre(Abstract_value::get_instance(_other->get_extend_pre()));
        ret->set_combine_pre(Abstract_value::get_instance(_other->get_combine_pre()));
    }
    return ret;
}


/**
* public methods
*/
Abstract_value::~Abstract_value()
{

}


/**
* external visible methods
*/
Value_set *Abstract_value::op_transform(Value_set *_vs0)
{

}

void Abstract_value::insert_combine_pre(Abstract_value *_combine_pre)
{
    if (this == _combine_pre)
    {
        std::cerr << "You cannot set itself as its combine_pre in Abstract_value::set_combine_pre!" << std::endl;
        exit(0);
    }
    combine_pre = _combine_pre;

    for (int i=0; i<combine_pres.size(); i++)
    {

    }
}


/**
* getters and setters
*/
Abstract_value *Abstract_value::get_extend_pre()
{
    return extend_pre;
}

void Abstract_value::set_extend_pre(Abstract_value *_extend_pre)
{
    if (this == _extend_pre)
    {
        std::cerr << "You cannot set itself as its extend_pre in Abstract_value::set_extend_pre!" << std::endl;
        exit(0);
    }
    extend_pre = _extend_pre;
}

Abstract_value *Abstract_value::get_combine_pre()
{
    return combine_pre;
}

void Abstract_value::set_combine_pre(Abstract_value *_combine_pre)
{
    if (this == _combine_pre)
    {
        std::cerr << "You cannot set itself as its combine_pre in Abstract_value::set_combine_pre!" << std::endl;
        exit(0);
    }
    combine_pre = _combine_pre;
}

Abstract_value_set_transfer *Abstract_value::get_value()
{
    return value;
}

std::vector<Abstract_value *>Abstract_value::get_combine_pres()
{
    return combine_pres;
}


/**
* helpers
*/
bool Abstract_value::equal(Abstract_value *_other)
{
    return value->equal(_other->get_value()) && (extend_pre == _other->get_extend_pre()) && (combine_pre == _other->get_combine_pre());
}

std::ostream &Abstract_value::print(std::ostream &_out)
{
    value->print(_out) << "\nextend_pre: ";
    if (extend_pre != 0)
    {
        extend_pre->print(_out);
    }
    else
    {
        _out << 0;
    }
    _out << " combine_pre: ";
    if (combine_pre != 0)
    {
        combine_pre->print(_out);
    }
    else
    {
        _out << 0;
    }

    return _out;
}

bool Abstract_value::isomorphic(Abstract_value *_other)
{
    if (!value->equal(_other->get_value()))
    {
        return false;
    }

    if (extend_pre == 0 && _other->get_extend_pre() == 0 && combine_pres.size() == 0 && _other->get_combine_pres().size() == 0)
    {
        return true;
    }

    if (extend_pre != 0 && _other->get_extend_pre() != 0 && combine_pres.size() == 0 && _other->get_combine_pres().size() == 0)
    {
        return extend_pre->isomorphic(_other->get_extend_pre());
    }

    if (extend_pre == 0 && _other->get_extend_pre() == 0 && combine_pres.size() == _other->get_combine_pres().size())
    {
        return combine_pre->isomorphic(_other->get_combine_pre());
    }

    if (extend_pre != 0 && _other->get_extend_pre() != 0 && combine_pre != 0 && _other->get_combine_pre() != 0)
    {
        return extend_pre->isomorphic(_other->get_extend_pre()) && combine_pre->isomorphic(_other->get_combine_pre());
    }

    return false;
}

/**
* helpers - debug only
*/
std::string Abstract_value::to_string()
{
    std::stringstream ss;

    ss << value->to_string() << " otimes " << extend_pre << " oplus " << combine_pre;

    return ss.str();
}

std::ostream &Abstract_value::print_dot(std::ostream &_out)
{
    _out << "\"" << this << "\" [label=\"[" << this->to_string() << "]\", color=lightblue,style=filled,shape=box]\n";

    if (extend_pre != 0)
    {
        _out << "\"" << this <<"\" -> \"" << extend_pre << "\" [label=extend_pre,color=black]\n";
        extend_pre->print_dot(_out);
    }
    if (combine_pre != 0)
    {
        _out << "\"" << this <<"\" -> \"" << combine_pre << "\" [label=combine_pre,color=black]\n";
        combine_pre->print_dot(_out);
    }
}


/**
* private methods
*/
Abstract_value::Abstract_value(Abstract_value_set_transfer *_value)
{
    COUNT++;
    value = _value;
    extend_pre = 0;
    combine_pre = 0;
}
