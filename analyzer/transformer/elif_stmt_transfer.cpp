#include "elif_stmt_transfer.h"
#include "../../parser/ST_parser.h"

Elif_stmt_transfer::Elif_stmt_transfer(symbol_c *_elif_statement)
{
    statement = _elif_statement;

    std::string str_stmt_name = _elif_statement->absyntax_cname();
    std::string str_expression;
    symbol_c *expression;

    if (str_stmt_name.compare("elseif_statement_c") == 0)
    {
        //SYM_REF2(elseif_statement_c, expression, statement_list)
        expression = ((elseif_statement_c *)statement)->expression;
        str_expression = expression->absyntax_cname();

    }
    else
    {
        //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
        expression = ((if_statement_c *)statement)->expression;
        str_expression = expression->absyntax_cname();
    }

    if (str_expression.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
        lt_expression_c *lt_expression = (lt_expression_c *)expression;

        op = ">=";
        str_left_var = ST_parser::parse(lt_expression->l_exp);
        str_right_var = ST_parser::parse(lt_expression->r_exp);
    }
    else if (str_expression.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
        gt_expression_c *gt_expression = (gt_expression_c *) expression;

        op = "<=";
        str_left_var = ST_parser::parse(gt_expression->l_exp);
        str_right_var = ST_parser::parse(gt_expression->r_exp);
    }
    else if (str_expression.compare("le_expression_c") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
        le_expression_c *le_expression = (le_expression_c *) expression;

        op = ">";
        str_left_var = ST_parser::parse(le_expression->l_exp);
        str_right_var = ST_parser::parse(le_expression->r_exp);
    }
    else if (str_expression.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
        ge_expression_c *ge_expression = (ge_expression_c *) expression;

        op = "<";
        str_left_var = ST_parser::parse(ge_expression->l_exp);
        str_right_var = ST_parser::parse(ge_expression->r_exp);
    }
    else if (str_expression.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
        equ_expression_c *equ_expression = (equ_expression_c *) expression;

        op = "<>";
        str_left_var = ST_parser::parse(equ_expression->l_exp);
        str_right_var = ST_parser::parse(equ_expression->r_exp);
    }
    else if (str_expression.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
        notequ_expression_c *notequ_expression = (notequ_expression_c *) expression;

        op = "=";
        str_left_var = ST_parser::parse(notequ_expression->l_exp);
        str_right_var = ST_parser::parse(notequ_expression->r_exp);
    }
    else if (str_expression.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
        not_expression_c *not_expression = (not_expression_c *) expression;

        op = "";
        str_left_var = ST_parser::parse(not_expression->exp);
        str_right_var = "";

    }
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
        op = "NOT";
        str_left_var = ST_parser::parse(expression);
        str_right_var = "";
    }
}
Elif_stmt_transfer::~Elif_stmt_transfer()
{
}

