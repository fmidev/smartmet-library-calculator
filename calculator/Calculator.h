// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::Calculator
 */
// ======================================================================

#pragma once

#include <memory>

namespace TextGen
{
class Acceptor;

class Calculator
{
 public:
  Calculator() = default;
  virtual ~Calculator() = default;
  virtual void operator()(float theValue) = 0;
  virtual float operator()() const = 0;
  virtual void acceptor(const Acceptor& theAcceptor) = 0;
  virtual std::shared_ptr<Calculator> clone() const = 0;
  virtual void reset() = 0;

};  // class Calculator

}  // namespace TextGen

// ======================================================================
