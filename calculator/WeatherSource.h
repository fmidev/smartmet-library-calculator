// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::WeatherSource
 */
// ======================================================================

#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <newbase/NFmiQueryData.h>

class NFmiQueryData;

namespace TextGen
{
typedef long WeatherId;

class WeatherSource
{
 public:
  virtual ~WeatherSource() {}
  virtual boost::shared_ptr<NFmiQueryData> data(const std::string& theName) const = 0;
  virtual WeatherId id(const std::string& theName) const = 0;

};  // class WeatherSource

}  // namespace TextGen


// ======================================================================
