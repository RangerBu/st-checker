//
// Created by Samson on 2018/5/31.
//

#ifndef VERIFY_ST_PROGRAMS_ABSTRACT_SYNTAX_VISITOR_H
#define VERIFY_ST_PROGRAMS_ABSTRACT_SYNTAX_VISITOR_H

#include <string>
#include <iostream>

#include "absyntax/visitor.hh"

class Symbol_to_string_visitor : public iterator_visitor_c
{
public:
    static std::string parse(symbol_c *_symbol);

    static symbol_c *has_invocation(symbol_c *_symbol);

    virtual ~Symbol_to_string_visitor();

    void *visit(symbol_c *_symbol);

    //SYM_TOKEN(identifier_c)
    void *visit(identifier_c *_symbol);

    //SYM_TOKEN(derived_datatype_identifier_c)
    void *visit(derived_datatype_identifier_c *_symbol);

    //SYM_TOKEN(poutype_identifier_c)
    void *visit(poutype_identifier_c *_symbol);

    //SYM_REF0(ref_value_null_literal_c)
    void *visit(ref_value_null_literal_c *_symbol);

    //SYM_TOKEN(real_c)
    void *visit(real_c *_symbol);

    //SYM_TOKEN(integer_c)
    void *visit(integer_c *_symbol);

    //SYM_TOKEN(binary_integer_c)
    void *visit(binary_integer_c *_symbol);

    //SYM_TOKEN(octal_integer_c)
    void *visit(octal_integer_c *_symbol);

    //SYM_TOKEN(hex_integer_c)
    void *visit(hex_integer_c *_symbol);

    //SYM_REF1(neg_real_c, exp)
    void *visit(neg_real_c *_symbol);

    //SYM_REF1(neg_integer_c, exp)
    void *visit(neg_integer_c *_symbol);

    //SYM_REF2(integer_literal_c, type, value)
    void *visit(integer_literal_c *_symbol);

    //SYM_REF2(real_literal_c, type, value)
    void *visit(real_literal_c *_symbol);

    //SYM_REF2(bit_string_literal_c, type, value)
    void *visit(bit_string_literal_c *_symbol);

    //SYM_REF2(boolean_literal_c, type, value)
    void *visit(boolean_literal_c *_symbol);

    //SYM_REF0(boolean_true_c)
    void *visit(boolean_true_c *_symbol);

    //SYM_REF0(boolean_false_c)
    void *visit(boolean_false_c *_symbol);

    //SYM_TOKEN(double_byte_character_string_c)
    void *visit(double_byte_character_string_c *_symbol);

    //SYM_TOKEN(single_byte_character_string_c)
    void *visit(single_byte_character_string_c *_symbol);

    //SYM_REF0(bool_type_name_c)
    void *visit(bool_type_name_c *_symbol);

    //SYM_REF0(int_type_name_c)
    void *visit(int_type_name_c *_symbol);

    //SYM_REF1(symbolic_variable_c, var_name)
    void *visit(symbolic_variable_c *_symbol);

    //SYM_TOKEN(direct_variable_c)
    void *visit(direct_variable_c *_symbol);

    //SYM_REF1(  ref_expression_c, exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard.  REF() -> returns address of the varible! */
    //SYM_REF1(deref_expression_c, exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard. DREF() -> dereferences an address!        */
    //SYM_REF1(deref_operator_c,   exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard.    ^   -> dereferences an address!        */
    //SYM_REF2( or_expression_c, l_exp, r_exp)
    void *visit(or_expression_c *_symbol);

    //SYM_REF2(xor_expression_c, l_exp, r_exp)
    void *visit(xor_expression_c *_symbol);

    //SYM_REF2(and_expression_c, l_exp, r_exp)
    void *visit(and_expression_c *_symbol);

    //SYM_REF2(equ_expression_c, l_exp, r_exp)
    void *visit(equ_expression_c *_symbol);

    //SYM_REF2(notequ_expression_c, l_exp, r_exp)
    void *visit(notequ_expression_c *_symbol);

    //SYM_REF2( lt_expression_c, l_exp, r_exp)
    void *visit(lt_expression_c *_symbol);

    //SYM_REF2( gt_expression_c, l_exp, r_exp)
    void *visit(gt_expression_c *_symbol);

