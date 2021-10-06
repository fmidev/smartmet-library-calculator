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
  ~ModChangeCalculator() override = default;
  void operator()(float theValue) override;
  float operator()() const override;
  void acceptor(const Acceptor& theAcceptor) override;
  boost::shared_ptr<Calculator> clone() const override;
  void reset() override;

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
