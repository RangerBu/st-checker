//
// Created by Samson on 2018/5/31.
//

#include <queue>
#include <map>

#include "../parser/visitors/symbol_to_string_visitor.h"
#include "abstract_simulator.h"
#include "../debug_helper.h"

Abstract_simulator::Abstract_simulator(Program *_program, std::vector<POU *> _v_pou_list) :
        program(_program), v_pou_list(_v_pou_list)
{
    wpds_model = new wali::wpds::WPDS();
    wali::Key p = wali::getKey("p");

    // 生成ICFG
    explore();

    // 根据边声称对应的Semiring值
    std::string str_cname = "";
    for (int i = 0; i < v_explored_edge_list.size(); ++i)
    {
        if (v_explored_edge_list[i]->get_label() == 0)
        {
            m_edge_to_weight[v_explored_edge_list[i]] = (Semiring *)Semiring::get_one().get_ptr();

        } else {
            m_edge_to_weight[v_explored_edge_list[i]] = new Semiring(v_explored_edge_list[i]->get_label());

        }
    }

    // 根据边，添加规则
    for (int i = 0; i < v_explored_edge_list.size(); ++i)
    {
        wali::Key k_from = wali::getKey(v_explored_edge_list[i]->get_from()->get_str_vertex_name());
        wali::Key k_to = wali::getKey(v_explored_edge_list[i]->get_to()->get_str_vertex_name());

        /**
         * todo：
         * 1. Semiring
         * 2. 边及对应的weight。wpds_model->add_rule(p, k_from, p, k_to, weight);
         */

        wpds_model->add_rule(p, k_from, p, k_to, m_edge_to_weight[v_explored_edge_list[i]]);
    }

}

Abstract_simulator::~Abstract_simulator()
{

}

void Abstract_simulator::print_explored_cfg(std::ostream &_out)
{
    _out << "digraph \"" << program->get_str_pou_name() << "\" {\n";

    // 打印点信息
    for (int i = 0; i < v_explored_vertex_list.size(); ++i)
    {
        _out << "\"" << (*v_explored_vertex_list[i]) << "\" [label=\"" << (*v_explored_vertex_list[i]) << "\", color=lightblue,style=filled,shape=box]\n";
    }

    for (int j = 0; j < v_explored_edge_list.size(); ++j)
    {
        // 打印边
        _out << "\"" << (*v_explored_edge_list[j]->get_from()) << "\" -> \"" << (*v_explored_edge_list[j]->get_to());

        // 打印边上标记
        if (v_explored_edge_list[j]->get_label() == 0)
        {
            _out << "\" [label=\"[ 0 ]\",color=black]\n";
        } else {
            _out << "\" [label=\"[ " << Symbol_to_string_visitor::parse(v_explored_edge_list[j]->get_label()) <<" ]\",color=black]\n";
        }
    }

    _out << "}\n";

}

std::vector<Configuration *> Abstract_simulator::simulate(Configuration *_init_configuration)
{
    wali::Key p = wali::getKey("p");
    wali::Key k_accept = wali::getKey("accept");
    wali::Key k_entry = wali::getKey(entry->get_str_vertex_name());

    post_query_automaton = new wali::wfa::WFA();
    // 补充：初始值
    post_query_automaton->addTrans(p, k_entry, k_accept, 0);
    post_query_automaton->set_initial_state(p);
    post_query_automaton->add_final_state(k_accept);

    wali::wfa::WFA answer;

    wpds_model->poststar(*post_query_automaton, answer);


}

/**
 * getters and setters
 */

Program* Abstract_simulator::get_program()
{
    return program;
}

std::vector<POU *> Abstract_simulator::get_v_pou_list()
{
    return v_pou_list;
}

wali::wpds::WPDS* Abstract_simulator::get_wpds_model()
{
    return wpds_model;
}

wali::wfa::WFA* Abstract_simulator::get_post_query_automaton()
{
    return post_query_automaton;
}

std::vector<Vertex *> Abstract_simulator::get_v_explored_vertex_list()
{
    return v_explored_vertex_list;
}

std::vector<Edge *> Abstract_simulator::get_v_explored_edge_list()
{
    return v_explored_edge_list;
}


// 将多个cfg合并成为一个icfg
void Abstract_simulator::explore()
{
    entry = program->get_cfg()->get_entry();
    exit = program->get_cfg()->get_exit();

    std::map<std::string, CFG *> m_name_to_cfg;
    std::vector<Edge *> v_work_list;

    CFG *cfg = 0;
    for (int i = 0; i < v_pou_list.size(); ++i)
    {
        cfg = v_pou_list[i]->get_cfg();
        m_name_to_cfg[v_pou_list[i]->get_str_pou_name()] = cfg;

        // 合并vertex
        std::vector<Vertex *> v_vertex_list = cfg->get_vertex_list();
        for (int j = 0; j < v_vertex_list.size(); ++j)
        {
            v_explored_vertex_list.push_back(v_vertex_list[j]);
        }

        // 合并edge
        std::vector<Edge *> v_edge_list = cfg->get_edge_list();
        for (int j = 0; j < v_edge_list.size(); ++j)
        {
            v_explored_edge_list.push_back(v_edge_list[j]);

            if (v_edge_list[j]->get_label() != 0)
            {
                std::string str_cname = v_edge_list[j]->get_label()->absyntax_cname();

                if (str_cname.compare("fb_invocation_c") == 0)
                {

                } else if (str_cname.compare("function_invocation_c") == 0)
                {

                } else {
                    Symbol_to_string_visitor::parse(v_edge_list[j]->get_label());

                    function_invocation_c *invocation = (function_invocation_c *) Symbol_to_string_visitor::has_invocation(
                            v_edge_list[j]->get_label());

                    if (invocation != 0)
                    {
                        std::string function_name = Symbol_to_string_visitor::parse(invocation->function_name);
                        /**
                        * 补充：（完成）
                        * 1. 从function_invocation_c中剥离出VAR_INPUT的赋值
                        * 2. 从function_invocation_c中剥离出VAR_OUT的赋值
                        */
                        // 从function_invocation_c中剥离出VAR_INPUT的赋值
                        v_explored_edge_list.push_back(
                                new Edge(v_edge_list[j]->get_from(), m_name_to_cfg[function_name]->get_entry(),
                                         invocation->formal_param_list));

                        // 从function_invocation_c中剥离出VAR_OUT的赋值
                        v_explored_edge_list.push_back(
                                new Edge(m_name_to_cfg[function_name]->get_exit(), v_edge_list[j]->get_to(),
                                         invocation->formal_param_list));


                    }
                }
            }
        }
    }
}