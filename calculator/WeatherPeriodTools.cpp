// ======================================================================
/*!
 * \file
 * \brief Implementation of namespace TextGen::WeatherPeriodTools
 */
// ======================================================================
/*!
 * \namespace TextGen::WeatherPeriodTools
 *
 * \brief Various tools related to WeatherPeriod objects
 *
 * The namespace provides tools for extracting subperiods
 * from weather periods, counting the number of specified
 * subperiods (for example nights) and so on.
 */
// ======================================================================

// boost included laitettava ennen newbase:n NFmiGlobals-includea,
// muuten MSVC:ss� min max m��rittelyt jo tehty

#include "WeatherPeriodTools.h"
#include <macgyver/Exception.h>
#include "TextGenPosixTime.h"
#include "WeatherPeriod.h"
#include <macgyver/StringConversion.h>

namespace TextGen
{
namespace WeatherPeriodTools
{
// ----------------------------------------------------------------------
/*!
 * \brief Calculate the length of the period in hours
 *
 * \param thePeriod The period
 * \return The length of the period in hours
 */
// ----------------------------------------------------------------------

int hours(const WeatherPeriod& thePeriod)
{
  return thePeriod.localEndTime().DifferenceInHours(thePeriod.localStartTime());
}

// ----------------------------------------------------------------------
/*!
 * \brief Count the number of specified subperiods in the period
 *
 * \param thePeriod The main period
 * \param theStartHour The normal start hour of the subperiod
 * \param theEndHour The normal end hour of the subperiod
 * \return The number of acceptable subperiods in the period
 */
// ----------------------------------------------------------------------

int countPeriods(const WeatherPeriod& thePeriod, int theStartHour, int theEndHour)
{
  return countPeriods(thePeriod, theStartHour, theEndHour, theStartHour, theEndHour);
}

// ----------------------------------------------------------------------
/*!
 * \brief Count the number of specified subperiods in the period
 *
 * \param thePeriod The main period
 * \param theStartHour The normal start hour of the subperiod
 * \param theEndHour The normal end hour of the subperiod
 * \param theMaxStartHour The maximum start hour of the subperiod
 * \param theMinEndHour The minimum end hour of the subperiod
 * \return The number of acceptable subperiods in the period
 */
// ----------------------------------------------------------------------

int countPeriods(const WeatherPeriod& thePeriod,
                 int theStartHour,
                 int theEndHour,
                 int theMaxStartHour,
                 int theMinEndHour)
{
  int count = 0;

  TextGenPosixTime start(thePeriod.localStartTime());
  start.ChangeByDays(-1);
  start.SetHour(theStartHour);

  // maximum allowed difference in hours after start of period
  const int maxdiff1 = (theMaxStartHour >= theStartHour ? theMaxStartHour - theStartHour
                                                        : theMaxStartHour + 24 - theStartHour);

  // maximum allowed difference in hours before end of period
  const int maxdiff2 =
      (theMinEndHour <= theEndHour ? theEndHour - theMinEndHour : theEndHour + 24 - theMinEndHour);

  for (; !thePeriod.localEndTime().IsLessThan(start); start.ChangeByDays(1))
  {
    TextGenPosixTime end(start);
    if (theEndHour <= theStartHour) end.ChangeByDays(1);
    end.SetHour(theEndHour);

    // Is period acceptable somehow?

    int diff1 = 0;
    if (start.IsLessThan(thePeriod.localStartTime()))
      diff1 = thePeriod.localStartTime().DifferenceInHours(start);
    int diff2 = 0;
    if (thePeriod.localEndTime().IsLessThan(end))
      diff2 = end.DifferenceInHours(thePeriod.localEndTime());

    if (diff1 <= maxdiff1 && diff2 <= maxdiff2) count++;
  }
  return count;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the desired subperiod
 *
 * Each subperiod is of the form
 * \code
 *  theStartHour...theMaxStartHour - theMinEndHour...theEndHour
 * \endcode
 *
 * \param thePeriod The main period
 * \param theNumber The ordinal of the period
 * \param theStartHour The normal start hour of the subperiod
 * \param theEndHour The normal end hour of the subperiod
 * \return The number of acceptable subperiods in the period
 */
// ----------------------------------------------------------------------

WeatherPeriod getPeriod(const WeatherPeriod& thePeriod,
                        int theNumber,
                        int theStartHour,
                        int theEndHour)
{
  return getPeriod(thePeriod, theNumber, theStartHour, theEndHour, theStartHour, theEndHour);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the desired subperiod
 *
 * Each subperiod is of the form
 * \code
 *  theStartHour...theMaxStartHour - theMinEndHour...theEndHour
 * \endcode
 *
 * \param thePeriod The main period
 * \param theNumber The index of the period to be generated (1...N)
 * \param theStartHour The normal start hour of the subperiod
 * \param theEndHour The normal end hour of the subperiod
 * \param theMaxStartHour The maximum start hour of the subperiod
 * \param theMinEndHour The minimum end hour of the subperiod
 * \return The number of acceptable subperiods in the period
 */
// ----------------------------------------------------------------------

WeatherPeriod getPeriod(const WeatherPeriod& thePeriod,
                        int theNumber,
                        int theStartHour,
                        int theEndHour,
                        int theMaxStartHour,
                        int theMinEndHour)

{
  const std::string msg =
      "WeatherPeriodTools: Cannot extract subperiod " + Fmi::to_string(theNumber);

  if (theNumber <= 0) throw Fmi::Exception(BCP, msg);

  TextGenPosixTime start(thePeriod.localStartTime());
  start.ChangeByDays(-1);
  start.SetHour(theStartHour);

  // maximum allowed difference in hours after start of period
  const int maxdiff1 = (theMaxStartHour >= theStartHour ? theMaxStartHour - theStartHour
                                                        : theMaxStartHour + 24 - theStartHour);

  // maximum allowed difference in hours before end of period
  const int maxdiff2 =
      (theMinEndHour <= theEndHour ? theEndHour - theMinEndHour : theEndHour + 24 - theMinEndHour);

  for (; !thePeriod.localEndTime().IsLessThan(start); start.ChangeByDays(1))
  {
    TextGenPosixTime end(start);
    if (theEndHour <= theStartHour) end.ChangeByDays(1);
    end.SetHour(theEndHour);

    // Is period acceptable somehow?

    int diff1 = 0;
    if (start.IsLessThan(thePeriod.localStartTime()))
      diff1 = thePeriod.localStartTime().DifferenceInHours(start);
    int diff2 = 0;
    if (thePeriod.localEndTime().IsLessThan(end))
      diff2 = end.DifferenceInHours(thePeriod.localEndTime());

    if (diff1 <= maxdiff1 && diff2 <= maxdiff2)
      if (--theNumber == 0)
      {
        start.ChangeByHours(diff1);
        end.ChangeByHours(-diff2);
        return {start, end};
      }
  }

  throw Fmi::Exception(BCP, msg);
}
}  // namespace WeatherPeriodTools
}  // namespace TextGen

// ======================================================================
