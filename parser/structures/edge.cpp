//
// Created by Samson on 2018/5/30.
//

#include "edge.h"

Edge::Edge(Vertex *_from, Vertex *_to, symbol_c *_label)
{
    from = _from;
    to = _to;
    label = _label;
}

Edge::~Edge()
{
}

/**
* getters and setters
*/
Vertex* Edge::get_from()
{
    return from;
}

Vertex* Edge::get_to()
{
    return to;
}

symbol_c* Edge::get_label()
{
    return label;
}

/**
* helpers
*/
bool Edge::equals(Edge *_other)
{
    /*
     * 补充： 加上label之间相等的条件
     */
    return from->equal(_other->get_from()) && to->equal(_other->get_to());
}

std::ostream &operator<<(std::ostream &_out, Edge &_edge)
{
    return _out << (*_edge.get_from()) << "(" << _edge.get_label() << ")" << (*_edge.get_to());

}