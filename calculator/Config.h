// ======================================================================
/*!
 * \brief A thread safe configuration object
 */
// ======================================================================

#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace Fmi
{
class Config
{
 public:
  static bool isset(const std::string& theName);
  static void set(const std::string& theName, const std::string& theValue);
  static void set(const std::string& theSettingsString);
  static void clear();
  static void release();

  static std::string requireString(const std::string& theName);
  static std::string optionalString(const std::string& theName, const std::string& theDefault);

  static bool requireBoolean(const std::string& theName);
  static bool optionalBoolean(const std::string& theName, bool theDefault);
  static int requireInteger(const std::string& theName);
  static int requireInteger(const std::string& theName, int theLoLimit, int theHiLimit);
  static int optionalInteger(const std::string& theName,
                             int theDefault,
                             int theLoLimit,
                             int theHiLimit);
  static int optionalInteger(const std::string& theName, int theDefault);
  static double requireDouble(const std::string& theName);
  static double optionalDouble(const std::string& theName, double theDefault);

};  // class Config

}  // namespace Fmi
