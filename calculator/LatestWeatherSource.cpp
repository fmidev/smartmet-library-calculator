// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::LatestWeatherSource
 */
// ======================================================================
/*!
 * \class TextGen::LatestWeatherSource
 *
 * \brief Weather data source for the latest forecasts
 *
 * The LatestWeatherSource class manages shared instances of weather data.
 * The class makes sure each requested forecast is the latest possible.
 *
 */
// ======================================================================

#include "LatestWeatherSource.h"
#include "IdGenerator.h"
#include "Settings.h"
#include <macgyver/Exception.h>

#include <newbase/NFmiFileSystem.h>
#include <newbase/NFmiQueryData.h>

#include <cassert>
#include <map>

// ----------------------------------------------------------------------
/*!
 * \brief Cached query data container
 */
// ----------------------------------------------------------------------

struct WeatherDataStruct
{
  std::time_t itsModTime = 0;
  std::time_t itsLastCheckTime = 0;
  std::string itsFilename;
  TextGen::WeatherId itsId = 0;
  std::shared_ptr<NFmiQueryData> itsData;
};

namespace
{
// ----------------------------------------------------------------------
/*!
 * \brief Complete the query data name into filename
 *
 * A valid name is for example "/data/pal/querydata/pal/skandinavia/pinta/"
 *
 * \param theName The name
 * \return The filename
 */
// ----------------------------------------------------------------------

std::string complete_filename(const std::string& theName)
{
  if (theName.empty()) throw Fmi::Exception(BCP, "Trying to search unnamed querydata");

  const std::string varname = "textgen::" + theName;
  const std::string queryname = Settings::optional_string(varname, theName);

  if (NFmiFileSystem::FileExists(queryname)) return queryname;

  if (!NFmiFileSystem::DirectoryExists(queryname))
    throw Fmi::Exception(BCP, "No directory named '" + queryname +
                                "' containing querydata found");

  std::string newestfile = NFmiFileSystem::NewestFile(queryname);
  if (newestfile.empty())
    throw Fmi::Exception(BCP, "Directory '" + queryname + "' does not contain any querydata");

  std::string fullname = queryname;
  const char lastchar = fullname[fullname.size() - 1];
  if (lastchar != '/' && lastchar != '\\') fullname += '/';
  fullname += newestfile;

  return fullname;
}

}  // namespace

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Implementation hiding details for LatestWeatherSource
 */
// ----------------------------------------------------------------------

class LatestWeatherSource::Pimple
{
 public:
  using container_type = std::map<std::string, WeatherDataStruct>;
  container_type itsData;

};  // class LatestWeatherSource::Pimple

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 *
 * The constructor makes sure the internal shared data is initialized.
 */
// ----------------------------------------------------------------------

LatestWeatherSource::LatestWeatherSource() : itsPimple(new Pimple) {}
// ----------------------------------------------------------------------
/*!
 * \brief Get the desired data
 *
 * \param theName The name of the data
 * \return Shared pointer to the desired data
 */
// ----------------------------------------------------------------------

std::shared_ptr<NFmiQueryData> LatestWeatherSource::data(const std::string& theName) const
{
  // Age limit for checking for new query data is 1 minute
  const int agelimit = 1 * 60;

  // See if we have a cached result
  auto it = itsPimple->itsData.find(theName);

  if (it != itsPimple->itsData.end())
  {
    // If the cached data is new enough, return it

    if (time(nullptr) - it->second.itsLastCheckTime < agelimit) return it->second.itsData;
  }

  // Associated filename
  const std::string filename = complete_filename(theName);
  const std::time_t modtime = NFmiFileSystem::FileModificationTime(filename);

  // Update the time we checked the modification time

  if (it != itsPimple->itsData.end()) it->second.itsLastCheckTime = time(nullptr);

  // See if the cached data is outdated. It is outdated if the
  // directory contains a newer file, or if the file itself
  // has been modified. We also require that the new modification
  // time is atleast 30 seconds old to make sure the file has been
  // fully created.

  if (it != itsPimple->itsData.end() &&
      (it->second.itsFilename == filename || it->second.itsModTime >= modtime) &&
      (time(nullptr) - modtime > 30))
    return it->second.itsData;

  // Erase the aged data
  if (it != itsPimple->itsData.end()) itsPimple->itsData.erase(it);

  // Read the new data
  std::shared_ptr<NFmiQueryData> qdata(new NFmiQueryData(filename));

  WeatherDataStruct newdata;
  newdata.itsId = IdGenerator::generate();
  newdata.itsModTime = modtime;
  newdata.itsLastCheckTime = time(nullptr);
  newdata.itsFilename = filename;
  newdata.itsData = qdata;

  using value_type = Pimple::container_type::value_type;

  itsPimple->itsData.insert(value_type(theName, newdata));

  return qdata;
}

// ----------------------------------------------------------------------
/*!
 * \brief Get id of desired data
 *
 * \param theName The name of the data
 * \return The ID
 */
// ----------------------------------------------------------------------

WeatherId LatestWeatherSource::id(const std::string& theName) const
{
  // See if we have a stored result
  using const_iterator = Pimple::container_type::const_iterator;
  const_iterator it = itsPimple->itsData.find(theName);
  if (it == itsPimple->itsData.end())
    throw Fmi::Exception(BCP, "No data named " + theName + " stored in LatestWeatherSource");

  return it->second.itsId;
}

}  // namespace TextGen

// ======================================================================
