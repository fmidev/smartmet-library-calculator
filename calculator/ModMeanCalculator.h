// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModMeanCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class ModMeanCalculator : public Calculator
{
 public:
  ModMeanCalculator(int theModulo);
  ~ModMeanCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  ModMeanCalculator() = delete;

  std::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsSum;
  double itsPreviousDirection;

};  // class ModMeanCalculator

}  // namespace TextGen

// ======================================================================
