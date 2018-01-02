#ifndef WPDS_BUILDER_H
#define WPDS_BUILDER_H

#include <vector>

#include "wali/wpds/WPDS.hpp"

#include "../flow-graph-builder/CFG.h"
#include "../flow-graph-builder/Edge.h"
#include "../flow-graph-builder/Node.h"

using wali::wpds::WPDS;

class WPDS_builder
{
    /**
    * public methods
    */
public:
    WPDS_builder(CFG *);
    virtual ~WPDS_builder();

    WPDS *create();

private:
    CFG *cfg;

};

#endif // WPDS_BUILDER_H
