// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::LatestWeatherSource
 */
// ======================================================================

#pragma once

#include "WeatherSource.h"
#include <boost/shared_ptr.hpp>

namespace TextGen
{
class LatestWeatherSource : public WeatherSource
{
 public:
  LatestWeatherSource();
  boost::shared_ptr<NFmiQueryData> data(const std::string& theName) const override;
  WeatherId id(const std::string& theName) const override;

 private:
  class Pimple;
  boost::shared_ptr<Pimple> itsPimple;

};  // class LatestWeatherSource

}  // namespace TextGen

// ======================================================================
