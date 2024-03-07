#include "TextGenPosixTime.h"
#include <macgyver/TimeZoneFactory.h>
#include <newbase/NFmiStaticTime.h>
#include <ctime>
#include <iostream>  // std::cout
#include <sstream>   // std::stringstream

// Used to be Europe/Helsinki, this is a more portable default
#define DEFAULT_TZ_ID "UTC"

static thread_local std::string tls;

void release_timezone_id() { tls.clear(); }

std::string& get_timezone_id() { return tls; }

TextGenPosixTime::TextGenPosixTime() : istPosixTime(Fmi::SecondClock::local_time()) {}
TextGenPosixTime::TextGenPosixTime(const Fmi::DateTime& theTime) : istPosixTime(theTime) {}

TextGenPosixTime::TextGenPosixTime(std::time_t theTime) : istPosixTime(Fmi::date_time::from_time_t(theTime)) {}

TextGenPosixTime::TextGenPosixTime(const NFmiStaticTime& theTime)
    : istPosixTime(Fmi::Date(theTime.GetYear(), theTime.GetMonth(), theTime.GetDay()),
                   Fmi::TimeDuration(theTime.GetHour(), theTime.GetMin(), theTime.GetSec()))
{
}

TextGenPosixTime::TextGenPosixTime(short year, short month, short day)
    : istPosixTime(Fmi::Date(year, month, day), Fmi::TimeDuration(0, 0, 0))
{
}

TextGenPosixTime::TextGenPosixTime(
    short year, short month, short day, short hour, short minute /*=0*/, short sec /*=0*/)
{
  Fmi::TimeDuration td(hour, minute, sec, 0);
  Fmi::Date d(year, month, day);
  istPosixTime = Fmi::DateTime(d, td);
}

void TextGenPosixTime::ChangeBySeconds(long sec) { istPosixTime += Fmi::Seconds(sec); }
void TextGenPosixTime::ChangeByMinutes(long min) { istPosixTime += Fmi::Minutes(min); }
void TextGenPosixTime::ChangeByHours(long hour) { istPosixTime += Fmi::Hours(hour); }
void TextGenPosixTime::ChangeByDays(long day) { istPosixTime += Fmi::date_time::Days(day); }
long TextGenPosixTime::DifferenceInMinutes(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(istPosixTime - anotherTime.istPosixTime);

  return td.total_seconds() / 60;
}

long TextGenPosixTime::DifferenceInHours(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(istPosixTime - anotherTime.istPosixTime);

  return td.total_seconds() / 3600;
}

long TextGenPosixTime::DifferenceInDays(const TextGenPosixTime& anotherTime) const
{
  Fmi::TimeDuration td(istPosixTime - anotherTime.istPosixTime);

  return td.total_seconds() / 86400;
}

bool TextGenPosixTime::IsEqual(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime == anotherTime.istPosixTime);
}

bool TextGenPosixTime::IsLessThan(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime < anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator<(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime < anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator>(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime > anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator>=(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime >= anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator<=(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime <= anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator==(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime == anotherTime.istPosixTime);
}

bool TextGenPosixTime::operator!=(const TextGenPosixTime& anotherTime) const
{
  return (istPosixTime != anotherTime.istPosixTime);
}

void TextGenPosixTime::SetDate(const short year, const short month, const short day)
{
  Fmi::Date d(year, month, day);
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(d, td);
}

void TextGenPosixTime::SetYear(short year)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(Fmi::Date(year, d.month(), d.day()), td);
}

void TextGenPosixTime::SetMonth(short month)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(Fmi::Date(d.year(), month, d.day()), td);
}

void TextGenPosixTime::SetDay(short day)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(Fmi::Date(d.year(), d.month(), day), td);
}

void TextGenPosixTime::SetHour(short hour)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(hour, td.minutes(), td.seconds()));
}

void TextGenPosixTime::SetMin(short minute)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(td.hours(), minute, td.seconds()));
}

