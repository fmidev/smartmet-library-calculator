// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::ModTrendCalculator
 */
// ======================================================================
/*!
 * \class TextGen::ModTrendCalculator
 *
 * \brief ModTrend intergator
 *
 */
// ======================================================================

#include "ModTrendCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

ModTrendCalculator::ModTrendCalculator(int theModulo)
    : itsAcceptor(new DefaultAcceptor()),
      itsModulo(theModulo),
      itsCounter(0),
      itsPositiveChanges(0),
      itsNegativeChanges(0),
      itsZeroChanges(0),
      itsLastValue(kFloatMissing)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void ModTrendCalculator::operator()(float theValue)
{
  if (itsAcceptor->accept(theValue))
  {
    if (itsCounter > 0)
    {
      const float diff = theValue - itsLastValue;
      if (diff < -itsModulo / 2.0)
        ++itsPositiveChanges;
      else if (diff > itsModulo / 2.0)
        ++itsNegativeChanges;
      else if (diff < 0)
        ++itsNegativeChanges;
      else if (diff > 0)
        ++itsPositiveChanges;
      else
        ++itsZeroChanges;
    }
    ++itsCounter;
    itsLastValue = theValue;
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated trend value
 */
// ----------------------------------------------------------------------

float ModTrendCalculator::operator()() const
{
  // The total number of numbers is one greater than number of changes,
  // hence the -1 in the divisor itsCounter-1

  if (itsCounter < 1)
    return kFloatMissing;
  if (itsCounter > 1)
    return (itsPositiveChanges + itsZeroChanges / 2.0) / (itsCounter - 1.0) * 100;

  return 0.0;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void ModTrendCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> ModTrendCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new ModTrendCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void ModTrendCalculator::reset()
{
  itsCounter = 0;
  itsPositiveChanges = 0;
  itsNegativeChanges = 0;
  itsZeroChanges = 0;
  itsLastValue = kFloatMissing;
}

}  // namespace TextGen

// ======================================================================
