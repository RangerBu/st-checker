#include <time.h>

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

/*
 * update the value of input, temporary variables in a value-set
 */
Value_set *update_value_set(Value_set *_vs0)
{
    Value_set *ret = new Value_set(_vs0);

    std::vector<key> vars_list = ret->get_vars_list();

    std::vector<key>::iterator it = vars_list.begin();
    for (; it != vars_list.end(); ++it)
    {
        if ((*it)->get_str_semantics().compare(Var::SEMANTICS_INPUT) == 0)
        {
            if ((*it)->get_str_type().compare(Var::TYPE_BOOL) == 0)
            {
                ret->set_var_value(*it, Bits_vector_1::get_top());
            }
            else if ((*it)->get_str_type().compare(Var::TYPE_BYTE) == 0)
            {

            }
            else if ((*it)->get_str_type().compare(Var::TYPE_INT) == 0)
            {
                ret->set_var_value(*it, Strided_interval::get_top());
            }
        }
        else if ((*it)->get_str_semantics().compare(Var::SEMANTICS_OUTPUT) == 0)
        {
            if ((*it)->get_str_type().compare(Var::TYPE_BOOL) == 0)
            {
                ret->set_var_value(*it, Bits_vector_1::get_bot());
            }
            else if ((*it)->get_str_type().compare(Var::TYPE_BYTE) == 0)
            {

            }
            else if ((*it)->get_str_type().compare(Var::TYPE_INT) == 0)
            {
                ret->set_var_value(*it, Strided_interval::get_bot());
            }
        }
    }

    return ret;
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


    // one-pass vsa

//    wali::wfa::WFA answer = VSA_process(wpds, p, start, accept, vs0);
//    wali::wfa::Trans tr;
//    for (int i=0; i<nodes_list.size(); i++)
//    {
//        wali::Key key = wali::getKey(nodes_list[i]->get_str_node().c_str());
//        answer.find(p, key, accept, tr);
//        Program_state *p = new Program_state(nodes_list[i], ((Value_set_semiring *) tr.weight().get_ptr())->get_value());
//        p->print(std::cout) << std::endl;
//    }

    /*
     * the beginning of the build process
     */
    double t1, t2, cost;
    t1 = clock();

    int tmp = 0;
    while(!reaches_fixed_point(initial_list, vs0))
    {
//        std::cout << tmp << std::endl;tmp++;
//        vs0->print(std::cout) << std::endl;

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
//        vs0 = update_value_set(vs0);

    }
    vs0->print(std::cout) << std::endl;

    t2 = clock();
    cost = (t2-t1) / CLOCKS_PER_SEC;

    std::cout << nodes_list.size() << std::endl;

    std::cout << s_set.size() << std::endl;

    std::cout << cost << std::endl;

    std::set<Program_state *>::iterator it = s_set.begin();

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
