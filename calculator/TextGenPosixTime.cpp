#include "TextGenPosixTime.h"
#include <macgyver/TimeZoneFactory.h>
#include <newbase/NFmiStaticTime.h>
#include <ctime>
#include <iostream>  // std::cout
#include <sstream>   // std::stringstream

namespace bg = boost::gregorian;
namespace bp = boost::posix_time;

// Used to be Europe/Helsinki, this is a more portable default
#define DEFAULT_TZ_ID "UTC"

static thread_local std::string tls;

void release_timezone_id() { tls.clear(); }

std::string& get_timezone_id() { return tls; }

TextGenPosixTime::TextGenPosixTime() : istPosixTime(bp::second_clock::local_time()) {}
TextGenPosixTime::TextGenPosixTime(const bp::ptime& theTime) : istPosixTime(theTime) {}

TextGenPosixTime::TextGenPosixTime(std::time_t theTime) : istPosixTime(bp::from_time_t(theTime)) {}

TextGenPosixTime::TextGenPosixTime(const NFmiStaticTime& theTime)
    : istPosixTime(bg::date(theTime.GetYear(), theTime.GetMonth(), theTime.GetDay()),
                   bp::time_duration(theTime.GetHour(), theTime.GetMin(), theTime.GetSec()))
{
}

TextGenPosixTime::TextGenPosixTime(short year, short month, short day)
    : istPosixTime(bg::date(year, month, day), bp::time_duration(0, 0, 0))
{
}

TextGenPosixTime::TextGenPosixTime(
    short year, short month, short day, short hour, short minute /*=0*/, short sec /*=0*/)
{
  bp::time_duration td(hour, minute, sec, 0);
  std::stringstream ss;
  ss << year << "-" << month << "-" << day;
  bg::date d(bg::from_simple_string(ss.str()));

  istPosixTime = bp::ptime(d, td);
}

void TextGenPosixTime::ChangeBySeconds(long sec) { istPosixTime += bp::seconds(sec); }
void TextGenPosixTime::ChangeByMinutes(long min) { istPosixTime += bp::minutes(min); }
void TextGenPosixTime::ChangeByHours(long hour) { istPosixTime += bp::hours(hour); }
void TextGenPosixTime::ChangeByDays(long day) { istPosixTime += bg::days(day); }
long TextGenPosixTime::DifferenceInMinutes(const TextGenPosixTime& anotherTime) const
{
  bp::time_duration td(istPosixTime - anotherTime.istPosixTime);

  return td.total_seconds() / 60;
}

long TextGenPosixTime::DifferenceInHours(const TextGenPosixTime& anotherTime) const
{
  bp::time_duration td(istPosixTime - anotherTime.istPosixTime);

  return td.total_seconds() / 3600;
}

long TextGenPosixTime::DifferenceInDays(const TextGenPosixTime& anotherTime) const
{
  bp::time_duration td(istPosixTime - anotherTime.istPosixTime);

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
  bg::date d(year, month, day);
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(d, td);
}

void TextGenPosixTime::SetYear(short year)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(bg::date(year, d.month(), d.day()), td);
}

void TextGenPosixTime::SetMonth(short month)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(bg::date(d.year(), month, d.day()), td);
}

void TextGenPosixTime::SetDay(short day)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(bg::date(d.year(), d.month(), day), td);
}

void TextGenPosixTime::SetHour(short hour)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(d, bp::time_duration(hour, td.minutes(), td.seconds()));
}

void TextGenPosixTime::SetMin(short minute)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(d, bp::time_duration(td.hours(), minute, td.seconds()));
}

void TextGenPosixTime::SetSec(short sec)
{
  bg::date d(istPosixTime.date());
  bp::time_duration td(istPosixTime.time_of_day());

  istPosixTime = bp::ptime(d, bp::time_duration(td.hours(), td.minutes(), sec));
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
    ss << std::setw(2) << (GetYear() - (GetYear() < 2000 ? 1900 : 2000));
  else if ((kLongYear & theTimeMask) != 0)
    ss << std::setw(4) << GetYear();

  if ((kMonth & theTimeMask) != 0) ss << std::setw(2) << std::setfill('0') << GetMonth();

  if ((kDay & theTimeMask) != 0) ss << std::setw(2) << std::setfill('0') << GetDay();

  if ((kHour & theTimeMask) != 0) ss << std::setw(2) << std::setfill('0') << GetHour();

  if ((kMinute & theTimeMask) != 0) ss << std::setw(2) << std::setfill('0') << GetMin();

  if ((kSecond & theTimeMask) != 0) ss << std::setw(2) << std::setfill('0') << GetSec();

  return ss.str();
}

