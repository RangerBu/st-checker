#ifndef ABSTRACT_DATA_H
#define ABSTRACT_DATA_H

#include <iostream>

class Abstract_data
{
    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Abstract_data();

    /*
    * de-constructor
    */
    ~Abstract_data();


    /**
    * methods should be inherited
    */
    /**
    * helpers
    */
    virtual bool equal(Abstract_data *)=0;

    virtual std::ostream &print(std::ostream &)=0;

    friend std::ostream &operator<<(std::ostream &, Abstract_data *);

};

#endif // ABSTRACT_DATA_H
