/*!
 * @author Nicholas Kidd
 *
 * @version $Id$
 */

#include "../Common.hpp"
#include "Visitor.hpp"
#include "Witness.hpp"
#include "WitnessExtend.hpp"
#include "WitnessCombine.hpp"
#include "WitnessTrans.hpp"
#include "WitnessRule.hpp"
#include "WitnessMerge.hpp"
#include <iostream>
#include <cassert>

namespace wali
{
  namespace witness
  {
    bool Visitor::visit( Witness * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visit invoked. Aborting.\n";
      return false;
    }

    bool Visitor::visitExtend( WitnessExtend * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visitextend invoked. Aborting.\n";
      return false;
    }

    bool Visitor::visitCombine( WitnessCombine * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visitCombine invoked. Aborting.\n";
      return false;
    }

    bool Visitor::visitRule( WitnessRule * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visitRule invoked. Aborting.\n";
      return false;
    }

    bool Visitor::visitTrans( WitnessTrans * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visitTrans invoked. Aborting.\n";
      return false;
    }

    bool Visitor::visitMerge( WitnessMerge * w ATTR_UNUSED )
    {
      (void) w;
      *waliErr << "[ERROR] wali::witness::Visitor::visitMerge invoked. Aborting.\n";
      return false;
    }

  } // namespace witness

} // namespace wali

