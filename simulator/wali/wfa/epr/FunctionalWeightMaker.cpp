/*!
 * @author Akash Lal
 */

#include "../../Common.hpp"
#include "../../SemElemPair.hpp"
#include "FunctionalWeightMaker.hpp"
#include "FunctionalWeight.hpp"
#include "../Trans.hpp"

namespace wali 
{
  namespace wfa 
  {
    namespace epr 
    {

      sem_elem_t FunctionalWeightMaker::make_weight( ITrans const *lhs, ITrans const *rhs) {

        return new FunctionalWeight(lhs, rhs);
      }

      sem_elem_t FunctionalWeightMaker::make_weight( sem_elem_t lhs, sem_elem_t rhs) {
        Trans *lt = new Trans(0, 0, 0, lhs);
        Trans *rt = new Trans(0, 0, 0, rhs);
        FunctionalWeight *fw = new FunctionalWeight(lt, rt);
        delete lt;
        delete rt;
        return fw;
      }

    }// namespace epr

  } // namespace wfa

} // namespace wali


