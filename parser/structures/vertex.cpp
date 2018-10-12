//
// Created by Samson on 2018/5/30.
//

#include <sstream>

#include "vertex.h"

Vertex::Vertex() : id(counter)
{
    std::stringstream ss;
    ss << "n" << counter++;
    str_vertex_name = ss.str();
}

Vertex::Vertex(std::string _str_vertex_name) : id(counter)
{
    counter++;

    str_vertex_name = _str_vertex_name;
}

Vertex::~Vertex()
{
}

/**
* getters and setters
*/
std::string Vertex::get_str_vertex_name()
{
    return str_vertex_name;
}

int Vertex::get_id()
{
    return id;
}

bool Vertex::equal(Vertex *_other)
{
    return id == _other->get_id() || str_vertex_name.compare(_other->get_str_vertex_name()) == 0;
}

std::ostream &operator<<(std::ostream &_out, Vertex &_vertex)
{
    std::stringstream ss;
    ss << "[" << _vertex.str_vertex_name << "]";
    return _out << ss.str();
}

/**
* private attributes
*/
int Vertex::counter = 1;