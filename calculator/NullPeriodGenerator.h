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
  using size_type = WeatherPeriodGenerator::size_type;

  NullPeriodGenerator(WeatherPeriod theMainPeriod);

  ~NullPeriodGenerator() override = default;
  bool undivided() const override;
  size_type size() const override;
  WeatherPeriod period() const override;
  WeatherPeriod period(size_type thePeriod) const override;

 private:
  NullPeriodGenerator() = delete;

  const WeatherPeriod itsMainPeriod;

};  // class NullPeriodGenerator

}  // namespace TextGen

// ======================================================================
