//
// Created by zero on 1/18/18.
//

#include "cfg.h"
#include "../../parser/st_parser.h"

/**
* public methods
*/
/*
* create a cfg with statement list using this constructor
*/
CFG::CFG(statement_list_c *_statement_list)
{
    statement_list = _statement_list;

    start_node = new Node("Start");
    end_node = new Node("End");

    init();
}

/*
* de-constructor
*/
CFG::~CFG()
{

}


/**
* getters and setters
*/
std::vector<Node *> CFG::get_node_list()
{
    return node_list;
}

std::vector<Edge *> CFG::get_edge_list()
{
    return edge_list;
}

std::vector<Var *> CFG::get_var_list()
{
    return var_list;
}

void CFG::set_var_list(std::vector<Var *> _var_list)
{
    for (int i=0; i<_var_list.size(); i++)
    {
        var_list.push_back(_var_list[i]);
    }
}

std::map<Edge *, Abstract_value_set_transfer *> CFG::get_weight_map()
{
    return weight_map;
}

Node *CFG::get_start_node()
{
    return start_node;
}

Node *CFG::get_end_node()
{
    return end_node;
}


/**
* helpers
*/
std::ostream &CFG::print(std::ostream &_out)
{
    // print nodes
    for (int i=0; i<node_list.size(); i++)
    {
        _out << node_list[i] << "\n";
    }

    // print edges
    for (int i=0; i<edge_list.size(); i++)
    {
        _out << edge_list[i] << "\n";
    }
    return _out;
}

std::ostream &CFG::print_dot(std::ostream &_out)
{
    _out << "digraph \"CFG\" \{\n";

    // print nodes in node_list
    for (int i=0; i<node_list.size(); i++)
    {
        _out << "\"" << node_list[i]->get_str_node() << "\" [label=\"" << node_list[i] << "\", color=lightblue,style=filled,shape=box]\n";
    }

    // print edges in edge_list
    for (int i=0; i<edge_list.size(); i++)
    {
        _out << "\"" << edge_list[i]->get_from()->get_str_node() << "\" -> \"" << edge_list[i]->get_to()->get_str_node();

        //print weight of each edge
        _out << "\" [label=\"[ "<< weight_map[edge_list[i]]->to_string() <<" ]\",color=black]\n";
    }
    return _out << "}\n";
}

std::ostream &operator << (std::ostream &_out, CFG *_cfg)
{
    return _cfg->print(_out);
}

/*
* if the edge _edge in false_edge_set, then return true
*/
bool CFG::is_false_edge(Edge *_edge)
{
    std::set<Edge *>::iterator it = false_edge_set.find(_edge);

    if (it != false_edge_set.end())
    {
        return true;
    }
    return false;
}

/*
* insert a node in node_list
*/
void CFG::insert_node(Node *_node)
{
    std::stringstream ss;
    ss << "n" << node_list.size();
    _node->set_str_node(ss.str());

    node_list.push_back(_node);
}

/*
* inset an edge in edge_list
*/
void CFG::insert_edge(Edge *_edge)
{
    edge_list.push_back(_edge);
}

void CFG::init()
{
    // Start
    Node *f = start_node; insert_node(f);

    if (statement_list ==0 || statement_list->n < 1)
    {
        std::cerr << "Passed an invalid statement_list_c object in CFG::Init()" << std::endl;
        exit(0);
    }

    Node *t = 0;
    for (int i=0; i<statement_list->n; i++)
    {
        t = new Node(statement_list->get_element(i));

        insert_node(t);
        insert_edge(new Edge(f, t));

        f = t;
    }

    // End
    t = end_node;

    insert_node(t);
    insert_edge(new Edge(f, t));

    refine();

    compute_weight();
}

