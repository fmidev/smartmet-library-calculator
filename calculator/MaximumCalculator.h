// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaximumCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class MaximumCalculator : public Calculator
{
 public:
  MaximumCalculator();
  virtual ~MaximumCalculator() = default;
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  float itsMaximum;

};  // class MaximumCalculator

}  // namespace TextGen

// ======================================================================
