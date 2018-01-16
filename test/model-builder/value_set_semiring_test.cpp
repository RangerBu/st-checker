//#define VALUE_SET_SEMIRING_TEST

#ifdef VALUE_SET_SEMIRING_TEST

#include <string>
#include <iostream>
#include <fstream>

#include "../../parser/ST_parser.h"
#include "../../builder/flow-graph-builder/CFG_builder.h"
#include "../../builder/model-builder/WPDS_builder.h"
#include "../../analyzer/transformer/value_set_transfer.h"
#include "../../builder/model-builder/transfer_semiring.h"
#include "../../builder/model-builder/structures/value_set_semiring.h"

using namespace std;


int main()
{
    std::string file_name = "inputs/Example_2.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = CFG_builder::get_instance();

    CFG *cfg = cfg_builder->create_CFG(&parser);

    std::ofstream dout("outputs/Example_2.dot");
    cfg->print_dot(dout);
    dout.close();

    WPDS_builder *wpds_builder = new WPDS_builder(cfg);

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");
    wali::Key start;

    WPDS *wpds = wpds_builder->create(p, start);

    wali::wfa::WFA post_query;

    Value_set *vs0 = new Value_set(cfg->get_var_list());
    Value_set_semiring *vss = new Value_set_semiring(Abstract_value_set_transfer::get_identity());
    vss->set_value(vs0);

//    vs0->print(std::cout) << endl;

    post_query.addTrans(p, start, accept, vss);


    post_query.set_initial_state(p);
    post_query.addFinalState(accept);

    wali::wfa::WFA answer;
    wpds->poststar(post_query, answer);

    std::vector<Node *> nodes = cfg->get_node_list();

    wali::wfa::Trans tr;

    std::ofstream fout("outputs/Example_2.weight");

    for (int i=0; i<nodes.size(); i++)
    {

        wali::Key key = wali::getKey(nodes[i]->get_str_node().c_str());
        answer.find(p, key, accept, tr);

        fout << nodes[i] << endl;

        Value_set_semiring *weight = (Value_set_semiring *)tr.weight().get_ptr();

        weight->get_value()->print(fout) << endl;
    }
    fout.close();

    return 0;
}


#endif // VALUE_SET_SEMIRING_TEST

