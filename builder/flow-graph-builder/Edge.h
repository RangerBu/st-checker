#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "Node.h"
#include "../../analyzer/transformer/Abstract_transfer.h"

class Edge{
public:
    Edge(Node *, Node *);
    virtual ~Edge();

    /**
    * getters and setters
    */
    Node *get_from();
    void set_from(Node *);
    Node *get_to();
    void set_to(Node *);
    Abstract_transfer *get_weight();
    void set_weight(Abstract_transfer *);

    bool get_if_true();
    void set_if_true();

    /**
    * helpers
    */
    void print(std::ostream &);
    void print_dot(std::ostream &);
    friend std::ostream &operator<<(std::ostream &, Edge &);
    friend std::ostream &operator<<(std::ostream &, Edge *);

private:
    Node *from;
    Node *to;
    Abstract_transfer *weight;

    bool if_true;

};

#endif // EDGE_H
