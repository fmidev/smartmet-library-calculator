// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::ModuloParameterAnalyzer
 */
// ======================================================================

#pragma once

#include "NullAcceptor.h"
#include "ParameterAnalyzer.h"
#include "WeatherDataType.h"
#include "WeatherFunction.h"
#include <string>

namespace TextGen
{

class ModuloParameterAnalyzer : public ParameterAnalyzer
{
 public:
  ModuloParameterAnalyzer() = delete;
  ModuloParameterAnalyzer(std::string theVariable, std::string theParameter, int theModulo);

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
  const std::string itsVariable;
  const std::string itsParameter;
  const int itsModulo;
};
}  // namespace TextGen

// ======================================================================