short TextGenPosixTime::GetZoneDifferenceHour(const TextGenPosixTime& theTime, bool isUtc)
{
  std::string timeZoneId(get_timezone_id().empty() ? DEFAULT_TZ_ID : get_timezone_id());
  const boost::local_time::time_zone_ptr timeZone =
      Fmi::TimeZoneFactory::instance().time_zone_from_string(timeZoneId);

  short dst_offset(timeZone->base_utc_offset().hours() + timeZone->dst_offset().hours());
  short normal_time_offset(timeZone->base_utc_offset().hours());
  bp::ptime dst_local_start_time(timeZone->dst_local_start_time(theTime.GetYear()));
  bp::ptime dst_local_end_time(timeZone->dst_local_end_time(theTime.GetYear()));
  bool dst_on = false;

  // in the southern hemisphere dst is in wintertime
  if (dst_local_start_time > dst_local_end_time)
  {
    if (isUtc)
      dst_on = (theTime.istPosixTime + bp::hours(dst_offset) >= dst_local_start_time ||
                theTime.istPosixTime + bp::hours(dst_offset) < dst_local_end_time);
    else
      dst_on = (theTime.istPosixTime >= dst_local_start_time ||
                theTime.istPosixTime < dst_local_end_time);
  }
  else
  {
    if (isUtc)
      dst_on = (theTime.istPosixTime + bp::hours(dst_offset) >= dst_local_start_time &&
                theTime.istPosixTime + bp::hours(dst_offset) < dst_local_end_time);
    else
      dst_on = (theTime.istPosixTime >= dst_local_start_time &&
                theTime.istPosixTime < dst_local_end_time);
  }

  if (dst_on) return dst_offset;

  return normal_time_offset;
}

std::time_t TextGenPosixTime::EpochTime() const
{
  bp::ptime time_t_epoch(bg::date(1970, 1, 1));

  return (istPosixTime - time_t_epoch).total_seconds();
}

short TextGenPosixTime::GetWeekday() const  // mon=1, tue=2,..., sat=6,  sun=7
{
  short retval = istPosixTime.date().day_of_week();

  if (retval == 0) retval = 7;

  return retval;
}

short TextGenPosixTime::GetJulianDay() const { return istPosixTime.date().julian_day(); }
short TextGenPosixTime::DaysInYear(const short aYear)
{
  bg::date d(aYear, 12, 1);

  return d.end_of_month().day_of_year();
}

short TextGenPosixTime::DaysInMonth(const short aMonth, const short aYear)
{
  bg::date d(aYear, aMonth, 1);

  return d.end_of_month().day();
}

TextGenPosixTime TextGenPosixTime::UtcTime(const TextGenPosixTime& localTime)
{
  short zdh = TextGenPosixTime::GetZoneDifferenceHour(localTime, false);

  bp::ptime utcptime = localTime.istPosixTime - bp::hours(zdh);

  return TextGenPosixTime(utcptime);
}

//
TextGenPosixTime TextGenPosixTime::LocalTime(const TextGenPosixTime& utcTime)
{
  short zdh = TextGenPosixTime::GetZoneDifferenceHour(utcTime, true);

  bp::ptime localptime = utcTime.istPosixTime + bp::hours(zdh);

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
  os << std::setw(2) << std::setfill('0') << std::right << tgTime.GetDay() << "." << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetMonth() << "." << tgTime.GetYear() << " "
     << std::setw(2) << std::setfill('0') << std::right << tgTime.GetHour() << ":" << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetMin() << ":" << std::setw(2)
     << std::setfill('0') << std::right << tgTime.GetSec();

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
