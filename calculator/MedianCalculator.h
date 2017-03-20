// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MedianCalculator
 */
// ======================================================================

#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>
#include "Calculator.h"

namespace TextGen
{
class MedianCalculator : public Calculator
{
 public:
  MedianCalculator();
  virtual ~MedianCalculator() {}
  virtual void operator()(float theValue);
  virtual float operator()() const;
  virtual void acceptor(const Acceptor& theAcceptor);
  virtual boost::shared_ptr<Calculator> clone() const;
  virtual void reset();

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  mutable std::vector<float> theValueVector;

};  // class MedianCalculator

}  // namespace TextGen

// ======================================================================
