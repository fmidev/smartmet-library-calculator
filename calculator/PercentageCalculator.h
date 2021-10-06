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
  virtual ~PercentageCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

  void condition(const Acceptor& theCondition);

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  boost::shared_ptr<Acceptor> itsCondition;
  long itsCounter{0};
  long itsTotalCounter{0};

};  // class PercentageCalculator

}  // namespace TextGen

// ======================================================================
