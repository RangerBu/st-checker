#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"
#include "../builder/model-builder/WPDS_builder.h"
#include "../analyzer/transformer/value_set_transfer.h"
#include "../builder/model-builder/abstract_new_value.h"
#include "../builder/model-builder/transfer_semiring.h"



int main()
{
    std::string file_name = "outputs/Example_4.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = new CFG_builder(&parser);

    CFG *cfg = cfg_builder->create();

    std::ofstream dout("outputs/Example_4.dot");
    cfg->print_dot(dout);
    dout.close();

    Value_set_transfer *t1, *t2;

    std::cout << cfg->get_nodes()[4] << std::endl;
    t1 = new Assign_stmt_transfer(cfg->get_nodes()[4]->get_stmt());

    std::cout << cfg->get_nodes()[2] << std::endl << std::endl;
    t2 = new If_stmt_transfer(cfg->get_nodes()[2]->get_stmt());


    Abstract_new_value *av1 = new Abstract_new_value(t1);
    Abstract_new_value *av2 = new Abstract_new_value(t2);

    Transfer_semiring *ts1 = new Transfer_semiring(av1);
    Transfer_semiring *ts2 = new Transfer_semiring(av2);


    WPDS_builder *wpds_builder = new WPDS_builder(cfg);

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");
    wali::Key start;

    WPDS *wpds = wpds_builder->create(p, start);


    wali::wfa::WFA post_query;
    post_query.addTrans(p, start, accept, new Transfer_semiring(new Abstract_new_value(Value_set_transfer::get_identity())));
    post_query.set_initial_state(p);
    post_query.addFinalState(accept);

    wali::wfa::WFA answer;
    wpds->poststar(post_query, answer);

    std::ofstream fout("outputs/Example_4.wpds");
    answer.print(fout) << std::endl;
    fout.close();


    return 0;
}

#endif // BUILDER_TEST
