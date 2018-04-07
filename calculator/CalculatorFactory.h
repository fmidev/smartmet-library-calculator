// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::CalculatorFactory
 */
// ======================================================================

#pragma once

#include "WeatherFunction.h"

#include "Calculator.h"

namespace TextGen
{
class Acceptor;

namespace CalculatorFactory
{
Calculator* create(WeatherFunction theFunction);

Calculator* create(WeatherFunction theFunction, int theModulo);

Calculator* create(WeatherFunction theFunction, const Acceptor& theTester);

Calculator* create(WeatherFunction theFunction, const Acceptor& theTester, int theModulo);

}  // namespace CalculatorFactory
}  // namespace TextGen

// ======================================================================
