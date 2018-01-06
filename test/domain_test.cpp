#define DOMAIN_TEST

#ifdef DOMAIN_TEST

#include <iostream>

#include "../analyzer/domain/Var.h"
#include "../analyzer/domain/Value_set.h"
#include "../analyzer/structures/Bits_vector_1.h"

int main()
{

    Var *in0 = new Var("in0", Var::TYPE_INT, Var::SEMANTICS_INPUT);
    Var *flag = new Var("flag", Var::TYPE_BOOL, Var::SEMANTICS_INPUT);
    Var *x = new Var("x", Var::TYPE_INT, Var::SEMANTICS_VAR);
    Var *y = new Var("y", Var::TYPE_INT, Var::SEMANTICS_OUTPUT);
    Var *tmp = new Var("tmp", Var::TYPE_BYTE, Var::SEMANTICS_VAR);

    Value_set *vs0 = new Value_set();

    vs0->insert_var(in0);
    vs0->insert_var(flag);
    vs0->insert_var(x);
    vs0->insert_var(y);
    vs0->insert_var(tmp);

    std::vector<key> vars_list;
    vars_list.push_back(in0);
    vars_list.push_back(flag);
    vars_list.push_back(x);
    vars_list.push_back(y);
    vars_list.push_back(tmp);

    Value_set *vs1 = new Value_set(vars_list);


    vs0->update_bool_var(flag, Bits_vector_1::get_top());

    vs0->update_int_var(x, Strided_interval::get_strided_interval(1, 3, 5));

    vs1->update_int_var(y, Strided_interval::get_singleton_set(20));

    std::cout << vs0->format()<< std::endl;

    std::cout << std::endl << vs1->format() << std::endl;

    Value_set *ans = vs0->Union(vs1);

    std::cout << std::endl << ans->format() << std::endl;



    return 0;
}

#endif // DOMAIN_TEST
