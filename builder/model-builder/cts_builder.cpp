#include "cts_builder.h"

/**
* methods only used in this file
*/
/*
* one-pass VSA
*/
wali::wfa::WFA VSA_process(wali::wpds::WPDS *_wpds, wali::Key &_p, wali::Key &_start, wali::Key &_accept, Value_set *_vs0)
{
    wali::wfa::WFA ret;

    wali::wfa::WFA post_query;
    post_query.addTrans(_p, _start, _accept, new Value_set_semiring(Abstract_value_set_transfer::get_identity(), _vs0));
    post_query.set_initial_state(_p);
    post_query.addFinalState(_accept);

    _wpds->poststar(post_query, ret);

    return ret;
}

/*
* whether the calculation reaches a fixed-point
*/
bool reaches_fixed_point(std::vector<Value_set *> &_list, Value_set *_vs0)
{
    if (_list.size() < 1)
    {
        return false;
    }
    for (int i=0; i<_list.size(); i++)
    {
        if (_list[i]->equal(_vs0))
        {
            return true;
        }
    }
    return false;
}



/**
* public static methods
*/

CTS_builder *CTS_builder::get_instance()
{
    if (builder == 0)
    {
        builder = new CTS_builder();
    }
    return builder;
}


/**
* public methods
*/
/*
* de-constructor
*/
CTS_builder::~CTS_builder()
{

}


/**
* external visible methods
*/
CTS *CTS_builder::create(CFG *_cfg)
{
    WPDS_builder *wpds_builder = WPDS_builder::get_instance();

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");
    wali::Key start;

    wali::wpds::WPDS *wpds = wpds_builder->create(_cfg, p, start);

    std::set<Program_state *> s_set;

    std::vector<Value_set *> initial_list;

    std::vector<Node *> nodes_list = _cfg->get_node_list();

    Value_set *vs0 = new Value_set(_cfg->get_var_list());

    while(!reaches_fixed_point(initial_list, vs0))
    {
        vs0->print(std::cout) << std::endl;

        initial_list.push_back(vs0);

        wali::wfa::WFA answer = VSA_process(wpds, p, start, accept, vs0);

        wali::wfa::Trans tr;
        for (int i=0; i<nodes_list.size(); i++)
        {
            wali::Key key = wali::getKey(nodes_list[i]->get_str_node().c_str());
            answer.find(p, key, accept, tr);

            s_set.insert(new Program_state(nodes_list[i], ((Value_set_semiring *) tr.weight().get_ptr())->get_value()));
        }

        /*
        * update the initial value_set of the next scan cycle
        */
        wali::Key end_key = wali::getKey(_cfg->get_end_node()->get_str_node().c_str());
        answer.find(p, end_key, accept, tr);
        vs0 = ((Value_set_semiring *) tr.weight().get_ptr())->get_value();

    }

    std::cout << s_set.size() << std::endl;

    std::set<Program_state *>::iterator it = s_set.begin();

    for (; it!=s_set.end(); ++it)
    {
        (*it)->get_location()->print(std::cout) << "\n";
        (*it)->get_value()->print(std::cout) << std::endl;
    }

//
//
//
//
//    initial_list.push_back(vs0);
//    wali::wfa::WFA answer = VSA_process(wpds, p, start, accept, vs0);
//
//
//
//
//
//    wali::Key key = wali::getKey(_cfg->get_end_node()->get_str_node().c_str());
//    wali::wfa::Trans tr;
//    answer.find(p, key, accept, tr);
//    Value_set_semiring *weight = (Value_set_semiring *) tr.weight().get_ptr();
//
//    weight->get_value()->print(std::cout) << std::endl;
//
//    answer = VSA_process(wpds, p, start, accept, weight->get_value());
//    answer.find(p, key, accept, tr);
//    weight = (Value_set_semiring *)tr.weight().get_ptr();
//
//    weight->get_value()->print(std::cout);




}


/**
* private methods and static attributes
*/
/*
* constructor
*/
CTS_builder::CTS_builder()
{

}

/*
* the only instance
*/
CTS_builder *CTS_builder::builder = 0;
