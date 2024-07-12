// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::CountCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <memory>

namespace TextGen
{
class CountCalculator : public Calculator
{
 public:
  CountCalculator();
  ~CountCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  std::shared_ptr<Calculator> clone() const override;
  void reset() override;

  void condition(const Acceptor& theCondition);

 private:
  std::shared_ptr<Acceptor> itsAcceptor;
  std::shared_ptr<Acceptor> itsCondition;
  long itsCounter{0};
  long itsTotalCounter{0};

};  // class CountCalculator

}  // namespace TextGen

// ======================================================================
