#ifndef ABSYNTAX_VISITOR_WEIGHT_H
#define ABSYNTAX_VISITOR_WEIGHT_H

#include <string>
#include <iostream>

#include "absyntax/visitor.hh"

#include "ST_parser.h"
#include "../../analyzer/domain/Var.h"
#include "../../analyzer/transformer/Abstract_transfer.h"

class Absyntax_visitor_weight : public iterator_visitor_c{

    /**
    * public methods
    */
public:
    Absyntax_visitor_weight();
    Absyntax_visitor_weight(Abstract_transfer *);
    virtual ~Absyntax_visitor_weight();

    void *visit(assignment_statement_c *);
    void *visit(if_statement_c *);
    void *visit(elseif_statement_c *);

private:
    Abstract_transfer *abstract_transfer;

    /**
    * private helpers
    */
    void weight_helper(symbol_c *);

};

#endif // ABSYNTAX_VISITOR_WEIGHT_H
