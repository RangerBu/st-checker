#ifndef WPDS_BUILDER_H
#define WPDS_BUILDER_H

#include <vector>
#include <stdlib.h>
#include <fstream>

#include "wali/wpds/WPDS.hpp"

#include "../flow-graph-builder/CFG.h"
#include "../flow-graph-builder/Edge.h"
#include "../flow-graph-builder/Node.h"
#include "transfer_semiring.h"

using wali::wpds::WPDS;

class WPDS_builder
{
    /**
    * public methods
    */
public:
    WPDS_builder(CFG *);
    virtual ~WPDS_builder();

    WPDS *create(wali::Key, wali::Key &);


private:
    CFG *cfg;
};

#endif // WPDS_BUILDER_H
