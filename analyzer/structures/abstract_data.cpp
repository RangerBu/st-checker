#include "abstract_data.h"

/**
* public methods
*/
/*
* constructor
*/
Abstract_data::Abstract_data()
{

}

/*
* de-constructor
*/
Abstract_data::~Abstract_data()
{

}


/**
* helpers
*/
std::ostream &operator<<(std::ostream &_out, Abstract_data *_data)
{
    return _data->print(_out);
}

