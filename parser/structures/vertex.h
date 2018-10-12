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
    // 每创建一个实例，计数器加1
    static int counter;

    // 类实例的唯一标识符
    int id;

    // 字符串类型的对象名
    std::string str_vertex_name;

};


#endif //VERIFY_ST_PROGRAMS_VERTEX_H