void CFG::refine()
{
    std::queue<Edge *> refine_queue;
    for (std::vector<Edge *>::iterator it = edge_list.begin(); it != edge_list.end(); )
    {
        if ((*it)->get_from()->get_str_type().compare(Node::IF) == 0)
        {
            refine_queue.push(*it);
            it = edge_list.erase(it);
        }
        else
        {
            ++it;
        }
    }

    Edge *e = 0;
    Node *f = 0, *t = 0;

    Edge *new_e = 0;
    Node *new_f = 0, *new_t = 0;

    while (refine_queue.size() > 0)
    {
        e = refine_queue.front(); refine_queue.pop();
        f = e->get_from();
        t = e->get_to();

        if (f->get_str_type().compare(Node::IF) == 0)
        {
            if_statement_c *if_stmt = (if_statement_c *)(f->get_stmt());

            // when condition is true
            statement_list_c *if_stmts_list = (statement_list_c *)if_stmt->statement_list;
            new_f = f;
            new_t = 0;
            new_e = 0;

            if (if_stmts_list != 0)
            {
                for (int i=0; i<if_stmts_list->n; ++i)
                {
                    new_t = new Node(if_stmts_list->get_element(i));
                    insert_node(new_t);

                    new_e = new Edge(new_f, new_t);
                    if (new_f->get_str_type().compare(Node::IF) == 0)
                    {
                        if (i > 0)
                        {
                            refine_queue.push(new_e);
                        }
                        else
                        {
                            insert_edge(new_e);
                        }

                    }
                    else
                    {
                        insert_edge(new_e);
                    }
                    new_f = new_t;
                }

                // last statement
                new_e = new Edge(new_f, t);
                if (new_f->get_str_type().compare(Node::IF) == 0)
                {
                    refine_queue.push(new_e);
                }
                else
                {
                    insert_edge(new_e);
                }
            }

            // when condition is false
            //else_if_list
            elseif_statement_list_c *elif_list = (elseif_statement_list_c *)if_stmt->elseif_statement_list;
            new_f = f;
            new_t = 0;
            new_e = 0;

            if (elif_list !=0 && elif_list->n > 0)
            {
                for (int i=0; i<elif_list->n; ++i)
                {
                    new_t = new Node(elif_list->get_element(i));
                    insert_node(new_t);

                    new_e = new Edge(new_f, new_t);
                    insert_edge(new_e);

                    false_edge_set.insert(new_e);

                    statement_list_c *elif_stmts_list = (statement_list_c *) ((elseif_statement_c *)new_t->get_stmt())->statement_list;
                    Node *ff = new_t, *tt = 0;
                    new_e = 0;
                    for (int j=0; j<elif_stmts_list->n; ++j)
                    {
                        tt = new Node(elif_stmts_list->get_element(j));
                        insert_node(tt);

                        new_e = new Edge(ff, tt);

                        if(ff->get_str_type().compare(Node::IF) == 0)
                        {
                            refine_queue.push(new_e);
                        }
                        else
                        {
                            insert_edge(new_e);
                        }
                        ff = tt;
                    }

                    // last statement
                    new_e = new Edge(ff, t);
                    if(ff->get_str_type().compare(Node::IF) == 0)
                    {
                        refine_queue.push(new_e);
                    }
                    else
                    {
                        insert_edge(new_e);
                    }

                    new_f = new_t;
                }
                // else
                statement_list_c *else_stmts_list = (statement_list_c *)if_stmt->else_statement_list;
                if (else_stmts_list !=0 && else_stmts_list->n > 0)
                {
                    for(int i=0; i<else_stmts_list->n; ++i)
                    {
                        new_t = new Node(else_stmts_list->get_element(i));
                        new_e = new Edge(new_f, new_t);
                        if (i==0)
                        {
                            false_edge_set.insert(new_e);
                        }
                        insert_node(new_t);

                        if(new_f->get_str_type().compare(Node::IF) == 0)
                        {
                            refine_queue.push(new_e);
                        }
                        else
                        {
                            insert_edge(new_e);
                        }
                        new_f = new_t;
                    }
                    new_e = new Edge(new_f, t);
                    if (new_f->get_str_type().compare(Node::IF) == 0)
                    {
                        refine_queue.push(new_e);
                    }
                    else
                    {
                        insert_edge(new_e);
                    }
                }
                else
                {
                    new_e = new Edge(new_f, t);
                    insert_edge(new_e);
                    false_edge_set.insert(new_e);
                }

            }
            else
            {
                //else
                statement_list_c *else_stmts_list = (statement_list_c *)if_stmt->else_statement_list;
                if (else_stmts_list !=0 && else_stmts_list->n > 0)
                {
                    new_f = f;
                    new_t = 0;
                    new_e = 0;
                    for (int i=0; i<else_stmts_list->n; i++)
                    {
                        new_t = new Node(else_stmts_list->get_element(i));
                        new_e = new Edge(new_f, new_t);
                        if(i==0)
                        {
                            false_edge_set.insert(new_e);
                        }
                        insert_node(new_t);

                        if(new_f->get_str_type().compare(Node::IF) == 0)
                        {
                            if (i > 0)
                            {
                                refine_queue.push(new_e);
                            }
                            else
                            {
                                insert_edge(new_e);
                            }
                        }
                        else
                        {
                            insert_edge(new_e);
                        }
                        new_f = new_t;
                    }
                    new_e = new Edge(new_f, t);
                    if (new_f->get_str_type().compare(Node::IF) == 0)
                    {
                        refine_queue.push(new_e);
                    }
                    else
                    {
                        insert_edge(new_e);
                    }
                }
                else
                {
                    new_e = new Edge(f, t);
                    insert_edge(new_e);
                    false_edge_set.insert(new_e);
                }
            }


        }
        else
        {
            std::cout << "unsupported Node types!\n";
        }
    }
}

void CFG::compute_weight()
{
    Node *from = 0;

    Abstract_value_set_transfer *transfer = 0;
    for (int i=0; i<edge_list.size(); i++)
    {
        from = edge_list[i]->get_from();

        if (from->get_str_type().compare(Node::IF) == 0 || from->get_str_type().compare(Node::ELSE_IF) == 0)
        {
            if (is_false_edge(edge_list[i]))
            {
                transfer = new Elif_stmt_transfer(from->get_stmt());
            }
            else
            {
                transfer = new If_stmt_transfer(from->get_stmt());
            }
        }
        else if (from->get_str_type().compare(Node::ASSIGNMENT) == 0)
        {
            transfer = new Assign_stmt_transfer(from->get_stmt());

        }
        else
        {
            transfer = Abstract_value_set_transfer::get_identity();
        }
        weight_map[edge_list[i]] = transfer;
    }
}


/**
* helpers - debug only
*/

