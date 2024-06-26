// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::ParameterAnalyzer
 */
// ======================================================================

#pragma once

#include "NullAcceptor.h"
#include "WeatherDataType.h"
#include "WeatherFunction.h"
#include "WeatherParameter.h"
#include <string>

namespace TextGen
{
class AnalysisSources;
class WeatherArea;
class WeatherPeriodGenerator;
class WeatherResult;

class ParameterAnalyzer
{
 public:
  virtual ~ParameterAnalyzer() = default;
  virtual WeatherResult analyze(const AnalysisSources& theSources,
                                const WeatherDataType& theDataType,
                                const WeatherFunction& theAreaFunction,
                                const WeatherFunction& theTimeFunction,
                                const WeatherFunction& theSubTimeFunction,
                                const WeatherArea& theArea,
                                const WeatherPeriodGenerator& thePeriods,
                                const Acceptor& theAreaAcceptor,
                                const Acceptor& theTimeAcceptor,
                                const Acceptor& theTester = NullAcceptor()) const = 0;

  static void getParameterStrings(const WeatherParameter& theParameter,
                                  std::string& theParameterName,
                                  std::string& theDataName);

  static const char* getDataTypeName(const TextGen::WeatherDataType& theDataType);

};  // class ParameterAnalyzer

}  // namespace TextGen

// ======================================================================
