// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::QueryDataIntegrator
 */
// ======================================================================

#pragma once

#include <vector>

class NFmiFastQueryInfo;
class NFmiIndexMask;
class NFmiIndexMaskSource;
class NFmiPoint;
class TextGenPosixTime;

namespace TextGen
{
class Calculator;
class WeatherPeriodGenerator;

namespace QueryDataIntegrator
{
// Integrate over time with current location & param & level

float Integrate(NFmiFastQueryInfo& theQI,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator);

// Integrate over time with current param & level and given latlon

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiPoint& theLatLon,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator);

// Integrate over time with subinterval generator w/ current location/param/level

float Integrate(NFmiFastQueryInfo& theQI,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator);

// Integrate over time with subinterval generator w/ current param/level for given latlon

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiPoint& theLatLon,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator);

// Integrate over grid with current param & time & level

float Integrate(const NFmiFastQueryInfo& theQI,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator);

// Integrate over grid and time with current param & level

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator);

// Integrate over time and grid with current param & level

float Integrate(NFmiFastQueryInfo& theQI,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator);

// Integrate over grid and time with time dependent mask, current P & L

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiIndexMaskSource& theMaskSource,
                Calculator& theSpaceCalculator,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator);

// Integrate over time, sub time and grid with current param & level

float Integrate(NFmiFastQueryInfo& theQI,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator);

// Integrate over time and sub time for each grid point with current param & level

bool IntegrateTime(NFmiFastQueryInfo& theQI,
                   const WeatherPeriodGenerator& thePeriods,
                   Calculator& theSubTimeCalculator,
                   Calculator& theMainTimeCalculator,
                   const NFmiIndexMask& theIndexMask,
                   std::vector<float>& theResults);

// Integrate over precalculated values

float Integrate(const std::vector<float>& theValues, Calculator& theCalculator);

}  // namespace QueryDataIntegrator
}  // namespace TextGen

// ======================================================================
