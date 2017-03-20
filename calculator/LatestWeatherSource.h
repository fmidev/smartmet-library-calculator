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
  virtual boost::shared_ptr<NFmiQueryData> data(const std::string& theName) const;
  virtual WeatherId id(const std::string& theName) const;

 private:
  class Pimple;
  boost::shared_ptr<Pimple> itsPimple;

};  // class LatestWeatherSource

}  // namespace TextGen


// ======================================================================
