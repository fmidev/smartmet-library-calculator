// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::GridForecaster
 */
// ======================================================================

#pragma once

#include "WeatherForecaster.h"

namespace TextGen
{
class Acceptor;
class AnalysisSources;
class WeatherArea;
class WeatherPeriodGenerator;
class WeatherResult;

class GridForecaster : public WeatherForecaster
{
 public:
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
                                const Acceptor& theTester = NullAcceptor()) const override;

};  // class GridForecaster

}  // namespace TextGen

// ======================================================================
