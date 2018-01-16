#include "cts.h"

/**
* public methods
*/
/*
* constructor
*/
CTS::CTS()
{
    t_0 = 0;
}

/*
* de-constructor
*/
CTS::~CTS()
{

}

/**
* getters and setters
*/
std::vector<int> CTS::get_T_list()
{
    return T_list;
}

void CTS::set_T_list(std::vector<int> _T_list)
{
    T_list = _T_list;
}

std::set<Program_state *> CTS::get_S_set()
{
    return S_set;
}

void CTS::set_S_set(std::set<Program_state *> _S_set)
{
    std::set<Program_state *>::iterator it = _S_set.begin();
    for (; it != _S_set.end(); ++it)
    {
        S_set.insert(*it);
    }
}

int CTS::get_t_0()
{
    return t_0;
}

void CTS::set_t_0(int _t_0)
{
    t_0 = _t_0;
}

Program_state * CTS::get_s_0()
{
    return s_0;
}

void CTS::set_s_0(Program_state *_s_0)
{
    s_0 = _s_0;
}

alphabet CTS::get_sigma()
{
    return sigma;
}

void CTS::set_sigma(alphabet _sigma)
{
    sigma = _sigma;
}

rules_map CTS::get_nabla()
{
    return nabla;
}

void CTS::set_nabla(rules_map _nabla)
{
    rules_map::iterator it = _nabla.begin();

    for (; it != _nabla.end(); ++it)
    {
        nabla[it->first] = (it->second);
    }
}


/**
* helpers
*/
std::ostream &CTS::print(std::ostream &_out)
{
    return _out;
}

std::ostream &CTS::print_dot(std::ostream &_out)
{
    return _out;
}


/**
* helpers - debug only
*/
std::string CTS::to_string()
{

}
