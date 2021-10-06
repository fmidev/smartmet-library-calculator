// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaskSource
 */
// ======================================================================

#pragma once

#include <boost/shared_ptr.hpp>
#include <string>

class NFmiIndexMask;
class NFmiIndexMaskSource;
class NFmiPoint;

namespace TextGen
{
class MapSource;
class WeatherArea;
class WeatherSource;

class MaskSource
{
 public:
  using mask_type = boost::shared_ptr<NFmiIndexMask>;
  using masks_type = boost::shared_ptr<NFmiIndexMaskSource>;

  virtual ~MaskSource() = default;
  virtual mask_type mask(const WeatherArea& theArea,
                         const std::string& theData,
                         const WeatherSource& theWeatherSource) const = 0;

  virtual masks_type masks(const WeatherArea& theArea,
                           const std::string& theData,
                           const WeatherSource& theWeatherSource) const = 0;

};  // class MaskSource

}  // namespace TextGen

// ======================================================================
