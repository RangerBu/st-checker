#include "CFG.h"
#include "../../parser/ST_parser.h"

CFG::CFG()
{

}
CFG::CFG(statement_list_c *_stmts_list)
{
    stmts_list = _stmts_list;
    init();
}
CFG::~CFG()
{

}
bool CFG::is_false_edge(Edge *_edge)
{
    int len = false_edges.size();
    for (int i=0; i<len; i++)
    {
        if (_edge->equals(false_edges[i]))
        {
            return true;
        }
    }
    return false;
}


/**
* getters and setters
*/
std::vector<Node *> CFG::get_nodes()
{
    return nodes;
}
std::vector<Edge *> CFG::get_edges()
{
    return edges;
}
statement_list_c *CFG::get_stmts_list()
{
    return stmts_list;
}
void CFG::set_stmts_list(statement_list_c *_stmts_list)
{
    stmts_list = _stmts_list;
}
std::vector<Var *> CFG::get_vars()
{
    return vars;
}
void CFG::set_vars(std::vector<Var *> _vars)
{
    vars = _vars;
}


/**
* helpers
*/
void CFG::print(std::ostream &out)
{
    out << *this;
}
void CFG::print_dot(std::ostream &out)
{
    out << "digraph \"CFG\" \{\n";
    // output nodes
    int n_len = nodes.size();
    int e_len = edges.size();

    for (int i=0; i<n_len; i++)
    {
        std::string str_node_name = "n";
        str_node_name.push_back((char)('0' + i));
        out << "\"" << str_node_name << "\" [label=\"" << nodes[i] << "\", color=lightblue,style=filled,shape=box]\n";
        nodes[i]->set_str_node_name(str_node_name);
    }
    Abstract_transfer *w = 0;
    for (int i=0; i<e_len; i++)
    {
        Edge *e = edges[i];
        w = e->get_weight();
        out << "\"" << e->get_from()->get_str_node_name() << "\" -> \"" << e->get_to()->get_str_node_name();
//        out << "\" [label=\"[" << w->get_left_var() << " to " << w->get_right_var1() << " " << w->get_op() << " " << w->get_right_var2() <<"]\",color=black]\n";
        std::string false_edge;
        if (w != 0)
        {
            false_edge = w->format();
        }
        else
        {
            false_edge = "T";
        }
        out << "\" [label=\"[ "<< false_edge <<" ]\",color=black]\n";
    }
    out << "}\n";
}
std::ostream &operator<<(std::ostream &out, CFG &c)
{
    std::vector<Edge *>::iterator it = c.get_edges().begin();
    while(it != c.get_edges().end())
    {
        out << *it << "\n";
        ++it;
    }
    return out;
}
std::ostream &operator<<(std::ostream &out, CFG *c)
{
    out << *c;
    return out;
}


