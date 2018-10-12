//
// Created by Samson on 2018/5/31.
//

#include "../utils.h"
#include "symbol_to_string_visitor.h"

std::string Symbol_to_string_visitor::parse(symbol_c *_symbol)
{
    return  (char *)visitor->visit(_symbol);
}

symbol_c* Symbol_to_string_visitor::has_invocation(symbol_c *_symbol)
{
    visitor->invocation = 0;

    visitor->visit(_symbol);

    return visitor->invocation;
}

Symbol_to_string_visitor::~Symbol_to_string_visitor()
{
}

void *Symbol_to_string_visitor::visit(symbol_c *_symbol)
{
    return (char *)_symbol->accept(*this);
}

void *Symbol_to_string_visitor::visit(identifier_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(derived_datatype_identifier_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(poutype_identifier_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(ref_value_null_literal_c *_symbol)
{
    std::string str_ret = "NULL";

    return (void *)str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(real_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(integer_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(binary_integer_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(octal_integer_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(hex_integer_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(neg_real_c *_symbol)
{
    std::string str_ret = "-";

    return utils::append((char *)str_ret.c_str(), (char *)_symbol->exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(neg_integer_c *_symbol)
{
    std::string str_ret = "-";

    return utils::append((char *)str_ret.c_str(), (char *)_symbol->exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(integer_literal_c *_symbol)
{
    return _symbol->value->accept(*this);
}

void *Symbol_to_string_visitor::visit(real_literal_c *_symbol)
{
    return _symbol->value->accept(*this);
}

void *Symbol_to_string_visitor::visit(bit_string_literal_c *_symbol)
{
    return _symbol->value->accept(*this);
}

void *Symbol_to_string_visitor::visit(boolean_literal_c *_symbol)
{
    return _symbol->value->accept(*this);
}

void *Symbol_to_string_visitor::visit(boolean_true_c *_symbol)
{
    std::string str_ret = "TRUE";

    return (void *)str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(boolean_false_c *_symbol)
{
    std::string str_ret = "FALSE";

    return (void *)str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(double_byte_character_string_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(single_byte_character_string_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(bool_type_name_c *_symbol)
{
    std::string str_ret = "BOOL";

    return (void *)str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(int_type_name_c *_symbol)
{
    std::string str_ret = "INT";

    return (void *)str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(symbolic_variable_c *_symbol)
{
    return _symbol->var_name->accept(*this);
}

void *Symbol_to_string_visitor::visit(direct_variable_c *_symbol)
{
    return (void *)_symbol->value;
}

void *Symbol_to_string_visitor::visit(or_expression_c *_symbol)
{
    std::string str_op = " OR ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(xor_expression_c *_symbol)
{
    std::string str_op = " XOR ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(and_expression_c *_symbol)
{
    std::string str_op = " AND ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(equ_expression_c *_symbol)
{
    std::string str_op = " = ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(notequ_expression_c *_symbol)
{
    std::string str_op = " <> ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(lt_expression_c *_symbol)
{
    std::string str_op = " < ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(gt_expression_c *_symbol)
{
    std::string str_op = " > ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(le_expression_c *_symbol)
{
    std::string str_op = " <= ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(ge_expression_c *_symbol)
{
    std::string str_op = " >= ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(add_expression_c *_symbol)
{
    std::string str_op = " + ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(sub_expression_c *_symbol)
{
    std::string str_op = " - ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}


void *Symbol_to_string_visitor::visit(mul_expression_c *_symbol)
{
    std::string str_op = " * ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(div_expression_c *_symbol)
{
    std::string str_op = " / ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(mod_expression_c *_symbol)
{
    std::string str_op = " MOD ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(power_expression_c *_symbol)
{
    std::string str_op = " POW ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(neg_expression_c *_symbol)
{
    std::string str_ret = "-";

    return utils::append((char *)str_ret.c_str(), (char *)_symbol->exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(not_expression_c *_symbol)
{
    std::string str_ret = "NOT ";

    return utils::append((char *)str_ret.c_str(), (char *)_symbol->exp->accept(*this));
}

//SYM_REF3(function_invocation_c, function_name, formal_param_list, nonformal_param_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)
void *Symbol_to_string_visitor::visit(function_invocation_c *_symbol)
{

    visitor->invocation = _symbol;

    char *ret_ch = utils::append((char *)_symbol->function_name->accept(*this), (char *)"(");

    ret_ch = utils::append(ret_ch, (char *) _symbol->formal_param_list->accept(*this));

    return utils::append(ret_ch, (char *)")");
}

void *Symbol_to_string_visitor::visit(assignment_statement_c *_symbol)
{
    std::string str_op = " := ";
    char *ret_ch = utils::append((char *)_symbol->l_exp->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->r_exp->accept(*this));
}

void *Symbol_to_string_visitor::visit(return_statement_c *_symbol)
{
    std::string str_ret = "RETURN";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(fb_invocation_c *_symbol)
{
    std::string str_ret = "FUNCTION_BLOCK";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(param_assignment_list_c *_symbol)
{
    char *ret_ch = (char *)"";

    for (int i = 0; i < _symbol->n; ++i)
    {
        ret_ch = utils::append(ret_ch, (char *)_symbol->get_element(i)->accept(*this));
        if (i < _symbol->n - 1)
        {
            ret_ch = utils::append(ret_ch, (char *)", ");
        }
    }

    return ret_ch;
}

void *Symbol_to_string_visitor::visit(input_variable_param_assignment_c *_symbol)
{

    std::string str_op = " := ";
    char *ret_ch = utils::append((char *)_symbol->variable_name->accept(*this), (char *)str_op.c_str());

    return utils::append(ret_ch, (char *)_symbol->expression->accept(*this));
}

void *Symbol_to_string_visitor::visit(output_variable_param_assignment_c *_symbol)
{
    char *ret_ch = utils::append((char *)_symbol->variable_name->accept(*this), (char *)"=>");
    ret_ch = utils::append(ret_ch, (char *)_symbol->variable->accept(*this));

    return ret_ch;
}

void *Symbol_to_string_visitor::visit(not_paramassign_c *_symbol)
{
    std::string str_ret = "not_paramassign";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(if_statement_c *_symbol)
{
    std::string str_keyword = "IF ";
    char *ret_ch = utils::append((char *)str_keyword.c_str(), (char *)_symbol->expression->accept(*this));
    str_keyword = " THEN";

    return utils::append(ret_ch, (char *)str_keyword.c_str());
}

void *Symbol_to_string_visitor::visit(elseif_statement_c *_symbol)
{
    std::string str_keyword = "ELSIF ";
    char *ret_ch = utils::append((char *)str_keyword.c_str(), (char *)_symbol->expression->accept(*this));
    str_keyword = " THEN";

    return utils::append(ret_ch, (char *)str_keyword.c_str());
}

void *Symbol_to_string_visitor::visit(case_statement_c *_symbol)
{
    std::string str_ret = "case_statement";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(case_element_list_c *_symbol)
{
    std::string str_ret = "case_element_list";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(case_element_c *_symbol)
{
    std::string str_ret = "case_element";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(case_list_c *_symbol)
{
    std::string str_ret = "case_list";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(for_statement_c *_symbol)
{
    std::string str_ret = "for_statement";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(while_statement_c *_symbol)
{
    std::string str_ret = "while_statement";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(repeat_statement_c *_symbol)
{
    std::string str_ret = "repeat_statement";

    return (void *) str_ret.c_str();
}

void *Symbol_to_string_visitor::visit(exit_statement_c *_symbol)
{
    std::string str_ret = "exit";

    return (void *) str_ret.c_str();
}

Symbol_to_string_visitor *Symbol_to_string_visitor::visitor = new Symbol_to_string_visitor();

Symbol_to_string_visitor::Symbol_to_string_visitor()
{

}