// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::UserWeatherSource
 */
// ======================================================================

#pragma once

#include "WeatherSource.h"
#include <boost/shared_ptr.hpp>

class NFmiQueryData;

namespace TextGen
{
class UserWeatherSource : public WeatherSource
{
 public:
  UserWeatherSource();
  virtual boost::shared_ptr<NFmiQueryData> data(const std::string& theName) const;
  virtual WeatherId id(const std::string& theName) const;

  void insert(const std::string& theName, boost::shared_ptr<NFmiQueryData> theData) const;

 private:
  class Pimple;
  boost::shared_ptr<Pimple> itsPimple;

};  // class UserWeatherSource

}  // namespace TextGen


// ======================================================================
