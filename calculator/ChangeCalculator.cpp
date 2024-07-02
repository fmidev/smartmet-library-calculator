// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::ChangeCalculator
 */
// ======================================================================
/*!
 * \class TextGen::ChangeCalculator
 *
 * \brief Change intergator
 *
 */
// ======================================================================

#include "ChangeCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

ChangeCalculator::ChangeCalculator()
    : itsAcceptor(new DefaultAcceptor()),
      
      itsStartValue(kFloatMissing),
      itsEndValue(kFloatMissing)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void ChangeCalculator::operator()(float theValue)
{
  if (itsAcceptor->accept(theValue))
  {
    if (itsCounter == 0) itsStartValue = theValue;
    itsEndValue = theValue;
    ++itsCounter;
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated change value
 */
// ----------------------------------------------------------------------

float ChangeCalculator::operator()() const
{
  if (itsCounter < 1 || itsStartValue == kFloatMissing || itsEndValue == kFloatMissing)
    return kFloatMissing;
  return (itsEndValue - itsStartValue);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void ChangeCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> ChangeCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new ChangeCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void ChangeCalculator::reset()
{
  itsCounter = 0;
  itsStartValue = kFloatMissing;
  itsEndValue = kFloatMissing;
}

}  // namespace TextGen

// ======================================================================
