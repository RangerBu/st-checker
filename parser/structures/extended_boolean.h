//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_EXTENDED_BOOLEAN_H
#define VERIFY_ST_PROGRAMS_EXTENDED_BOOLEAN_H

#include "abstract_value.h"

class Extended_boolean : public Abstract_value
{
public:
    static Extended_boolean *FALSE;

    static Extended_boolean *TRUE;

    static Extended_boolean *TOP;

    virtual ~Extended_boolean();

    Abstract_value *get_top();

    bool equal(Abstract_value *_other);

private:
    Extended_boolean(std::string _str_value);
};


#endif //VERIFY_ST_PROGRAMS_EXTENDED_BOOLEAN_H
