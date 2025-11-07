#include "TextGenPosixTime.h"
#include <macgyver/TimeZoneFactory.h>
#include <newbase/NFmiStaticTime.h>
#include <ctime>
#include <iostream>  // std::cout
#include <sstream>   // std::stringstream

// Used to be Europe/Helsinki, this is a more portable default
#define DEFAULT_TZ_ID "UTC"

static thread_local std::string tls;

void release_timezone_id()
{
  tls.clear();
}

std::string& get_timezone_id()
{
  return tls;
}

TextGenPosixTime::TextGenPosixTime() : itsPosixTime(Fmi::SecondClock::local_time()) {}
TextGenPosixTime::TextGenPosixTime(const Fmi::DateTime& theTime) : itsPosixTime(theTime) {}

TextGenPosixTime::TextGenPosixTime(std::time_t theTime)
    : itsPosixTime(Fmi::date_time::from_time_t(theTime))
{
}

TextGenPosixTime::TextGenPosixTime(const NFmiStaticTime& theTime)
    : itsPosixTime(Fmi::Date(theTime.GetYear(), theTime.GetMonth(), theTime.GetDay()),
                   Fmi::TimeDuration(theTime.GetHour(), theTime.GetMin(), theTime.GetSec()))
{
}

TextGenPosixTime::TextGenPosixTime(short year, short month, short day)
    : itsPosixTime(Fmi::Date(year, month, day), Fmi::TimeDuration(0, 0, 0))
{
}

TextGenPosixTime::TextGenPosixTime(
    short year, short month, short day, short hour, short minute /*=0*/, short sec /*=0*/)
{
  Fmi::TimeDuration td(hour, minute, sec, 0);
  Fmi::Date d(year, month, day);
  itsPosixTime = Fmi::DateTime(d, td);
}

void TextGenPosixTime::ChangeBySeconds(long sec)
{
  itsPosixTime += Fmi::Seconds(sec);
}
void TextGenPosixTime::ChangeByMinutes(long min)
{
  itsPosixTime += Fmi::Minutes(min);
}
void TextGenPosixTime::ChangeByHours(long hour)
{
  itsPosixTime += Fmi::Hours(hour);
}
void TextGenPosixTime::ChangeByDays(long day)
{
  itsPosixTime += Fmi::date_time::Days(day);
}
long TextGenPosixTime::DifferenceInMinutes(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(itsPosixTime - anotherTime.itsPosixTime);

  return td.total_seconds() / 60;
}

long TextGenPosixTime::DifferenceInHours(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(itsPosixTime - anotherTime.itsPosixTime);

  return td.total_seconds() / 3600;
}

long TextGenPosixTime::DifferenceInDays(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(itsPosixTime - anotherTime.itsPosixTime);

  return td.total_seconds() / 86400;
}

bool TextGenPosixTime::IsEqual(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime == anotherTime.itsPosixTime);
}

bool TextGenPosixTime::IsLessThan(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime < anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator<(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime < anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator>(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime > anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator>=(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime >= anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator<=(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime <= anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator==(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime == anotherTime.itsPosixTime);
}

bool TextGenPosixTime::operator!=(const TextGenPosixTime& anotherTime) const
{
  return (itsPosixTime != anotherTime.itsPosixTime);
}

void TextGenPosixTime::SetDate(const short year, const short month, const short day)
{
  Fmi::Date d(year, month, day);
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(d, td);
}

void TextGenPosixTime::SetYear(short year)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(Fmi::Date(year, d.month(), d.day()), td);
}

void TextGenPosixTime::SetMonth(short month)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(Fmi::Date(d.year(), month, d.day()), td);
}

void TextGenPosixTime::SetDay(short day)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(Fmi::Date(d.year(), d.month(), day), td);
}

void TextGenPosixTime::SetHour(short hour)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(hour, td.minutes(), td.seconds()));
}

void TextGenPosixTime::SetMin(short minute)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(td.hours(), minute, td.seconds()));
}

void TextGenPosixTime::SetSec(short sec)
{
  Fmi::Date d(itsPosixTime.date());
  Fmi::TimeDuration td(itsPosixTime.time_of_day());

  itsPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(td.hours(), td.minutes(), sec));
}

short TextGenPosixTime::GetYear() const
{
  return itsPosixTime.date().year();
}
short TextGenPosixTime::GetMonth() const
{
  return itsPosixTime.date().month();
}
short TextGenPosixTime::GetDay() const
{
  return itsPosixTime.date().day();
}
short TextGenPosixTime::GetHour() const
{
  return itsPosixTime.time_of_day().hours();
}
short TextGenPosixTime::GetMin() const
{
  return itsPosixTime.time_of_day().minutes();
}
short TextGenPosixTime::GetSec() const
{
  return itsPosixTime.time_of_day().seconds();
}

