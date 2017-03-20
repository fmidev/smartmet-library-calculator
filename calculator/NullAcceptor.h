// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::NullAcceptor
 */
// ======================================================================

#pragma once

#include "Acceptor.h"

namespace TextGen
{
class NullAcceptor : public Acceptor
{
 public:
  virtual ~NullAcceptor() {}
  virtual bool accept(float theValue) const;
  virtual Acceptor* clone() const;

};  // class NullAcceptor
}  // namespace TextGen


// ======================================================================
