// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::WeatherSource
 */
// ======================================================================

#pragma once

#include <memory>
#include <newbase/NFmiQueryData.h>
#include <string>

class NFmiQueryData;

namespace TextGen
{
using WeatherId = long;

class WeatherSource
{
 public:
  virtual ~WeatherSource() = default;
  virtual std::shared_ptr<NFmiQueryData> data(const std::string& theName) const = 0;
  virtual WeatherId id(const std::string& theName) const = 0;

};  // class WeatherSource

}  // namespace TextGen

// ======================================================================
