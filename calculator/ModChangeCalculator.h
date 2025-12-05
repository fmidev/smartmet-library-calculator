// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModChangeCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class ModChangeCalculator : public Calculator
{
 public:
  ModChangeCalculator() = delete;
  ModChangeCalculator(int theModulo);
  ~ModChangeCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsCumulativeChange;
  double itsLastValue;

};  // class ModChangeCalculator

}  // namespace TextGen

// ======================================================================
