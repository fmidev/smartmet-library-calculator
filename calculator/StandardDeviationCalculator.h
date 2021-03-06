// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::StandardDeviationCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class StandardDeviationCalculator : public Calculator
{
 public:
  StandardDeviationCalculator();
  virtual ~StandardDeviationCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter;
  double itsSum;
  double itsSquaredSum;

};  // class StandardDeviationCalculator

}  // namespace TextGen

// ======================================================================
