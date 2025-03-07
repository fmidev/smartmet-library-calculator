// ======================================================================
/*!
 * \file
 * \brief Implementation of singleton LocationSource
 */
// ======================================================================
/*!
 * \class TextGen::LocationSource
 *
 * \brief Provides information of named points of the world
 *
 * The class provides means for converting a name to a coordinate
 * point.
 *
 * Sample usage:
 *
 * \code
 * if(LocationSource::instance().hasCoordinates("Helsinki"))
 *   cout << "Helsinki " << LocationSource::instance().coordinates("Helsinki");
 * \endcode
 */
// ======================================================================

#include "LocationSource.h"
#include "Settings.h"
#include <macgyver/Exception.h>
#include <newbase/NFmiLocationFinder.h>
#include <newbase/NFmiPoint.h>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Implementation hiding pimple
 */
// ----------------------------------------------------------------------

class LocationSource::Pimple
{
 public:
  Pimple();

  bool hasCoordinates(const std::string& theLocation) const;
  const NFmiPoint coordinates(const std::string& theLocation) const;

  mutable std::string itsLastSuccesfulName;
  mutable NFmiPoint itsLastSuccesfulPoint;
  mutable NFmiLocationFinder itsFinder;

};  // Pimple

// ----------------------------------------------------------------------
/*!
 * \brief Pimple constructor
 */
// ----------------------------------------------------------------------

LocationSource::Pimple::Pimple() : itsLastSuccesfulPoint(kFloatMissing, kFloatMissing) {}

// ----------------------------------------------------------------------
/*!
 * \brief Test whether the given location name has known coordinates
 */
// ----------------------------------------------------------------------

bool LocationSource::Pimple::hasCoordinates(const std::string& theLocation) const
{
  if (theLocation.empty())
    throw Fmi::Exception(BCP, "Cannot request coordinates for an empty location name");

  if (theLocation == itsLastSuccesfulName) return true;

  if (itsFinder.Empty())
  {
    std::string filename = Settings::optional_string("textgen::coordinates",
                                                     "/smartmet/share/coordinates/default.txt");
    itsFinder.AddFile(filename, false);
  }

  NFmiPoint point = itsFinder.Find(theLocation);
  if (itsFinder.LastSearchFailed()) return false;

  itsLastSuccesfulName = theLocation;
  itsLastSuccesfulPoint = point;

  return true;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinate of the given named point
 */
// ----------------------------------------------------------------------

const NFmiPoint LocationSource::Pimple::coordinates(const std::string& theLocation) const
{
  if (hasCoordinates(theLocation)) return itsLastSuccesfulPoint;

  throw Fmi::Exception(BCP, "Cannot request coordinates for unknown location '" + theLocation + "'");
}

// ----------------------------------------------------------------------
/*!
 * \brief Private constructor for instance()
 */
// ----------------------------------------------------------------------

LocationSource::LocationSource() : itsPimple(new Pimple()) {}
// ----------------------------------------------------------------------
/*!
 * \brief Return an instance of LocationSource
 *
 * \return A reference to a LocationSource singleton
 */
// ----------------------------------------------------------------------

LocationSource& LocationSource::instance()
{
  static LocationSource source;
  return source;
}

// ----------------------------------------------------------------------
/*!
 * \brief Test whether the given location name has known coordinates
 *
 * Note that the result is cached internally so that a subsequent
 * coordinate request would be very fast.
 *
 * \param theLocation The location name
 * \return True, if the location has known coordinates
 */
// ----------------------------------------------------------------------

bool LocationSource::hasCoordinates(const std::string& theLocation) const
{
  return itsPimple->hasCoordinates(theLocation);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinate of the given named point
 *
 * Throws if the location has no known coordinates
 *
 * \param theLocation The location name
 * \return The coordinates (lonlat)
 */
// ----------------------------------------------------------------------

NFmiPoint LocationSource::coordinates(const std::string& theLocation) const
{
  return itsPimple->coordinates(theLocation);
}

}  // namespace TextGen

// ======================================================================
