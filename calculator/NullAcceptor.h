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
  ~NullAcceptor() override = default;
  bool accept(float theValue) const override;
  Acceptor* clone() const override;

};  // class NullAcceptor
}  // namespace TextGen

// ======================================================================
