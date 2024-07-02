// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::LatestWeatherSource
 */
// ======================================================================

#pragma once

#include "WeatherSource.h"
#include <memory>

namespace TextGen
{
class LatestWeatherSource : public WeatherSource
{
 public:
  LatestWeatherSource();
  std::shared_ptr<NFmiQueryData> data(const std::string& theName) const override;
  WeatherId id(const std::string& theName) const override;

 private:
  class Pimple;
  std::shared_ptr<Pimple> itsPimple;

};  // class LatestWeatherSource

}  // namespace TextGen

// ======================================================================