void TextGenPosixTime::SetSec(short sec)
{
  Fmi::Date d(istPosixTime.date());
  Fmi::TimeDuration td(istPosixTime.time_of_day());

  istPosixTime = Fmi::DateTime(d, Fmi::TimeDuration(td.hours(), td.minutes(), sec));
}

short TextGenPosixTime::GetYear() const { return istPosixTime.date().year(); }
short TextGenPosixTime::GetMonth() const { return istPosixTime.date().month(); }
short TextGenPosixTime::GetDay() const { return istPosixTime.date().day(); }
short TextGenPosixTime::GetHour() const { return istPosixTime.time_of_day().hours(); }
short TextGenPosixTime::GetMin() const { return istPosixTime.time_of_day().minutes(); }
short TextGenPosixTime::GetSec() const { return istPosixTime.time_of_day().seconds(); }

std::string TextGenPosixTime::ToStr(const unsigned long theTimeMask) const
{
  std::stringstream ss;
  if ((kShortYear & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%y", istPosixTime);
  else if ((kLongYear & theTimeMask) != 0)
    ss << Fmi::date_time::format_time("%Y", istPosixTime);

  if ((kMonth & theTimeMask) != 0) ss << Fmi::date_time::format_time("%m", istPosixTime);

  if ((kDay & theTimeMask) != 0) ss << Fmi::date_time::format_time("%d", istPosixTime);

  if ((kHour & theTimeMask) != 0) ss << Fmi::date_time::format_time("%H", istPosixTime);

  if ((kMinute & theTimeMask) != 0) ss << Fmi::date_time::format_time("%M", istPosixTime);

  if ((kSecond & theTimeMask) != 0) ss << Fmi::date_time::format_time("%S", istPosixTime);

  return ss.str();
}

short TextGenPosixTime::GetZoneDifferenceHour(const TextGenPosixTime& theTime, bool isUtc)
{
  std::string timeZoneId(get_timezone_id().empty() ? DEFAULT_TZ_ID : get_timezone_id());
  const Fmi::TimeZonePtr timeZone =
      Fmi::TimeZoneFactory::instance().time_zone_from_string(timeZoneId);
  Fmi::LocalDateTime ldt(theTime.istPosixTime.date(), theTime.istPosixTime.time_of_day(), timeZone);
  return ldt.offset().total_seconds() / 3600;
}

std::time_t TextGenPosixTime::EpochTime() const
{
  Fmi::DateTime time_t_epoch(Fmi::Date(1970, 1, 1));

  return (istPosixTime - time_t_epoch).total_seconds();
}

short TextGenPosixTime::GetWeekday() const  // mon=1, tue=2,..., sat=6,  sun=7
{
  short retval = istPosixTime.date().day_of_week().iso_encoding();

  if (retval == 0) retval = 7;

  return retval;
}

short TextGenPosixTime::GetJulianDay() const { return istPosixTime.date().julian_day(); }
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

  Fmi::DateTime utcptime = localTime.istPosixTime - Fmi::Hours(zdh);

  return TextGenPosixTime(utcptime);
}

//
TextGenPosixTime TextGenPosixTime::LocalTime(const TextGenPosixTime& utcTime)
{
  short zdh = TextGenPosixTime::GetZoneDifferenceHour(utcTime, true);

  Fmi::DateTime localptime = utcTime.istPosixTime + Fmi::Hours(zdh);

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

void TextGenPosixTime::ResetThreadTimeZone() { release_timezone_id(); }
std::ostream& operator<<(std::ostream& os, const TextGenPosixTime& tgTime)
{
#if 1
  os << Fmi::date_time::format_time("%d.%m.%y %H:%M:%S", tgTime.GetDateTime());
#else
  os << std::setw(2) << std::setfill('0') << std::right << tgTime.GetDay() << "." << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetMonth() << "." << tgTime.GetYear() << " "
     << std::setw(2) << std::setfill('0') << std::right << tgTime.GetHour() << ":" << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetMin() << ":" << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetSec();
#endif
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
