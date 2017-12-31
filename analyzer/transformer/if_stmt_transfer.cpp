#include "if_stmt_transfer.h"
#include "../../parser/ST_parser.h"

If_stmt_transfer::If_stmt_transfer()
{
}
If_stmt_transfer::If_stmt_transfer(symbol_c *_if_statement)
{
    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    if_statement_c *stmt = (if_statement_c *)_if_statement;

    std::string str_expression = stmt->expression->absyntax_cname();

    if (str_expression.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
        lt_expression_c *lt_expression = (lt_expression_c *)stmt->expression;

        op = "<";
        str_left_var = ST_parser::parse(lt_expression->l_exp);
        str_right_var = ST_parser::parse(lt_expression->r_exp);
    }
    else if (str_expression.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
        gt_expression_c *gt_expression = (gt_expression_c *) stmt->expression;

        op = ">";
        str_left_var = ST_parser::parse(gt_expression->l_exp);
        str_right_var = ST_parser::parse(gt_expression->r_exp);
    }
    else if (str_expression.compare("le_expression_c") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
        le_expression_c *le_expression = (le_expression_c *)stmt->expression;

        op = "<=";
        str_left_var = ST_parser::parse(le_expression->l_exp);
        str_right_var = ST_parser::parse(le_expression->r_exp);
    }
    else if (str_expression.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
        ge_expression_c *ge_expression = (ge_expression_c *) stmt->expression;

        op = ">=";
        str_left_var = ST_parser::parse(ge_expression->l_exp);
        str_right_var = ST_parser::parse(ge_expression->r_exp);
    }
    else if (str_expression.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
        equ_expression_c *equ_expression = (equ_expression_c *) stmt->expression;

        op = "=";
        str_left_var = ST_parser::parse(equ_expression->l_exp);
        str_right_var = ST_parser::parse(equ_expression->r_exp);
    }
    else if (str_expression.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
        notequ_expression_c *notequ_expression = (notequ_expression_c *) stmt->expression;

        op = "<>";
        str_left_var = ST_parser::parse(notequ_expression->l_exp);
        str_right_var = ST_parser::parse(notequ_expression->r_exp);
    }
    else if (str_expression.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
        not_expression_c *not_expression = (not_expression_c *) stmt->expression;

        op = "NOT";
        str_left_var = ST_parser::parse(not_expression->exp);
        str_right_var = "";

    }
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
        op = "";
        str_left_var = ST_parser::parse(stmt->expression);
        str_right_var = "";
    }
}
If_stmt_transfer::~If_stmt_transfer()
{
}

