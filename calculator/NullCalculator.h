// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::NullCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"

namespace TextGen
{
class Acceptor;

class NullCalculator : public Calculator
{
 public:
  ~NullCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

};  // class Calculator

}  // namespace TextGen

// ======================================================================
