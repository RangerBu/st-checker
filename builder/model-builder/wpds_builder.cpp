#include "wpds_builder.h"

/**
* public static methods
*/
WPDS_builder *WPDS_builder::get_instance()
{
    if (builder == 0)
    {
        builder = new WPDS_builder();
    }
    return builder;
}


/**
* public methods
*/
/*
* de-constructor
*/
WPDS_builder::~WPDS_builder()
{

}


/**
* external visible methods
*/
wali::wpds::WPDS *WPDS_builder::create(CFG *_cfg, wali::Key _p, wali::Key &start)
{
    std::vector<Edge *> edges = _cfg->get_edge_list();

    wali::wpds::WPDS *ret = new wali::wpds::WPDS();

    for (int i=0; i<edges.size(); i++)
    {
        Node *from, *to;
        from = edges[i]->get_from();
        to = edges[i]->get_to();

        wali::Key key_from = wali::getKey(from->get_str_node().c_str());
        wali::Key key_to = wali::getKey(to->get_str_node().c_str());

        Abstract_value_set_transfer *transfer = 0;
        if (from->get_str_type().compare(Node::ENTRY) == 0)
        {
            // value_set_transfer::IDENTITY
            transfer = Abstract_value_set_transfer::get_identity();
            start = key_from;
        }
        else if (from->get_str_type().compare(Node::ASSIGNMENT) == 0)
        {
            // assign_stmt_transfer
            transfer = new Assign_stmt_transfer(from->get_stmt());
        }
        else if (from->get_str_type().compare(Node::IF) == 0 || from->get_str_type().compare(Node::ELSE_IF) == 0)
        {
            // elif_stmt_transfer
            if (_cfg->is_false_edge(edges[i]))
            {
                transfer = new Elif_stmt_transfer(from->get_stmt());
            }
            else
            {
                // if_stmt_transfer
                transfer = new If_stmt_transfer(from->get_stmt());
            }
        }
        else
        {
            std::cerr << "Unsupported Node type in constructing WPDS!" << std::endl;
            exit(0);
        }
        ret->add_rule(_p, key_from, _p, key_to, new Value_set_semiring(transfer));
    }

    return ret;
}


/**
* private methods and static attributes
*/
/*
* constructor
*/
WPDS_builder::WPDS_builder()
{

}

WPDS_builder *WPDS_builder::builder = 0;