Value_set *If_stmt_transfer::Transform(symbol_c *_if_statement, Value_set *_vs0)
{
    Value_set *ret = new Value_set(_vs0);

    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    if_statement_c *stmt = (if_statement_c *)_if_statement;

    std::string str_expression = stmt->expression->absyntax_cname();

    if (str_expression.compare("lt_expression_c") == 0)
    {
        //SYM_REF2( lt_expression_c, l_exp, r_exp)
        lt_expression_c *lt_expression = (lt_expression_c *)stmt->expression;

        op = "<";
        str_left_var = ST_parser::parse(lt_expression->l_exp);
        str_right_var = ST_parser::parse(lt_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) + 1);
            left_si = left_si->remove_upper_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if(right_var != 0)
            {
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-1" << std::endl;
                exit(0);
            }
            ret->update_int_var(right_var, right_si->Intersect(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if(left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! lt_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var)-1);
            right_si = right_si->remove_lower_bound();

            ret->update_int_var(left_var, left_si->Intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if(left_var!=0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
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
                ret->update_int_var(left_var, Strided_interval::get_bot());
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
                    ret->update_int_var(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_upper() >= right_si->get_upper())
            {
                ret->update_int_var(right_var, Strided_interval::get_bot());
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
                    ret->update_int_var(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_expression.compare("gt_expression_c") == 0)
    {
        //SYM_REF2( gt_expression_c, l_exp, r_exp)
        gt_expression_c *gt_expression = (gt_expression_c *) stmt->expression;

        op = ">";
        str_left_var = ST_parser::parse(gt_expression->l_exp);
        str_right_var = ST_parser::parse(gt_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var) - 1);
            left_si = left_si->remove_lower_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-1" << std::endl;
                exit(0);
            }
            ret->update_int_var(right_var, right_si->Intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! gt_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var) + 1);
            right_si = right_si->remove_upper_bound();

            ret->update_int_var(left_var, left_si->Intersect(right_si));
        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
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
                ret->update_int_var(left_var, Strided_interval::get_bot());
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
                    ret->update_int_var(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_lower() <= right_si->get_lower())
            {
                //bot
                ret->update_int_var(right_var, Strided_interval::get_bot());
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
                    ret->update_int_var(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

        }
    }
    else if (str_expression.compare("le_expression_c") == 0)
    {
        //SYM_REF2( le_expression_c, l_exp, r_exp)
        le_expression_c *le_expression = (le_expression_c *)stmt->expression;

        op = "<=";
        str_left_var = ST_parser::parse(le_expression->l_exp);
        str_right_var = ST_parser::parse(le_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));
            left_si = left_si->remove_upper_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-1" << std::endl;
                exit(0);
            }
            ret->update_int_var(right_var, right_si->Intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! le_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));
            right_si = right_si->remove_lower_bound();

            ret->update_int_var(left_var, left_si->Intersect(right_si));
        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
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
                ret->update_int_var(left_var, Strided_interval::get_bot());
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
                    ret->update_int_var(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_upper() > right_si->get_upper())
            {
                ret->update_int_var(right_var, Strided_interval::get_bot());
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
                    ret->update_int_var(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }
        }
    }
    else if (str_expression.compare("ge_expression_c") == 0)
    {
        //SYM_REF2( ge_expression_c, l_exp, r_exp)
        ge_expression_c *ge_expression = (ge_expression_c *) stmt->expression;

        op = ">=";
        str_left_var = ST_parser::parse(ge_expression->l_exp);
        str_right_var = ST_parser::parse(ge_expression->r_exp);

        if (is_number(str_left_var) && !is_number(str_right_var))
        {
            left_var = 0;
            int_value left_si = Strided_interval::get_singleton_set(to_number(str_left_var));
            left_si = left_si->remove_lower_bound();

            int_value right_si;
            right_var = _vs0->contains_var(str_right_var);
            if (right_var != 0)
            {
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-1" << std::endl;
                exit(0);
            }

            ret->update_int_var(right_var, right_si->Intersect(left_si));
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));
            right_si = right_si->remove_upper_bound();

            ret->update_int_var(left_var, left_si->Intersect(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if(left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! ge_expression-3" << std::endl;
                exit(0);
            }

            //left
            if (right_si->get_upper() > left_si->get_upper())
            {
                //bot
                ret->update_int_var(left_var, Strided_interval::get_bot());
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
                    ret->update_int_var(left_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(left_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

            //right
            if (left_si->get_lower() < right_si->get_lower())
            {
                //bot
                ret->update_int_var(right_var, Strided_interval::get_bot());
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
                    ret->update_int_var(right_var, Strided_interval::get_singleton_set(lower));
                }
                else
                {
                    ret->update_int_var(right_var, Strided_interval::get_strided_interval(stride, lower, upper));
                }
            }

        }
    }
    else if (str_expression.compare("equ_expression_c") == 0)
    {
        //SYM_REF2(equ_expression_c, l_exp, r_exp)
        equ_expression_c *equ_expression = (equ_expression_c *) stmt->expression;

        op = "=";
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
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-1" << std::endl;
                exit(0);
            }

            ret->update_int_var(right_var, left_si);
        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));

            ret->update_int_var(left_var, right_si);

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! equ_expression-3" << std::endl;
                exit(0);
            }

            //left
            ret->update_int_var(left_var, left_si->Intersect(right_si));

            //right
            ret->update_int_var(right_var, right_si->Intersect(left_si));

        }

    }
    else if (str_expression.compare("notequ_expression_c") == 0)
    {
        //SYM_REF2(notequ_expression_c, l_exp, r_exp)
        notequ_expression_c *notequ_expression = (notequ_expression_c *) stmt->expression;

        op = "<>";
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
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-1" << std::endl;
                exit(0);
            }

            // remove an element
            ret->update_int_var(right_var, right_si->Except(left_si));

        }
        else if (!is_number(str_left_var) && is_number(str_right_var))
        {
            int_value left_si;
            left_var = _vs0->contains_var(str_left_var);
            if (left_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-2" << std::endl;
                exit(0);
            }

            right_var = 0;
            int_value right_si = Strided_interval::get_singleton_set(to_number(str_right_var));

            //remove an element
            ret->update_int_var(left_var, left_si->Except(right_si));

        }
        else
        {
            int_value left_si, right_si;
            left_var = _vs0->contains_var(str_left_var);
            right_var = _vs0->contains_var(str_right_var);

            if (left_var != 0 && right_var != 0)
            {
                left_si = _vs0->get_int_value(left_var);
                right_si = _vs0->get_int_value(right_var);
            }
            else
            {
                std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! notequ_expression-3" << std::endl;
                exit(0);
            }

            //remove elements

            //left
            ret->update_int_var(left_var, left_si->Except(right_si));

            //right
            ret->update_int_var(right_var, right_si->Except(left_si));

        }
    }
    /* unary */
    else if (str_expression.compare("not_expression_c") == 0)
    {
        //SYM_REF1(not_expression_c, exp)
        not_expression_c *not_expression = (not_expression_c *) stmt->expression;

        op = "NOT";
        str_left_var = ST_parser::parse(not_expression->exp);

        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value(left_var);
        }
        else
        {
            std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! not_expression-1" << std::endl;
            exit(0);
        }

        ret->update_bool_var(left_var, (bool_value)left_bv->Join(Bits_vector_1::get_instance(false)));

    }
    /* variable */
    else
    {
        //SYM_REF1(symbolic_variable_c, var_name)
        op = "";
        str_left_var = ST_parser::parse(stmt->expression);

        bool_value left_bv;
        left_var = _vs0->contains_var(str_left_var);
        right_var = 0;
        if (left_var != 0)
        {
            left_bv = _vs0->get_bool_value(left_var);
        }
        else
        {
            std::cout << "An error occurred when getting value of variable, may pass a wrong variable name! other_expression-1" << std::endl;
            exit(0);
        }

        ret->update_bool_var(left_var, (bool_value)left_bv->Join(Bits_vector_1::get_instance(true)));

    }
    return ret;
}

std::string If_stmt_transfer::format()
{
    return (str_left_var + " " + op + " " + str_right_var);
}
