#ifndef REACH_GUARD
#define REACH_GUARD 1

/*!
 * @author Nicholas Kidd
 */

#include "SemElem.hpp"

namespace wali {

class Reach : public SemElem
{

  public:

    Reach( bool b );

    virtual ~Reach();

    sem_elem_t one() const;

    sem_elem_t zero() const;

    // zero is the annihilator for extend
    sem_elem_t extend( SemElem* rhs );

    // zero is neutral for combine
    sem_elem_t combine( SemElem* rhs );

    bool equal( SemElem* rhs ) const;

    std::ostream & print( std::ostream & o ) const;

    sem_elem_t from_string( const std::string& s ) const;

    static int numReaches;

  protected:
    bool isreached;

};

}

#endif	// REACH_GUARD

