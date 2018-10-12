#include "if_stmt_transfer.h"
#include "../../parser/st_parser.h"

/**
* public methods
*/
/*
* constructor
*/
If_stmt_transfer::If_stmt_transfer(symbol_c *_statement)
{
    statement = _statement;

    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    if_statement_c *stmt = (if_statement_c *)statement;

    std::string str_expression = stmt->expression->absyntax_cname();

    if (str_expression.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
        lt_expression_c *lt_expression = (lt_expression_c *)stmt->expression;

        str_op = "<";
        str_left_var = ST_parser::parse(lt_expression->l_exp);
        str_right_var1 = ST_parser::parse(lt_expression->r_exp);
    }
    else if (str_expression.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
        gt_expression_c *gt_expression = (gt_expression_c *) stmt->expression;

        str_op = ">";
        str_left_var = ST_parser::parse(gt_expression->l_exp);
        str_right_var1 = ST_parser::parse(gt_expression->r_exp);
    }
    else if (str_expression.compare("le_expression_c") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
        le_expression_c *le_expression = (le_expression_c *)stmt->expression;

        str_op = "<=";
        str_left_var = ST_parser::parse(le_expression->l_exp);
        str_right_var1 = ST_parser::parse(le_expression->r_exp);
    }
    else if (str_expression.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
        ge_expression_c *ge_expression = (ge_expression_c *) stmt->expression;

        str_op = ">=";
        str_left_var = ST_parser::parse(ge_expression->l_exp);
        str_right_var1 = ST_parser::parse(ge_expression->r_exp);
    }
    else if (str_expression.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
        equ_expression_c *equ_expression = (equ_expression_c *) stmt->expression;

        str_op = "=";
        str_left_var = ST_parser::parse(equ_expression->l_exp);
        str_right_var1 = ST_parser::parse(equ_expression->r_exp);
    }
    else if (str_expression.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
        notequ_expression_c *notequ_expression = (notequ_expression_c *) stmt->expression;

        str_op = "<>";
        str_left_var = ST_parser::parse(notequ_expression->l_exp);
        str_right_var1 = ST_parser::parse(notequ_expression->r_exp);
    }
    else if (str_expression.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
        not_expression_c *not_expression = (not_expression_c *) stmt->expression;

        str_op = "NOT";
        str_left_var = ST_parser::parse(not_expression->exp);
        str_right_var1 = "";

    }
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
        str_op = "";
        str_left_var = ST_parser::parse(stmt->expression);
        str_right_var1 = "";
    }
}

/*
* de-constructor
*/
If_stmt_transfer::~If_stmt_transfer()
{

}


