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
  ~ModTrendCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

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
