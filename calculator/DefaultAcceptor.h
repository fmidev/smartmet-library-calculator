// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::DefaultAcceptor
 */
// ======================================================================

#pragma once

#include "Acceptor.h"

namespace TextGen
{
class DefaultAcceptor : public Acceptor
{
 public:
  virtual ~DefaultAcceptor() = default;
  virtual bool accept(float theValue) const;
  virtual Acceptor* clone() const;

};  // class DefaultAcceptor
}  // namespace TextGen

// ======================================================================
