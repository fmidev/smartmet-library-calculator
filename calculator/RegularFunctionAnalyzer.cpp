// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::RegularFunctionAnalyzer
 */
// ======================================================================
/*!
 * \class TextGen::RegularFunctionAnalyzer
 *
 * \brief Regular function analysis
 *
 */
// ======================================================================

#include "RegularFunctionAnalyzer.h"
#include "AnalysisSources.h"
#include "CalculatorFactory.h"
#include "MaskSource.h"
#include "QueryDataIntegrator.h"
#include "Settings.h"
#include "WeatherArea.h"
#include "WeatherPeriod.h"
#include "WeatherResult.h"
#include "WeatherSource.h"
#include <macgyver/Exception.h>
#include <macgyver/StringConversion.h>
#include <newbase/NFmiEnumConverter.h>
#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiQueryData.h>
#include <memory>
#include <sstream>
#include <string>

namespace
{
//! A static instance to avoid construction costs

NFmiEnumConverter converter;

}  // namespace

// ----------------------------------------------------------------------
/*!
 * \brief Return data type as string
 *
 * \param theDataType The data type
 * \return The string
 */
// ----------------------------------------------------------------------

const char* data_type_name(const TextGen::WeatherDataType& theDataType)
{
  switch (theDataType)
  {
    case TextGen::Forecast:
      return "forecast";
    case TextGen::Observation:
      return "observation";
    case TextGen::Climatology:
      return "climatology";
  }

  throw Fmi::Exception(BCP, "Unrecognized WeatherDataType");
}

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 *
 * \param theAreaFunction The area function
 * \param theTimeFunction The time function
 * \param theSubTimeFunction The time function for subperiods
 */
// ----------------------------------------------------------------------

RegularFunctionAnalyzer::RegularFunctionAnalyzer(const WeatherFunction& theAreaFunction,
                                                 const WeatherFunction& theTimeFunction,
                                                 const WeatherFunction& theSubTimeFunction)
    : itsAreaFunction(theAreaFunction),
      itsTimeFunction(theTimeFunction),
      itsSubTimeFunction(theSubTimeFunction),
      itIsModulo(false),
      itsModulo(-1)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the modulo of the parameter values
 *
 * Throws for 0 or negative modulo
 *
 * \param theModulo The modulo value
 */
// ----------------------------------------------------------------------

void RegularFunctionAnalyzer::modulo(int theModulo)
{
  if (theModulo <= 0)
    throw Fmi::Exception(BCP, "Trying to analyze data modulo " + Fmi::to_string(theModulo));
  itsModulo = theModulo;
  itIsModulo = true;
}

// ----------------------------------------------------------------------
/*!
 * \brief Analyze area and time functions
 *
 * Note that theTester argument is associated to both itsAreaCalculator
 * and itsTimeCalculator. Naturally the association is real only
 * for functions which require the tester. At the moment Percentage
 * is the only such function.
 *
 * It is assumed that the space and time functions are never both
 * Percentage, hence atmost one Acceptor is needed for Percentage
 * calculations.
 *
 * \param theSources Analysis sources
 * \param theDataType Analysis data type
 * \param theArea Analysis area
 * \param thePeriods Analysis periods
 * \param theAreaAcceptor The data acceptor in area integration
 * \param theTimeAcceptor The data acceptor in space integration
 * \param theTester The data tester for Percentage calculations
 * \param theDataName The name of the data file
 * \param theParameterName The name of the parameter
 * \return The analysis result
 */
// ----------------------------------------------------------------------

