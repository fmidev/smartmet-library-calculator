// ======================================================================
/*!
 * \brief A thread safe configuration object
 */
// ======================================================================

#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <map>
#include <stdexcept>
#include <string>

namespace Fmi
{
class Config
{
 public:
  Config();

  static bool isset(const std::string& theName);
  static void set(const std::string& theName, const std::string& theValue);
  static void set(const std::string& theSettingsString);
  static void clear();
  static void release();

  std::string requireString(const std::string& theName) const;
  std::string optionalString(const std::string& theName, const std::string& theDefault) const;
  bool requireBoolean(const std::string& theName) const;
  bool optionalBoolean(const std::string& theName, bool theDefault) const;
  int requireInteger(const std::string& theName) const;
  int requireInteger(const std::string& theName, int theLoLimit, int theHiLimit) const;
  int optionalInteger(const std::string& theName,
                      int theDefault,
                      int theLoLimit,
                      int theHiLimit) const;
  int optionalInteger(const std::string& theName, int theDefault) const;
  double requireDouble(const std::string& theName) const;
  double optionalDouble(const std::string& theName, double theDefault) const;

 private:
  //	std::map<std::string,std::string> itsSettings;	// the settings
  //	boost::mutex itsMutex;							// settings mutex

};  // class Config

}  // namespace Fmi
