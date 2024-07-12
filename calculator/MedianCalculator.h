// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MedianCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>
#include <vector>

namespace TextGen
{
class MedianCalculator : public Calculator
{
 public:
  MedianCalculator();
  ~MedianCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  mutable std::vector<float> theValueVector;

};  // class MedianCalculator

}  // namespace TextGen

// ======================================================================
