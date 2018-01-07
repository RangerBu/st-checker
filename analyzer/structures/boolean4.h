#ifndef BOOL4_H
#define BOOL4_H

#include "abstract_data.h"

class Boolean4 : public Abstract_data
{
    /**
    * static methods
    */
public:
    /*
    * get an instance using an int value, false if the value is 0, true if the value greater than 0
    */
    static Boolean4 *get_instance(int);

    /*
    * get an instance using boolean value
    */
    static Boolean4 *get_instance(bool);

    /*
    * get top instance
    */
    static Boolean4 *get_top();

    /*
    * get bot instance
    */
    static Boolean4 *get_bot();

    /*
    * get false instance
    */
    static Boolean4 *get_false();

    /*
    * get true instance
    */
    static Boolean4 *get_true();


    /**
    * public methods
    */
    /*
    * de-constructor
    */
    virtual ~Boolean4();

    /**
    * operations
    */
    Boolean4 *op_and(Boolean4 *);

    Boolean4 *op_or(Boolean4 *);

    Boolean4 *op_not();

    Boolean4 *op_xor(Boolean4 *);

    Boolean4 *op_union(Boolean4 *);

    /**
    * inherited methods (helpers)
    */
    bool equal(Abstract_data *);

    std::ostream &print(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * static private attributes and methods
    */
private:
    /*
    * top instance
    */
    static Boolean4 *ELEM_TOP;

    /*
    * bot instance
    */
    static Boolean4 *ELEM_BOT;

    /*
    * false instance
    */
    static Boolean4 *ELEM_FALSE;

    /*
    * true instance
    */
    static Boolean4 *ELEM_TRUE;


    /*
    * constructor
    */
    Boolean4();

};

#endif // BOOL4_H
