// ======================================================================
/*!
 * \file
 * \brief Implementation of namespace TextGen::QueryDataIntegrator
 */
// ======================================================================
/*!
 * \namespace TextGen::QueryDataIntegrator
 *
 * \brief Functions for integrating query data
 *
 * The QueryDataIntegrator namespace defines several methods
 * for performing data integration in space and time.
 *
 */
// ======================================================================

#include "QueryDataIntegrator.h"
#include "Calculator.h"
#include "QueryDataTools.h"
#include "TextGenPosixTime.h"
#include "WeatherPeriod.h"
#include "WeatherPeriodGenerator.h"
#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiGlobals.h>
#include <newbase/NFmiIndexMask.h>
#include <newbase/NFmiIndexMaskSource.h>
#include <newbase/NFmiMetTime.h>
#include <algorithm>
#include <typeinfo>
#include <vector>

namespace
{
// ----------------------------------------------------------------------
/*!
 * \brief Consecutive time steps
 */
// ----------------------------------------------------------------------

struct TimeRange
{
  unsigned long startindex = 0;
  unsigned long count = 0;
};

// ----------------------------------------------------------------------
/*!
 * \brief Test if values can be read directly from the raw data
 *
 * Derived classes such as MaximumWindQueryInfo calculate the values
 * in a virtual GetFloatValue method, and combined parameters need
 * decoding, hence both must be read one value at a time.
 */
// ----------------------------------------------------------------------

bool can_read_blocks(const NFmiFastQueryInfo& theQI)
{
  return typeid(theQI) == typeid(NFmiFastQueryInfo) && !theQI.IsSubParamUsed();
}

// ----------------------------------------------------------------------
/*!
 * \brief Read a block of raw values for consecutive locations and times
 *
 * Reading one value at a time is slow for high resolution data. Since
 * both the locations and the time steps are stored at regular intervals
 * in querydata, a block can be read with a few calls instead.
 *
 * \return False if the block cannot be read directly
 */
// ----------------------------------------------------------------------

bool read_raw_block(const NFmiFastQueryInfo& theQI,
                    unsigned long theFirstLocation,
                    unsigned long theLocationCount,
                    unsigned long theStartIndex,
                    unsigned long theCount,
                    std::vector<float>& theValues,
                    std::vector<float>& theColumn)
{
  const auto invalid = static_cast<size_t>(-1);
  const unsigned long param = theQI.ParamIndex();
  const unsigned long level = theQI.LevelIndex();
  const unsigned long lastlocation = theFirstLocation + theLocationCount - 1;

  // If the corners of the block are valid, so is everything in between

  const size_t idx = theQI.Index(param, theFirstLocation, level, theStartIndex);
  if (idx == invalid)
    return false;
  if (theQI.Index(param, lastlocation, level, theStartIndex + theCount - 1) == invalid)
    return false;

  // The time steps of a single location are consecutive

  if (theLocationCount == 1)
    return theQI.GetValues(idx, 1, theCount, theValues);

  // Otherwise read one time step at a time for all the locations

  const size_t step = theQI.Index(param, theFirstLocation + 1, level, theStartIndex) - idx;

  if (theCount == 1)
    return theQI.GetValues(idx, step, theLocationCount, theValues);

  theValues.resize(theLocationCount * theCount);

  for (unsigned long i = 0; i < theCount; i++)
  {
    if (!theQI.GetValues(idx + i, step, theLocationCount, theColumn))
      return false;
    for (unsigned long loc = 0; loc < theLocationCount; loc++)
      theValues[loc * theCount + i] = theColumn[loc];
  }

  return true;
}

// ----------------------------------------------------------------------
/*!
 * \brief Read a block of values for consecutive locations and times
 *
 * The active parameter and level are used. The time series of each
 * location are stored consecutively into the output vector.
 *
 * \param theQI The query info
 * \param theBlockFlag True if can_read_blocks is true for the info
 * \param theFirstLocation The first location index
 * \param theLocationCount The number of locations
 * \param theStartIndex The first time index
 * \param theCount The number of time steps
 * \param theValues The values read
 * \param theColumn Work space
 */
// ----------------------------------------------------------------------

void read_block(const NFmiFastQueryInfo& theQI,
                bool theBlockFlag,
                unsigned long theFirstLocation,
                unsigned long theLocationCount,
                unsigned long theStartIndex,
                unsigned long theCount,
                std::vector<float>& theValues,
                std::vector<float>& theColumn)
{
  if (theBlockFlag &&
      read_raw_block(
          theQI, theFirstLocation, theLocationCount, theStartIndex, theCount, theValues, theColumn))
    return;

  const unsigned long param = theQI.ParamIndex();
  const unsigned long level = theQI.LevelIndex();

  theValues.resize(theLocationCount * theCount);

  for (unsigned long loc = 0; loc < theLocationCount; loc++)
    for (unsigned long i = 0; i < theCount; i++)
    {
      // possible -1 is handled by IndexFloatValue
      const size_t idx = theQI.Index(param, theFirstLocation + loc, level, theStartIndex + i);
      theValues[loc * theCount + i] = theQI.GetFloatValue(idx);
    }
}

// ----------------------------------------------------------------------
/*!
 * \brief Call a function with the time series of each location in the mask
 *
 * The function is called in mask order with a pointer to the values
 * of the given time steps.
 *
 * \param theQI The query info
 * \param theIndexMask The mask containing the space indices
 * \param theStartIndex The first time index
 * \param theCount The number of time steps
 * \param theFunction The function to call
 */
// ----------------------------------------------------------------------

template <typename Function>
void for_each_series(const NFmiFastQueryInfo& theQI,
                     const NFmiIndexMask& theIndexMask,
                     unsigned long theStartIndex,
                     unsigned long theCount,
                     const Function& theFunction)
{
  if (theCount == 0)
  {
    for (auto it = theIndexMask.begin(); it != theIndexMask.end(); ++it)
      theFunction(nullptr);
    return;
  }

  // Limits the size of the work space
  const unsigned long max_locations = 1024;

  const bool blockflag = can_read_blocks(theQI);
  std::vector<float> values;
  std::vector<float> column;

  auto it = theIndexMask.begin();
  const auto end = theIndexMask.end();

  while (it != end)
  {
    // Collect consecutive locations

    const unsigned long first = *it;
    unsigned long count = 1;
    for (++it; it != end && count < max_locations && *it == first + count; ++it)
      ++count;

    read_block(theQI, blockflag, first, count, theStartIndex, theCount, values, column);

    for (unsigned long loc = 0; loc < count; loc++)
      theFunction(&values[loc * theCount]);
  }
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time for each location in the mask
 *
 * \param theQI The query info
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The modifier for accumulating the time result
 * \param theIndexMask The mask containing the space indices
 * \param theConsumer Function called with the time result of each location
 * \return False if the integration is not possible
 */
// ----------------------------------------------------------------------

template <typename Consumer>
bool integrate_time(NFmiFastQueryInfo& theQI,
                    const TextGenPosixTime& theStartTime,
                    const TextGenPosixTime& theEndTime,
                    TextGen::Calculator& theTimeCalculator,
                    const NFmiIndexMask& theIndexMask,
                    const Consumer& theConsumer)
{
  if (theIndexMask.empty())
    return false;

  unsigned long startindex = 0;
  unsigned long endindex = 0;

  if (!TextGen::QueryDataTools::findIndices(theQI, theStartTime, theEndTime, startindex, endindex))
    return false;

  // The start time is always processed, the time at the end index never is

  const unsigned long lastindex = std::min<unsigned long>(endindex, theQI.SizeTimes());
  const unsigned long count = (lastindex > startindex ? lastindex - startindex : 1);

  for_each_series(theQI,
                  theIndexMask,
                  startindex,
                  count,
                  [&](const float* theSeries)
                  {
                    theTimeCalculator.reset();
                    for (unsigned long i = 0; i < count; i++)
                      theTimeCalculator(theSeries[i]);
                    theConsumer(theTimeCalculator());
                  });
  return true;
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time with subperiods for each location in the mask
 *
 * \param theQI The query info
 * \param thePeriods The subperiod generator
 * \param theSubTimeCalculator The modifier for accumulating the subperiod result
 * \param theMainTimeCalculator The modifier for accumulating the subperiod results
 * \param theIndexMask The mask containing the space indices
 * \param theConsumer Function called with the time result of each location
 * \return False if the integration is not possible
 */
// ----------------------------------------------------------------------

template <typename Consumer>
bool integrate_time(NFmiFastQueryInfo& theQI,
                    const TextGen::WeatherPeriodGenerator& thePeriods,
                    TextGen::Calculator& theSubTimeCalculator,
                    TextGen::Calculator& theMainTimeCalculator,
                    const NFmiIndexMask& theIndexMask,
                    const Consumer& theConsumer)
{
  if (thePeriods.undivided())
  {
    return integrate_time(theQI,
                          thePeriods.period(1).utcStartTime(),
                          thePeriods.period(1).utcEndTime(),
                          theMainTimeCalculator,
                          theIndexMask,
                          theConsumer);
  }

  if (thePeriods.size() <= 0)
    return false;

  if (theIndexMask.empty())
    return false;

  // The time steps of each subperiod are the same for all locations

  std::vector<TimeRange> ranges;
  unsigned long startindex = 0;
  unsigned long endindex = 0;

  for (unsigned int i = 1; i < thePeriods.size(); i++)
  {
    TextGen::WeatherPeriod period = thePeriods.period(i);

    if (!TextGen::QueryDataTools::firstTime(theQI, period.utcStartTime(), period.utcEndTime()))
      return false;

    TimeRange range;
    range.startindex = theQI.TimeIndex();
    range.count = 1;
    while (theQI.NextTime() && theQI.Time() <= period.utcEndTime())
      ++range.count;

    if (ranges.empty())
    {
      startindex = range.startindex;
      endindex = range.startindex + range.count;
    }
    else
    {
      startindex = std::min(startindex, range.startindex);
      endindex = std::max(endindex, range.startindex + range.count);
    }

    ranges.push_back(range);
  }

  for_each_series(theQI,
                  theIndexMask,
                  startindex,
                  endindex - startindex,
                  [&](const float* theSeries)
                  {
                    theMainTimeCalculator.reset();

                    for (const auto& range : ranges)
                    {
                      theSubTimeCalculator.reset();

                      const float* values = theSeries + (range.startindex - startindex);
                      for (unsigned long i = 0; i < range.count; i++)
                        theSubTimeCalculator(values[i]);

                      theMainTimeCalculator(theSubTimeCalculator());
                    }

                    theConsumer(theMainTimeCalculator());
                  });
  return true;
}

}  // namespace

namespace TextGen
{
namespace QueryDataIntegrator
{
// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time
 *
 * Integrate over time with current location, parameter and level.
 *
 * If the start time does not exist in the data, a missing value
 * is returned.
 *
 * \param theQI The query info
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The calculator for accumulating the result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator)
{
  theTimeCalculator.reset();

  if (!QueryDataTools::firstTime(theQI, theStartTime, theEndTime))
    return kFloatMissing;

  for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= theEndTime)
  {
    const float tmp = theQI.FloatValue();
    theTimeCalculator(tmp);
  }

  return theTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time
 *
 * Integrate over time with current parameter and level and given latlon
 *
 * If the start time does not exist in the data, a missing value
 * is returned.
 *
 * \param theQI The query info
 * \param theLatLon The coordinate
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The calculator for accumulating the result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiPoint& theLatLon,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator)
{
  theTimeCalculator.reset();

  if (!QueryDataTools::firstTime(theQI, theStartTime, theEndTime))
    return kFloatMissing;

  for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= theEndTime)
  {
    const float tmp = theQI.InterpolatedValue(theLatLon);
    theTimeCalculator(tmp);
  }

  return theTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time with subinterval generator
 *
 * Integrate over time with current location, parameter and level.
 * The time interval is divided into subinterval by a given
 * generator and the subintervals are integrated using a separate
 * calculator.
 *
 * Note that the generated periods are inclusive, both the start
 * and end time are considered to belong into the period.
 *
 * If no subintervals can be created, a missing value is returned.
 *
 * \param theQI The query info
 * \param thePeriods The subperiod generator
 * \param theSubTimeCalculator The calculator for accumulating the subresult
 * \param theMainTimeCalculator The calculator for subresults
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator)
{
  if (thePeriods.undivided())
  {
    return Integrate(theQI,
                     thePeriods.period(1).utcStartTime(),
                     thePeriods.period(1).utcEndTime(),
                     theMainTimeCalculator);
  }

  // Safety against bad loop
  if (thePeriods.size() <= 0)
    return kFloatMissing;

  theMainTimeCalculator.reset();

  for (unsigned int i = 1; i < thePeriods.size(); i++)
  {
    WeatherPeriod period = thePeriods.period(i);

    if (!QueryDataTools::firstTime(theQI, period.utcStartTime(), period.utcEndTime()))
      return kFloatMissing;

    theSubTimeCalculator.reset();

    for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= period.utcEndTime())
    {
      const float tmp = theQI.FloatValue();
      theSubTimeCalculator(tmp);
    }

    const float subresult = theSubTimeCalculator();
    theMainTimeCalculator(subresult);
  }

