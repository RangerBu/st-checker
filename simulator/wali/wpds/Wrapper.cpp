/**
 * @author Nicholas Kidd
 * @version $Id$
 */

#include "Wrapper.hpp"
#include "../wfa/ITrans.hpp"
#include "Rule.hpp"
#include "ewpds/ERule.hpp"

namespace wali
{
  namespace wpds
  {
    // default does nothing
    sem_elem_t Wrapper::wrap( wfa::ITrans const & t )
    {
      return t.weight();
    }

    // default does nothing
    sem_elem_t Wrapper::wrap( wpds::Rule const & r )
    {
      return r.weight();
    }

    // default does nothing
    merge_fn_t Wrapper::wrap( wpds::ewpds::ERule const & r ATTR_UNUSED, merge_fn_t user_merge )
    {
      (void) r;
      return user_merge;
    }

    sem_elem_t Wrapper::unwrap( sem_elem_t se )
    {
      return se;
    }

    merge_fn_t Wrapper::unwrap( merge_fn_t mf )
    {
      return mf;
    }

  } // namespace wpds

} // namespace wali

