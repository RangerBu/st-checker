//#define TRANSFER_TEST

#ifdef TRANSFER_TEST

#include <iostream>

#include "../analyzer/transformer/value_set_transfer.h"
#include "../analyzer/transformer/assign_stmt_transfer.h"
#include "../analyzer/transformer/if_stmt_transfer.h"
#include "../parser/st_parser.h"
#include "../builder/flow-graph-builder/cfg_builder.h"


int main()
{
    std::string file_name = "files/inputs/Example_0.st";
    ST_parser parser(file_name);
    CFG_builder *builder = CFG_builder::get_instance();

    CFG *cfg = builder->create_CFG(&parser);

    Abstract_value_set_transfer *t1;
    Abstract_value_set_transfer *t2;
    Abstract_value_set_transfer *t3;



    std::vector<Var *> var_list = cfg->get_var_list();

    Value_set *vs0 = new Value_set(var_list);

    vs0->print(std::cout) << std::endl;
    //cfg->get_nodes()[4] x := x+1;
    std::cout << cfg->get_node_list()[3] << std::endl;

    symbol_c *stmt = cfg->get_node_list()[3]->get_stmt();
    std::string cname = stmt->absyntax_cname();

    if (cname.compare("assignment_statement_c") == 0)
    {
        t1 = new Assign_stmt_transfer(stmt);


        Value_set *vs1 = t1->op_transform(vs0);

        std::cout << vs1->get_vars_map().size() << std::endl;

        std::cout << vs1->to_string() << std::endl;
    }
    else if (cname.compare("if_statement_c") == 0)
    {
        Var *x = vs0->contains_var("x");
        vs0->set_var_value(x, Strided_interval::get_strided_interval(1, 3, 15));
        Var *y = vs0->contains_var("y");
        vs0->set_var_value(y, Strided_interval::get_strided_interval(2, 8, 10));

        vs0->print(std::cout) << std::endl;

        Var *flag = vs0->contains_var("flag");
        vs0->set_var_value(flag, Bits_vector_1::get_instance("*"));

        t2 = new If_stmt_transfer(stmt);
        Value_set *vs1 = t2->op_transform(vs0);
        std::cout << vs1->to_string() << std::endl;
    }

    t1 = new Assign_stmt_transfer(cfg->get_node_list()[4]->get_stmt());
    t2 = new If_stmt_transfer(cfg->get_node_list()[2]->get_stmt());
    t3 = new Elif_stmt_transfer(cfg->get_node_list()[2]->get_stmt());


    return 0;
}

#endif // TRANSFER_TEST
