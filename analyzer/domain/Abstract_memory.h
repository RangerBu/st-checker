#ifndef ABSTRACT_MEMORY_H
#define ABSTRACT_MEMORY_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Var.h"
#include "Value_set.h"

class Abstract_memory{



    /**
    * public methods
    */
public:
    Abstract_memory();
    Abstract_memory(std::vector<Var *>);
    virtual ~Abstract_memory();

    void set_value(Var *, Value_set *);
    Value_set *get_value(Var *);

    /**
    * getters and setters
    */
    std::vector<Var *> &get_vars();
    std::map<std::string, Value_set *> &get_values();

    /**
    * helpers
    */
    // (x:vs_x, y:vs_y, ...)
    std::string format();
    void print(std::ostream &);

    /**
    * private attributes and methods
    */
private:
    std::vector<Var *> vars;
    std::map<std::string, Value_set *> values;

    void init_memory();

};

#endif // ABSTRACT_MEMORY_H
