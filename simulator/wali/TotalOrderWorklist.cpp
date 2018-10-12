/*!
 * @author Nicholas Kidd
 */

#include "Common.hpp"
#include "TotalOrderWorklist.hpp"
#include "wfa/Trans.hpp"

namespace wali
{
  TotalOrderWorklist::TotalOrderWorklist() : PriorityWorklist<LessThan>()
  {
  }

  TotalOrderWorklist::~TotalOrderWorklist()
  {
  }
}

