// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::StandardDeviationCalculator
 */
// ======================================================================

#pragma once

#include "Acceptor.h"
#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class StandardDeviationCalculator : public Calculator
{
 public:
  StandardDeviationCalculator();
  ~StandardDeviationCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  double itsSum{0};
  double itsSquaredSum{0};

};  // class StandardDeviationCalculator

}  // namespace TextGen

// ======================================================================
