//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_VARIABLE_H
#define VERIFY_ST_PROGRAMS_VARIABLE_H

#include <string>
#include <iostream>

class Variable
{
public:

    static std::string VARIABLE_TYPE_INT;

    static std::string VARIABLE_TYPE_BOOL;

    Variable(std::string _str_variable_name, std::string _str_variable_type);

    virtual ~Variable();

    bool equal(Variable *_other);

    /**
     * getters and setters
     */
    std::string get_str_variable_name();

    std::string get_str_variable_type();

    /**
     * helpers
     */
    friend std::ostream &operator<<(std::ostream &_out, Variable &_variable);

private:
    std::string str_variable_name;
    std::string str_variable_type;
};


#endif //VERIFY_ST_PROGRAMS_VARIABLE_H
