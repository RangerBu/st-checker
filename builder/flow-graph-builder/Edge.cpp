#include "Edge.h"

Edge::Edge(Node *_from, Node *_to)
{
    from = _from;
    to = _to;

    if_true = false;
}
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
void Edge::set_from(Node *_from)
{
    from = _from;
}
Node *Edge::get_to()
{
    return to;
}
void Edge::set_to(Node *_to)
{
    to = _to;
}
Value_set_transfer *Edge::get_weight()
{
    return weight;
}
void Edge::set_weight(Value_set_transfer *_weight)
{
    weight = _weight;
}
bool Edge::get_if_true()
{
    return if_true;
}
void Edge::set_if_true()
{
    if_true = true;
}


/**
* helpers
*/
void Edge::print(std::ostream &out)
{
    out << *this;
}
void Edge::print_dot(std::ostream &out)
{
    // not implemented
}
std::ostream &operator<<(std::ostream &out, Edge &e)
{
    out << e.get_from() << "----->" << e.get_to();
    return out;
}
std::ostream &operator<<(std::ostream &out, Edge *e)
{
    out << *e;
    return out;
}
bool Edge::equals(Edge *_other)
{
    return from->equals(_other->get_from()) && to->equals(_other->get_to());
}
