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

Node::Node(symbol_c *_stmt)
{
    stmt = _stmt;
    str_stmt = ST_parser::parse(_stmt);
    init_node_type();
}
Node::Node(std::string _str_stmt)
{
    stmt = 0;
    str_stmt = _str_stmt;
    init_node_type();
}
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
void Node::set_str_stmt(std::string _str_stmt)
{
    str_stmt = _str_stmt;
}
symbol_c *Node::get_stmt()
{
    return stmt;
}
void Node::set_stmt(symbol_c *_stmt)
{
    stmt = _stmt;
}
std::string Node::get_node_type()
{
    return type;
}
std::string Node::get_str_node_name()
{
    return str_node_name;
}
void Node::set_str_node_name(std::string _str_node_name)
{
    str_node_name = _str_node_name;
}

/**
* helpers
*/

void Node::print(std::ostream &out)
{
    out << *this;
}
void Node::print_dot(std::ostream &out)
{
    // need to be implemented
}
std::ostream &operator<<(std::ostream &out, Node &n)
{
    if (n.get_str_stmt().length() > 0)
    {
        out << "[" << n.get_str_stmt() << "]";
    }
    else
    {
        out << "Uninitialized string";
    }
    return out;
}
std::ostream &operator<<(std::ostream &out, Node *n)
{
    out << *n;
    return out;
}
bool Node::equals(Node *_other)
{
    return str_stmt.compare(_other->get_str_stmt()) == 0 && type.compare(_other->get_node_type()) == 0;
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
            type = Node::ENTRY;
        }
        else if (str_stmt.compare(Node::EXIT) == 0)
        {
            type = Node::EXIT;
        }
        else
        {
            std::cout << "Incorrect Initial Node Type!\n";
        }
    }
    else
    {
        std::string str_type = stmt->absyntax_cname();

        if (str_type.compare("assignment_statement_c") == 0)
        {
            type = Node::ASSIGNMENT;
        }
        else if (str_type.compare("return_statement_c") == 0)
        {
            type = Node::RETURN;
        }
        else if (str_type.compare("fb_invocation_c") == 0)
        {
            type = Node::FB_INVOCATION;
        }
        else if (str_type.compare("if_statement_c") == 0)
        {
            type = Node::IF;
        }
        else if (str_type.compare("elseif_statement_c") ==0 )
        {
            type = Node::ELSE_IF;
        }
        else if (str_type.compare("for_statement_c") == 0)
        {
            type = Node::FOR;
        }
        else
        {
            std::cout << "Incorrect Initial Node Type!\n";
        }
    }
}
