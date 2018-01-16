#include "program_state.h"

/**
* public methods
*/
/*
* constructor
*/
Program_state::Program_state(Node *_location, Value_set *_value)
{
    location = _location;
    value = _value;
}

/*
* de-constructor
*/
Program_state::~Program_state()
{

}


/**
* getters and setters
*/
Node *Program_state::get_location()
{
    return location;
}

Value_set *Program_state::get_value()
{
    return value;
}


/**
* helpers
*/
bool Program_state::equal(Program_state *_other)
{
    return location->equal(_other->get_location()) && value->equal(_other->get_value());
}

std::ostream& Program_state::print(std::ostream &_out)
{
    _out << "<" << location->get_str_node() << ", \n";
    return value->print(_out) << ">";
}


/**
* helpers - debug only
*/
std::string Program_state::to_string()
{
    std::stringstream ss;
    ss << "<" << location->get_str_node() << ", " << value << ">";
    return ss.str();
}
