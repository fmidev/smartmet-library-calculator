// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ListedPeriodGenerator
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

class ListedPeriodGenerator : public WeatherPeriodGenerator
{
 public:
  using size_type = WeatherPeriodGenerator::size_type;

  ListedPeriodGenerator(const WeatherPeriod& theMainPeriod);

  ~ListedPeriodGenerator() override = default;
  bool undivided() const override;
  size_type size() const override;
  WeatherPeriod period() const override;
  WeatherPeriod period(size_type thePeriod) const override;

  void add(const WeatherPeriod& thePeriod);

 private:
  ListedPeriodGenerator() = delete;

  const WeatherPeriod itsMainPeriod;
  std::vector<WeatherPeriod> itsPeriods;

};  // class ListedPeriodGenerator

}  // namespace TextGen

// ======================================================================
