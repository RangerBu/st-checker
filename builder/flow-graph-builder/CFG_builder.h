//
// Created by zero on 1/18/18.
//

#ifndef ST_CHECKER_CFG_BUILDER_H
#define ST_CHECKER_CFG_BUILDER_H


#include <vector>
#include <string>

#include "cfg.h"
#include "../../parser/st_parser.h"
#include "../../analyzer/domain/var.h"

class CFG_builder{
    /**
    * static methods
    */
public:
    static CFG_builder *get_instance();


    /**
    * public methods
    */
public:
    /*
    * de-constructor
    */
    virtual ~CFG_builder();


    /**
    * external
    */
    CFG *create_CFG(ST_parser *);


    /**
    * private attributes and methods
    */
private:
    /*
    * make sure there only one instance of this class
    */
    CFG_builder();

    /*
    * the only one instance
    */
    static CFG_builder *builder;

};


#endif //ST_CHECKER_CFG_BUILDER_H
