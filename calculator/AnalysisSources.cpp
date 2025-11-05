// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::AnalysisSources
 */
// ======================================================================
/*!
 * \class TextGen::AnalysisSources
 *
 * \brief Contains weather analysis data sources and caches
 *
 */
// ======================================================================

#include "AnalysisSources.h"
#include "MaskSource.h"
#include "WeatherSource.h"
#include <memory>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Return the weather source
 *
 * \return The weather source
 */
// ----------------------------------------------------------------------

std::shared_ptr<WeatherSource> AnalysisSources::getWeatherSource() const
{
  return itsWeatherSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the plain mask source
 *
 * \return The mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getMaskSource() const
{
  return itsMaskSource;
}
// ----------------------------------------------------------------------
/*!
 * \brief Return the land mask source
 *
 * \return The land mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getLandMaskSource() const
{
  return itsLandMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the coast mask source
 *
 * \return The coast mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getCoastMaskSource() const
{
  return itsCoastMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the inland mask source
 *
 * \return The inland mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getInlandMaskSource() const
{
  return itsInlandMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the northern mask source
 *
 * \return The northern mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getNorthernMaskSource() const
{
  return itsNorthernMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the southern mask source
 *
 * \return The southern mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getSouthernMaskSource() const
{
  return itsSouthernMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the eastern mask source
 *
 * \return The eastern mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getEasternMaskSource() const
{
  return itsEasternMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the western mask source
 *
 * \return The western mask source
 */
// ----------------------------------------------------------------------

std::shared_ptr<MaskSource> AnalysisSources::getWesternMaskSource() const
{
  return itsWesternMaskSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the weather source
 *
 * \param theSource The weather source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setWeatherSource(const std::shared_ptr<WeatherSource>& theSource)
{
  itsWeatherSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the plain mask source
 *
 * \param theSource The mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the land mask source
 *
 * \param theSource The land mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setLandMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsLandMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the coast mask source
 *
 * \param theSource The coast mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setCoastMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsCoastMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the inland mask source
 *
 * \param theSource The inland mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setInlandMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsInlandMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the northern mask source
 *
 * \param theSource The northern mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setNorthernMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsNorthernMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the southern mask source
 *
 * \param theSource The southern mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setSouthernMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsSouthernMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the eastern mask source
 *
 * \param theSource The eastern mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setEasternMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsEasternMaskSource = theSource;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the western mask source
 *
 * \param theSource The western mask source
 */
// ----------------------------------------------------------------------

void AnalysisSources::setWesternMaskSource(const std::shared_ptr<MaskSource>& theSource)
{
  itsWesternMaskSource = theSource;
}

}  // namespace TextGen

// ======================================================================
