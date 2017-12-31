#include "Var.h"

/**
* static methods
*/
int Var::get_int_semantic(std::string _str_semantic)
{
    if (_str_semantic.compare("VAR") == 0)
    {
        return Var::SEMANTIC_VAR;
    }
    else if (_str_semantic.compare("INPUT") == 0)
    {
        return Var::SEMANTIC_INPUT;
    }
    else if (_str_semantic.compare("OUTPUT") == 0)
    {
        return Var::SEMANTIC_OUTPUT;
    }
    else if (_str_semantic.compare("IN_OUT") == 0)
    {
        return Var::SEMANTIC_IN_OUT;
    }
    else if (_str_semantic.compare("RETENTIVE") == 0)
    {
        return Var::SEMANTIC_RETENTIVE;
    }
    else if (_str_semantic.compare("LOCATED") == 0)
    {
        return Var::SEMANTIC_LOCATED;
    }
    else if (_str_semantic.compare("EXTERNAL") == 0)
    {
        return Var::SEMANTIC_EXTERNAL;
    }
    else if (_str_semantic.compare("GLOBAL") == 0)
    {
        return Var::SEMANTIC_GLOBAL;
    }
    else
    {
        std::cout << "Pass an incorrect type name!" << std::endl;
    }

}
int Var::get_int_type(std::string _str_type)
{
    if (_str_type.compare("INT") == 0)
    {
        return Var::TYPE_INT;
    }
    else if (_str_type.compare("BOOL") == 0)
    {
        return Var::TYPE_BOOL;
    }
    else if (_str_type.compare("BYTE") == 0)
    {
        return Var::TYPE_BYTE;
    }
    else
    {
        std::cout << "Pass an incorrect type name!" << std::endl;
    }
}


/**
* public methods
*/
Var::Var(std::string _str_name, int _type, int _semantic)
{
    str_name = _str_name;
    type = _type;
    semantic = _semantic;
}
Var::~Var()
{
}

/**
* getters and setters
*/
std::string Var::get_str_name()
{
    return str_name;
}
int Var::get_type()
{
    return type;
}
int Var::get_semantic()
{
    return semantic;
}

/**
* helpers
*/
std::string Var::format()
{
    std::stringstream o;
    o << str_name << "[" << type << "](" << semantic << ")";
    return o.str();
}
void Var::print(std::ostream &out)
{
    out << this->format();
}
bool Var::equals(Var *_other)
{
    return (str_name.compare(_other->get_str_name()) == 0) && (type == _other->get_type()) && (semantic == _other->get_semantic());
}
