// ======================================================================
/*!
 * \file
 * \brief Implementation of namespace TextGen::CalculatorFactory
 */
// ======================================================================
/*!
 * \namespace TextGen::CalculatorFactory
 *
 * \brief Creating TextGen::Calculator objects
 *
 */
// ======================================================================

#include "CalculatorFactory.h"
#include "ChangeCalculator.h"
#include "CountCalculator.h"
#include "MaximumCalculator.h"
#include "MeanCalculator.h"
#include "MedianCalculator.h"
#include "MinimumCalculator.h"
#include "ModChangeCalculator.h"
#include "ModMeanCalculator.h"
#include "ModStandardDeviationCalculator.h"
#include "ModTrendCalculator.h"
#include "NullCalculator.h"
#include "PercentageCalculator.h"
#include "RangeAcceptor.h"
#include "StandardDeviationCalculator.h"
#include "SumCalculator.h"
#include <macgyver/Exception.h>
#include "TrendCalculator.h"
#include <boost/move/make_unique.hpp>
#include <macgyver/StringConversion.h>
#include <string>

namespace TextGen
{
namespace CalculatorFactory
{
// ----------------------------------------------------------------------
/*!
 * \brief Create an calculator suitable for the given WeatherFunction
 *
 * Throws if there is no suitable data modifier.
 *
 * \param theFunction The weather function
 * \return The data modifier
 */
// ----------------------------------------------------------------------

Calculator* create(WeatherFunction theFunction)
{
  switch (theFunction)
  {
    case Mean:
      return new MeanCalculator;
    case Maximum:
      return new MaximumCalculator;
    case Minimum:
      return new MinimumCalculator;
    case Median:
      return new MedianCalculator;
    case Sum:
      return new SumCalculator;
    case Percentage:
      return new PercentageCalculator;
    case Count:
      return new CountCalculator;
    case Trend:
      return new TrendCalculator;
    case Change:
      return new ChangeCalculator;
    case NullFunction:
      return new NullCalculator;
    case StandardDeviation:
      return new StandardDeviationCalculator;
  }

  throw Fmi::Exception(BCP, "CalculatorFactory failed to recognize the given function" +
                     Fmi::to_string(static_cast<int>(theFunction)));
}

// ----------------------------------------------------------------------
/*!
 * \brief Create a modular calculator suitable for the given WeatherFunction
 *
 * Throws if there is no suitable data modifier.
 *
 * \param theFunction The weather function
 * \param theModulo The modulo value
 * \return The data modifier
 */
// ----------------------------------------------------------------------

Calculator* create(WeatherFunction theFunction, int theModulo)
{
  switch (theFunction)
  {
    case Mean:
      return new ModMeanCalculator(theModulo);
    case StandardDeviation:
      return new ModStandardDeviationCalculator(theModulo);
    case Change:
      return new ModChangeCalculator(theModulo);
    case Trend:
      return new ModTrendCalculator(theModulo);

    case Percentage:
      return new PercentageCalculator;
    case Count:
      return new CountCalculator;
    case NullFunction:
      return new NullCalculator;

    case Median:
      throw Fmi::Exception(BCP, "CalculatorFactory cannot create modular Median analyzer");
    case Maximum:
      throw Fmi::Exception(BCP, "CalculatorFactory cannot create modular Maximum analyzer");
    case Minimum:
      throw Fmi::Exception(BCP, "CalculatorFactory cannot create modular Minimum analyzer");
    case Sum:
      throw Fmi::Exception(BCP, "CalculatorFactory cannot create modular Sum analyzer");
  }

  throw Fmi::Exception(BCP, "CalculatorFactory failed to recognize the given function" +
                     Fmi::to_string(static_cast<int>(theFunction)));
}

// ----------------------------------------------------------------------
/*!
 * \brief Create an calculator suitable for the given WeatherFunction
 *
 * Throws if there is no suitable data modifier.
 *
 * \param theFunction The weather function
 * \param theTester The tester for Percentage calculations
 * \return The data modifier
 */
// ----------------------------------------------------------------------

Calculator* create(WeatherFunction theFunction, const Acceptor& theTester)
{
  switch (theFunction)
  {
    case Mean:
    case Maximum:
    case Minimum:
    case Median:
    case StandardDeviation:
    case Sum:
    case Trend:
    case Change:
    case NullFunction:
      return create(theFunction);
    case Percentage:
    {
      auto tmp = std::make_unique<PercentageCalculator>();
      tmp->condition(theTester);
      return tmp.release();
    }
    case Count:
    {
      auto tmp = std::make_unique<CountCalculator>();
      tmp->condition(theTester);
      return tmp.release();
    }
  }

  throw Fmi::Exception(BCP, "CalculatorFactory failed to recognize the given function" +
                     Fmi::to_string(static_cast<int>(theFunction)));
}

// ----------------------------------------------------------------------
/*!
 * \brief Create a modular calculator suitable for the given WeatherFunction
 *
 * Throws if there is no suitable data modifier.
 *
 * \param theFunction The weather function
 * \param theTester The tester for Percentage calculations
 * \param theModulo The modulo value
 * \return The data modifier
 */
// ----------------------------------------------------------------------

Calculator* create(WeatherFunction theFunction, const Acceptor& theTester, int theModulo)
{
  switch (theFunction)
  {
    case Mean:
    case Maximum:
    case Minimum:
    case Median:
    case StandardDeviation:
    case Sum:
    case Trend:
    case Change:
    case NullFunction:
      return create(theFunction, theModulo);
    case Percentage:
    {
      auto tmp = std::make_unique<PercentageCalculator>();
      tmp->condition(theTester);
      return tmp.release();
    }
    case Count:
    {
      auto tmp = std::make_unique<CountCalculator>();
      tmp->condition(theTester);
      return tmp.release();
    }
  }

  throw Fmi::Exception(BCP, "CalculatorFactory failed to recognize the given function" +
                     Fmi::to_string(static_cast<int>(theFunction)));
}

}  // namespace CalculatorFactory
}  // namespace TextGen

// ======================================================================
