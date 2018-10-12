//
// Created by Samson on 2018/5/29.
//

#ifndef VERIFY_ST_PROGRAMS_PROGRAM_H
#define VERIFY_ST_PROGRAMS_PROGRAM_H

#include <iostream>
#include <string>

#include "pou.h"

class Program : public POU
{
public:
    Program(symbol_c *_symbol);

    virtual ~Program();

};


#endif //VERIFY_ST_PROGRAMS_PROGRAM_H
