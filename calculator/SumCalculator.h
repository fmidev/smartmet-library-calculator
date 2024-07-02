// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::SumCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <memory>

namespace TextGen
{
class SumCalculator : public Calculator
{
 public:
  SumCalculator();
  ~SumCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  double itsSum{0};

};  // class SumCalculator

}  // namespace TextGen

// ======================================================================
