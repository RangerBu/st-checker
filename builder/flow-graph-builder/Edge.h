#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "Node.h"

class Edge{
    /**
    * public attributes
    */
public:
    /*
    * create an edge with start node and end node using this constructor
    */
    Edge(Node *, Node *);

    /*
    * de-constructor
    */
    virtual ~Edge();


    /**
    * getters and setters
    */
    Node *get_from();

    Node *get_to();


    /**
    * helpers
    */
    bool equal(Edge *);

    std::ostream &print(std::ostream &);

    friend std::ostream &operator<<(std::ostream &, Edge *);

    /**
    * helpers - debug only
    */


    /**
    * private attributes
    */
private:
    /*
    * the start node of a edge
    */
    Node *from;

    /*
    * the end node of a edge
    */
    Node *to;
};

#endif // EDGE_H
