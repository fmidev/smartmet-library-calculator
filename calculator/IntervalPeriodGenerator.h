// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::IntervalPeriodGenerator
 */
// ======================================================================

#pragma once

#include "WeatherPeriod.h"
#include "WeatherPeriodGenerator.h"

#include <string>
#include <vector>

namespace TextGen
{
class WeatherPeriod;

class IntervalPeriodGenerator : public WeatherPeriodGenerator
{
 public:
  using size_type = WeatherPeriodGenerator::size_type;

  IntervalPeriodGenerator(WeatherPeriod theMainPeriod,
                          int theStartHour,
                          int theInterval,
                          int theMinimumInterval);

  IntervalPeriodGenerator(WeatherPeriod theMainPeriod, const std::string& theVariable);

  ~IntervalPeriodGenerator() override = default;
  bool undivided() const override;
  size_type size() const override;
  WeatherPeriod period() const override;
  WeatherPeriod period(size_type thePeriod) const override;

 private:
  IntervalPeriodGenerator() = delete;
  void init();

  const WeatherPeriod itsMainPeriod;
  const int itsStartHour;
  const int itsInterval;
  const int itsMinimumInterval;

  std::vector<WeatherPeriod> itsPeriods;

};  // class IntervalPeriodGenerator

}  // namespace TextGen

// ======================================================================
