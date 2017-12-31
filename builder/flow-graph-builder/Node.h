#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>

#include "absyntax/absyntax.hh"

class Node{

    /**
    * static constants
    */

public:
    static const std::string ENTRY;
    static const std::string ASSIGNMENT;
    static const std::string RETURN;
    static const std::string FB_INVOCATION;
    static const std::string IF;
    static const std::string ELSE_IF;
    static const std::string FOR;
    static const std::string EXIT;

    /**
    * public methods
    */

public:
    Node(std::string);
    Node(symbol_c *);
    virtual ~Node();

    /**
    *  getters and setters
    */

    std::string get_str_stmt();
    void set_str_stmt(std::string);
    symbol_c *get_stmt();
    void set_stmt(symbol_c *);
    std::string get_node_type();

    // used in print_dot
    std::string get_str_node_name();
    void set_str_node_name(std::string);

    /**
    * helpers
    */

    void print(std::ostream &);
    void print_dot(std::ostream &);
    friend std::ostream &operator<<(std::ostream &, Node &);
    friend std::ostream &operator<<(std::ostream &, Node *);

    /**
    * private attributes and methods
    */

private:
    std::string str_stmt;
    symbol_c *stmt;
    std::string type;
    //used in print_dot
    std::string str_node_name;

    void init_node_type();

};


#endif // NODE_H
