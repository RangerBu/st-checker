#ifndef CFG_H
#define CFG_H

#include <vector>
#include <set>
#include <string>
#include <queue>

#include "absyntax/absyntax.hh"

#include "Node.h"
#include "Edge.h"
#include "../../analyzer/domain/Var.h"
#include "../../analyzer/transformer/value_set_transfer.h"
#include "../../analyzer/transformer/assign_stmt_transfer.h"
#include "../../analyzer/transformer/elif_stmt_transfer.h"
#include "../../analyzer/transformer/if_stmt_transfer.h"


class CFG
{
    /**
    * public methods
    */
public:
    /*
    * create a CFG with statement list
    */
    CFG(statement_list_c *);

    /*
    * de-constructor
    */
    virtual ~CFG();


    /**
    * getters and setters
    */


    std::vector<Node *> get_node_list();

    std::vector<Edge *> get_edge_list();

    std::vector<Var *> get_var_list();

    void set_var_list(std::vector<Var *>);

    std::map<Edge *, Value_set_transfer *> get_weight_map();


    /**
    * helpers
    */
    std::ostream &print(std::ostream &);

    std::ostream &print_dot(std::ostream &);

    bool is_false_edge(Edge *);

    void insert_node(Node *);

    void insert_edge(Edge *);

    void init();

    void refine();

    void compute_weight();


    /**
    * helpers - debug only
    */


    friend std::ostream &operator<<(std::ostream &, CFG *);


    /**
    * private attributes
    */
private:
    /*
    * all nodes in a cfg
    */
    std::vector <Node *> node_list;

    /*
    * all edges in a cfg
    */
    std::vector<Edge *> edge_list;

    /*
    * weights that assigned to edges
    */
    std::map<Edge *, Value_set_transfer *> weight_map;

    /*
    * all false edges who has a Node::IF type start node and the condition is false
    */
    std::set<Edge *> false_edge_set;

    /*
    * all variables appeared in a cfg
    */
    std::vector<Var *> var_list;

    /*
    * the attached statements
    */
    statement_list_c *statement_list;


};

#endif // CFG_H
