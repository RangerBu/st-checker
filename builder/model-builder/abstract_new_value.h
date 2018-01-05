#ifndef ABSTRACT_NEW_VALUE_H
#define ABSTRACT_NEW_VALUE_H

#include <vector>
#include <string>
#include <sstream>

#include "../../analyzer/transformer/value_set_transfer.h"


class Abstract_new_value
{
    /**
    * public methods
    */
public:
    Abstract_new_value(Value_set_transfer *);
    virtual ~Abstract_new_value();

    void insert_pre(Abstract_new_value *);
    void insert_post(Abstract_new_value *);

    /**
    * helper methods
    */
    bool equals(Abstract_new_value *);
    std::string format();

    /**
    * getters and setters
    */
    std::vector<Abstract_new_value *> get_pres();
    std::vector<Abstract_new_value *> get_posts();
    Value_set_transfer *get_transfer();
    std::string get_str_repr();

    /**
    * private attributes and methods
    */
private:
    Value_set_transfer *transfer;
    std::vector <Abstract_new_value *> pres;
    std::vector <Abstract_new_value *> posts;

    std::string str_repr;
};

#endif // ABSTRACT_NEW_VALUE_H
