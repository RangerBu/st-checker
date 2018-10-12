#ifndef WALI_SHORTEST_PATH_SEMIRING_HPP
#define WALI_SHORTEST_PATH_SEMIRING_HPP

#include "SemElem.hpp"
#include "MergeFn.hpp"
#include "ref_ptr.hpp"
#include "Key.hpp"
#include <set>


namespace wali {

  
  class ShortestPathSemiring : public wali::SemElem
  {
  public:

    //-----------------------------
    // semiring one and zero
    //-----------------------------
    sem_elem_t one() const;

    sem_elem_t zero() const;

    //---------------------------------
    // semiring operations
    //---------------------------------
    sem_elem_t extend( SemElem* rhs );

    sem_elem_t combine( SemElem* rhs );

    bool equal(SemElem *rhs) const;

    bool containerLessThan(SemElem const * rhs) const;

    size_t hash() const;

    //------------------------------------
    // output
    //------------------------------------
    std::ostream & print(std::ostream &out) const;

    unsigned int getNum() const;

  private:
    
    unsigned int v;

  public:
    //---------------------
    // Constructors 
    //---------------------
    ShortestPathSemiring() : v(0) { }
    ShortestPathSemiring(unsigned int _v) : v(_v) {}

    static
    ShortestPathSemiring *
    make_one() {
      return new ShortestPathSemiring(0);
    }

    static
    ShortestPathSemiring *
    make_zero() {
      return new ShortestPathSemiring((unsigned)-1);
    }
  };



}

#endif // REACH_SEMIRING
