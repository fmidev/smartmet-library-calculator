#pragma once

#include "TextGenPosixTime.h"
#include <string>

namespace TextGen
{
class WeatherHistory
{
 public:
  WeatherHistory() = default;
  WeatherHistory(const WeatherHistory& other) = default;

  void updateTimePhrase(const std::string& theWeekdayPhrase,
                        const std::string& theDayPhasePhrase,
                        const TextGenPosixTime& theTime);
  void updateWeekdayPhrase(const std::string& theWeekdayPhrase, const TextGenPosixTime& theTime);
  void updateDayPhasePhrase(const std::string& theDayPhasePhrase);

  TextGenPosixTime latestDate{1970, 1, 1};
  std::string latestWeekdayPhrase;
  std::string latestDayPhasePhrase;
};

}  // namespace TextGen
