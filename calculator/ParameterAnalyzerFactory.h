// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::ParameterAnalyzerFactory
 */
// ======================================================================

#pragma once

#include "WeatherParameter.h"

namespace TextGen
{
class ParameterAnalyzer;

namespace ParameterAnalyzerFactory
{
ParameterAnalyzer* create(TextGen::WeatherParameter theParameter);

}  // namespace ParameterAnalyzerFactory
}  // namespace TextGen

// ======================================================================
