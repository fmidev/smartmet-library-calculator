// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::UserWeatherSource
 */
// ======================================================================

#pragma once

#include "WeatherSource.h"
#include <memory>

class NFmiQueryData;

namespace TextGen
{
class UserWeatherSource : public WeatherSource
{
 public:
  UserWeatherSource();
  std::shared_ptr<NFmiQueryData> data(const std::string& theName) const override;
  WeatherId id(const std::string& theName) const override;

  void insert(const std::string& theName, const std::shared_ptr<NFmiQueryData>& theData) const;

 private:
  class Pimple;
  std::shared_ptr<Pimple> itsPimple;

};  // class UserWeatherSource

}  // namespace TextGen

// ======================================================================
