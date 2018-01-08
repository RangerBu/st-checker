#ifndef VALUE_SET_H
#define VALUE_SET_H

#include <map>
#include <iostream>
#include <iomanip>

#include "../structures/abstract_data.h"
#include "../structures/bits_vector_1.hpp"
#include "../structures/bits_vector_8.hpp"
#include "../structures/strided_interval.h"
#include "var.h"

typedef Var* key;
typedef Abstract_data* value;

class Value_set
{
    /**
    * public methods
    */
public:
    Value_set(std::vector<key>);

    Value_set(int, key *);

    Value_set(Value_set *);

    virtual ~Value_set();


    /**
    * external visible methods
    */
    void set_var_value(key, value);

    int_value get_int_value_by(key);

    bool_value get_bool_value_by(key);

    byte_value get_byte_value_by(key);

    key contains_var(std::string);

    key contains_var(key);

    void insert_var(key);


    /**
    * operations
    */
    Value_set *op_union(Value_set *);


    /**
    * getters and setters
    */
    std::map<key, value> get_vars_map();

    std::vector<key> get_vars_list();


    /**
    * helpers
    */
    bool equal(Value_set *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes
    */
private:
    std::vector<key> vars_list;

    std::map<key, value> vars_map;

    std::map<key, int_value> int_vars_map;

    std::map<key, bool_value> bool_vars_map;

    std::map<key, byte_value> byte_vars_map;
};

#endif // VALUE_SET_H
