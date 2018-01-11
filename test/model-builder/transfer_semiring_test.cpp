//#define TRANSFER_SEMIRING_TEST

#ifdef TRANSFER_SEMIRING_TEST

#include <iostream>
#include <fstream>

#include "../../parser/ST_parser.h"
#include "../../builder/flow-graph-builder/CFG_builder.h"
#include "../../builder/model-builder/WPDS_builder.h"
#include "../../analyzer/transformer/value_set_transfer.h"
#include "../../builder/model-builder/abstract_new_value.h"
#include "../../builder/model-builder/transfer_semiring.h"

using namespace std;


int main()
{
    std::string file_name = "outputs/transfer_semiring_test.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = CFG_builder::get_instance();

    CFG *cfg = cfg_builder->create_CFG(&parser);

    std::ofstream dout("outputs/transfer_semiring_test.dot");
    cfg->print_dot(dout);
    dout.close();

    WPDS_builder *wpds_builder = new WPDS_builder(cfg);

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");
    wali::Key start;

    WPDS *wpds = wpds_builder->create(p, start);

    wali::wfa::WFA post_query;

    post_query.addTrans(p, start, accept, new Transfer_semiring(Abstract_value::get_instance(Abstract_value_set_transfer::get_identity())));
    post_query.set_initial_state(p);
    post_query.addFinalState(accept);

//    wali::wfa::WFA answer;
//    wpds->poststar(post_query, answer);

    std::vector<Node *> nodes = cfg->get_node_list();

    cout << nodes[3] << endl;
    wali::wfa::Trans tr;

/*
    std::ofstream fdot;
    string file_base = "outputs/weights-graphs-3/";
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
*/


    Abstract_value *a = Abstract_value::get_instance("a");
    Abstract_value *b = Abstract_value::get_instance("b");
    Abstract_value *c = Abstract_value::get_instance("c");

    Abstract_value *o = Abstract_value::get_instance("o");
    Abstract_value *pp = Abstract_value::get_instance("p");
    Abstract_value *q = Abstract_value::get_instance("q");

//    Transfer_semiring *tsa = new Transfer_semiring(a);
//    Transfer_semiring *tsb = new Transfer_semiring(b);
//    Transfer_semiring *tsc = new Transfer_semiring(c);
//
//    Transfer_semiring *tso = new Transfer_semiring(o);
//    Transfer_semiring *tsp = new Transfer_semiring(pp);
//    Transfer_semiring *tsq = new Transfer_semiring(q);
//
//    Transfer_semiring *tsx = (Transfer_semiring *)tsa->extend(tsb).get_ptr();
//    Transfer_semiring *tsy = (Transfer_semiring *)tsa->extend(tsc).get_ptr();
//
//    Transfer_semiring *tsu = (Transfer_semiring *)tso->extend(tsp).get_ptr();
//    Transfer_semiring *tsv = (Transfer_semiring *)tso->extend(tsq).get_ptr();

//     tsu->get_value()->print_dot(cout);

    Abstract_value *x = a->extend(b);
    Abstract_value *y = a->extend(c);

    Abstract_value *u = o->extend(pp);
    Abstract_value *v = o->extend(q);

    Abstract_value *x_oplus_y = x->combine(y);
    Abstract_value *u_oplus_v = u->combine(v);





    std::ofstream fdot("outputs/weights-graphs-3/transfer_semiring_test.dot");
    fdot << "digraph \"test\" {\n";
    x_oplus_y->extend(u)->combine(u_oplus_v)->show_name(fdot);
    fdot << "}\n\n\n";
    fdot.close();






    return 0;
}


#endif // TRANSFER_SEMIRING_TEST
