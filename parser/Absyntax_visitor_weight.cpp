#include "Absyntax_visitor_weight.h"
#include "ST_parser.h"

/**
* public methods
*/
Absyntax_visitor_weight::Absyntax_visitor_weight()
{
}
Absyntax_visitor_weight::Absyntax_visitor_weight(Abstract_transfer *_abstract_transfer)
{
    abstract_transfer = _abstract_transfer;
}
Absyntax_visitor_weight::~Absyntax_visitor_weight()
{
}

void *Absyntax_visitor_weight::visit(assignment_statement_c *_assignment)
{
    //SYM_REF2(assignment_statement_c, l_exp, r_exp)
//    abstract_transfer->set_left_var(ST_parser::parse(_assignment->l_exp));

    std::string str_r_exp_type = _assignment->r_exp->absyntax_cname();

    /* binary expression*/
    //SYM_REF2(add_expression_c, l_exp, r_exp, bool deprecated_operation;)
    if (str_r_exp_type.compare("add_expression_c") == 0)
    {
        add_expression_c *r_exp = (add_expression_c *)_assignment->r_exp;
//        abstract_transfer->set_op("+");
//        abstract_transfer->set_right_var1(ST_parser::parse(r_exp->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(r_exp->r_exp));


    }
    //SYM_REF2(sub_expression_c, l_exp, r_exp, bool deprecated_operation;)
    else if (str_r_exp_type.compare("sub_expression_c") == 0)
    {
        sub_expression_c *r_exp = (sub_expression_c *)_assignment->r_exp;
//        abstract_transfer->set_op("-");
//        abstract_transfer->set_right_var1(ST_parser::parse(r_exp->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(r_exp->r_exp));

    }
    /* unary expression */
    else
    {
        //SYM_TOKEN(integer_c)
        //SYM_REF2(boolean_literal_c, type, value)
        // variable
//        abstract_transfer->set_right_var1(ST_parser::parse(_assignment->r_exp));
    }

}
void *Absyntax_visitor_weight::visit(elseif_statement_c *_elseif)
{
    //SYM_REF2(elseif_statement_c, expression, statement_list)
    weight_helper(_elseif->expression);
}
void *Absyntax_visitor_weight::visit(if_statement_c *_if_statement)
{
    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    weight_helper(_if_statement->expression);
}


/**
* private helpers
*/
void Absyntax_visitor_weight::weight_helper(symbol_c *_expression)
{
    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    std::string str_expression_type = _expression->absyntax_cname();

    /* binary */
    if (str_expression_type.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op("<");

        lt_expression_c *lt_expression = (lt_expression_c *)_expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(lt_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(lt_expression->r_exp));


    }
    else if (str_expression_type.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op(">");

        gt_expression_c *gt_expression = (gt_expression_c *) _expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(gt_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(gt_expression->r_exp));
    }
    else if (str_expression_type.compare("le_expression_c") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op("<=");

        le_expression_c *le_expression = (le_expression_c *)_expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(le_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(le_expression->r_exp));

    }
    else if (str_expression_type.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op(">=");

        ge_expression_c *ge_expression = (ge_expression_c *) _expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(ge_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(ge_expression->r_exp));
    }
    else if (str_expression_type.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op("=");

        equ_expression_c *equ_expression = (equ_expression_c *) _expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(equ_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(equ_expression->r_exp));

    }
    else if (str_expression_type.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
//        abstract_transfer->set_op("<>");

        notequ_expression_c *notequ_expression = (notequ_expression_c *) _expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(notequ_expression->l_exp));
//        abstract_transfer->set_right_var2(ST_parser::parse(notequ_expression->r_exp));
    }
    /* unary */
    else if (str_expression_type.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
//        abstract_transfer->set_op("NOT");

        not_expression_c *not_expression = (not_expression_c *) _expression;
//        abstract_transfer->set_right_var1(ST_parser::parse(not_expression->exp));
    }
    /* variable */
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
//        abstract_transfer->set_right_var1(ST_parser::parse(_expression));
    }
}