Value_set *Elif_stmt_transfer::Transform(Value_set *_vs0)
{
    Value_set *ret = new Value_set(_vs0);

    std::string str_stmt_name = statement->absyntax_cname();
    std::string str_expression;
    symbol_c *expression;

    if (str_stmt_name.compare("elseif_statement_c") == 0)
    {
        //SYM_REF2(elseif_statement_c, expression, statement_list)
        expression = ((elseif_statement_c *)statement)->expression;
        str_expression = expression->absyntax_cname();

    }
    else
    {
        //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
        expression = ((if_statement_c *)statement)->expression;
        str_expression = expression->absyntax_cname();
    }

    if (str_expression.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
        lt_expression_c *lt_expression = (lt_expression_c *)expression;

//        op = "<";
        op = ">=";
        str_left_var = ST_parser::parse(lt_expression->l_exp);
        str_right_var = ST_parser::parse(lt_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) + 1);
            left_si = left_si->remove_lower_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if(right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-1" << std::endl;
                exit(0);
            }
            ret->set_var_value(right_var, right_si->op_intersect(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if(left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var)-1);
            right_si = right_si->remove_upper_bound();

            ret->set_var_value(left_var, left_si->op_intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if(left_var!=0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-3" << std::endl;
                exit(0);
            }

            //left
            if (right_si->get_upper() > left_si->get_upper())
            {
                //bot
                ret->set_var_value(left_var, Strided_interval::get_bot());
            }
            else if (right_si->get_upper() > left_si->get_lower())
            {
                int lower = right_si->get_upper();
                int upper = left_si->get_upper();
                int stride = left_si->get_stride();

                while ((upper - lower) % stride != 0)
                {
                    lower++;
                }
                if (upper == lower)
                {
                    ret->set_var_value(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_lower() < right_si->get_lower())
            {
                //bot
                ret->set_var_value(right_var, Strided_interval::get_bot());
            }
            else if (left_si->get_lower() < right_si->get_upper())
            {
                int lower = right_si->get_lower();
                int upper = left_si->get_lower();
                int stride = right_si->get_stride();

                while((upper - lower) % stride != 0)
                {
                    upper--;
                }
                if (lower == upper)
                {
                    ret->set_var_value(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }

    }
    else if (str_expression.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
        gt_expression_c *gt_expression = (gt_expression_c *) expression;

//        op = ">";
        op = "<=";
        str_left_var = ST_parser::parse(gt_expression->l_exp);
        str_right_var = ST_parser::parse(gt_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));
            left_si = left_si->remove_upper_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-1" << std::endl;
                exit(0);
            }
            ret->set_var_value(right_var, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));
            right_si = right_si->remove_lower_bound();

            ret->set_var_value(left_var, left_si->op_intersect(right_si));
        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-3" << std::endl;
                exit(0);
            }

            //left
            if (right_si->get_lower() < left_si->get_lower())
            {
                //bot
                ret->set_var_value(left_var, Strided_interval::get_bot());
            }
            else if (right_si->get_lower() < left_si->get_upper())
            {
                int lower = left_si->get_lower();
                int upper = right_si->get_lower();
                int stride = left_si->get_stride();

                while ((upper - lower) % stride != 0)
                {
                    upper--;
                }
                if (upper == lower)
                {
                    ret->set_var_value(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_upper() > right_si->get_upper())
            {
                ret->set_var_value(right_var, Strided_interval::get_bot());
            }
            else if (left_si->get_upper() > right_si->get_lower())
            {
                int lower = left_si->get_upper();
                int upper = right_si->get_upper();
                int stride = right_si->get_stride();

                while ((upper - lower) % stride != 0)
                {
                    lower++;
                }
                if (upper == lower)
                {
                    ret->set_var_value(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_expression.compare("le_expression_c") == 0)
        {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
        le_expression_c *le_expression = (le_expression_c *)expression;

//        op = "<=";
        op = ">";
        str_left_var = ST_parser::parse(le_expression->l_exp);
        str_right_var = ST_parser::parse(le_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) - 1);
            left_si = left_si->remove_lower_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-1" << std::endl;
                exit(0);
            }
            ret->set_var_value(right_var, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var) + 1);
            right_si = right_si->remove_upper_bound();

            ret->set_var_value(left_var, left_si->op_intersect(right_si));
        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-3" << std::endl;
                exit(0);
            }

            //left

            if (right_si->get_upper() >= left_si->get_upper())
            {
                //bot
                ret->set_var_value(left_var, Strided_interval::get_bot());
            }
            else if (right_si->get_upper() >= left_si->get_lower())
            {
                int lower = right_si->get_upper() + 1;
                int upper = left_si->get_upper();
                int stride = left_si->get_stride();

                while((upper - lower) % stride != 0)
                {
                    lower++;
                }
                if (upper == lower)
                {
                    ret->set_var_value(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_lower() <= right_si->get_lower())
            {
                //bot
                ret->set_var_value(right_var, Strided_interval::get_bot());
            }
            else if (left_si->get_lower() <= right_si->get_upper())
            {
                int lower = right_si->get_lower();
                int upper = left_si->get_lower() - 1;
                int stride = right_si->get_stride();

                while ((upper - lower) % stride != 0)
                {
                    upper--;
                }
                if (upper == lower)
                {
                    ret->set_var_value(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

        }
    }
    else if (str_expression.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
        ge_expression_c *ge_expression = (ge_expression_c *) expression;

//        op = ">=";
        op = "<";
        str_left_var = ST_parser::parse(ge_expression->l_exp);
        str_right_var = ST_parser::parse(ge_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) + 1);
            left_si = left_si->remove_upper_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if(right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-1" << std::endl;
                exit(0);
            }
            ret->set_var_value(right_var, right_si->op_intersect(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if(left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var)-1);
            right_si = right_si->remove_lower_bound();

            ret->set_var_value(left_var, left_si->op_intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if(left_var!=0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-3" << std::endl;
                exit(0);
            }

            //left
            if (right_si->get_lower() <= left_si->get_lower())
            {
                //bot
                ret->set_var_value(left_var, Strided_interval::get_bot());
            }
            else if (right_si->get_lower() <= left_si->get_upper())
            {
                int lower = left_si->get_lower();
                int upper = right_si->get_lower() - 1;
                int stride = left_si->get_stride();

                while ((upper - lower) % stride != 0)
                {
                    upper--;
                }
                if (upper == lower)
                {
                    ret->set_var_value(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_upper() >= right_si->get_upper())
            {
                ret->set_var_value(right_var, Strided_interval::get_bot());
            }
            else if (left_si->get_upper() >= right_si->get_lower())
            {
                int lower = left_si->get_upper() + 1;
                int upper = right_si->get_upper();
                int stride = right_si->get_stride();

                while((upper - lower) % stride != 0)
                {
                    lower++;
                }
                if (lower == upper)
                {
                    ret->set_var_value(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_expression.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
        equ_expression_c *equ_expression = (equ_expression_c *) expression;

//        op = "=";
        op = "<>";
        str_left_var = ST_parser::parse(equ_expression->l_exp);
        str_right_var = ST_parser::parse(equ_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-1" << std::endl;
                exit(0);
            }

            // remove an element
            ret->set_var_value(right_var, right_si->op_except(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));

            //remove an element
            ret->set_var_value(left_var, left_si->op_except(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-3" << std::endl;
                exit(0);
            }

            //remove elements

            //left
            ret->set_var_value(left_var, left_si->op_except(right_si));

            //right
            ret->set_var_value(right_var, right_si->op_except(left_si));

        }

    }
    else if (str_expression.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
        notequ_expression_c *notequ_expression = (notequ_expression_c *) expression;

//        op = "<>";
        op = "=";
        str_left_var = ST_parser::parse(notequ_expression->l_exp);
        str_right_var = ST_parser::parse(notequ_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-1" << std::endl;
                exit(0);
            }

            ret->set_var_value(right_var, left_si);
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));

            ret->set_var_value(left_var, right_si);

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-3" << std::endl;
                exit(0);
            }

            //left
            ret->set_var_value(left_var, left_si->op_intersect(right_si));

            //right
            ret->set_var_value(right_var, right_si->op_intersect(left_si));

        }
    }
    /* unary */
    else if (str_expression.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
        not_expression_c *not_expression = (not_expression_c *) expression;

//        op = "NOT";
        op = "";
        str_left_var = ST_parser::parse(not_expression->exp);

        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value_by(left_var);
        }
        else
        {
            std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! other_expression-1" << std::endl;
            exit(0);
        }

        ret->set_var_value(left_var, (bool_value)left_bv->op_union(Bits_vector_1::get_instance(true)));


    }
    /* variable */
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
//        op = "";
        op = "NOT";
        str_left_var = ST_parser::parse(expression);

        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value_by(left_var);
        }
        else
        {
            std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! not_expression-1" << std::endl;
            exit(0);
        }

        ret->set_var_value(left_var, (bool_value)left_bv->op_union(Bits_vector_1::get_instance(false)));

    }


    return ret;
}

std::string Elif_stmt_transfer::format()
{
    return (str_left_var + " " + op + " " + str_right_var);
}
