// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::IdGenerator
 */
// ======================================================================

#include "IdGenerator.h"

#include <boost/atomic.hpp>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Return a new ID
 *
 * \return The generated ID
 */
// ----------------------------------------------------------------------

long IdGenerator::generate()
{
  static boost::atomic<long> id;
  return ++id;
}

}  // namespace TextGen

// ======================================================================
