// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaskSource
 */
// ======================================================================

#pragma once

#include <memory>
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
  using mask_type = std::shared_ptr<NFmiIndexMask>;
  using masks_type = std::shared_ptr<NFmiIndexMaskSource>;

  virtual ~MaskSource();
  virtual mask_type mask(const WeatherArea& theArea,
                         const std::string& theData,
                         const WeatherSource& theWeatherSource) const = 0;

  virtual masks_type masks(const WeatherArea& theArea,
                           const std::string& theData,
                           const WeatherSource& theWeatherSource) const = 0;

};  // class MaskSource

}  // namespace TextGen

// ======================================================================
