// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::ParameterAnalyzerFactory
 */
// ======================================================================

#pragma once

#include "ParameterAnalyzer.h"
#include "WeatherParameter.h"

namespace TextGen
{
namespace ParameterAnalyzerFactory
{
ParameterAnalyzer* create(TextGen::WeatherParameter theParameter);

}  // namespace ParameterAnalyzerFactory
}  // namespace TextGen

// ======================================================================
