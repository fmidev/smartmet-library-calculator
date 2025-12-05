// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModStandardDeviationCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class ModStandardDeviationCalculator : public Calculator
{
 public:
  ModStandardDeviationCalculator() = delete;
  ModStandardDeviationCalculator(int theModulo);
  ~ModStandardDeviationCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsSum;
  double itsSquaredSum;
  double itsPreviousDirection;

};  // class ModStandardDeviationCalculator

}  // namespace TextGen

// ======================================================================
