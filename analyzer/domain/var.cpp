#include "var.h"

/**
* static attributes
*/
/*
* string representation of variable types
*/
std::string Var::TYPE_INT = "INT";
std::string Var::TYPE_BOOL = "BOOL";
std::string Var::TYPE_BYTE = "BYTE";

/*
* string representation of variable semantics
*/
std::string Var::SEMANTICS_VAR = "VAR";
std::string Var::SEMANTICS_INPUT = "INPUT";
std::string Var::SEMANTICS_OUTPUT = "OUTPUT";
std::string Var::SEMANTICS_RETENTIVE = "RETENTIVE";
std::string Var::SEMANTICS_LOCATED = "LOCATED";


/**
* public methods
*/
/*
* constructor
*/
Var::Var(std::string _str_name, std::string _str_type, std::string _str_semantics)
{
    str_name = _str_name;
    str_type = _str_type;
    str_semantics = _str_semantics;
}

Var::Var(Var *_other)
{
    str_name = _other->get_str_name();
    str_type = _other->get_str_type();
    str_semantics = _other->get_str_semantics();
}

/*
* de-constructor
*/
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

std::string Var::get_str_type()
{
    return str_type;
}

std::string Var::get_str_semantics()
{
    return str_semantics;
}


/**
* helpers
*/
bool Var::equal(Var *_other)
{
    if (this == _other)
    {
        return true;
    }
    return str_name.compare(_other->get_str_name()) == 0 && str_type.compare(_other->get_str_type()) == 0
            && str_semantics.compare(_other->get_str_semantics()) == 0;
}

std::ostream &Var::print(std::ostream &_out)
{
    return _out << str_name << "[" << str_type << "](" << str_semantics << ")";
}

std::ostream &operator<<(std::ostream &_out, Var *_var)
{
    return _var->print(_out);
}


/**
* helpers - debug only
*/
std::string Var::to_string()
{
    std::stringstream ss;
    ss << str_name << "[" << str_type << "](" << str_semantics << ")";

    return ss.str();
}


///**
//* static methods
//*/
//int get_int_semantic(std::string _str_semantic)
//{
//    if (_str_semantic.compare("VAR") == 0)
//    {
//        return Var::SEMANTICS_VAR;
//    }
//    else if (_str_semantic.compare("INPUT") == 0)
//    {
//        return Var::SEMANTICS_INPUT;
//    }
//    else if (_str_semantic.compare("OUTPUT") == 0)
//    {
//        return Var::SEMANTICS_OUTPUT;
//    }
////    else if (_str_semantic.compare("IN_OUT") == 0)
////    {
////        return Var::SEMANTIC_IN_OUT;
////    }
//    else if (_str_semantic.compare("RETENTIVE") == 0)
//    {
//        return Var::SEMANTICS_RETENTIVE;
//    }
////    else if (_str_semantic.compare("LOCATED") == 0)
////    {
////        return Var::SEMANTIC_LOCATED;
////    }
////    else if (_str_semantic.compare("EXTERNAL") == 0)
////    {
////        return Var::SEMANTIC_EXTERNAL;
////    }
////    else if (_str_semantic.compare("GLOBAL") == 0)
////    {
////        return Var::SEMANTIC_GLOBAL;
////    }
//    else
//    {
//        std::cout << "Pass an incorrect type name!" << std::endl;
//    }
//
//}
//int get_int_type(std::string _str_type)
//{
//    if (_str_type.compare("INT") == 0)
//    {
//        return Var::TYPE_INT;
//    }
//    else if (_str_type.compare("BOOL") == 0)
//    {
//        return Var::TYPE_BOOL;
//    }
//    else if (_str_type.compare("BYTE") == 0)
//    {
//        return Var::TYPE_BYTE;
//    }
//    else
//    {
//        std::cout << "Pass an incorrect type name!" << std::endl;
//    }
//}
