// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::WeatherPeriodGenerator
 */
// ======================================================================

#pragma once

namespace TextGen
{
class WeatherPeriod;

class WeatherPeriodGenerator
{
 public:
  using size_type = unsigned int;

  WeatherPeriodGenerator() = default;
  virtual ~WeatherPeriodGenerator() = default;
  virtual bool undivided() const = 0;
  virtual size_type size() const = 0;
  virtual WeatherPeriod period() const = 0;
  virtual WeatherPeriod period(size_type thePeriod) const = 0;

};  // class WeatherPeriodGenerator

}  // namespace TextGen

// ======================================================================
