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
  ~DefaultAcceptor() override = default;
  bool accept(float theValue) const override;
  Acceptor* clone() const override;

};  // class DefaultAcceptor
}  // namespace TextGen

// ======================================================================
