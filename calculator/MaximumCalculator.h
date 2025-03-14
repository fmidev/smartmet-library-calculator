// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaximumCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class MaximumCalculator : public Calculator
{
 public:
  MaximumCalculator();
  ~MaximumCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  float itsMaximum;

};  // class MaximumCalculator

}  // namespace TextGen

// ======================================================================
