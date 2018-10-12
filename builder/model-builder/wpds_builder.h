#ifndef WPDS_BUILDER_H
#define WPDS_BUILDER_H

#include "wali/wpds/WPDS.hpp"

#include "../flow-graph-builder/cfg.h"
#include "structures/value_set_semiring.h"

class WPDS_builder
{
    /**
    * public static methods
    */
public:
    static WPDS_builder *get_instance();


    /**
    * public methods
    */

    /*
    * de-constructor
    */
    virtual ~WPDS_builder();


    /**
    * external visible methods
    */
    wali::wpds::WPDS *create(CFG *, wali::Key, wali::Key &);


    /**
    * private methods and static attributes
    */
private:
    /*
    * constructor
    */
    WPDS_builder();

    /*
    * the only one instance
    */
    static WPDS_builder *builder;

};

#endif // WPDS_BUILDER_H
