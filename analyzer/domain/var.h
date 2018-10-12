#ifndef VAR_H
#define VAR_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


class Var
{
    /**
    * static attributes
    */
public:
    /*
    * string representation of variable types
    */
    static std::string TYPE_INT;
    static std::string TYPE_BOOL;
    static std::string TYPE_BYTE;

    /*
    * string representation of variable semantics
    */
    static std::string SEMANTICS_VAR;
    static std::string SEMANTICS_INPUT;
    static std::string SEMANTICS_OUTPUT;


    /**
    * public methods
    */
public:
    /*
    * constructor
    */
    Var(std::string, std::string, std::string);

    Var(Var *);

    /*
    * de-constructor
    */
    ~Var();


    /**
    * getters and setters
    */
    std::string get_str_name();

    std::string get_str_type();

    std::string get_str_semantics();

    std::string get_str_constant();

    void set_str_constant(std::string);


    /**
    * helpers
    */
    bool equal(Var *);

    std::ostream &print(std::ostream &);

    friend std::ostream &operator<<(std::ostream &, Var *);


    /**
    * helpers - debug only
    */
    std::string to_string();

    /**
    * private attributes
    */
private:
    /*
    * the string variable name
    */
    std::string str_name;

    /*
    * the string variable type
    */
    std::string str_type;

    /*
    * the string variable semantics
    */
    std::string str_semantics;

    /*
     * the initial constant of the variable
     */
    std::string str_constant;

};

#endif // VAR_H
