#define BUILDER_TEST

#ifdef BUILDER_TEST

#include <iostream>
#include <fstream>

#include "../parser/st_parser.h"
#include "../builder/flow-graph-builder/cfg_builder.h"
#include "../builder/model-builder/wpds_builder.h"
#include "../analyzer/transformer/value_set_transfer.h"
#include "../builder/model-builder/structures/cts.h"
#include "../builder/model-builder/cts_builder.h"

using namespace std;


int main()
{

//    Strided_interval *a = Strided_interval::get_strided_interval(5, -5, 5);
//    Strided_interval *b = Strided_interval::get_singleton_set(50);
//
//    a->op_except(b)->print(cout) << endl << endl <<endl;

//    std::string file_name = "files/inputs/test_1.st";
//    std::string file_name = "files/inputs/Example_0.st";
//    std::string file_name = "files/inputs/robot_motion.st";
//    std::string file_name = "files/inputs/SF_EmergencyStop_2.st";
    std::string file_name = "files/inputs/SF_SafetyRequest_2.st";
//    std::string file_name = "files/inputs/SF_GuardMonitoring_2.st";



    ST_parser parser(file_name);
    CFG_builder *cfg_builder = CFG_builder::get_instance();

    CFG *cfg = cfg_builder->create_CFG(&parser);

    cout << "hello" << endl;

    CTS_builder *cts_builder = CTS_builder::get_instance();

    std::ofstream fdot ("files/outputs/test_1.dot");
    cfg->print_dot(fdot);
    fdot.close();

    cts_builder->create(cfg);

    std::cout << "hello"<< std::endl;

    return 0;
}

#endif // BUILDER_TEST
