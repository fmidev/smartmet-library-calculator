// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::TrendCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include "Acceptor.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class TrendCalculator : public Calculator
{
 public:
  TrendCalculator();
  virtual ~TrendCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;

  long itsCounter;
  long itsPositiveChanges;
  long itsNegativeChanges;
  long itsZeroChanges;

  float itsLastValue;

};  // class TrendCalculator

}  // namespace TextGen


// ======================================================================
