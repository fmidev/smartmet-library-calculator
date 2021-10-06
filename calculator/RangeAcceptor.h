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
  virtual ~RangeAcceptor() = default;
  virtual bool accept(float theValue) const;
  virtual Acceptor* clone() const;

  RangeAcceptor();
  void lowerLimit(float theLimit);
  void upperLimit(float theLimit);

 private:
  float itsLoLimit;
  float itsHiLimit;

};  // class RangeAcceptor
}  // namespace TextGen

// ======================================================================
