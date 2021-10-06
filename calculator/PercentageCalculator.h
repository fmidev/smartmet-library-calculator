// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::PercentageCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class PercentageCalculator : public Calculator
{
 public:
  PercentageCalculator();
  PercentageCalculator(const PercentageCalculator& theOther);
  ~PercentageCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

  void condition(const Acceptor& theCondition);

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  boost::shared_ptr<Acceptor> itsCondition;
  long itsCounter{0};
  long itsTotalCounter{0};

};  // class PercentageCalculator

}  // namespace TextGen

// ======================================================================
