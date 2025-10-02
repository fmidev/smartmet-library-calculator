// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::PeakCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>
#include <vector>

namespace TextGen
{
class PeakCalculator : public Calculator
{
 public:
  PeakCalculator();
  ~PeakCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  mutable std::vector<float> theValueVector;

};  // class PeakCalculator

}  // namespace TextGen

// ======================================================================
