#include "WeatherHistory.h"

namespace TextGen
{
WeatherHistory::WeatherHistory() : latestDate(1970, 1, 1) {}

void WeatherHistory::updateWeekdayPhrase(const std::string& theWeekdayPhrase,
                                         const TextGenPosixTime& theTime)
{
  latestWeekdayPhrase = theWeekdayPhrase;
  latestDate = theTime;
}

void WeatherHistory::updateDayPhasePhrase(const std::string& theDayPhasePhrase)
{
  latestDayPhasePhrase = theDayPhasePhrase;
}

void WeatherHistory::updateTimePhrase(const std::string& theWeekdayPhrase,
                                      const std::string& theDayPhasePhrase,
                                      const TextGenPosixTime& theTime)
{
  latestWeekdayPhrase = theWeekdayPhrase;
  latestDayPhasePhrase = theDayPhasePhrase;
  latestDate = theTime;
}
}  // namespace TextGen
