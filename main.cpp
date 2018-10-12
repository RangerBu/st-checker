#include <iostream>
#include <fstream>

#include "parser/parser.h"
#include "simulator/abstract_simulator.h"
#include "simulator/structures/semiring.h"
#include "parser/visitors/symbol_to_string_visitor.h"
#include "simulator/structures/stack_symbol.h"

int main()
{
    std::string file_name = "fibonacci-numbers";
    Parser parser("../ios/" + file_name + ".st");

    Abstract_simulator simulator(parser.get_program(), parser.get_v_pou_list());

    std::ofstream dout ("../ios/" + file_name + "_icfg.dot");
    simulator.print_explored_cfg(dout);

//    std::vector<Edge *> v_explored_edge_list = simulator.get_v_explored_edge_list();



    std::cerr << "finished" << std::endl;
    return 0;
}