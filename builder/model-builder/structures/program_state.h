#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../../flow-graph-builder/node.h"
#include "../../../analyzer/domain/value_set.h"

class Program_state
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Program_state(Node *, Value_set *);

    /*
    * de-constructor
    */
    virtual ~Program_state();


    /**
    * getters and setters
    */
    Node *get_location();

    Value_set *get_value();


    /**
    * helpers
    */
    bool equal(Program_state *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    Node *location;

    Value_set *value;

};

#endif // PROGRAM_STATE_H
