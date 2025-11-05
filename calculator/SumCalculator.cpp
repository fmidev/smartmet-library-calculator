// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::SumCalculator
 */
// ======================================================================
/*!
 * \class TextGen::SumCalculator
 *
 * \brief Sum intergator
 *
 */
// ======================================================================

#include "SumCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

SumCalculator::SumCalculator() : itsAcceptor(new DefaultAcceptor()) {}
// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void SumCalculator::operator()(float theValue)
{
  ++itsCounter;
  if (itsAcceptor->accept(theValue))
  {
    itsSum += theValue;
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated sum value
 */
// ----------------------------------------------------------------------

float SumCalculator::operator()() const
{
  if (itsCounter == 0)
    return kFloatMissing;
  return itsSum;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void SumCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> SumCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new SumCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void SumCalculator::reset()
{
  itsCounter = 0;
  itsSum = 0;
}

}  // namespace TextGen

// ======================================================================
