// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::WeatherResult
 */
// ======================================================================

#pragma once

#include <iosfwd>

namespace TextGen
{
class WeatherResult
{
 public:
#ifdef NO_COMPILER_GENERATED
  ~WeatherResult();
  WeatherResult(const WeatherResult& theResult);
  WeatherResult& operator=(const WeatherResult& theResult);
#endif

  WeatherResult(float theValue, float theError);

  float value() const;
  float error() const;

 private:
  WeatherResult() = delete;
  float itsValue;
  float itsError;

};  // class WeatherResult

}  // namespace TextGen

// Free functions

bool operator==(const TextGen::WeatherResult& theLhs, const TextGen::WeatherResult& theRhs);

bool operator!=(const TextGen::WeatherResult& theLhs, const TextGen::WeatherResult& theRhs);

std::ostream& operator<<(std::ostream& theOutput, const TextGen::WeatherResult& theResult);

// ======================================================================
