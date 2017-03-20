// ======================================================================
/*!
 * \file
 * \brief Definition of enumeration TextGen::WeatherDataType
 */
// ======================================================================

#pragma once

namespace TextGen
{
enum WeatherDataType
{
  Forecast,
  Observation,
  Climatology
};

}  // namespace TextGen

const char* data_type_name(const TextGen::WeatherDataType& theDataType);


// ======================================================================
