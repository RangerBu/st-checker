#include "abstract_new_value.h"

/**
* public methods
*/
Abstract_new_value::Abstract_new_value(Value_set_transfer *_transfer)
{
    transfer = _transfer;
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
    if (!transfer->equals(_other->get_transfer()))
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
    std::string ret = transfer->format();

    if (pres.size() > 0 ) ret+= "\n";

    for (int i=0; i<pres.size(); i++)
    {
        ret += pres[i]->format();
        if (i!=pres.size()-1)
        {
            ret += "\n";
        }

    }
    return ret;
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
Value_set_transfer *Abstract_new_value::get_transfer()
{
    return transfer;
}
