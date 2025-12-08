// ======================================================================
/*!
 * \file
 * \brief Interface of singleton LocationSource
 */
// ======================================================================

#pragma once

#include <memory>
#include <string>

class NFmiPoint;

namespace TextGen
{
class LocationSource
{
 public:
  LocationSource(const LocationSource& theSrc) = delete;
  LocationSource& operator=(const LocationSource& theSrc) = delete;

  static LocationSource& instance();

  bool hasCoordinates(const std::string& theLocation) const;
  NFmiPoint coordinates(const std::string& theLocation) const;

 private:
  class Pimple;
  std::shared_ptr<Pimple> itsPimple;

  // Singleton protection
  LocationSource();
  ~LocationSource() = default;

};  // class LocationSource

}  // namespace TextGen

// ======================================================================
