#ifndef NODE_H
#define NODE_H

#include <string>
#include <sstream>
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
    /*
    * create a Start node or End node with this constructor
    */
    Node(std::string);

    /*
    * create an internal node attached a statement (symbol *) with this constructor
    */
    Node(symbol_c *);

    /*
    * de-constructor
    */
    virtual ~Node();

    /**
    *  getters and setters
    */
    std::string get_str_stmt();

    symbol_c *get_stmt();

    std::string get_str_type();

    std::string get_str_node();

    void set_str_node(std::string);


    /**
    * helpers
    */
    bool equal(Node *);

    std::ostream &print(std::ostream &);

    friend std::ostream &operator<<(std::ostream &, Node *);


    /**
    * helpers - debug only
    */
    std::string to_string();


    /**
    * private attributes and methods
    */
private:

    /*
    * the string form of the statement attached to this node
    */
    std::string str_stmt;

    /*
    * the statement attached to this node
    */
    symbol_c *stmt;

    /*
    * the type of this node
    */
    std::string str_type;

    /*
    * the string representation of this node
    *
    * used in print_dot() function
    */
    std::string str_node;

    /*
    * initiate the node type according to stmt or str_stmt
    */
    void init_node_type();

};


#endif // NODE_H
