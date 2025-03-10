// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::RegularMaskSource
 */
// ======================================================================
/*!
 * \class TextGen::RegularMaskSource
 *
 * \brief Provides mask services to clients
 *
 * The RegularMaskSource class provides access to masks calculated from
 * named SVG paths which represent geographic areas.
 *
 * The constructor takes as an optional argument the distance in kilometers
 * by which each area may be expanded for a grid point to be considered
 * to be representative for the area. Normally we might use a distance
 * half the forecast grid spacing.
 */
// ======================================================================

#include "RegularMaskSource.h"

#include <macgyver/Exception.h>
#include "WeatherArea.h"
#include "WeatherSource.h"

#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiGrid.h>
#include <newbase/NFmiIndexMask.h>
#include <newbase/NFmiIndexMaskSource.h>
#include <newbase/NFmiIndexMaskTools.h>
#include <newbase/NFmiQueryData.h>

#include <map>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Utility structure to each cache management
 */
// ----------------------------------------------------------------------

struct WeatherAreaAndID
{
  WeatherId itsID;
  WeatherArea itsArea;

  WeatherAreaAndID(const WeatherId& theID, const WeatherArea& theArea)
      : itsID(theID), itsArea(theArea)
  {
  }

  bool operator==(const WeatherAreaAndID& theOther) const
  {
    return (itsID == theOther.itsID && itsArea == theOther.itsArea);
  }

  bool operator<(const WeatherAreaAndID& theOther) const
  {
    return (itsID != theOther.itsID ? itsID < theOther.itsID : itsArea < theOther.itsArea);
  }
};

// ----------------------------------------------------------------------
/*!
 * \brief Implementation hiding detail for TextGen::RegularMaskSource
 */
// ----------------------------------------------------------------------

class RegularMaskSource::Pimple
{
 public:
  using mask_storage = std::map<WeatherAreaAndID, mask_type>;
  using masks_storage = std::map<WeatherAreaAndID, masks_type>;

  mask_storage itsMaskStorage;
  masks_storage itsMasksStorage;

  mask_type find(const WeatherId& theID, const WeatherArea& theArea) const;

  void insert(const WeatherId& theID, const WeatherArea& theArea, const mask_type& theMask);

  mask_type create_mask(const WeatherArea& theArea,
                        const std::string& theData,
                        const WeatherSource& theWeatherSource) const;

};  // class RegularMaskSource::Pimple

// ----------------------------------------------------------------------
/*!
 * \brief Find mask from cache
 *
 * Returns a 0-shared pointer if mask is not found
 *
 * \param theID The weather ID
 * \param theArea The weather area
 * \return std::shared_ptr to mask or 0
 */
// ----------------------------------------------------------------------

RegularMaskSource::mask_type RegularMaskSource::Pimple::find(const WeatherId& theID,
                                                             const WeatherArea& theArea) const
{
  static std::shared_ptr<NFmiIndexMask> dummy;

  WeatherAreaAndID key(theID, theArea);

  const auto it = itsMaskStorage.find(key);
  if (it == itsMaskStorage.end()) return dummy;

  return it->second;
}

// ----------------------------------------------------------------------
/*!
 * \brief Insert a new mask into the cache
 *
 * \param theID The data ID
 * \param theArea The weather area
 * \param theMask The mask itself
 */
// ----------------------------------------------------------------------

void RegularMaskSource::Pimple::insert(const WeatherId& theID,
                                       const WeatherArea& theArea,
                                       const mask_type& theMask)
{
  using value_type = mask_storage::value_type;

  WeatherAreaAndID key(theID, theArea);

  itsMaskStorage.insert(value_type(key, theMask));

  if (itsMaskStorage.insert(value_type(key, theMask)).second)
    throw Fmi::Exception(BCP, "Could not cache mask for " + theArea.name());
}

// ----------------------------------------------------------------------
/*!
 * \brief Create a new weather area
 *
 * \param theArea The area
 * \param theData The data name
 * \param theWeatherSource The weather source
 * \return The mask
 */
// ----------------------------------------------------------------------

RegularMaskSource::mask_type RegularMaskSource::Pimple::create_mask(
    const WeatherArea& theArea,
    const std::string& theData,
    const WeatherSource& theWeatherSource) const
{
  const NFmiSvgPath& svg = theArea.path();
  const float radius = theArea.radius();

  std::shared_ptr<NFmiQueryData> qdata = theWeatherSource.data(theData);
  NFmiFastQueryInfo qi = NFmiFastQueryInfo(qdata.get());
  if (!qi.IsGrid())
    throw Fmi::Exception(BCP, "The data in " + theData + " is not gridded - cannot generate mask for it");

  mask_type areamask(new NFmiIndexMask(NFmiIndexMaskTools::MaskExpand(*(qi.Grid()), svg, radius)));
  return areamask;
}

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

RegularMaskSource::RegularMaskSource() : itsPimple(new Pimple()) {}
// ----------------------------------------------------------------------
/*!
 * \brief Return the mask for the given area
 *
 * \param theArea The weather area
 * \param theData The data name
 * \param theWeatherSource The source for weather data
 */
// ----------------------------------------------------------------------

RegularMaskSource::mask_type RegularMaskSource::mask(const WeatherArea& theArea,
                                                     const std::string& theData,
                                                     const WeatherSource& theWeatherSource) const
{
  if (theArea.isPoint()) throw Fmi::Exception(BCP, "Trying to generate mask for point");

  // Establish the ID for the data

  WeatherId id = theWeatherSource.id(theData);

  // Try to find cached mask first

  mask_type areamask = itsPimple->find(id, theArea);

  if (areamask.get() != nullptr) return areamask;

  // Calculate new mask and cache it

  areamask = itsPimple->create_mask(theArea, theData, theWeatherSource);
  itsPimple->insert(id, theArea, areamask);

  return areamask;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the mask source for the given area
 *
 * \param theArea The weather area
 * \param theData The data name
 * \param theWeatherSource The source for weather data
 */
// ----------------------------------------------------------------------

RegularMaskSource::masks_type RegularMaskSource::masks(
    const WeatherArea& /* theArea */,
    const std::string& /* theData */,
    const WeatherSource& /* theWeatherSource */) const
{
  throw Fmi::Exception(BCP, "RegularMaskSource::masks not implemented");
}

}  // namespace TextGen

// ======================================================================
