// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ChangeCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class Acceptor;

class ChangeCalculator : public Calculator
{
 public:
  ChangeCalculator();
  ~ChangeCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  std::shared_ptr<Acceptor> itsAcceptor;

  long itsCounter{0};
  float itsStartValue;
  float itsEndValue;

};  // class ChangeCalculator

}  // namespace TextGen

// ======================================================================
