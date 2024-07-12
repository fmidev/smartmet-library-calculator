// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::AnalysisSources
 */
// ======================================================================

#pragma once

#include <memory>

namespace TextGen
{
class MaskSource;
class WeatherSource;

class AnalysisSources
{
 public:
  std::shared_ptr<WeatherSource> getWeatherSource() const;
  std::shared_ptr<MaskSource> getMaskSource() const;
  std::shared_ptr<MaskSource> getLandMaskSource() const;
  std::shared_ptr<MaskSource> getCoastMaskSource() const;
  std::shared_ptr<MaskSource> getInlandMaskSource() const;
  std::shared_ptr<MaskSource> getNorthernMaskSource() const;
  std::shared_ptr<MaskSource> getSouthernMaskSource() const;
  std::shared_ptr<MaskSource> getEasternMaskSource() const;
  std::shared_ptr<MaskSource> getWesternMaskSource() const;

  void setWeatherSource(const std::shared_ptr<WeatherSource>& theSource);
  void setMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setLandMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setCoastMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setInlandMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setNorthernMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setSouthernMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setEasternMaskSource(const std::shared_ptr<MaskSource>& theSource);
  void setWesternMaskSource(const std::shared_ptr<MaskSource>& theSource);

 private:
  std::shared_ptr<WeatherSource> itsWeatherSource;
  std::shared_ptr<MaskSource> itsMaskSource;
  std::shared_ptr<MaskSource> itsLandMaskSource;
  std::shared_ptr<MaskSource> itsCoastMaskSource;
  std::shared_ptr<MaskSource> itsInlandMaskSource;
  std::shared_ptr<MaskSource> itsNorthernMaskSource;
  std::shared_ptr<MaskSource> itsSouthernMaskSource;
  std::shared_ptr<MaskSource> itsEasternMaskSource;
  std::shared_ptr<MaskSource> itsWesternMaskSource;

};  // class AnalysisSources

}  // namespace TextGen

// ======================================================================
