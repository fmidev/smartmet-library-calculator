// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::UserWeatherSource
 */
// ======================================================================
/*!
 * \class TextGen::UserWeatherSource
 *
 * \brief Weather data source
 *
 * In this version of the WeatherSource interface the user
 * is expected to manually insert all name-data pairs into
 * the class. This facilitates for example regression testing
 * with specific data.
 *
 */
// ======================================================================

#include "UserWeatherSource.h"
#include "IdGenerator.h"
#include <macgyver/Exception.h>
#include <newbase/NFmiQueryData.h>
#include <cassert>
#include <map>

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Implementation hiding details for UserWeatherSource
 */
// ----------------------------------------------------------------------

class UserWeatherSource::Pimple
{
 public:
  using container_type = std::map<std::string, std::shared_ptr<NFmiQueryData> >;
  container_type itsData;

  using id_container_type = std::map<std::string, WeatherId>;
  id_container_type itsIdData;
};

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 *
 * The constructor makes sure the internal shared data is initialized.
 */
// ----------------------------------------------------------------------

UserWeatherSource::UserWeatherSource() : itsPimple(new Pimple) {}
// ----------------------------------------------------------------------
/*!
 * \brief Get the desired data
 *
 * \param theName The name of the data
 * \return Shared pointer to the desired data
 */
// ----------------------------------------------------------------------

std::shared_ptr<NFmiQueryData> UserWeatherSource::data(const std::string& theName) const
{
  // See if we have a stored result
  using const_iterator = Pimple::container_type::const_iterator;
  const_iterator it = itsPimple->itsData.find(theName);
  if (it == itsPimple->itsData.end())
    throw Fmi::Exception(BCP, "No data named " + theName + " stored in UserWeatherSource");

  return it->second;
}

// ----------------------------------------------------------------------
/*!
 * \brief Get id of desired data
 *
 * \param theName The name of the data
 * \return The ID
 */
// ----------------------------------------------------------------------

WeatherId UserWeatherSource::id(const std::string& theName) const
{
  // See if we have a stored result
  using const_iterator = Pimple::id_container_type::const_iterator;
  const_iterator it = itsPimple->itsIdData.find(theName);
  if (it == itsPimple->itsIdData.end())
    throw Fmi::Exception(BCP, "No data named " + theName + " stored in UserWeatherSource");

  return it->second;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add new named data
 *
 * \param theName The name for the data
 * \param theData The data itself
 */
// ----------------------------------------------------------------------

void UserWeatherSource::insert(const std::string& theName,
                               const std::shared_ptr<NFmiQueryData>& theData) const
{
  {
    using value_type = Pimple::container_type::value_type;
    itsPimple->itsData.insert(value_type(theName, theData));
  }

  {
    WeatherId newid = IdGenerator::generate();
    using value_type = Pimple::id_container_type::value_type;
    itsPimple->itsIdData.insert(value_type(theName, newid));
  }
}

}  // namespace TextGen

// ======================================================================
