#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"



int main()
{
    std::string file_name = "outputs/Example_4.st";
    ST_parser parser(file_name);
    CFG_builder *builder = new CFG_builder(&parser);

    CFG *cfg = builder->create();

    std::ofstream dout("outputs/Example_4.dot");
    cfg->print_dot(dout);
    dout.close();

    return 0;
}

#endif // BUILDER_TEST
