#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/ST_parser.h"
#include "../builder/flow-graph-builder/CFG_builder.h"
#include "../builder/model-builder/wpds_builder.h"
#include "../analyzer/transformer/value_set_transfer.h"
#include "../builder/model-builder/structures/cts.h"
#include "../builder/model-builder/cts_builder.h"

using namespace std;


int main()
{
    std::string file_name = "inputs/Example_0.st";
    ST_parser parser(file_name);
    CFG_builder *cfg_builder = CFG_builder::get_instance();

    CFG *cfg = cfg_builder->create_CFG(&parser);

    CTS_builder *cts_builder = CTS_builder::get_instance();

    cts_builder->create(cfg);

    return 0;
}

#endif // BUILDER_TEST
