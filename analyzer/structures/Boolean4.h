#ifndef BOOL4_H
#define BOOL4_H

#include <string>
#include <sstream>
#include <iostream>

class Boolean4
{
    /**
    * static attributes and methods
    */
public:
    static Boolean4 *TRUE;
    static Boolean4 *FALSE;
    static Boolean4 *MAYBE;
    static Boolean4 *BOT;

    /**
    * public methods
    */
public:
    Boolean4(int);
    virtual ~Boolean4();

    Boolean4 *And(Boolean4 *);
    Boolean4 *Or(Boolean4 *);
    Boolean4 *Not();
    Boolean4 *Xor(Boolean4 *);
    Boolean4 *Join(Boolean4 *);

    /**
    * getters and setters
    */
    int get_value();
    void set_value(int );

    /**
    * helpers
    */
    std::string format();
    void print(std::ostream &);

    bool equals(Boolean4 *);

    /**
    * private attributes
    */
private:
    int value;


};

#endif // BOOL4_H
