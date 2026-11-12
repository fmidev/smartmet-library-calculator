// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::WindChillFunctionAnalyzer
 */
// ======================================================================

#pragma once

#include "FunctionAnalyzer.h"
#include "WeatherDataType.h"
#include "WeatherFunction.h"
#include <string>

namespace TextGen
{

class WindChillFunctionAnalyzer : public FunctionAnalyzer
{
 public:
  WindChillFunctionAnalyzer() = delete;
  ~WindChillFunctionAnalyzer() override = default;
  WindChillFunctionAnalyzer(const WeatherFunction& theAreaFunction,
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

};  // class WindChillFunctionAnalyzer

}  // namespace TextGen

// ======================================================================
