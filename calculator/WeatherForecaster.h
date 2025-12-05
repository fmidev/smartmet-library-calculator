// ======================================================================
/*!
 * \file
 * \brief Interface of abstract class TextGen::WeatherForecaster
 */
// ======================================================================

#pragma once

#include "WeatherAnalyzer.h"

namespace TextGen
{
class Acceptor;
class AnalysisSources;
class WeatherArea;
class WeatherPeriodGenerator;
class WeatherResult;

class WeatherForecaster : public WeatherAnalyzer
{
 public:
  ~WeatherForecaster() override;
  using WeatherAnalyzer::analyze;

  WeatherResult analyze(const AnalysisSources& theSources,
                        const WeatherParameter& theParameter,
                        const WeatherFunction& theAreaFunction,
                        const WeatherFunction& theTimeFunction,
                        const WeatherFunction& theSubTimeFunction,
                        const WeatherArea& theArea,
                        const WeatherPeriodGenerator& thePeriods,
                        const Acceptor& theAreaAcceptor = DefaultAcceptor(),
                        const Acceptor& theTimeAcceptor = DefaultAcceptor(),
                        const Acceptor& theTester = NullAcceptor()) const override = 0;

};  // class WeatherForecaster

}  // namespace TextGen

// ======================================================================