/**
* external visible methods - inherited methods
*/
Value_set *If_stmt_transfer::op_transform(Value_set *_vs0)
{
    Value_set *ret = new Value_set(_vs0);

    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)

    if (str_op.compare("<") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) + 1);
            left_si = left_si->remove_upper_bound();

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if(right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if(left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */
            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1)-1);
            right_si = right_si->remove_lower_bound();

            /*
            * update the value of left_var as right_var is a number
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));

        }
        else if (!is_number(str_left_var) && !is_number(str_right_var1))
        {
            int_value left_si, right_si;
            /*
            * get the left operand
            */
            left_var = _vs0->contains_var(str_left_var);

            /*
            * get the right operand
            */
            right_var1 = _vs0->contains_var(str_right_var1);

            if(left_var!=0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-3" << std::endl;
                exit(0);
            }

            /*
            * update the value of left_var
            */
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
            else if (right_si->get_lower() > left_si->get_upper())
            {
                /*
                 * do nothing
                 */
            }

            /*
            * update the value of right_var
            */
            if (left_si->get_upper() >= right_si->get_upper())
            {
                ret->set_var_value(right_var1, Strided_interval::get_bot());
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
                    ret->set_var_value(right_var1, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var1, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_op.compare(">") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) - 1);
            left_si = left_si->remove_lower_bound();

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if (right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */
            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1) + 1);
            right_si = right_si->remove_upper_bound();

            /*
            * update the value of left_var as right_var is a number
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));
        }
        else
        {
            int_value left_si, right_si;

            /*
            * get the left operand
            */
            left_var = _vs0->contains_var(str_left_var);

            /*
            * get the right operand
            */
            right_var1 = _vs0->contains_var(str_right_var1);

            if (left_var != 0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-3" << std::endl;
                exit(0);
            }

            /*
            * update the value of left_var
            */
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

            /*
            * update the value of right_var
            */
            if (left_si->get_lower() <= right_si->get_lower())
            {
                //bot
                ret->set_var_value(right_var1, Strided_interval::get_bot());
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
                    ret->set_var_value(right_var1, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var1, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

        }
    }
    else if (str_op.compare("<=") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));
            left_si = left_si->remove_upper_bound();

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if (right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */
            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1));
            right_si = right_si->remove_lower_bound();

            /*
            * update the value of left_var as right_var is a number
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));
        }
        else if (!is_number(str_left_var) && !is_number(str_right_var1))
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var1 = _vs0->contains_var(str_right_var1);

            if (left_var != 0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-3" << std::endl;
                exit(0);
            }

            /*
            * update the value of left_var
            */
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

            /*
            * update the value of right_var
            */
            if (left_si->get_upper() > right_si->get_upper())
            {
                ret->set_var_value(right_var1, Strided_interval::get_bot());
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
                    ret->set_var_value(right_var1, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var1, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_op.compare(">=") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));
            left_si = left_si->remove_lower_bound();

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if (right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */
            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1));
            right_si = right_si->remove_upper_bound();

            /*
            * update the value of left_var as right_var is a number
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;

            /*
            * get the left operand
            */
            left_var = _vs0->contains_var(str_left_var);

            /*
            * get the right operand
            */
            right_var1 = _vs0->contains_var(str_right_var1);

            if(left_var != 0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-3" << std::endl;
                exit(0);
            }

            /*
            * update the value of left_var
            */
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

            /*
            * update the value of right_var
            */
            if (left_si->get_lower() < right_si->get_lower())
            {
                //bot
                ret->set_var_value(right_var1, Strided_interval::get_bot());
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
                    ret->set_var_value(right_var1, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->set_var_value(right_var1, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

        }
    }
    else if (str_op.compare("=") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if (right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);

            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */

            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1));


            /*
            * update the value of left_var as right_var is a number
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;

            /*
            * get the left operand
            */
            left_var = _vs0->contains_var(str_left_var);

            /*
            * get the right operand
            */
            right_var1 = _vs0->contains_var(str_right_var1);

            if (left_var != 0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-3" << std::endl;
                exit(0);
            }

            /*
            * update the value of left_var
            */
            ret->set_var_value(left_var, left_si->op_intersect(right_si));

            /*
            * update the value of right_var
            */
            ret->set_var_value(right_var1, right_si->op_intersect(left_si));

        }

    }
    else if (str_op.compare("<>") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)

        if (is_number(str_left_var) && !is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));

            /*
            * get the right operand
            */
            int_value right_si;
            right_var1 = _vs0->contains_var(str_right_var1);
            if (right_var1 != 0)
            {
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-1" << std::endl;
                exit(0);
            }

            /*
            * update the value of right_var1 as left_var is a number
            */
            ret->set_var_value(right_var1, right_si->op_except(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var1))
        {
            /*
            * get the left operand
            */
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-2" << std::endl;
                exit(0);
            }

            /*
            * get the right operand
            */
            right_var1 = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var1));

            /*
            * update the value of left_var as right_var1 is a number
            */
            ret->set_var_value(left_var, left_si->op_except(right_si));

        }
        else
        {
            int_value left_si, right_si;

            /*
            * get the left operand
            */
            left_var = _vs0->contains_var(str_left_var);

            /*
            * get the right operand
            */
            right_var1 = _vs0->contains_var(str_right_var1);

            if (left_var != 0 && right_var1 != 0)
            {
                left_si = _vs0->get_int_value_by(left_var);
                right_si = _vs0->get_int_value_by(right_var1);
            }
            else
            {
                std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-3" << std::endl;
                exit(0);
            }

            //remove elements
            /*
            * update the value of left_var
            */
            ret->set_var_value(left_var, left_si->op_except(right_si));

            /*
            * update the value of right_var
            */
            ret->set_var_value(right_var1, right_si->op_except(left_si));

        }
    }
    /* unary */
    else if (str_op.compare("NOT") == 0)
    {
        //SYM_REF1(not_expression_c, exp)

        /*
        * get the only operand left_var
        */
        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var1 = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value_by(left_var);
        }
        else
        {
            std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! not_expression-1" << std::endl;
            std::cerr << str_left_var << std::endl;
            exit(0);
        }

        /*
        * update the only operand left_var
        */
        ret->set_var_value(left_var, (bool_value)left_bv->op_intersect(Bits_vector_1::get_instance(false)));

    }
    /* variable */
    else if (str_op.compare("") == 0)
    {
        //SYM_REF1(symbolic_variable_c, var_name)
        /*
        * get the only operand left_var
        */
        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var1 = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value_by(left_var);
        }
        else
        {
            std::cerr << "An error occurred when getting value of variable, may pass a wrong variable name! other_expression-1" << std::endl;
            std::cerr << str_left_var << std::endl;
            exit(0);
        }

        /*
        * update the only operand left_var
        */
        ret->set_var_value(left_var, (bool_value)left_bv->op_intersect(Bits_vector_1::get_instance(true)));

    }
    return ret;
}


/**
* getters and setters
*/
Var *If_stmt_transfer::get_left_var()
{
    return left_var;
}

Var *If_stmt_transfer::get_right_var1()
{
    return right_var1;
}

std::string If_stmt_transfer::get_str_left_var()
{
    return str_left_var;
}

std::string If_stmt_transfer::get_str_right_var1()
{
    return str_right_var1;
}

std::string If_stmt_transfer::get_str_op()
{
    return str_op;
}

symbol_c *If_stmt_transfer::get_statement()
{
    return statement;
}


/**
* helpers - inherited methods
*/
bool If_stmt_transfer::equal(Abstract_value_set_transfer *_other)
{
    If_stmt_transfer *other = (If_stmt_transfer *)_other;

    return statement == other->get_statement() && str_op.compare(other->get_str_op()) == 0;
}

std::ostream &If_stmt_transfer::print(std::ostream &_out)
{
    return _out << str_left_var << " " << str_op << " " << str_right_var1;
}


/**
* helpers - debug only
*/
std::string If_stmt_transfer::to_string()
{
    return (str_left_var + " " + str_op + " " + str_right_var1);
}
