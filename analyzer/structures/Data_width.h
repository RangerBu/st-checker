#ifndef DATA_WIDTH_H
#define DATA_WIDTH_H

#include <string>
#include <sstream>
#include <iostream>

class Data_width
{
    /**
    * public static methods
    */
public:
    static Data_width *get_instance(int);
    static Data_width *maximum(Data_width *, Data_width *);

    /**
    * public methods
    */
public:
    virtual ~Data_width();

    int effective_value(int);
    int compare_to(Data_width *);


    /**
    * getters and setters
    */
    int get_width();
    int get_maximum_value();
    int get_minimum_value();

    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);

    /**
    * private attributes and methods
    */
private:
    int width;
    int maximum_value;
    int minimum_value;

    Data_width(int);



};

#endif // DATA_WIDTH_H
