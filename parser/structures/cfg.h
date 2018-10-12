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
     * ���䣺get_successors �� get_succ_edges
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
    // �ڵ��б�
    std::vector<Vertex *> v_vertex_list;

    // ���б�
    std::vector<Edge *> v_edge_list;

    // Ψһ���
    Vertex *entry;

    // Ψһ����
    Vertex *exit;

    // ���������б�
    statement_list_c *statement_list;

    // �ַ������͵�cfg����
    std::string str_cfg_name;
};


#endif //VERIFY_ST_PROGRAMS_CFG_H
