//
// Created by Samson on 2018/5/30.
//

#include "debug_helper.h"

void Debug_helper::print_debug_info(std::string _file, int _line, std::string _info)
{
    std::cerr << _file << " : " << _line << std::endl;
    std::cerr << _info << std::endl;
}