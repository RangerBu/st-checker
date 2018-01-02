#ifndef CFG_H
#define CFG_H

#include <vector>
#include <string>
#include <queue>

#include "absyntax/absyntax.hh"

#include "Node.h"
#include "Edge.h"
#include "../../analyzer/domain/Var.h"
#include "../../analyzer/transformer/assign_stmt_transfer.h"
#include "../../analyzer/transformer/elif_stmt_transfer.h"
#include "../../analyzer/transformer/if_stmt_transfer.h"

class CFG
{
public:
    CFG();
    CFG(statement_list_c *);
    virtual ~CFG();

    bool is_false_edge(Edge *);
    void insert_node(Node *);
    void insert_edge(Edge *);

    /**
    * getters and setters
    */
    std::vector<Node *> get_nodes();
    std::vector<Edge *> get_edges();
    statement_list_c *get_stmts_list();
    void set_stmts_list(statement_list_c *);
    std::vector<Var *> get_vars();
    void set_vars(std::vector<Var *>);

    /**
    * helpers
    */
    void print(std::ostream &);
    void print_dot(std::ostream &);
    friend std::ostream &operator<<(std::ostream &, CFG &);
    friend std::ostream &operator<<(std::ostream &, CFG *);



private:
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    statement_list_c *stmts_list;
    std::vector<Var *> vars;

    std::vector<Edge *> false_edges;

    /**
    * helpers
    */
    void init();
    void refine();
    void compute_weight();

};

#endif // CFG_H
