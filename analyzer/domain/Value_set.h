#ifndef VALUE_SET_H
#define VALUE_SET_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "Var.h"
#include "../structures/Bits_vector_1.h"
#include "../structures/Bits_vector_8.h"
#include "../structures/Strided_interval.h"

typedef Var* key;
typedef Bits_vector_1* bool_value;
typedef Bits_vector_8* byte_value;
typedef Strided_interval* int_value;

class Value_set{

public:
    Value_set();
    Value_set(std::vector<key>);
    Value_set(Value_set *);
    virtual ~Value_set();


public:
    void insert_var(key);
    void insert_bool_var(key, bool_value);
    void insert_byte_var(key, byte_value);
    void insert_int_var(key, int_value);

    void update_bool_var(key, bool_value);
    void update_byte_var(key, byte_value);
    void update_int_var(key, int_value);

    bool_value get_bool_value(key);
    byte_value get_byte_value(key);
    int_value get_int_value(key);

    Value_set *Union(Value_set *);

    key contains_var(std::string);
    key contains_var(key);

    /**
    * getters and setters
    */
    std::map<key, bool_value> get_bool_vars();
    std::map<key, byte_value> get_byte_vars();
    std::map<key, int_value> get_int_vars();

    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);
    bool equals(Value_set *);


private:
    /**
    * private attributes
    */
    std::map<key, bool_value> bool_vars;
    std::map<key, byte_value> byte_vars;
    std::map<key, int_value> int_vars;

    std::vector<key> vars_list;

    /**
    * private methods
    */
    bool is_top();
    bool is_bot();
};

#endif // VALUE_SET_H
