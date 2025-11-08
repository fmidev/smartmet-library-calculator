// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::PeakCalculator
 */
// ======================================================================
/*!
 * \class TextGen::PeakCalculator
 *
 * \brief Peak intergator
 *
 */
// ======================================================================

#include "PeakCalculator.h"
#include "DefaultAcceptor.h"

#include <newbase/NFmiGlobals.h>

#include <algorithm>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

PeakCalculator::PeakCalculator() : itsAcceptor(new DefaultAcceptor()) {}
// ----------------------------------------------------------------------
/*!
 * \brief Integrate a new value
 *
 * \param theValue
 */
// ----------------------------------------------------------------------

void PeakCalculator::operator()(float theValue)
{
  if (itsAcceptor->accept(theValue))
  {
    theValueVector.push_back(theValue);
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the integrated value
 *
 * \return The integrated mean value
 */
// ----------------------------------------------------------------------

float PeakCalculator::operator()() const
{
  if (theValueVector.empty())
    return kFloatMissing;

  unsigned int sz = theValueVector.size();
  if (sz < 10)
    return *std::max_element(theValueVector.begin(), theValueVector.end());

  unsigned int n = 95 * sz / 100;
  std::nth_element(theValueVector.begin(), theValueVector.begin() + n, theValueVector.end());
  return theValueVector[n];
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the internal acceptor
 *
 * \param theAcceptor The acceptor to be used
 */
// ----------------------------------------------------------------------

void PeakCalculator::acceptor(const Acceptor& theAcceptor)
{
  itsAcceptor = std::shared_ptr<Acceptor>(theAcceptor.clone());
}

// ----------------------------------------------------------------------
/*!
 * \brief Clone
 */
// ----------------------------------------------------------------------

std::shared_ptr<Calculator> PeakCalculator::clone() const
{
  return std::shared_ptr<Calculator>(new PeakCalculator(*this));
}

// ----------------------------------------------------------------------
/*!
 * \brief Reset
 */
// ----------------------------------------------------------------------

void PeakCalculator::reset()
{
  theValueVector.clear();
}
}  // namespace TextGen

// ======================================================================