  return theMainTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time with subinterval generator
 *
 * Integrate over time with current parameter and level and given latlon
 * The time interval is divided into subinterval by a given
 * generator and the subintervals are integrated using a separate
 * calculator.
 *
 * Note that the generated periods are inclusive, both the start
 * and end time are considered to belong into the period.
 *
 * If no subintervals can be created, a missing value is returned.
 *
 * \param theQI The query info
 * \param thePeriods The subperiod generator
 * \param theSubTimeCalculator The calculator for accumulating the subresult
 * \param theMainTimeCalculator The calculator for subresults
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiPoint& theLatLon,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator)
{
  if (thePeriods.undivided())
  {
    return Integrate(theQI,
                     theLatLon,
                     thePeriods.period(1).utcStartTime(),
                     thePeriods.period(1).utcEndTime(),
                     theMainTimeCalculator);
  }

  // Safety against bad loop
  if (thePeriods.size() <= 0)
    return kFloatMissing;

  theMainTimeCalculator.reset();

  for (unsigned int i = 1; i < thePeriods.size(); i++)
  {
    WeatherPeriod period = thePeriods.period(i);

    if (!QueryDataTools::firstTime(theQI, period.utcStartTime(), period.utcEndTime()))
      return kFloatMissing;

    theSubTimeCalculator.reset();

    for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= period.utcEndTime())
    {
      const float tmp = theQI.InterpolatedValue(theLatLon);
      theSubTimeCalculator(tmp);
    }

    const float subresult = theSubTimeCalculator();
    theMainTimeCalculator(subresult);
  }

  return theMainTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over space
 *
 * Integrate over space with current time, parameter and level.
 *
 * It is assumed that the index mask was generated from a grid
 * equivalent to the one in the query data.
 *
 * \param theQI The query info
 * \param theIndexMask The mask containing the space indices
 * \param theSpaceCalculator The modifier for accumulating the result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(const NFmiFastQueryInfo& theQI,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator)
{
  if (theIndexMask.empty())
    return kFloatMissing;

  theSpaceCalculator.reset();

  for (const auto& mask : theIndexMask)
  {
    // possible -1 is handled by IndexFloatValue
    const unsigned long idx =
        theQI.Index(theQI.ParamIndex(), mask, theQI.LevelIndex(), theQI.TimeIndex());
    const float tmp = theQI.GetFloatValue(idx);
    theSpaceCalculator(tmp);
  }

  return theSpaceCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over space and time
 *
 * Integrate over space and time with current parameter and level.
 * Note that the integration order is different from the Integrate
 * command where the order of time and space arguments are reversed.
 * Here space integration is performed first, then time integration.
 *
 * If the start time does not exist in the data, a missing value
 * is returned.
 *
 * \param theQI The query info
 * \param theIndexMask The  mask containing the space indices
 * \param theSpaceCalculator  The calculator for accumulating space result
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The calculator for accumulating the time result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator)
{
  theTimeCalculator.reset();

  if (!QueryDataTools::firstTime(theQI, theStartTime, theEndTime))
    return kFloatMissing;
  if (theIndexMask.empty())
    return kFloatMissing;

  for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= theEndTime)
  {
    const float tmp = Integrate(theQI, theIndexMask, theSpaceCalculator);
    theTimeCalculator(tmp);
  }

  return theTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time and space
 *
 * Integrate over time and space with current parameter and level.
 * Note that the integration order is different from the Integrate
 * command where the order of time and space arguments are reversed.
 * Here time integration is performed first, then space integration.
 *
 * If the start time does not exist in the data, a missing value
 * is returned.
 *
 * \param theQI The query info
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The calculator for accumulating the time result
 * \param theIndexMask The mask containing the space indices
 * \param theSpaceCalculator The calculator for accumulating the space result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator)
{
  theSpaceCalculator.reset();

  if (!integrate_time(theQI,
                      theStartTime,
                      theEndTime,
                      theTimeCalculator,
                      theIndexMask,
                      [&](float theValue) { theSpaceCalculator(theValue); }))
    return kFloatMissing;

  return theSpaceCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over space and time with time dependent masks
 *
 * Integrate over space and time with current parameter and level.
 * The space mask is time dependent and is obtained from a
 * NFmiIndexMaskSource.
 *
 * If the start time does not exist in the data, a missing value
 * is returned.
 *
 * \param theQI The query info
 * \param theMaskSource The masks for any specific time
 * \param theSpaceCalculator The calculator for accumulating the space result
 * \param theStartTime The start time of the integration.
 * \param theEndTime The end time of the integration.
 * \param theTimeCalculator The calculator for accumulating the time result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const NFmiIndexMaskSource& theMaskSource,
                Calculator& theSpaceCalculator,
                const TextGenPosixTime& theStartTime,
                const TextGenPosixTime& theEndTime,
                Calculator& theTimeCalculator)
{
  theTimeCalculator.reset();

  if (!QueryDataTools::firstTime(theQI, theStartTime, theEndTime))
    return kFloatMissing;

  for (bool more = true; more; more = theQI.NextTime() && theQI.Time() <= theEndTime)
  {
    const NFmiIndexMask& mask = theMaskSource.Find(theQI.Time());
    const float tmp = Integrate(theQI, mask, theSpaceCalculator);
    theTimeCalculator(tmp);
  }

  return theTimeCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time, subtime, time and space
 *
 * Integrate over time and space with current parameter and level.
 * Note that the integration order is different from the Integrate
 * command where the order of time and space arguments are reversed.
 * Here time integration is performed first, then space integration.
 * Also, the time integration is split into two parts with separate
 * modifiers. The parts are generated by the given WeatherPeriodGenerator.
 *
 * \param theQI The query info
 * \param thePeriods The weather period generator
 * \param theSubTimeCalculator The calculator for accumulating sub periods
 * \param theMainTimeCalculator The calculator for accumulating sub period results
 * \param theIndexMask The mask containing the space indices
 * \param theSpaceCalculator The calculator for accumulating the space result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(NFmiFastQueryInfo& theQI,
                const WeatherPeriodGenerator& thePeriods,
                Calculator& theSubTimeCalculator,
                Calculator& theMainTimeCalculator,
                const NFmiIndexMask& theIndexMask,
                Calculator& theSpaceCalculator)
{
  theSpaceCalculator.reset();

  if (!integrate_time(theQI,
                      thePeriods,
                      theSubTimeCalculator,
                      theMainTimeCalculator,
                      theIndexMask,
                      [&](float theValue) { theSpaceCalculator(theValue); }))
    return kFloatMissing;

  return theSpaceCalculator();
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over time for each location in the mask
 *
 * Integrate over time with current parameter and level. The results
 * can be integrated over space with several different calculators
 * without reading the data again.
 *
 * If the period generator returns undivided periods, theMainTimeCalculator
 * is used alone.
 *
 * \param theQI The query info
 * \param thePeriods The subperiod generator
 * \param theSubTimeCalculator The modifier for accumulating the subperiod result
 * \param theMainTimeCalculator The modifier for accumulating the subperiod results
 * \param theIndexMask The mask containing the space indices
 * \param theResults The time integration result for each location in the mask
 * \return False if the integration is not possible
 */
// ----------------------------------------------------------------------

bool IntegrateTime(NFmiFastQueryInfo& theQI,
                   const WeatherPeriodGenerator& thePeriods,
                   Calculator& theSubTimeCalculator,
                   Calculator& theMainTimeCalculator,
                   const NFmiIndexMask& theIndexMask,
                   std::vector<float>& theResults)
{
  theResults.clear();
  theResults.reserve(theIndexMask.size());

  return integrate_time(theQI,
                        thePeriods,
                        theSubTimeCalculator,
                        theMainTimeCalculator,
                        theIndexMask,
                        [&](float theValue) { theResults.push_back(theValue); });
}

// ----------------------------------------------------------------------
/*!
 * \brief Integrate over precalculated values
 *
 * \param theValues The values, for example from IntegrateTime
 * \param theCalculator The modifier for accumulating the result
 * \return The accumulation result
 */
// ----------------------------------------------------------------------

float Integrate(const std::vector<float>& theValues, Calculator& theCalculator)
{
  theCalculator.reset();

  for (const float value : theValues)
    theCalculator(value);

  return theCalculator();
}

}  // namespace QueryDataIntegrator
}  // namespace TextGen

// ======================================================================
