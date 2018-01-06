#include "Edge.h"

/**
* public attributes
*/
/*
* create an edge with start node _from and end node _to using this constructor
*/
Edge::Edge(Node *_from, Node *_to)
{
    from = _from;
    to = _to;
}

/*
* de-constructor
*/
Edge::~Edge()
{

}


/**
* getters and setters
*/
Node *Edge::get_from()
{
    return from;
}

Node *Edge::get_to()
{
    return to;
}


/**
* helpers
*/
bool Edge::equal(Edge *_other)
{
    return from->equal(_other->get_from()) && to->equal(_other->get_to());
}

std::ostream &Edge::print(std::ostream &_out)
{
    return  to->print(from->print(_out) << " ---> ");
}

std::ostream &operator<<(std::ostream &_out, Edge *_edge)
{
    return _edge->print(_out);
}


/**
* helpers - debug only
*/

