// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::HourPeriodGenerator
 */
// ======================================================================

#pragma once

#include "WeatherPeriod.h"
#include "WeatherPeriodGenerator.h"

#include <string>

namespace TextGen
{
class WeatherPeriod;

class HourPeriodGenerator : public WeatherPeriodGenerator
{
 public:
  using size_type = WeatherPeriodGenerator::size_type;

  HourPeriodGenerator() = delete;
  HourPeriodGenerator(WeatherPeriod theMainPeriod,
                      int theStartHour,
                      int theEndHour,
                      int theMaxStartHour,
                      int theMinEndHour);

  HourPeriodGenerator(WeatherPeriod theMainPeriod, const std::string& theVariable);

  ~HourPeriodGenerator() override = default;
  bool undivided() const override;
  size_type size() const override;
  WeatherPeriod period() const override;
  WeatherPeriod period(size_type thePeriod) const override;

 private:
  const WeatherPeriod itsMainPeriod;
  const int itsStartHour;
  const int itsEndHour;
  const int itsMaxStartHour;
  const int itsMinEndHour;
  const size_type itsSize;

};  // class HourPeriodGenerator

}  // namespace TextGen

// ======================================================================
