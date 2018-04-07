// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ChangeCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class ChangeCalculator : public Calculator
{
 public:
  ChangeCalculator();
  virtual ~ChangeCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;

  long itsCounter;
  float itsStartValue;
  float itsEndValue;

};  // class ChangeCalculator

}  // namespace TextGen

// ======================================================================
