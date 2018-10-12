//
// Created by Samson on 2018/5/29.
//

#ifndef VERIFY_ST_PROGRAMS_PARSER_H
#define VERIFY_ST_PROGRAMS_PARSER_H

#include <vector>
#include <string>

#include "structures/pou.h"
#include "structures/program.h"

class Parser
{
public:

    Parser(std::string _file_path);
    virtual ~Parser();

    /**
     * getters and setters
     */
    std::vector<POU *> get_v_pou_list();

    Program *get_program();

private:
    // 文件中包含的所有pou列表
    std::vector<POU *> v_pou_list;

    // 程序入出
    Program *program;

    std::string file_path;

};


#endif //VERIFY_ST_PROGRAMS_PARSER_H
