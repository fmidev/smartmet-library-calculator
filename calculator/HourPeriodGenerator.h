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
  typedef WeatherPeriodGenerator::size_type size_type;

  HourPeriodGenerator(WeatherPeriod theMainPeriod,
                      int theStartHour,
                      int theEndHour,
                      int theMaxStartHour,
                      int theMinEndHour);

  HourPeriodGenerator(WeatherPeriod theMainPeriod, const std::string& theVariable);

  virtual ~HourPeriodGenerator() {}
  virtual bool undivided() const;
  virtual size_type size() const;
  virtual WeatherPeriod period() const;
  virtual WeatherPeriod period(size_type thePeriod) const;

 private:
  HourPeriodGenerator(void);

  const WeatherPeriod itsMainPeriod;
  const int itsStartHour;
  const int itsEndHour;
  const int itsMaxStartHour;
  const int itsMinEndHour;
  const size_type itsSize;

};  // class HourPeriodGenerator

}  // namespace TextGen

// ======================================================================
