/*!
 * @author Rich Joiner
 */

#include "../Common.hpp"
#include "WitnessLengthWorklist.hpp"
#include "../wfa/Trans.hpp"

namespace wali
{
  namespace witness
  {
    WitnessLengthWorklist::WitnessLengthWorklist() : PriorityWorklist<ShorterThan>()
    {
    }

    WitnessLengthWorklist::~WitnessLengthWorklist()
    {
    }
  }
}

