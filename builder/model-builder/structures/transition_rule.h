#ifndef TRANSITION_RULE_H
#define TRANSITION_RULE_H

#include "program_state.h"

class Transition_rule
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Transition_rule(Program_state *, Program_state *);

    /*
    * de-constructor
    */
    virtual ~Transition_rule();


    /**
    * getters and setters
    */
    Program_state *get_left_state();

    Program_state *get_right_state();


    /**
    * helpers
    */
    bool equal(Transition_rule *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    /*
    * the left hand of a transition rule
    */
    Program_state *left_state;

    /*
    * the right hand of a transition rule
    */
    Program_state *right_state;

};

#endif // TRANSITION_RULE_H
