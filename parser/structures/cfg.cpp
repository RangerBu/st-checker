//
// Created by Samson on 2018/5/30.
//

#include <queue>

#include "cfg.h"
#include "../../debug_helper.h"
#include "../visitors/symbol_to_string_visitor.h"

CFG::CFG(std::string _str_cfg_name, statement_list_c *_statement_list) :
        str_cfg_name(_str_cfg_name), statement_list(_statement_list)
{
    entry = new Vertex(str_cfg_name + "_entry");
    exit = new Vertex(str_cfg_name + "_exit");

    v_vertex_list.push_back(entry);

    /**
     * 初始化
     */
    Vertex *from = entry, *to = 0;

    if (statement_list == 0 || statement_list->n < 1)
    {
        Debug_helper::print_debug_info(__FILE__, __LINE__, "传入的程序语句statement_list_c对象为空");
        std::exit(233);
    }

    from = entry;
    to = new Vertex(); v_vertex_list.push_back(to);
    v_edge_list.push_back(new Edge(from, to, 0));
    from = to;

    for (int i = 0; i < statement_list->n - 1; ++i)
    {
        to = new Vertex(); v_vertex_list.push_back(to);

        v_edge_list.push_back(new Edge(from, to, statement_list->get_element(i)));

        from = to;
    }

    v_edge_list.push_back(new Edge(from, exit, statement_list->get_element(statement_list->n - 1)));

    /**
     * 计算需要精化的边列表 - 将if, while等精化
     */
    std::queue<Edge *> q_refine_list;
    for (std::vector<Edge *>::iterator it = v_edge_list.begin(); it != v_edge_list.end();)
    {
        if ((*it)->get_label() == 0)
        {
            ++it;
        } else {
            std::string str_cname = (*it)->get_label()->absyntax_cname();

            if (str_cname.compare("if_statement_c") == 0 || str_cname.compare("while_statement_c") == 0)
            {
                q_refine_list.push(*it);
                it = v_edge_list.erase(it);
            } else {
                ++it;
            }
        }
    }

    Edge *e = 0;
    Vertex *from_new = 0, *to_new = 0;

    while (q_refine_list.size() > 0)
    {
        e = q_refine_list.front();
        q_refine_list.pop();

        from = e->get_from();
        to = e->get_to();

        string str_cname = e->get_label()->absyntax_cname();
        if (str_cname.compare("if_statement_c") == 0)
        {
            if_statement_c *if_statement = (if_statement_c *) e->get_label();

            // 条件为真
            to_new = new Vertex(); v_vertex_list.push_back(to_new);

            v_edge_list.push_back(new Edge(from, to_new, if_statement->expression));

            from_new = to_new;
            to_new = to;

            if (((statement_list_c *) if_statement->statement_list)->n > 0)
            {
                q_refine_list.push(new Edge(from_new, to_new, if_statement->statement_list));
            } else
            {
                v_edge_list.push_back(new Edge(from_new, to_new, 0));
            }

            // 条件为假
            to_new = new Vertex(); v_vertex_list.push_back(to_new);

            v_edge_list.push_back(new Edge(from, to_new, new not_expression_c(if_statement->expression)));

            // 如果有ELSEIF
            elseif_statement_list_c *elseif_list = (elseif_statement_list_c *) if_statement->elseif_statement_list;
            if (elseif_list->n > 0)
            {
                from_new = to_new;

                for (int i = 0; i < elseif_list->n; ++i)
                {
                    elseif_statement_c *elseif_statement = (elseif_statement_c *) elseif_list->get_element(i);

                    // 条件为真
                    to_new = new Vertex(); v_vertex_list.push_back(to_new);

                    v_edge_list.push_back(new Edge(from_new, to_new, elseif_statement->expression));

                    if (((statement_list_c *) elseif_statement->statement_list)->n > 0)
                    {
                        q_refine_list.push(new Edge(to_new, to, elseif_statement->statement_list));
                    } else
                    {
                        v_edge_list.push_back(new Edge(to_new, to, 0));
                    }

                    // 条件为假
                    to_new = new Vertex(); v_vertex_list.push_back(to_new);

                    v_edge_list.push_back(new Edge(from_new, to_new, new not_expression_c(elseif_statement->expression)));

                    from_new = to_new;
                }
            }

            // 如果有ELSE
            if (if_statement->else_statement_list != 0)
            {
                from_new = to_new;

                if (((statement_list_c *) if_statement->else_statement_list)->n > 0)
                {
                    q_refine_list.push(new Edge(from_new, to, if_statement->else_statement_list));
                } else {
                    v_edge_list.push_back(new Edge(from_new, to, 0));
                }
            }

        } else if (str_cname.compare("while_statement_c") == 0)
        {
            while_statement_c *while_statement = (while_statement_c *) e->get_label();

            // 条件为真
            to_new = new Vertex(); v_vertex_list.push_back(to_new);

            v_edge_list.push_back(new Edge(from, to_new, while_statement->expression));

            if (((statement_list_c *)while_statement->statement_list)->n > 0)
            {
                q_refine_list.push(new Edge(to_new, from, while_statement->statement_list));
            } else {
                v_edge_list.push_back(new Edge(to_new, from, 0));
            }

            // 条件为假
            v_edge_list.push_back(new Edge(from, to, new not_expression_c(while_statement->expression)));

        } else if (str_cname.compare("statement_list_c") == 0)
        {
            statement_list_c *statement_list = (statement_list_c *) e->get_label();

            from_new = from;

            for (int i = 0; i < statement_list->n - 1; ++i)
            {
                to_new = new Vertex(); v_vertex_list.push_back(to_new);

                std::string str_cname = statement_list->get_element(i)->absyntax_cname();

                if (str_cname.compare("if_statement_c") == 0 || str_cname.compare("while_statement_c") == 0)
                {
                    q_refine_list.push(new Edge(from_new, to_new, statement_list->get_element(i)));
                } else
                {
                    v_edge_list.push_back(new Edge(from_new, to_new, statement_list->get_element(i)));
                }
                from_new = to_new;
            }

            std::string str_cname = statement_list->get_element(statement_list->n - 1)->absyntax_cname();
            if (str_cname.compare("if_statement_c") == 0 || str_cname.compare("while_statement_c") == 0)
            {
                q_refine_list.push(new Edge(from_new, to, statement_list->get_element(statement_list->n - 1)));
            } else
            {
                v_edge_list.push_back(new Edge(from_new, to, statement_list->get_element(statement_list->n - 1)));
            }

        } else {
            Debug_helper::print_debug_info(__FILE__, __LINE__, "精化过程中遇到了不支持的边类型");
            std::exit(233);
        }
    }
    v_vertex_list.push_back(exit);

    // 增加表示扫描周期的边
//    v_edge_list.push_back(new Edge(exit, entry, 0));

}
CFG::~CFG()
{
}

