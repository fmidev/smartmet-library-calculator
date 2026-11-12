// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::GridForecaster
 */
// ======================================================================

#pragma once

#include "DefaultAcceptor.h"
#include "NullAcceptor.h"
#include "WeatherAnalyzer.h"
#include "WeatherForecaster.h"
#include "WeatherFunction.h"
#include "WeatherParameter.h"

namespace TextGen
{

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
