// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::TrendCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class TrendCalculator : public Calculator
{
 public:
  TrendCalculator();
  virtual ~TrendCalculator() = default;
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;

  long itsCounter{0};
  long itsPositiveChanges{0};
  long itsNegativeChanges{0};
  long itsZeroChanges{0};

  float itsLastValue;

};  // class TrendCalculator

}  // namespace TextGen

// ======================================================================