    //SYM_REF2( le_expression_c, l_exp, r_exp)
    void *visit(le_expression_c *_symbol);

    //SYM_REF2( ge_expression_c, l_exp, r_exp)
    void *visit(ge_expression_c *_symbol);

    //SYM_REF2(add_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(add_expression_c *_symbol);

    //SYM_REF2(sub_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(sub_expression_c *_symbol);

    //SYM_REF2(mul_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(mul_expression_c *_symbol);

    //SYM_REF2(div_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(div_expression_c *_symbol);

    //SYM_REF2(mod_expression_c, l_exp, r_exp)
    void *visit(mod_expression_c *_symbol);

    //SYM_REF2(power_expression_c, l_exp, r_exp)
    void *visit(power_expression_c *_symbol);

    //SYM_REF1(neg_expression_c, exp)
    void *visit(neg_expression_c *_symbol);


    //SYM_REF1(not_expression_c, exp)
    void *visit(not_expression_c *_symbol);

    //SYM_REF3(function_invocation_c, function_name, formal_param_list, nonformal_param_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)
    void *visit(function_invocation_c *_symbol);

    //SYM_REF2(assignment_statement_c, l_exp, r_exp)
    void *visit(assignment_statement_c *_symbol);

    /*  RETURN */
    //SYM_REF0(return_statement_c)
    void *visit(return_statement_c *_symbol);

    /* fb_name '(' [param_assignment_list] ')' */
    /*    formal_param_list -> may be NULL ! */
    /* nonformal_param_list -> may be NULL ! */
    /* NOTE: The parameter 'called_fb_declaration'is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
    //SYM_REF3(fb_invocation_c, fb_name, formal_param_list, nonformal_param_list, symbol_c *called_fb_declaration;)
    void *visit(fb_invocation_c *_symbol);

    /* helper symbol for fb_invocation */
    /* param_assignment_list ',' param_assignment */
    //SYM_LIST(param_assignment_list_c)
    void *visit(param_assignment_list_c *_symbol);

    /*  variable_name ASSIGN expression */
    //SYM_REF2(input_variable_param_assignment_c, variable_name, expression)
    void *visit(input_variable_param_assignment_c *_symbol);

    /* [NOT] variable_name '=>' variable */
    //SYM_REF3(output_variable_param_assignment_c, not_param, variable_name, variable)
    void *visit(output_variable_param_assignment_c *_symbol);

    /* helper CLASS for output_variable_param_assignment */
    //SYM_REF0(not_paramassign_c)
    void *visit(not_paramassign_c *_symbol);

    /* IF expression THEN statement_list elseif_statement_list ELSE statement_list END_IF */
    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    void *visit(if_statement_c *_symbol);

    /* helper symbol for elseif_statement_list */
    /* ELSIF expression THEN statement_list    */
    //SYM_REF2(elseif_statement_c, expression, statement_list)
    void *visit(elseif_statement_c *_symbol);

    /* CASE expression OF case_element_list ELSE statement_list END_CASE */
    //SYM_REF3(case_statement_c, expression, case_element_list, statement_list)
    void *visit(case_statement_c *_symbol);

    /* helper symbol for case_statement */
    //SYM_LIST(case_element_list_c)
    void *visit(case_element_list_c *_symbol);

    /*  case_list ':' statement_list */
    //SYM_REF2(case_element_c, case_list, statement_list)
    void *visit(case_element_c *_symbol);

    //SYM_LIST(case_list_c)
    void *visit(case_list_c *_symbol);

    //SYM_REF5(for_statement_c, control_variable, beg_expression, end_expression, by_expression, statement_list)
    void *visit(for_statement_c *_symbol);

    /*  WHILE expression DO statement_list END_WHILE */
    //SYM_REF2(while_statement_c, expression, statement_list)
    void *visit(while_statement_c *_symbol);

    /*  REPEAT statement_list UNTIL expression END_REPEAT */
    //SYM_REF2(repeat_statement_c, statement_list, expression)
    void *visit(repeat_statement_c *_symbol);

    /*  EXIT */
    //SYM_REF0(exit_statement_c)
    void *visit(exit_statement_c *_symbol);

private:
    static Symbol_to_string_visitor *visitor;

    Symbol_to_string_visitor();

    symbol_c *invocation;
};

#endif //VERIFY_ST_PROGRAMS_ABSTRACT_SYNTAX_VISITOR_H
