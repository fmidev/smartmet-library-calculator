// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModChangeCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class ModChangeCalculator : public Calculator
{
 public:
  ModChangeCalculator(int theModulo);
  virtual ~ModChangeCalculator() = default;
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  ModChangeCalculator() = delete;

  boost::shared_ptr<Acceptor> itsAcceptor;
  const int itsModulo;

  long itsCounter;
  double itsCumulativeChange;
  double itsLastValue;

};  // class ModChangeCalculator

}  // namespace TextGen

// ======================================================================
