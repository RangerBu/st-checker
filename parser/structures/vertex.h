//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_VERTEX_H
#define VERIFY_ST_PROGRAMS_VERTEX_H

#include <string>
#include <iostream>

class Vertex
{
public:
    Vertex();

    Vertex(std::string _str_vertex_name);

    virtual ~Vertex();


    /**
     * getters and setters
     */
    std::string get_str_vertex_name();

    int get_id();

    bool equal(Vertex *_other);

    friend std::ostream &operator<<(std::ostream &_out, Vertex &_vertex);

    /**
     * private attribute
     */
private:
    // ÿ����һ��ʵ������������1
    static int counter;

    // ��ʵ����Ψһ��ʶ��
    int id;

    // �ַ������͵Ķ�����
    std::string str_vertex_name;

};


#endif //VERIFY_ST_PROGRAMS_VERTEX_H
