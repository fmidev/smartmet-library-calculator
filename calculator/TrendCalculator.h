// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::TrendCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <memory>

namespace TextGen
{
class TrendCalculator : public Calculator
{
 public:
  TrendCalculator();
  ~TrendCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;

  long itsCounter{0};
  long itsPositiveChanges{0};
  long itsNegativeChanges{0};
  long itsZeroChanges{0};

  float itsLastValue;

};  // class TrendCalculator

}  // namespace TextGen

// ======================================================================
