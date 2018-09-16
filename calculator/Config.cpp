#include "Config.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>
#include <macgyver/StringConversion.h>
#include <functional>
#include <stdexcept>
#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

#include <boost/filesystem.hpp>

namespace Fmi
{
using SettingsData = std::map<std::string, std::string>;

static boost::thread_specific_ptr<SettingsData> tls;

void release_settings()
{
  if (tls.get() != nullptr) delete tls.release();  // NOLINT(cppcoreguidelines-owning-memory)
}

SettingsData& get_settings()
{
  if (tls.get() == nullptr) tls.reset(new SettingsData);  // NOLINT(cppcoreguidelines-owning-memory)

  return *tls;
}

bool Config::isset(const std::string& theName)
{
  const SettingsData& settings(get_settings());

  return (settings.find(theName) != settings.end());
}

void Config::set(const std::string& theName, const std::string& theValue)
{
  SettingsData& settings(get_settings());

  if (settings.find(theName) == settings.end())
    settings.insert(make_pair(theName, theValue));
  else
    settings[theName] = theValue;
}

// Assumes format: "key=value\nkey=value\n..."
void Config::set(const std::string& theSettingsString)
{
  using tokenizer = boost::tokenizer<boost::char_separator<char> >;
  boost::char_separator<char> sep("\n");
  tokenizer tokens(theSettingsString, sep);
  for (const std::string& t : tokens)
  {
    if (t.find('=') == std::string::npos) continue;

    boost::char_separator<char> sep2("=");
    tokenizer tokens2(t, sep2);
    tokenizer::iterator tok_iter = tokens2.begin();
    std::string key(*tok_iter);
    boost::trim(key);
    tok_iter++;
    std::string value(*tok_iter);
    boost::trim(value);
    Fmi::Config::set(key, value);
  }
}

void Config::clear()
{
  SettingsData& settings(get_settings());
  settings.clear();
}

void Config::release() { release_settings(); }
// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a string
 */
// ----------------------------------------------------------------------

std::string Config::requireString(const std::string& theName) const
{
  SettingsData& params(get_settings());

  if (params.find(theName) == params.end())
    throw std::runtime_error("The variable " + theName + " is required to have a value");

  return params[theName];
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a string
 */
// ----------------------------------------------------------------------

std::string Config::optionalString(const std::string& theName, const std::string& theDefault) const
{
  SettingsData& params(get_settings());

  if (params.find(theName) == params.end()) return theDefault;

  return params[theName];
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a boolean
 */
// ----------------------------------------------------------------------

bool Config::optionalBoolean(const std::string& theName, bool theDefault) const
{
  SettingsData& params(get_settings());

  if (params.find(theName) == params.end()) return theDefault;

  return requireBoolean(theName);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a boolean
 */
// ----------------------------------------------------------------------

bool Config::requireBoolean(const std::string& theName) const
{
  std::string value = boost::algorithm::to_lower_copy(requireString(theName));

  if (value == "1" || value == "true") return true;
  if (value == "0" || value == "false") return false;

  throw std::runtime_error("Variable '" + theName + "' value must be a boolean");
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a int
 */
// ----------------------------------------------------------------------

int Config::optionalInteger(const std::string& theName, int theDefault) const
{
  SettingsData& params(get_settings());

  if (params.find(theName) == params.end()) return theDefault;

  return requireInteger(theName);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a integer
 */
// ----------------------------------------------------------------------

int Config::requireInteger(const std::string& theName) const
{
  std::string value = requireString(theName);

  return std::stoi(value);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a integer
 */
// ----------------------------------------------------------------------

int Config::requireInteger(const std::string& theName, int theLoLimit, int theHiLimit) const
{
  int value = std::stoi(requireString(theName));

  if (value >= theLoLimit && value <= theHiLimit) return value;
  throw std::runtime_error("Variable '" + theName + "' value is out of range " +
                           Fmi::to_string(theLoLimit) + "..." + Fmi::to_string(theHiLimit));
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a integer
 */
// ----------------------------------------------------------------------

int Config::optionalInteger(const std::string& theName,
                            int theDefault,
                            int theLoLimit,
                            int theHiLimit) const
{
  int value = optionalInteger(theName, theDefault);

  if (value >= theLoLimit && value <= theHiLimit) return value;
  throw std::runtime_error("Variable '" + theName + "' value is out of range " +
                           Fmi::to_string(theLoLimit) + "..." + Fmi::to_string(theHiLimit));
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a double
 */
// ----------------------------------------------------------------------

double Config::optionalDouble(const std::string& theName, double theDefault) const
{
  SettingsData& params(get_settings());

  if (params.find(theName) == params.end()) return theDefault;

  return requireDouble(theName);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get setting value as a integer
 */
// ----------------------------------------------------------------------

double Config::requireDouble(const std::string& theName) const
{
  std::string value = requireString(theName);

  return std::stod(value);
}

}  // namespace Fmi
