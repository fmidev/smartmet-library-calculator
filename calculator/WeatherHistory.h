#pragma once

#include "TextGenPosixTime.h"
#include <string>

namespace TextGen
{
class WeatherHistory
{
 public:
  WeatherHistory();
  WeatherHistory(const WeatherHistory& theWeatherHistory);

  void updateTimePhrase(const std::string& theWeekdayPhrase,
                        const std::string& theDayPhasePhrase,
                        const TextGenPosixTime& theTime);
  void updateWeekdayPhrase(const std::string& theWeekdayPhrase, const TextGenPosixTime& theTime);
  void updateDayPhasePhrase(const std::string& theDayPhasePhrase);

  TextGenPosixTime latestDate;
  std::string latestWeekdayPhrase;
  std::string latestDayPhasePhrase;
};

}  // namespace TextGen
