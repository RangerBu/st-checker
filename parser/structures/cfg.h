//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_CFG_H
#define VERIFY_ST_PROGRAMS_CFG_H

#include <vector>
#include <string>

#include "absyntax/absyntax.hh"

#include "vertex.h"
#include "edge.h"

class CFG
{
public:
    CFG(std::string _str_cfg_name, statement_list_c *_statement_list);

    virtual ~CFG();

    /**
     * 补充：get_successors 和 get_succ_edges
     */

    /**
     * getters and setters
     */
    std::vector<Vertex *> get_vertex_list();

    std::vector<Edge *> get_edge_list();

    Vertex *get_entry();

    Vertex *get_exit();

    statement_list_c *get_statement_list();

    std::string get_str_cfg_name();

    /**
     * helpers
     */
    friend std::ostream &operator<<(std::ostream &_out, CFG &_cfg);

private:
    // 节点列表
    std::vector<Vertex *> v_vertex_list;

    // 边列表
    std::vector<Edge *> v_edge_list;

    // 唯一入点
    Vertex *entry;

    // 唯一出点
    Vertex *exit;

    // 传入的语句列表
    statement_list_c *statement_list;

    // 字符串类型的cfg名称
    std::string str_cfg_name;
};


#endif //VERIFY_ST_PROGRAMS_CFG_H
