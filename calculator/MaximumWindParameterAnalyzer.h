// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaximumWindParameterAnalyzer
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

class MaximumWindParameterAnalyzer : public ParameterAnalyzer
{
 public:
  MaximumWindParameterAnalyzer(std::string theVariable, std::string theParameter);

  WeatherResult analyze(const AnalysisSources& theSources,
                        const WeatherDataType& theDataType,
                        const WeatherFunction& theAreaFunction,
                        const WeatherFunction& theTimeFunction,
                        const WeatherFunction& theSubTimeFunction,
                        const WeatherArea& theArea,
                        const WeatherPeriodGenerator& thePeriods,
                        const Acceptor& theAreaAcceptor,
                        const Acceptor& theTimeAcceptor,
                        const Acceptor& theTester = NullAcceptor()) const override;

 private:
  MaximumWindParameterAnalyzer() = delete;

  const std::string itsVariable;
  const std::string itsParameter;
};
}  // namespace TextGen

// ======================================================================
