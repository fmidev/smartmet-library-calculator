// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::RegularMaskSource
 */
// ======================================================================

#pragma once

#include "MaskSource.h"

namespace TextGen
{
class RegularMaskSource : public MaskSource
{
 public:
  using mask_type = MaskSource::mask_type;
  using masks_type = MaskSource::masks_type;

  RegularMaskSource();

  mask_type mask(const WeatherArea& theArea,
                         const std::string& theData,
                         const WeatherSource& theWeatherSource) const override;

  masks_type masks(const WeatherArea& theArea,
                           const std::string& theData,
                           const WeatherSource& theWeatherSource) const override;

 private:
  class Pimple;
  std::shared_ptr<Pimple> itsPimple;

};  // class RegularMaskSource

}  // namespace TextGen

// ======================================================================
