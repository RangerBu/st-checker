#ifndef CFG_H
#define CFG_H

#include <string>
#include <vector>

#include "absyntax/absyntax.hh"

using std::string;

enum CFG_TYPE
{
    FUNCTION = 1,
    FUNCTION_BLOCK,
    PROGRAM
};
enum NODE_TYPE
{
    WRONG_NODE_TYPE = -1,
    START = 0,
    ASSIGNMENT,
    RETURN,
    FB_INVOCATION,
    IF,
    ELSEIF_LIST,
    ELSEIF,
    CASE,
    CASE_ELEMENT_LIST,
    CASE_ELEMENT,
    FOR,
    WHILE,
    REPEAT,
    EXIT,
    END
};


class Node
{
public:
    /**
    * 节点名称
    * start,end节点只有name，statement为null
    * 其他节点，name是statement的字符串形式
    */
    string name;

    int type; // 节点类型，NODE_TYPE中的一个

    symbol_c *statement; // 节点对应的语句

    int number_of_predecessor; // 流入当前节点的控制流数量

    std::vector<Node *> successors; // 当前节点的后继

public:
    Node(string);
    Node(symbol_c *);
    virtual ~Node();
};

class CFG
{
public:
    string name; // 函数名称

    int type; // FUNCTION or FUNCTION_BLOCK or PROGRAM

    symbol_c *pou; //该pou对应的symbol_c
    statement_list_c *stmt_list; // body部分的语句列表

    Node *start; // CFG入口

    CFG(symbol_c *);
    virtual ~CFG();

    void print_CFG();
    void init_CFG();
    void refine_CFG();


private:
    statement_list_c *statements;

};

#endif // CFG_H
