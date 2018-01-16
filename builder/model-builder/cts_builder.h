#ifndef CTS_BUILDER_H
#define CTS_BUILDER_H

#include "structures/cts.h"
#include "wpds_builder.h"

class CTS_builder
{
    /**
    * public static methods
    */
public:
    static CTS_builder *get_instance();


    /**
    * public methods
    */
    /*
    * de-constructor
    */
    virtual ~CTS_builder();


    /**
    * external visible methods
    */
    CTS *create(CFG *);


    /**
    * private methods and static attributes
    */
private:
    /*
    * constructor
    */
    CTS_builder();

    /*
    * the only instance
    */
    static CTS_builder *builder;
};

#endif // CTS_BUILDER_H
