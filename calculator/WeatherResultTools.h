// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::WeatherResultTools
 */
// ======================================================================

#pragma once

#include "WeatherParameter.h"
#include "WeatherResult.h"
#include <string>
#include <vector>

namespace TextGen
{
namespace WeatherResultTools
{
WeatherResult min(const WeatherResult& theResult1, const WeatherResult& theResult2);

WeatherResult max(const WeatherResult& theResult1, const WeatherResult& theResult2);

WeatherResult mean(const WeatherResult& theResult1, const WeatherResult& theResult2);

WeatherResult min(const WeatherResult& theResult1,
                  const WeatherResult& theResult2,
                  const WeatherResult& theResult3);

WeatherResult max(const WeatherResult& theResult1,
                  const WeatherResult& theResult2,
                  const WeatherResult& theResult3);

WeatherResult mean(const WeatherResult& theResult1,
                   const WeatherResult& theResult2,
                   const WeatherResult& theResult3);

bool isSimilarRange(const WeatherResult& theMinimum1,
                    const WeatherResult& theMaximum1,
                    const WeatherResult& theMinimum2,
                    const WeatherResult& theMaximum2,
                    const std::string& theVar);

void checkMissingValue(const std::string& theStoryName,
                       WeatherParameter theParameter,
                       const WeatherResult& theWeatherResult);

void checkMissingValue(const std::string& theStoryName,
                       WeatherParameter theParameter,
                       const std::vector<WeatherResult>& theWeatherResultVector);
}  // namespace WeatherResultTools
}  // namespace TextGen

// ======================================================================