std::string TextGenPosixTime::ToIsoExtendedStr() const
{
  return itsPosixTime.to_iso_extended_string();
}

std::string TextGenPosixTime::ToStr(const unsigned long theTimeMask) const
{
  std::stringstream ss;
  if ((kShortYear & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%y", itsPosixTime);
  else if ((kLongYear & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%Y", itsPosixTime);

  if ((kMonth & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%m", itsPosixTime);

  if ((kDay & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%d", itsPosixTime);

  if ((kHour & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%H", itsPosixTime);

  if ((kMinute & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%M", itsPosixTime);

  if ((kSecond & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%S", itsPosixTime);

  return ss.str();
}

short TextGenPosixTime::GetZoneDifferenceHour(const TextGenPosixTime& theTime, bool isUtc)
{
  std::string timeZoneId(get_timezone_id().empty() ? DEFAULT_TZ_ID : get_timezone_id());
  const Fmi::TimeZonePtr timeZone =
      Fmi::TimeZoneFactory::instance().time_zone_from_string(timeZoneId);
  Fmi::LocalDateTime ldt(theTime.itsPosixTime.date(), theTime.itsPosixTime.time_of_day(), timeZone);
  return ldt.offset().total_seconds() / 3600;
}

std::time_t TextGenPosixTime::EpochTime() const
{
  Fmi::DateTime time_t_epoch(Fmi::Date(1970, 1, 1));

  return (itsPosixTime - time_t_epoch).total_seconds();
}

short TextGenPosixTime::GetWeekday() const  // mon=1, tue=2,..., sat=6,  sun=7
{
  short retval = itsPosixTime.date().day_of_week().iso_encoding();

  if (retval == 0)
    retval = 7;

  return retval;
}

short TextGenPosixTime::GetJulianDay() const
{
  return itsPosixTime.date().julian_day();
}
short TextGenPosixTime::DaysInYear(const short aYear)
{
  Fmi::Date d(aYear, 12, 1);

  return d.end_of_month().day_of_year();
}

short TextGenPosixTime::DaysInMonth(const short aMonth, const short aYear)
{
  Fmi::Date d(aYear, aMonth, 1);

  return d.end_of_month().day();
}

TextGenPosixTime TextGenPosixTime::UtcTime(const TextGenPosixTime& localTime)
{
  short zdh = TextGenPosixTime::GetZoneDifferenceHour(localTime, false);

  Fmi::DateTime utcptime = localTime.itsPosixTime - Fmi::Hours(zdh);

  return TextGenPosixTime(utcptime);
}

//
TextGenPosixTime TextGenPosixTime::LocalTime(const TextGenPosixTime& utcTime)
{
  short zdh = TextGenPosixTime::GetZoneDifferenceHour(utcTime, true);

  Fmi::DateTime localptime = utcTime.itsPosixTime + Fmi::Hours(zdh);

  return TextGenPosixTime(localptime);
}

// https://stackoverflow.com/questions/3118582/how-do-i-find-the-current-system-timezone
std::string get_current_timezone()
{
  ::time_t ts = 0;
  struct tm t;
  char buf[16];
  ::localtime_r(&ts, &t);
  ::strftime(buf, sizeof(buf), "%Z", &t);
  return buf;
}

void TextGenPosixTime::SetThreadTimeZone(const std::string& theTimeZoneId /*= ""*/)
{
  if (theTimeZoneId.empty())
    release_timezone_id();
  else
  {
    if (theTimeZoneId != "local" && theTimeZoneId != "localtime")
      get_timezone_id() = theTimeZoneId;
    else
      get_timezone_id() = get_current_timezone();
  }
}

void TextGenPosixTime::ResetThreadTimeZone()
{
  release_timezone_id();
}
std::ostream& operator<<(std::ostream& os, const TextGenPosixTime& tgTime)
{
  os << tgTime.ToIsoExtendedStr();
  return os;
}

bool operator<=(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime)
{
  return TextGenPosixTime(nfmiStaticTime) <= tgTime;
}

bool operator>=(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime)
{
  return TextGenPosixTime(nfmiStaticTime) >= tgTime;
}

bool operator==(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime)
{
  return TextGenPosixTime(nfmiStaticTime) == tgTime;
}

bool operator<(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime)
{
  return TextGenPosixTime(nfmiStaticTime) < tgTime;
}

bool operator>(const NFmiStaticTime& nfmiStaticTime, const TextGenPosixTime& tgTime)
{
  return TextGenPosixTime(nfmiStaticTime) > tgTime;
}
