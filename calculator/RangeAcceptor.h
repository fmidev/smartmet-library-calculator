// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::RangeAcceptor
 */
// ======================================================================

#pragma once

#include "Acceptor.h"

namespace TextGen
{
class RangeAcceptor : public Acceptor
{
 public:
  ~RangeAcceptor() override = default;
  bool accept(float theValue) const override;
  Acceptor* clone() const override;

  RangeAcceptor();
  void lowerLimit(float theLimit);
  void upperLimit(float theLimit);

 private:
  float itsLoLimit;
  float itsHiLimit;

};  // class RangeAcceptor
}  // namespace TextGen

// ======================================================================
