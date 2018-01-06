//#define FLOW_GRAPH_BUILDER_TEST

#ifdef FLOW_GRAPH_BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../builder/flow-graph-builder/CFG_builder.h"
#include "../builder/flow-graph-builder/Node.h"
#include "../builder/flow-graph-builder/Edge.h"
#include "../parser/ST_parser.h"

using namespace std;

int main()
{
    std::string file_name = "outputs/Example_4.st";
    ST_parser parser(file_name);
    CFG_builder *builder = CFG_builder::get_instance();

    CFG *cfg = builder->create_CFG(&parser);

    std::ofstream fout("outputs/Example_4.dot");

    cfg->print_dot(fout) << endl;

    fout.close();

    Node *s = new Node("Start");
    Node *e = new Node("End");


    Edge *edge = new Edge(s, e);

    cout << edge << endl;
    return 0;
}

#endif // FLOW_GRAPH_BUILDER_TEST
