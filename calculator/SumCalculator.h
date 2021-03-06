// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::SumCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class SumCalculator : public Calculator
{
 public:
  SumCalculator();
  virtual ~SumCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter;
  double itsSum;

};  // class SumCalculator

}  // namespace TextGen

// ======================================================================
