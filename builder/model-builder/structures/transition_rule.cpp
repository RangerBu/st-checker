#include "transition_rule.h"

/**
* public methods
*/
/*
* constructor
*/
Transition_rule::Transition_rule(Program_state *_left_state, Program_state *_right_state)
{
    left_state = _left_state;
    right_state = _right_state;
}

/*
* de-constructor
*/
Transition_rule::~Transition_rule()
{

}


/**
* getters and setters
*/
Program_state *Transition_rule::get_left_state()
{
    return left_state;
}

Program_state *Transition_rule::get_right_state()
{
    return right_state;
}


/**
* helpers
*/
bool Transition_rule::equal(Transition_rule *_other)
{
    return left_state->equal(_other->get_left_state()) && right_state->equal(_other->get_right_state());
}

std::ostream &Transition_rule::print(std::ostream &_out)
{
    left_state->print(_out);
    _out << " ----> ";
    right_state->print(_out);
    return _out;
}


/**
* helpers - debug only
*/
std::string Transition_rule::to_string()
{
    std::stringstream ss;
    ss << left_state->to_string() << " -----> " << right_state->to_string();
    return ss.str();
}
