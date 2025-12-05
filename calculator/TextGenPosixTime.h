#pragma once

#include <macgyver/DateTime.h>  //include all types plus i/o
#include <newbase/NFmiStaticTime.h>
#include <string>  // std::string

class TextGenPosixTime
{
 public:
  TextGenPosixTime() = default;
  TextGenPosixTime(const TextGenPosixTime& theTime) = default;

  TextGenPosixTime(time_t theTime);
  TextGenPosixTime(const Fmi::DateTime& theTime);
  TextGenPosixTime(const NFmiStaticTime& theTime);

  TextGenPosixTime(short year, short month, short day);
  TextGenPosixTime(short year, short month, short day, short hour, short minute = 0, short sec = 0);

  void ChangeBySeconds(long sec);
  void ChangeByMinutes(long min);
  void ChangeByHours(long hour);
  void ChangeByDays(long day);

  long DifferenceInMinutes(const TextGenPosixTime& anotherTime) const;
  long DifferenceInHours(const TextGenPosixTime& anotherTime) const;
  long DifferenceInDays(const TextGenPosixTime& anotherTime) const;

  bool IsEqual(const TextGenPosixTime& anotherTime) const;
  bool IsLessThan(const TextGenPosixTime& anotherTime) const;
  bool operator<(const TextGenPosixTime& anotherTime) const;
  bool operator>(const TextGenPosixTime& anotherTime) const;
  bool operator>=(const TextGenPosixTime& anotherTime) const;
  bool operator<=(const TextGenPosixTime& anotherTime) const;
  bool operator==(const TextGenPosixTime& anotherTime) const;
  bool operator!=(const TextGenPosixTime& anotherTime) const;

  short GetYear() const;
  short GetMonth() const;
  short GetDay() const;
  short GetHour() const;
  short GetMin() const;
  short GetSec() const;

  void SetDate(short year, short month, short day);
  void SetYear(short year);
  void SetMonth(short month);
  void SetDay(short day);
  void SetHour(short hour);
  void SetMin(short minute);
  void SetSec(short sec);

  std::string ToStr(unsigned long theTimeMask) const;
  std::string ToIsoExtendedStr() const;
  time_t EpochTime() const;
  short GetJulianDay() const;
  short GetWeekday() const;  // mon=1, tue=2,..., sat=6,  sun=7
  const Fmi::DateTime& PosixTime() { return itsPosixTime; }
  static TextGenPosixTime UtcTime(const TextGenPosixTime& localTime);
  static TextGenPosixTime LocalTime(const TextGenPosixTime& utcTime);
  // parameter isUtc tells whether theTime is in UTC or localtime:
  // it must be known when the theTime is in the proximity of daylight saving time change
  static short GetZoneDifferenceHour(const TextGenPosixTime& theTime, bool isUtc);

  static short DaysInYear(short aYear);
  static short DaysInMonth(short aMonth, short aYear);

  static void SetThreadTimeZone(const std::string& theTimeZoneId = "");
  static void ResetThreadTimeZone();

  inline const Fmi::DateTime& GetDateTime() const { return itsPosixTime; }

 private:
  Fmi::DateTime itsPosixTime{Fmi::SecondClock::local_time()};

};  // class TextGenPosixTime

std::ostream& operator<<(std::ostream& os, const TextGenPosixTime& tgTime);

bool operator<=(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime);
bool operator>=(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime);
bool operator==(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime);
bool operator<(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime);
bool operator>(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime);
