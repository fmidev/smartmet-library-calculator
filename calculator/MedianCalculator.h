// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MedianCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>
#include <vector>

namespace TextGen
{
class MedianCalculator : public Calculator
{
 public:
  MedianCalculator();
  ~MedianCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  mutable std::vector<float> theValueVector;

};  // class MedianCalculator

}  // namespace TextGen

// ======================================================================
