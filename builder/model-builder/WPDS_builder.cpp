#include "WPDS_builder.h"

WPDS_builder::WPDS_builder(CFG *_cfg)
{
    cfg = _cfg;
}
WPDS_builder::~WPDS_builder()
{
}

WPDS *WPDS_builder::create(wali::Key _p, wali::Key &start)
{
    std::vector<Edge *> edges = cfg->get_edge_list();

    WPDS *ret = new WPDS();

    int len = edges.size();
    for (int i=0; i<len; i++)
    {
        Node *from, *to;
        from = edges[i]->get_from();
        to = edges[i]->get_to();

        wali::Key key1 = wali::getKey(from->get_str_node().c_str());
        wali::Key key2 = wali::getKey(to->get_str_node().c_str());

        Abstract_value_set_transfer *transfer = 0;
        if (from->get_str_type().compare(Node::ENTRY) == 0)
        {
            // value_set_transfer::IDENTITY
            transfer = Abstract_value_set_transfer::get_identity();
            start = key1;
        }
        else if (from->get_str_type().compare(Node::ASSIGNMENT) == 0)
        {
            // assign_stmt_transfer
            transfer = new Assign_stmt_transfer(from->get_stmt());
        }
        else if (from->get_str_type().compare(Node::IF) == 0 || from->get_str_type().compare(Node::ELSE_IF) == 0)
        {
            // elif_stmt_transfer
            if (cfg->is_false_edge(edges[i]))
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
            std::cout << "Unsupported Node type in constructing WPDS!" << std::endl;
            exit(0);
        }
        ret->add_rule(_p, key1, _p, key2, new Transfer_semiring(Abstract_value::get_instance(transfer)));
    }

    return ret;
//    std::ofstream fout("outputs/Example_4.wpds");
//    ret->print(fout) << std::endl;
//    fout.close();
}
