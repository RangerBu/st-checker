#ifndef ABSTRACT_VALUE_H
#define ABSTRACT_VALUE_H

#include <set>
#include <sstream>

#include "../../../analyzer/transformer/value_set_transfer.h"

class Abstract_value
{
    /**
    * public static attributes and methods
    */
public:
    /*
    * count the number of objects created
    */
    static int COUNT;

    static Abstract_value *get_instance(Abstract_value_set_transfer *);

    static Abstract_value *get_instance(Abstract_value *);


    /**
    * public methods
    */
    virtual ~Abstract_value();


    /**
    * external visible methods
    */
    Value_set *op_transform(Value_set *);

    /**
    * getters and setters
    */
    Abstract_value *get_extend_pre();

    void set_extend_pre(Abstract_value *);

    Abstract_value *get_combine_pre();

    void set_combine_pre(Abstract_value *);

    Abstract_value_set_transfer *get_value();


    /**
    * helpers
    */
    bool equal(Abstract_value *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();

    std::ostream &print_dot(std::ostream &);


    /**
    * private attributes and methods
    */
private:
    Abstract_value *extend_pre;

    Abstract_value *combine_pre;

    Abstract_value_set_transfer *value;

    /*
    * constructor
    */
    Abstract_value(Abstract_value_set_transfer *);


    /**
    * private helpers - attributes and methods
    */
    std::set<Abstract_value_set_transfer *> transfers_pool;

    bool in_pool(Abstract_value_set_transfer *);



};

#endif // ABSTRACT_VALUE_H
