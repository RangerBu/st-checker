#ifndef VAR_H
#define VAR_H

#include <string>
#include <iostream>
#include <sstream>


class Var{

    /**
    * static attributes and methods
    */
public:
    // variable types
    static const int TYPE_INT = 0; // 0
    static const int TYPE_BOOL = 1;// 1
    static const int TYPE_BYTE = 2;// 2

    // variable semantics
    static const int SEMANTIC_VAR = 0; // 0
    static const int SEMANTIC_INPUT = 1; //1
    static const int SEMANTIC_OUTPUT = 2; //2
    static const int SEMANTIC_IN_OUT = 3; //3
    static const int SEMANTIC_RETENTIVE = 4; //4
    static const int SEMANTIC_LOCATED = 5; //5
    static const int SEMANTIC_EXTERNAL = 6; //6
    static const int SEMANTIC_GLOBAL = 7; //7

    static int get_int_semantic(std::string);
    static int get_int_type(std::string);

    /**
    * public methods
    */
public:
    Var(std::string, int, int);
    virtual ~Var();

    /**
    * getters and setters
    */
    std::string get_str_name();
    int get_type();
    int get_semantic();

    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);
    bool equals(Var *);

    /**
    * private attributes and methods
    */
private:

    std::string str_name;
    int type;
    int semantic;







};

#endif // VAR_H
