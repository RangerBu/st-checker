#include "WPDS_builder.h"

WPDS_builder::WPDS_builder(CFG *_cfg)
{
    cfg = _cfg;
}
WPDS_builder::~WPDS_builder()
{
}

WPDS *WPDS_builder::create()
{
    std::vector<Node *> nodes = cfg->get_nodes();
    std::vector<Edge *> edges = cfg->get_edges();

    WPDS *ret = new WPDS();

    wali::Key p = wali::getKey("p");
    wali::Key accept = wali::getKey("accept");

    int len = nodes.size();
    wali::Key N[len];

    for (int i=0; i<len; i++)
    {
        N[i] = wali::getKey(nodes[i]->get_str_node_name().c_str());
    }


}
