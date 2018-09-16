// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::WindChillParameterAnalyzer
 */
// ======================================================================

#pragma once

#include "ParameterAnalyzer.h"
#include <string>

namespace TextGen
{
class AnalyzerSources;
class WeatherArea;
class WeatherPeriodGenerator;
class WeatherResult;

class WindChillParameterAnalyzer : public ParameterAnalyzer
{
 public:
  WindChillParameterAnalyzer(std::string theVariable, std::string theParameter);

  virtual WeatherResult analyze(const AnalysisSources& theSources,
                                const WeatherDataType& theDataType,
                                const WeatherFunction& theAreaFunction,
                                const WeatherFunction& theTimeFunction,
                                const WeatherFunction& theSubTimeFunction,
                                const WeatherArea& theArea,
                                const WeatherPeriodGenerator& thePeriods,
                                const Acceptor& theAreaAcceptor,
                                const Acceptor& theTimeAcceptor,
                                const Acceptor& theTester = NullAcceptor()) const;

 private:
  WindChillParameterAnalyzer();

  const std::string itsVariable;
  const std::string itsParameter;
};
}  // namespace TextGen

// ======================================================================