/**
 * getters and setters
 */
std::vector<Vertex *> CFG::get_vertex_list()
{
    return v_vertex_list;
}

std::vector<Edge *> CFG::get_edge_list()
{
    return v_edge_list;
}

Vertex* CFG::get_entry()
{
    return entry;
}

Vertex* CFG::get_exit()
{
    return exit;
}

statement_list_c* CFG::get_statement_list()
{
    return statement_list;
}

std::string CFG::get_str_cfg_name()
{
    return str_cfg_name;
}

std::ostream &operator<<(std::ostream &_out, CFG &_cfg)
{
    _out << "digraph \"" << _cfg.str_cfg_name << "\" {\n";

    // 打印点信息
    for (int i = 0; i < _cfg.v_vertex_list.size(); ++i)
    {
        _out << "\"" << (*_cfg.v_vertex_list[i]) << "\" [label=\"" << (*_cfg.v_vertex_list[i]) << "\", color=lightblue,style=filled,shape=box]\n";
    }

    // 打印边信息
    for (int j = 0; j < _cfg.v_edge_list.size(); ++j)
    {
        // 打印边
        _out << "\"" << (*_cfg.v_edge_list[j]->get_from()) << "\" -> \"" << (*_cfg.v_edge_list[j]->get_to());

        // 打印边上标记
        if (_cfg.v_edge_list[j]->get_label() == 0)
        {
            _out << "\" [label=\"[ 0 ]\",color=black]\n";
        } else {
            _out << "\" [label=\"[ " << Symbol_to_string_visitor::parse(_cfg.v_edge_list[j]->get_label()) <<" ]\",color=black]\n";
        }
    }
    return _out << "}\n";
}