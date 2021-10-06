// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::WeatherSource
 */
// ======================================================================

#pragma once

#include <boost/shared_ptr.hpp>
#include <newbase/NFmiQueryData.h>
#include <string>

class NFmiQueryData;

namespace TextGen
{
typedef long WeatherId;

class WeatherSource
{
 public:
  virtual ~WeatherSource() = default;
  virtual boost::shared_ptr<NFmiQueryData> data(const std::string& theName) const = 0;
  virtual WeatherId id(const std::string& theName) const = 0;

};  // class WeatherSource

}  // namespace TextGen

// ======================================================================
