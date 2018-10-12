//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_EDGE_H
#define VERIFY_ST_PROGRAMS_EDGE_H

#include "absyntax/absyntax.hh"

#include "vertex.h"

class Edge
{
public:
    Edge(Vertex *_from, Vertex *_to, symbol_c *_label);

    virtual ~Edge();

    /**
     * getters and setters
     */
    Vertex *get_from();

    Vertex *get_to();

    symbol_c *get_label();

    /**
     * helpers
     */
    bool equals(Edge *_other);

    friend std::ostream &operator<<(std::ostream &_out, Edge &_edge);


private:
    // ����ߵ���ʼ�ڵ�
    Vertex *from;

    // ����ߵ���ֹ�ڵ�
    Vertex *to;

    // ���ϵı�ǩ
    symbol_c *label;
};


#endif //VERIFY_ST_PROGRAMS_EDGE_H
