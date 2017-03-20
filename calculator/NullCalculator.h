// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::NullCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"

namespace TextGen
{
class Acceptor;

class NullCalculator : public Calculator
{
 public:
  virtual ~NullCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

};  // class Calculator

}  // namespace TextGen


// ======================================================================
