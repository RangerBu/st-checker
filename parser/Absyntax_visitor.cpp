#include "Absyntax_visitor.h"
#include "../utils/utils.h"

string AbsyntaxVisitor::str_statement = "";

AbsyntaxVisitor::AbsyntaxVisitor()
{
}

AbsyntaxVisitor::~AbsyntaxVisitor()
{
    //dtor
}


string AbsyntaxVisitor::get_str_statement()
{
    return utils::trim(str_statement);
}
void AbsyntaxVisitor::init_str_statement()
{
    str_statement = "";
}


/********************/
/* B 3.2 Statements */
/********************/
//SYM_LIST(statement_list_c)


/*********************************/
/* B 3.2.1 Assignment Statements */
/*********************************/
//SYM_REF2(assignment_statement_c, l_exp, r_exp)
void *AbsyntaxVisitor::visit(assignment_statement_c *symbol)
{
    str_statement = "";
    symbol->l_exp->accept(*this);
    str_statement += " := ";
    symbol->r_exp->accept(*this);
    return NULL;
}

/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/

/*  RETURN */
//SYM_REF0(return_statement_c)
void *AbsyntaxVisitor::visit(return_statement_c *symbol)
{
    str_statement = "RETURN";
}

/* fb_name '(' [param_assignment_list] ')' */
/*    formal_param_list -> may be NULL ! */
/* nonformal_param_list -> may be NULL ! */
/* NOTE: The parameter 'called_fb_declaration'is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
//SYM_REF3(fb_invocation_c, fb_name, formal_param_list, nonformal_param_list, symbol_c *called_fb_declaration;)
void *AbsyntaxVisitor::visit(fb_invocation_c *symbol)
{
    str_statement = "FB_INVOCATION";
}

/* helper symbol for fb_invocation */
/* param_assignment_list ',' param_assignment */
//SYM_LIST(param_assignment_list_c)
void *AbsyntaxVisitor::visit(param_assignment_list_c *symbol)
{

}

/*  variable_name ASSIGN expression */
//SYM_REF2(input_variable_param_assignment_c, variable_name, expression)
void *AbsyntaxVisitor::visit(input_variable_param_assignment_c *symbol)
{

}

/* [NOT] variable_name '=>' variable */
//SYM_REF3(output_variable_param_assignment_c, not_param, variable_name, variable)
void *AbsyntaxVisitor::visit(output_variable_param_assignment_c *symbol)
{

}

/* helper CLASS for output_variable_param_assignment */
//SYM_REF0(not_paramassign_c)
void *AbsyntaxVisitor::visit(not_paramassign_c *symbol)
{

}


/********************************/
/* B 3.2.3 Selection Statements */
/********************************/
/* IF expression THEN statement_list elseif_statement_list ELSE statement_list END_IF */
//SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
void *AbsyntaxVisitor::visit(if_statement_c *symbol)
{
    str_statement = "IF ";
    symbol->expression->accept(*this);
    str_statement += " THEN";
}

/* helper symbol for if_statement */
//SYM_LIST(elseif_statement_list_c)
void *AbsyntaxVisitor::visit(elseif_statement_list_c *symbol)
{

}

/* helper symbol for elseif_statement_list */
/* ELSIF expression THEN statement_list    */
//SYM_REF2(elseif_statement_c, expression, statement_list)
void *AbsyntaxVisitor::visit(elseif_statement_c *symbol)
{
    str_statement = "ELSIF ";
    symbol->expression->accept(*this);
    str_statement += " THEN";
}

/* CASE expression OF case_element_list ELSE statement_list END_CASE */
//SYM_REF3(case_statement_c, expression, case_element_list, statement_list)
void *AbsyntaxVisitor::visit(case_statement_c *symbol)
{
}

/* helper symbol for case_statement */
//SYM_LIST(case_element_list_c)
void *AbsyntaxVisitor::visit(case_element_list_c *symbol)
{

}

/*  case_list ':' statement_list */
//SYM_REF2(case_element_c, case_list, statement_list)
void *AbsyntaxVisitor::visit(case_element_c *symbol)
{
}

//SYM_LIST(case_list_c)
void *AbsyntaxVisitor::visit(case_list_c *symbol)
{
}


/********************************/
/* B 3.2.4 Iteration Statements */
/********************************/
/*  FOR control_variable ASSIGN expression TO expression [BY expression] DO statement_list END_FOR */
//SYM_REF5(for_statement_c, control_variable, beg_expression, end_expression, by_expression, statement_list)
void *AbsyntaxVisitor::visit(for_statement_c *symbol)
{}

/*  WHILE expression DO statement_list END_WHILE */
//SYM_REF2(while_statement_c, expression, statement_list)
void *AbsyntaxVisitor::visit(while_statement_c *symbol)
{
}

/*  REPEAT statement_list UNTIL expression END_REPEAT */
//SYM_REF2(repeat_statement_c, statement_list, expression)
void *AbsyntaxVisitor::visit(repeat_statement_c *symbol)
{
}

/*  EXIT */
//SYM_REF0(exit_statement_c)
void *AbsyntaxVisitor::visit(exit_statement_c *symbol)
{

}
