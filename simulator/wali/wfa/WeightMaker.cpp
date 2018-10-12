/*!
 * @author Nicholas Kidd
 */

#include "../Common.hpp"
#include "../SemElemPair.hpp"
#include "WeightMaker.hpp"

namespace wali
{
  namespace wfa
  {
    sem_elem_t WeightMaker::make_weight( ITrans const * lhs,
        ITrans const * rhs) {
      return make_weight(lhs->weight(), rhs->weight());
    }

    sem_elem_t KeepLeft::make_weight( sem_elem_t lhs, sem_elem_t rhs ATTR_UNUSED )
    {
      return lhs;
    }

    sem_elem_t KeepRight::make_weight( sem_elem_t lhs ATTR_UNUSED, sem_elem_t rhs )
    {
      return rhs;
    }

    sem_elem_t KeepBoth::make_weight( sem_elem_t lhs, sem_elem_t rhs )
    {
      return new SemElemPair(lhs,rhs);
    }

  } // namespace wfa

} // namespace wali

