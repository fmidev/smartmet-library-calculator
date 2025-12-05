// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::MaximumWindFunctionAnalyzer
 */
// ======================================================================

#pragma once

#include "FunctionAnalyzer.h"
#include "MaximumWindQueryInfo.h"
#include "WeatherFunction.h"

#include <string>

class NFmiDataModifier;

namespace TextGen
{
class AnalysisSources;
class Calculator;
class WeatherArea;
class WeatherLimits;
class WeatherPeriod;
class WeatherPeriodGenerator;
class WeatherResult;

class MaximumWindFunctionAnalyzer : public FunctionAnalyzer
{
 public:
  MaximumWindFunctionAnalyzer() = delete;
  ~MaximumWindFunctionAnalyzer() override = default;
  MaximumWindFunctionAnalyzer(const WeatherFunction& theAreaFunction,
                              const WeatherFunction& theTimeFunction,
                              const WeatherFunction& theSubTimeFunction);

  WeatherResult analyze(const AnalysisSources& theSources,
                        const WeatherDataType& theDataType,
                        const WeatherArea& theArea,
                        const WeatherPeriodGenerator& thePeriods,
                        const Acceptor& theAreaAcceptor,
                        const Acceptor& theTimeAcceptor,
                        const Acceptor& theTester,
                        const std::string& theDataName,
                        const std::string& theParameterName) const override;

  void modulo(int theModulo);

 private:
  const WeatherFunction itsAreaFunction;
  const WeatherFunction itsTimeFunction;
  const WeatherFunction itsSubTimeFunction;

  bool itIsModulo;
  int itsModulo;

};  // class MaximumWindFunctionAnalyzer

}  // namespace TextGen

// ======================================================================
