//#define DOMAIN_TEST

#ifdef DOMAIN_TEST

#include <iostream>

#include "../analyzer/domain/var.h"
#include "../analyzer/domain/value_set.h"
#include "../analyzer/structures/bits_vector_1.hpp"

int main()
{

    Var *in0 = new Var("in0", Var::TYPE_INT, Var::SEMANTICS_INPUT);
    Var *flag = new Var("flag", Var::TYPE_BOOL, Var::SEMANTICS_INPUT);
    Var *x = new Var("x", Var::TYPE_INT, Var::SEMANTICS_VAR);
    Var *y = new Var("y", Var::TYPE_INT, Var::SEMANTICS_OUTPUT);
    Var *tmp = new Var("tmp", Var::TYPE_BYTE, Var::SEMANTICS_VAR);

    std::vector<key> vars;
    vars.push_back(in0);
    vars.push_back(flag);
    vars.push_back(x);
    vars.push_back(y);
    vars.push_back(tmp);

    Value_set *vs0 = new Value_set(vars);

    std::vector<key> vars_list;
    vars_list.push_back(in0);
    vars_list.push_back(flag);
    vars_list.push_back(x);
    vars_list.push_back(y);
    vars_list.push_back(tmp);

    Value_set *vs1 = new Value_set(vars_list);

    vs0->set_var_value(flag, Bits_vector_1::get_top());

    vs0->set_var_value(x, Strided_interval::get_strided_interval(1, 3, 5));

    vs1->set_var_value(y, Strided_interval::get_singleton_set(20));

    std::cout << vs0->to_string()<< std::endl;

    std::cout << std::endl << vs1->to_string() << std::endl;

    Value_set *ans = vs0->op_union(vs1);

    std::cout << std::endl << ans->to_string()<< std::endl;



    return 0;
}

#endif // DOMAIN_TEST
