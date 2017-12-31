#define TRANSFER_TEST

#ifdef TRANSFER_TEST

#include <iostream>

#include "../analyzer/transformer/Abstract_transfer.h"
#include "../analyzer/transformer/assign_stmt_transfer.h"
#include "../analyzer/transformer/if_stmt_transfer.h"
#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"


int main()
{
    std::string file_name = "../outputs/Example 4.st";
    ST_parser parser(file_name);
    CFG_builder *builder = new CFG_builder(&parser);

    CFG *cfg = builder->create();

    Abstract_transfer *t1 = new Assign_stmt_transfer();
    Abstract_transfer *t2 = new If_stmt_transfer();

    Value_set *vs0 = new Value_set(cfg->get_vars());

    //cfg->get_nodes()[4] x := x+1;

    std::cout << vs0->format() << std::endl;

    std::cout << cfg->get_nodes()[2] << std::endl;

    symbol_c *stmt = cfg->get_nodes()[2]->get_stmt();
    std::string cname = stmt->absyntax_cname();

    if (cname.compare("assignment_statement_c") == 0)
    {
        Value_set *vs1 = t1->Transform(stmt, vs0);
        std::cout << vs1->format() << std::endl;
    }
    else if (cname.compare("if_statement_c") == 0)
    {
        Var *x = vs0->contains_var("x");
        vs0->update_int_var(x, Strided_interval::get_strided_interval(1, 3, 15));
        Var *y = vs0->contains_var("y");
        vs0->update_int_var(y, Strided_interval::get_strided_interval(2, 8, 10));

        Var *flag = vs0->contains_var("flag");
        vs0->update_bool_var(flag, Bits_vector_1::get_instance("*"));

        Value_set *vs1 = t2->Transform(stmt, vs0);
        std::cout << vs1->format() << std::endl;
    }

    std::cout << (1<<31)-1 << std::endl;

    return 0;
}

#endif // TRANSFER_TEST
