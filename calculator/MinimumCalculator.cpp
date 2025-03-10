// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::MinimumCalculator
 */
// ======================================================================
/*!
 * \class TextGen::MinimumCalculator
 *
 * \brief Minimum calculator
 *
 */
// ======================================================================

#include "MinimumCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

MinimumCalculator::MinimumCalculator()
    : itsAcceptor(new DefaultAcceptor()),  itsMinimum(kFloatMissing)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void MinimumCalculator::operator()(float theValue)
{
  if (itsAcceptor->accept(theValue))
  {
    if (itsCounter == 0)
      itsMinimum = theValue;
    else
      itsMinimum = std::min(itsMinimum, theValue);
    ++itsCounter;
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated minimum value
 */
// ----------------------------------------------------------------------

float MinimumCalculator::operator()() const
{
  if (itsCounter == 0) return kFloatMissing;

  return itsMinimum;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void MinimumCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> MinimumCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new MinimumCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void MinimumCalculator::reset()
{
  itsCounter = 0;
  itsMinimum = 0;
}

}  // namespace TextGen

// ======================================================================
