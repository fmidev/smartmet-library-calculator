// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::MaximumCalculator
 */
// ======================================================================
/*!
 * \class TextGen::MaximumCalculator
 *
 * \brief Maximum calculator
 *
 */
// ======================================================================

#include "MaximumCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

MaximumCalculator::MaximumCalculator()
    : itsAcceptor(new DefaultAcceptor()), itsMaximum(kFloatMissing)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void MaximumCalculator::operator()(float theValue)
{
  if (itsAcceptor->accept(theValue))
  {
    if (itsCounter == 0)
      itsMaximum = theValue;
    else
      itsMaximum = std::max(itsMaximum, theValue);
    ++itsCounter;
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated maximum value
 */
// ----------------------------------------------------------------------

float MaximumCalculator::operator()() const
{
  if (itsCounter == 0)
    return kFloatMissing;

  return itsMaximum;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void MaximumCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> MaximumCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new MaximumCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void MaximumCalculator::reset()
{
  itsCounter = 0;
  itsMaximum = 0;
}

}  // namespace TextGen

// ======================================================================
