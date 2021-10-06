// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::NullPeriodGenerator
 */
// ======================================================================

#pragma once

#include "WeatherPeriod.h"
#include "WeatherPeriodGenerator.h"

#include <string>

namespace TextGen
{
class WeatherPeriod;

class NullPeriodGenerator : public WeatherPeriodGenerator
{
 public:
  typedef WeatherPeriodGenerator::size_type size_type;

  NullPeriodGenerator(WeatherPeriod theMainPeriod);

  virtual ~NullPeriodGenerator() = default;
  virtual bool undivided() const;
  virtual size_type size() const;
  virtual WeatherPeriod period() const;
  virtual WeatherPeriod period(size_type thePeriod) const;

 private:
  NullPeriodGenerator() = delete;

  const WeatherPeriod itsMainPeriod;

};  // class NullPeriodGenerator

}  // namespace TextGen

// ======================================================================
