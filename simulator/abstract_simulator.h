//
// Created by Samson on 2018/5/31.
//

#ifndef VERIFY_ST_PROGRAMS_ABSTRACT_SIMULATOR_H
#define VERIFY_ST_PROGRAMS_ABSTRACT_SIMULATOR_H

#include <vector>
#include <iostream>

#include "wali/wpds/WPDS.hpp"

#include "../parser/structures/program.h"
#include "structures/semiring.h"

class Abstract_simulator
{
public:
    Abstract_simulator(Program *_program, std::vector<POU *> _v_pou_list);

    virtual ~Abstract_simulator();

    void print_explored_cfg(std::ostream &_out);

    std::vector<Configuration *> simulate(Configuration *_init_configuration);

    /**
     * getters and setters
     */

    Program *get_program();

    std::vector<POU *> get_v_pou_list();

    wali::wpds::WPDS *get_wpds_model();

    wali::wfa::WFA *get_post_query_automaton();

    std::vector<Vertex *> get_v_explored_vertex_list();

    std::vector<Edge *> get_v_explored_edge_list();



private:
    // ������
    Program *program;

    // �漰������pou���б�
    std::vector<POU *> v_pou_list;

    // �����Ӧ��wpdsģ��
    wali::wpds::WPDS *wpds_model;

    // wpds���н��
    wali::wfa::WFA *post_query_automaton;

    // �����CFG�ϲ�
    void explore();

    // �ϲ����vertex�б�
    std::vector<Vertex *> v_explored_vertex_list;

    // �ϲ����edge�б�
    std::vector<Edge *> v_explored_edge_list;

    // �ϲ����main entry
    Vertex *entry;

    // �ϲ����main exit
    Vertex *exit;

    // �������Ӧ��Semiring����
    std::map<Edge *, Semiring *> m_edge_to_weight;

};


#endif //VERIFY_ST_PROGRAMS_ABSTRACT_SIMULATOR_H
