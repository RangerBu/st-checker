#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"
#include "../builder/model-builder/WPDS_builder.h"



int main()
{
    std::string file_name = "outputs/Example_4.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = new CFG_builder(&parser);

    CFG *cfg = cfg_builder->create();

//    std::ofstream dout("outputs/Example_4.dot");
//    cfg->print_dot(dout);
//    dout.close();

    WPDS_builder *wpds_builder = new WPDS_builder(cfg);
    WPDS *wpds = wpds_builder->create();

    return 0;
}

#endif // BUILDER_TEST
