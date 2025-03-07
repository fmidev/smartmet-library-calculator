// ======================================================================
/*!
 * \file
 * \brief Implementation of namespace TextGen::WeatherResultTools
 */
// ======================================================================
/*!
 * \namespace TextGen::WeatherResultTools
 *
 * \brief Utility functions operating on WeatherResult objects
 */
// ======================================================================

#include "WeatherResultTools.h"
#include "MathTools.h"
#include "Settings.h"
#include <macgyver/Exception.h>

#include <newbase/NFmiGlobals.h>
#include <cmath>
#include <cstdlib>
#include <utility>

namespace TextGen
{
namespace WeatherResultTools
{
// ----------------------------------------------------------------------
/*!
 * \brief Return the result with smaller magnitude
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \return The smaller result
 */
// ----------------------------------------------------------------------

WeatherResult min(const WeatherResult& theResult1, const WeatherResult& theResult2)
{
  WeatherResult result(std::min(theResult1.value(), theResult2.value()),
                       std::max(theResult1.error(), theResult2.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the result with greater magnitude
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \return The greater result
 */
// ----------------------------------------------------------------------

WeatherResult max(const WeatherResult& theResult1, const WeatherResult& theResult2)
{
  WeatherResult result(std::max(theResult1.value(), theResult2.value()),
                       std::max(theResult1.error(), theResult2.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the mean result
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \return The mean result
 */
// ----------------------------------------------------------------------

WeatherResult mean(const WeatherResult& theResult1, const WeatherResult& theResult2)
{
  WeatherResult result(MathTools::mean(theResult1.value(), theResult2.value()),
                       std::max(theResult1.error(), theResult2.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the smallest result
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \param theResult3 The third result result
 * \return The smallest result
 */
// ----------------------------------------------------------------------

WeatherResult min(const WeatherResult& theResult1,
                  const WeatherResult& theResult2,
                  const WeatherResult& theResult3)
{
  WeatherResult result(MathTools::min(theResult1.value(), theResult2.value(), theResult3.value()),
                       MathTools::max(theResult1.error(), theResult2.error(), theResult3.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the largest result
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \param theResult3 The third result result
 * \return The largest result
 */
// ----------------------------------------------------------------------

WeatherResult max(const WeatherResult& theResult1,
                  const WeatherResult& theResult2,
                  const WeatherResult& theResult3)
{
  WeatherResult result(MathTools::max(theResult1.value(), theResult2.value(), theResult3.value()),
                       MathTools::max(theResult1.error(), theResult2.error(), theResult3.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the mean result
 *
 * \param theResult1 The first result
 * \param theResult2 The second result
 * \param theResult3 The third result result
 * \return The mean result
 */
// ----------------------------------------------------------------------

WeatherResult mean(const WeatherResult& theResult1,
                   const WeatherResult& theResult2,
                   const WeatherResult& theResult3)
{
  WeatherResult result(MathTools::mean(theResult1.value(), theResult2.value(), theResult3.value()),
                       MathTools::max(theResult1.error(), theResult2.error(), theResult3.error()));
  return result;
}

// ----------------------------------------------------------------------
/*!
 * \brief Test if two ranges are similar
 *
 * The control variables are
 * \code
 * ::same::minimum = [0-X] (=0)
 * ::same::maximum = [0-X] (=0)
 * \endcode
 *
 * \param theMinimum1 The first range minimum
 * \param theMaximum1 The first range maximum
 * \param theMinimum2 The second range minimum
 * \param theMaximum2 The second range maximum
 * \param theVar The variable containing similarity limits
 * \return True if the intervals are close enough
 */
// ----------------------------------------------------------------------

bool isSimilarRange(const WeatherResult& theMinimum1,
                    const WeatherResult& theMaximum1,
                    const WeatherResult& theMinimum2,
                    const WeatherResult& theMaximum2,
                    const std::string& theVar)
{
  using Settings::optional_int;

  const int same_minimum = optional_int(theVar + "::same::minimum", 0);
  const int same_maximum = optional_int(theVar + "::same::maximum", 0);

  const int minvalue1 = lroundf(theMinimum1.value());
  const int maxvalue1 = lroundf(theMaximum1.value());
  const int minvalue2 = lroundf(theMinimum2.value());
  const int maxvalue2 = lroundf(theMaximum2.value());

  return (abs(minvalue1 - minvalue2) <= same_minimum && abs(maxvalue1 - maxvalue2) <= same_maximum);
}

// ----------------------------------------------------------------------
/*!
 * \brief If value of theWeatherResult is kFloatMissing, throws an exception
 *
 * \param theStoryName The name of the story
 * \param theParameter The parameter
 * \param theWeatherResult The WeatherResult to be checked
 */
// ----------------------------------------------------------------------

void checkMissingValue(const std::string& theStoryName,
                       WeatherParameter theParameter,
                       const WeatherResult& theWeatherResult)
{
  if (theWeatherResult.value() != kFloatMissing) return;

  std::string parameter;
  switch (theParameter)
  {
    case Temperature:
    {
      parameter = "Temperature";
    }
    break;
    case Precipitation:
    {
      parameter = "Precipitation";
    }
    break;
    case PrecipitationType:
    {
      parameter = "PrecipitationType";
    }
    break;
    case PrecipitationForm:
    {
      parameter = "PrecipitationForm";
    }
    break;
    case PrecipitationProbability:
    {
      parameter = "PrecipitationProbability";
    }
    break;
    case Cloudiness:
    {
      parameter = "Cloudiness";
    }
    break;
    case Frost:
    {
      parameter = "Frost";
    }
    break;
    case SevereFrost:
    {
      parameter = "SevereFrost";
    }
    break;
    case RelativeHumidity:
    {
      parameter = "RelativeHumidity";
    }
    break;
    case WindSpeed:
    {
      parameter = "WindSpeed";
    }
    break;
    case WindDirection:
    {
      parameter = "WindDirection";
    }
    break;
    case Thunder:
    {
      parameter = "Thunder";
    }
    break;
    case RoadTemperature:
    {
      parameter = "RoadTemperature";
    }
    break;
    case RoadCondition:
    {
      parameter = "RoadCondition";
    }
    break;
    case WaveHeight:
    {
      parameter = "WaveHeight";
    }
    break;
    case WaveDirection:
    {
      parameter = "WaveDirection";
    }
    break;
    case RoadWarning:
    {
      parameter = "RoadWarning";
    }
    break;
    case ForestFireIndex:
    {
      parameter = "ForestFireIndex";
    }
    break;
    case Evaporation:
    {
      parameter = "Evaporation";
    }
    break;
    case DewPoint:
    {
      parameter = "DewPoint";
    }
    break;
    case GustSpeed:
    {
      parameter = "GustSpeed";
    }
    break;
    case Pressure:
    {
      parameter = "Pressure";
    }
    break;
    case Fog:
    {
      parameter = "Fog";
    }
    break;
    case MaximumWind:
    {
      parameter = "MaximumWind";
    }
    break;
    case EffectiveTemperatureSum:
    {
      parameter = "EffectiveTemperatureSum";
    }
    break;
    case PrecipitationRate:
    {
      parameter = "PrecipitationRate";
    }
    break;
    case WaterEquivalentOfSnow:
    {
      parameter = "WaterEquivalentOfSnow";
    }
    break;
    case NormalMaxTemperatureF02:
    {
      parameter = "NormalMaxTemperatureF02";
    }
    break;
    case NormalMaxTemperatureF12:
    {
      parameter = "NormalMaxTemperatureF12";
    }
    break;
    case NormalMaxTemperatureF37:
    {
      parameter = "NormalMaxTemperatureF37";
    }
    break;
    case NormalMaxTemperatureF50:
    {
      parameter = "NormalMaxTemperatureF50";
    }
    break;
    case NormalMaxTemperatureF63:
    {
      parameter = "NormalMaxTemperatureF63";
    }
    break;
    case NormalMaxTemperatureF88:
    {
      parameter = "NormalMaxTemperatureF88";
    }
    break;
    case NormalMaxTemperatureF98:
    {
      parameter = "NormalMaxTemperatureF98";
    }
    break;
    case NormalMeanTemperatureF02:
    {
      parameter = "NormalMeanTemperatureF02";
    }
    break;
    case NormalMeanTemperatureF12:
    {
      parameter = "NormalMeanTemperatureF12";
    }
    break;
    case NormalMeanTemperatureF37:
    {
      parameter = "NormalMeanTemperatureF37";
    }
    break;
    case NormalMeanTemperatureF50:
    {
      parameter = "NormalMeanTemperatureF50";
    }
    break;
    case NormalMeanTemperatureF63:
    {
      parameter = "NormalMeanTemperatureF63";
    }
    break;
    case NormalMeanTemperatureF88:
    {
      parameter = "NormalMeanTemperatureF88";
    }
    break;
    case NormalMeanTemperatureF98:
    {
      parameter = "NormalMeanTemperatureF98";
    }
    break;
    case NormalMinTemperatureF02:
    {
      parameter = "NormalMinTemperatureF02";
    }
    break;
    case NormalMinTemperatureF12:
    {
      parameter = "NormalMinTemperatureF12";
    }
    break;
    case NormalMinTemperatureF37:
    {
      parameter = "NormalMinTemperatureF37";
    }
    break;
    case NormalMinTemperatureF50:
    {
      parameter = "NormalMinTemperatureF50";
    }
    break;
    case NormalMinTemperatureF63:
    {
      parameter = "NormalMinTemperatureF63";
    }
    break;
    case NormalMinTemperatureF88:
    {
      parameter = "NormalMinTemperatureF88";
    }
    break;
    case NormalMinTemperatureF98:
    {
      parameter = "NormalMinTemperatureF98";
    }
    break;
    case WindChill:
    {
      parameter = "WindChill";
    }
    break;
    case GrowthPeriodOnOff:
    {
      parameter = "GrowthPeriodOnOff";
    }
    break;
    default:
      parameter = "UnknownParameter";
      break;
  }

  throw Fmi::Exception(BCP, "Error in '" + theStoryName + "' story: " + parameter +
                     " value missing, cannot continue!");
}

void checkMissingValue(const std::string& theStoryName,
                       WeatherParameter theParameter,
                       const std::vector<WeatherResult>& theWeatherResultVector)
{
  for (const WeatherResult& wr : theWeatherResultVector)
    checkMissingValue(theStoryName, theParameter, wr);
}

}  // namespace WeatherResultTools
}  // namespace TextGen

// ======================================================================
