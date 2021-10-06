// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::Acceptor
 */
// ======================================================================

#pragma once

namespace TextGen
{
class Acceptor
{
 public:
  Acceptor() = default;
  virtual ~Acceptor() = default;
  virtual bool accept(float theValue) const = 0;
  virtual Acceptor* clone() const = 0;

};  // class Acceptor
}  // namespace TextGen

// ======================================================================
