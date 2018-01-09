#include "abstract_new_value.h"

/**
* public methods
*/
Abstract_new_value::Abstract_new_value(Abstract_value_set_transfer *_transfer)
{
    transfer = _transfer;
    str_repr = "";
}
Abstract_new_value::~Abstract_new_value()
{

}
void Abstract_new_value::insert_post(Abstract_new_value *_post)
{
    posts.push_back(_post);
}
void Abstract_new_value::insert_pre(Abstract_new_value *_pre)
{
    pres.push_back(_pre);
}


/**
* helper methods
*/
bool Abstract_new_value::equals(Abstract_new_value *_other)
{
    if (!transfer->equal(_other->get_transfer()))
    {
        return false;
    }
    if (pres.size() != _other->get_pres().size() || posts.size() != _other->get_posts().size())
    {
        return false;
    }

    for (int i=0; i<pres.size(); i++)
    {
        if (!(pres[i]==_other->get_pres()[i]))
        {
            return false;
        }
    }
    for (int i=0; i<posts.size(); i++)
    {
        if (!(posts[i] == _other->get_posts()[i]))
        {
            return false;
        }
    }
    return true;

}
std::string Abstract_new_value::format()
{
    std::stringstream ss;
    int len = pres.size();
    std::cout << "here" << std::endl;
    if (len == 0)
    {
        // entry
        ss << "[" << this << "] <" << transfer->to_string() << ">";
//        ss << "\"[" << this << "]\" \[label=\"" << transfer->format() << "\", color=lightblue,style=filled,shape=box]\n";
    }
    else if (len == 1)
    {
        // one node on a path
        ss << "[" << this << "] <" << transfer->to_string() << "> otimes [" << pres[0] << "]";
        ss << "\n" << pres[0]->format();
//        ss << "\"[" << this << "]\" \[label=\"" << transfer->format() << "\", color=lightblue,style=filled,shape=box]\n";


    }
    else
    {
        // combined node
        ss << "[" << this << "] <" << transfer->to_string()<< "> = [" << pres[0] << "] oplus [" << pres[1] << "]";
        ss << "\n" << pres[0]->format() << "\n" << pres[1]->format();
    }
    str_repr = ss.str();
    return str_repr;
}


/**
* getters and setters
*/
std::vector<Abstract_new_value *> Abstract_new_value::get_pres()
{
    return pres;
}
std::vector<Abstract_new_value *> Abstract_new_value::get_posts()
{
    return posts;
}
Abstract_value_set_transfer *Abstract_new_value::get_transfer()
{
    return transfer;
}
std::string Abstract_new_value::get_str_repr()
{
    return str_repr;
}
