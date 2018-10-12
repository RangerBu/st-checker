#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


#include "parser/st_parser.h"
//#include "analyzer/structures/strided_interval.h"
//#include "analyzer/structures/bits_vector.h"
//#include "analyzer/structures/bits_vector_1.hpp"
//#include "analyzer/structures/bits_vector_8.hpp"
//#include "analyzer/domain/var.h"
//#include "analyzer/transformer/value_set_transfer.h"
//#include "builder/flow-graph-builder/CFG_builder.h"
//#include "builder/flow-graph-builder/Node.h"
//#include "builder/flow-graph-builder/Edge.h"
//#include "builder/flow-graph-builder/CFG.h"

using namespace std;

runtime_options_t runtime_options;
#define DEBUG

#ifndef DEBUG

int main()
{
    std::string file_name = "files/inputs/Example_0.st";
    ST_parser parser(file_name);

//    CFG c(parser.get_stmts_list());
//    std::vector<Node *> &nodes = c.get_nodes();

//    for (int i=0; i<nodes.size(); i++)
//    {
//        cout << nodes[i]->get_node_type() << endl;
//    }
//    ofstream dout("outputs/Example4.dot");
//    c.print_dot(dout);
//    dout.close();

//    Strided_interval *si_0 = new Strided_interval(2, 2, 0);
//    Strided_interval *si_1 = new Strided_interval(1, 1, 0);
//
//    si_0->print(cout); cout << endl;
//    si_1->print(cout); cout << endl;
//
//    Strided_interval *si = si_0->add(si_1);
//    si->print(cout);

//    Strided_interval *si_3 = new Strided_interval(1, 3, 7);
//    Strided_interval *si_7 = new Strided_interval(4);
//
//    Strided_interval *si = si_3->Intersection(si_7);
//
//    si->print(cout);
//    int a[8] = {-1, 0, 1, 2, 2, 1, 0, -1};
//    int b[9] = {-1, 0, 1, 2, 2, 1, 0, -1};
//
//
//    Bits_vector *bv_8_a = new Bits_vector_8(a);
//    Bits_vector *bv_8_b = new Bits_vector_8(b);
//
//    Bits_vector *ans = bv_8_a->Join(bv_8_b);
//
//    ans->print(cout);

//    Var *x = new Var("x");
//    Var *y = new Var("y", Var::BOOL_T, Var::INPUT_S);
//    std::vector<Var *> vars;
//
//    vars.push_back(x);
//    vars.push_back(y);
//
//    Abstract_memory *mem = new Abstract_memory(vars);
//    mem->print(cout);

//    Node *n = nodes[4];
//    Absyntax_visitor_weight avw;
//
//    avw.visit((assignment_statement_c *)n->get_stmt());

//    CFG_builder *builder = new CFG_builder(&parser);
//
//    CFG *cfg = builder->create();
//
//    ofstream dout("../outputs/Example-4.dot");
//    cfg->print_dot(dout);
//    dout.close();

//
//    Abstract_memory *mem = new Abstract_memory(cfg->get_vars());
//
//    mem->print(cout);

//    std::vector<Node *> nodes = cfg->get_nodes();
//    for (int i=0; i<nodes.size(); i++)
//    {
//        symbol_c *stmt = nodes[i]->get_stmt();
//        if (nodes[i]->get_stmt() != 0)
//        {
//            Abstract_transfer *atf = new Abstract_transfer(nodes[i]->get_stmt());
//            ST_parser::parse_weight(stmt, atf);
//            atf->print(cout); cout << endl;
//        }
//    }

    return 0;
}
#endif // DEBUG
