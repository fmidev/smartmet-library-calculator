// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MinimumCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class MinimumCalculator : public Calculator
{
 public:
  MinimumCalculator();
  ~MinimumCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  float itsMinimum;

};  // class MinimumCalculator

}  // namespace TextGen

// ======================================================================
