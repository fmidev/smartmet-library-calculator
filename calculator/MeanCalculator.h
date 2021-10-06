// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MeanCalculator
 */
// ======================================================================

#pragma once

#include "Calculator.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class MeanCalculator : public Calculator
{
 public:
  MeanCalculator();
  ~MeanCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

 private:
  boost::shared_ptr<Acceptor> itsAcceptor;
  long itsCounter{0};
  double itsSum{0};

};  // class MeanCalculator

}  // namespace TextGen

// ======================================================================
