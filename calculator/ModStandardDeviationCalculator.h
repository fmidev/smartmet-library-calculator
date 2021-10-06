// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModStandardDeviationCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class ModStandardDeviationCalculator : public Calculator
{
 public:
  ModStandardDeviationCalculator(int theModulo);
  ~ModStandardDeviationCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  ModStandardDeviationCalculator() = delete;

  boost::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsSum;
  double itsSquaredSum;
  double itsPreviousDirection;

};  // class ModStandardDeviationCalculator

}  // namespace TextGen

// ======================================================================
