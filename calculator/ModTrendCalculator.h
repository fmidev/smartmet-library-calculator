// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModTrendCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class ModTrendCalculator : public Calculator
{
 public:
  ModTrendCalculator(int theModulo);
  virtual ~ModTrendCalculator() = default;
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  ModTrendCalculator() = delete;

  boost::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  unsigned long itsCounter;
  unsigned long itsPositiveChanges;
  unsigned long itsNegativeChanges;
  unsigned long itsZeroChanges;

  float itsLastValue;

};  // class ModTrendCalculator

}  // namespace TextGen

// ======================================================================
