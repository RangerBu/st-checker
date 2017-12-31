#ifndef CFG_BUILDER_H
#define CFG_BUILDER_H

#include <vector>
#include <string>

#include "CFG.h"
#include "../../parser/ST_parser.h"
#include "../../analyzer/domain/Var.h"

class CFG_builder{

    /**
    * public methods
    */
public:
    CFG_builder();
    CFG_builder(ST_parser *);
    virtual ~CFG_builder();

    CFG *create();

    /**
    * getters and setters
    */
    std::vector<Var *> get_vars();

    /**
    * private attributes and methods
    */
private:
    ST_parser *parser;
    std::vector<Var *> vars;

    void init_vars();


};

#endif // CFG_BUILDER_H
