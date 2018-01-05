#include "../../parser/ST_parser.h"

#include "Node.h"

/**
* static constants
*/
const std::string Node::ENTRY = "Start";
const std::string Node::ASSIGNMENT = "ASSIGNMENT";
const std::string Node::RETURN = "RETURN";
const std::string Node::FB_INVOCATION = "FB_INVOCATION";
const std::string Node::IF = "IF";
const std::string Node::ELSE_IF = "ELSE_IF";
const std::string Node::FOR = "FOR";
const std::string Node::EXIT = "End";






/**
* public methods
*/
/*
* create a Start node or End node with this constructor
*/
Node::Node(std::string _str_stmt)
{
    stmt = 0;
    str_stmt = _str_stmt;
    init_node_type();
}

/*
* create an internal node attached a statement (symbol *) with this constructor
*/
Node::Node(symbol_c *_stmt)
{
    stmt = _stmt;
    str_stmt = ST_parser::parse(_stmt);
    init_node_type();
}

/*
* de-constructor
*/
Node::~Node()
{
}

/**
* getters and setters
*/
std::string Node::get_str_stmt()
{
    return str_stmt;
}

symbol_c *Node::get_stmt()
{
    return stmt;
}

std::string Node::get_str_type()
{
    return str_type;
}

std::string Node::get_str_node()
{
    return str_node;
}

void Node::set_str_node(std::string _str_node)
{
    str_node = _str_node;
}


/**
* helpers
*/
bool Node::equal(Node *_other)
{
    if (this == _other)
    {
        return true;
    }
    return str_stmt.compare(_other->get_str_stmt()) == 0 && str_type.compare(_other->get_str_type()) == 0;
}

std::ostream &Node::print(std::ostream &_out)
{
    return _out << "[" << str_stmt << "]";
}

std::ostream &Node::print_dot(std::ostream &_out)
{
    //need to be implemented
}


/**
* helpers - debug only
*/
std::ostream &operator<<(std::ostream &_out, Node *_node)
{
    return _node->print(_out);
}


/**
* private attributes and methods
*/

void Node::init_node_type()
{
    if(stmt == 0)
    {
        if (str_stmt.compare(Node::ENTRY) == 0)
        {
            str_type = Node::ENTRY;
        }
        else if (str_stmt.compare(Node::EXIT) == 0)
        {
            str_type = Node::EXIT;
        }
        else
        {
            std::cout << "Incorrect Initial Node Type!\n";
        }
    }
    else
    {
        std::string str_stmt_type = stmt->absyntax_cname();

        if (str_stmt_type.compare("assignment_statement_c") == 0)
        {
            str_type = Node::ASSIGNMENT;
        }
        else if (str_stmt_type.compare("return_statement_c") == 0)
        {
            str_type = Node::RETURN;
        }
        else if (str_stmt_type.compare("fb_invocation_c") == 0)
        {
            str_type = Node::FB_INVOCATION;
        }
        else if (str_stmt_type.compare("if_statement_c") == 0)
        {
            str_type = Node::IF;
        }
        else if (str_stmt_type.compare("elseif_statement_c") ==0 )
        {
            str_type = Node::ELSE_IF;
        }
        else if (str_stmt_type.compare("for_statement_c") == 0)
        {
            str_type = Node::FOR;
        }
        else
        {
            std::cout << "Incorrect Initial Node Type!\n";
        }
    }
}
