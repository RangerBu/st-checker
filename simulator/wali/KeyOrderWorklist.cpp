/*!
 * @author Nicholas Kidd
 */

#include "Common.hpp"
#include "KeyOrderWorklist.hpp"
#include "wfa/Trans.hpp"
#include "KeyContainer.hpp"

namespace wali
{
  KeyOrderWorklist::KeyOrderWorklist() : PriorityWorklist<KeyComparer>()
  {
  }

  KeyOrderWorklist::~KeyOrderWorklist()
  {
  }
}

