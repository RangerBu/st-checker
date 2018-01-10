//#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"
#include "../builder/model-builder/WPDS_builder.h"
#include "../analyzer/transformer/value_set_transfer.h"
#include "../builder/model-builder/abstract_new_value.h"
#include "../builder/model-builder/transfer_semiring.h"

using namespace std;

Abstract_value *extend1(Abstract_value *_first, Abstract_value *_second)
{

    Abstract_value *ret = Abstract_value::get_instance(_second);

    std::vector<Abstract_value*> update_list;

    std::queue<Abstract_value *> work_queue;
    work_queue.push(ret);
    Abstract_value *v = 0;
    while(work_queue.size() > 0)
    {
        v = work_queue.front(); work_queue.pop();

        if (v->get_extend_pre() == 0)
        {
            update_list.push_back(v);
        }
        else
        {
            work_queue.push(v->get_extend_pre());
        }
    }

    std::cout << "update_list.size() = " << update_list.size() << std::endl;
    Abstract_value *first = Abstract_value::get_instance(_first);
    for (int i=0; i<update_list.size(); i++)
    {
        update_list[i]->set_extend_pre(first);
    }
    return ret;
}

Abstract_value *combine1(Abstract_value *_first, Abstract_value *_second)
{
    Abstract_value *ret = Abstract_value::get_instance(_first);

    ret->set_combine_pre(Abstract_value::get_instance(_second));

    return ret;
}

int main()
{
    std::string file_name = "outputs/Example_4.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = CFG_builder::get_instance();

    CFG *cfg = cfg_builder->create_CFG(&parser);

    std::ofstream dout("outputs/Example_4.dot");
    cfg->print_dot(dout);
    dout.close();

    Abstract_value_set_transfer *t1, *t2;

    std::cout << cfg->get_node_list()[4] << std::endl;
    t1 = new Assign_stmt_transfer(cfg->get_node_list()[4]->get_stmt());

    std::cout << cfg->get_node_list()[2] << std::endl << std::endl;
    t2 = new If_stmt_transfer(cfg->get_node_list()[2]->get_stmt());


    Abstract_value *av1 = Abstract_value::get_instance(t1);
    Abstract_value *av2 = Abstract_value::get_instance(t2);

    Transfer_semiring *ts1 = new Transfer_semiring(av1);
    Transfer_semiring *ts2 = new Transfer_semiring(av2);

    WPDS_builder *wpds_builder = new WPDS_builder(cfg);

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");
    wali::Key start;

    WPDS *wpds = wpds_builder->create(p, start);


    wali::wfa::WFA post_query;

    post_query.addTrans(p, start, accept, new Transfer_semiring(Abstract_value::get_instance(Abstract_value_set_transfer::get_identity())));
    post_query.set_initial_state(p);
    post_query.addFinalState(accept);

    wali::wfa::WFA answer;
    wpds->poststar(post_query, answer);

    std::ofstream fout("outputs/Example_4s.dot");
//    std::ofstream fout("outputs/Example_4_wpds.dot");
//    answer.print_dot(fout) << std::endl;
//    fout.close();

    // queries of answer wfa

    std::vector<Node *> nodes = cfg->get_node_list();
    wali::wfa::Trans tr;

    std::ofstream fdot;
    string file_base = "outputs/weights-graphs/";
    stringstream ss;
    for (int i=0; i<nodes.size(); i++)
    {
        ss << file_base << i << ".dot";
        fdot.open(ss.str().c_str());
        ss.str("");

        wali::Key key = wali::getKey(nodes[i]->get_str_node().c_str());
        answer.find(p, key, accept, tr);

//        fout << nodes[i] << endl;
        wali::sem_elem_t weight = tr.weight();
////        if (i==3)std::cout << ((Transfer_semiring *) weight.get_ptr())->get_value()->to_string() << std::endl;
////        if (i==3) ((Transfer_semiring *) weight.get_ptr())->get_value()->print(cout) << endl;
//        ((Transfer_semiring *) weight.get_ptr())->get_value()->print(fout) << endl;
//        fout << std::endl;

//        fout << "digraph \"" << nodes[i] << "\" {\n";
//        ((Transfer_semiring *) weight.get_ptr())->get_value()->print_dot(fout);
//        fout << "}\n\n\n";

        fdot << "digraph \"" << nodes[i] << "\" {\n";
        ((Transfer_semiring *) weight.get_ptr())->get_value()->print_dot(fdot);
        fdot << "}\n\n\n";
        fdot.close();
    }
    fout.close();


//    Abstract_value *f = Abstract_value::get_instance(Abstract_value_set_transfer::get_bot());
//    Abstract_value *g = Abstract_value::get_instance(Abstract_value_set_transfer::get_bot());
//
//    Abstract_value *h = Abstract_value::get_instance(Abstract_value_set_transfer::get_bot());
//    Abstract_value *k = Abstract_value::get_instance(Abstract_value_set_transfer::get_bot());
//
//    Abstract_value *u = extend1(f, g);
//    Abstract_value *v = extend1(h, k);
//
//    Abstract_value *ans = combine1(u, v);
//
//    u->print(cout) << endl<< endl;
//
//    v->print(cout) << endl<< endl;
//
//    ans->print(cout) << endl<< endl;

    return 0;
}

#endif // BUILDER_TEST
