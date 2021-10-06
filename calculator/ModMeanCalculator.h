// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModMeanCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class ModMeanCalculator : public Calculator
{
 public:
  ModMeanCalculator(int theModulo);
  virtual ~ModMeanCalculator() = default;
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  ModMeanCalculator() = delete;

  boost::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsSum;
  double itsPreviousDirection;

};  // class ModMeanCalculator

}  // namespace TextGen

// ======================================================================