/**
* private helpers
*/
void CFG::init()
{
    Node *f = new Node("Start");
    Node *t;
    int len = stmts_list->n;

    nodes.push_back(f);
    for (int i=0; i<len; i++)
    {
        t = new Node(stmts_list->get_element(i));
        nodes.push_back(t);
        edges.push_back(new Edge(f, t));
        f = t;
    }
    t = new Node("End");
    nodes.push_back(t);
    edges.push_back(new Edge(f, t));

    refine();
    std::cout << false_edges.size() << std::endl;
    compute_weight();
}
void CFG::refine()
{

    std::queue<Edge *> re_queue;
    std::vector<Edge *>::iterator it;
    for (it = edges.begin(); it != edges.end(); )
    {

        if ((*it)->get_from()->get_node_type().compare(Node::IF) == 0)
        {
            re_queue.push(*it);
            it = edges.erase(it);
        }
        else
        {
            it++;
        }
    }
    Edge *e = 0;
    Node *f = 0, *t = 0;
    while (re_queue.size() > 0)
    {
        e = re_queue.front(); re_queue.pop();
        f = e->get_from();
        t = e->get_to();

        if (f->get_node_type().compare(Node::IF) == 0)
        {
            if_statement_c *if_stmt = (if_statement_c *)(f->get_stmt());

            // when condition is true
            statement_list_c *if_stmts_list = (statement_list_c *)if_stmt->statement_list;
            Node *new_f = f, *new_t = 0;
            Edge *new_e = 0;

            if (if_stmts_list != 0)
            {
                for (int i=0; i<if_stmts_list->n; ++i)
                {
                    new_t = new Node(if_stmts_list->get_element(i));
                    new_e = new Edge(new_f, new_t);
                    nodes.push_back(new_t);

                    if (i>0 && new_f->get_node_type().compare(Node::IF) == 0)
                    {
                        re_queue.push(new_e);
                    }
                    else
                    {
                        if (i==0)new_e->set_if_true();
                        edges.push_back(new_e);
                    }
                    new_f = new_t;
                }
                new_e = new Edge(new_f, t);
                if (new_f->get_node_type().compare(Node::IF) == 0)
                {
                    re_queue.push(new_e);
                }
                else
                {
                    edges.push_back(new_e);
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
                    new_e = new Edge(new_f, new_t);
                    nodes.push_back(new_t);
                    edges.push_back(new_e);
                    false_edges.push_back(new_e);
                    new_e = 0;

                    statement_list_c *elif_stmts_list = (statement_list_c *) ((elseif_statement_c *)new_t->get_stmt())->statement_list;
                    Node *ff = new_t, *tt = 0;
                    for (int j=0; j<elif_stmts_list->n; ++j)
                    {
                        tt = new Node(elif_stmts_list->get_element(j));
                        nodes.push_back(tt);
                        new_e = new Edge(ff, tt);

                        if(ff->get_node_type().compare(Node::IF) == 0)
                        {
                            re_queue.push(new_e);
                        }
                        else
                        {
                            if (j==0) new_e->set_if_true();
                            edges.push_back(new_e);
                        }
                        ff = tt;
                    }
                    new_e = new Edge(ff, t);
                    if(ff->get_node_type().compare(Node::IF) == 0)
                    {
                        re_queue.push(new_e);
                    }
                    else
                    {
                        edges.push_back(new_e);
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
                            false_edges.push_back(new_e);
                        }
                        nodes.push_back(new_t);

                        if(new_f->get_node_type().compare(Node::IF) == 0)
                        {
                            re_queue.push(new_e);
                        }
                        else
                        {
                            edges.push_back(new_e);
                        }
                        new_f = new_t;
                    }
                    new_e = new Edge(new_f, t);
                    if (new_f->get_node_type().compare(Node::IF) == 0)
                    {
                        re_queue.push(new_e);
                    }
                    else
                    {
                        edges.push_back(new_e);
                    }
                }
                else
                {
                    new_e = new Edge(new_f, t);
                    edges.push_back(new_e);
                    false_edges.push_back(new_e);
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
                            false_edges.push_back(new_e);
                        }
                        nodes.push_back(new_t);

                        if(i>0 && new_f->get_node_type().compare(Node::IF) == 0)
                        {
                            re_queue.push(new_e);
                        }
                        else
                        {
                            edges.push_back(new_e);
                        }
                        new_f = new_t;
                    }
                    new_e = new Edge(new_f, t);
                    if (new_f->get_node_type().compare(Node::IF) == 0)
                    {
                        re_queue.push(new_e);
                    }
                    else
                    {
                        edges.push_back(new_e);
                    }
                }
                else
                {
                    new_e = new Edge(f, t);
                    edges.push_back(new_e);
                    false_edges.push_back(new_e);
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
    int n = edges.size();
    Node *from = 0;
    Abstract_transfer *weight = 0;
    for (int i=0; i<n; i++)
    {
        from = edges[i]->get_from();

        Abstract_transfer *transfer = 0;
        if (from->get_node_type().compare(Node::IF) == 0 || from->get_node_type().compare(Node::ELSE_IF) == 0)
        {
            if (is_false_edge(edges[i]))
            {
                transfer = new Elif_stmt_transfer(from->get_stmt());
                edges[i]->set_weight(transfer);
            }
            else
            {
                transfer = new If_stmt_transfer(from->get_stmt());
                edges[i]->set_weight(transfer);
            }
        }
        else if (from->get_node_type().compare(Node::ASSIGNMENT) == 0)
        {
            transfer = new Assign_stmt_transfer(from->get_stmt());
            edges[i]->set_weight(transfer);
        }
        else
        {
            edges[i]->set_weight(0);
        }
    }
}