WeatherResult RegularFunctionAnalyzer::analyze(const AnalysisSources& theSources,
                                               const WeatherDataType& theDataType,
                                               const WeatherArea& theArea,
                                               const WeatherPeriodGenerator& thePeriods,
                                               const Acceptor& theAreaAcceptor,
                                               const Acceptor& theTimeAcceptor,
                                               const Acceptor& theTester,
                                               const std::string& theDataName,
                                               const std::string& theParameterName) const
{
  // Establish the data

  const std::string default_forecast = Settings::optional_string("textgen::default_forecast", "");
  const std::string datavar = theDataName + '_' + data_type_name(theDataType);
  const std::string dataname = Settings::optional_string(datavar, default_forecast);
  const std::string paramname = Settings::optional_string(theDataName, theParameterName);

  // Get the data into use

  std::shared_ptr<WeatherSource> wsource = theSources.getWeatherSource();
  std::shared_ptr<NFmiQueryData> qd = wsource->data(dataname);
  NFmiFastQueryInfo qi = NFmiFastQueryInfo(qd.get());

  // Try activating the parameter

  auto param = FmiParameterName(converter.ToEnum(paramname));
  if (param == kFmiBadParameter)
    throw Fmi::Exception(BCP, "Parameter " + paramname + " is not defined in newbase");

  if (paramname != "HourlyMaximumWindSpeed" && paramname != "WindChill")
  {
    if (!qi.Param(param))
      throw Fmi::Exception(BCP, paramname + " is not available in " + dataname);
  }

  // Handle points and areas separately

  std::shared_ptr<Calculator> spacemod, timemod, subtimemod;

  if (!itIsModulo)
  {
    timemod.reset(CalculatorFactory::create(itsTimeFunction, theTester));
    subtimemod.reset(CalculatorFactory::create(itsSubTimeFunction, theTester));
  }
  else
  {
    timemod.reset(CalculatorFactory::create(itsTimeFunction, theTester, itsModulo));
    subtimemod.reset(CalculatorFactory::create(itsSubTimeFunction, theTester, itsModulo));
  }
  timemod->acceptor(theTimeAcceptor);
  subtimemod->acceptor(theTimeAcceptor);

  if (!theArea.isPoint())
  {
    MaskSource::mask_type mask;

    switch (theArea.type())
    {
      case WeatherArea::Full:
        mask = theSources.getMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Land:
        mask = theSources.getLandMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Coast:
        mask = theSources.getCoastMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Inland:
        mask = theSources.getInlandMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Northern:
        mask = theSources.getNorthernMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Southern:
        mask = theSources.getSouthernMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Eastern:
        mask = theSources.getEasternMaskSource()->mask(theArea, dataname, *wsource);
        break;
      case WeatherArea::Western:
        mask = theSources.getWesternMaskSource()->mask(theArea, dataname, *wsource);
        break;
    }

    // Result

    if (!itIsModulo)
      spacemod.reset(CalculatorFactory::create(itsAreaFunction, theTester));
    else
      spacemod.reset(CalculatorFactory::create(itsAreaFunction, theTester, itsModulo));
    spacemod->acceptor(theAreaAcceptor);

    float result =
        QueryDataIntegrator::Integrate(qi, thePeriods, *subtimemod, *timemod, *mask, *spacemod);

    if (result == kFloatMissing)
      return WeatherResult(kFloatMissing, 0);

    if (itsAreaFunction != Mean)
      return WeatherResult(result, 0);

    // Calculate standard deviation for the mean

    if (!itIsModulo)
      spacemod.reset(CalculatorFactory::create(StandardDeviation, theTester));
    else
      spacemod.reset(CalculatorFactory::create(StandardDeviation, theTester, itsModulo));
    spacemod->acceptor(theAreaAcceptor);

    float error =
        QueryDataIntegrator::Integrate(qi, thePeriods, *subtimemod, *timemod, *mask, *spacemod);

    // This would happen if the area covers one point only
    if (error == kFloatMissing)
      return WeatherResult(result, 0);

    return {result, error};
  }

  if (!(qi.Location(theArea.point())))
  {
    std::ostringstream msg;
    msg << "Could not set desired coordinate (" << theArea.point().X() << ',' << theArea.point().Y()
        << ')';
    if (theArea.isNamed())
      msg << " named " << theArea.name();
    msg << " in " << dataname;
    throw Fmi::Exception(BCP, msg.str());
  }

  float result =
      QueryDataIntegrator::Integrate(qi, theArea.point(), thePeriods, *subtimemod, *timemod);

  return {result, 0};
}

}  // namespace TextGen

// ======================================================================
