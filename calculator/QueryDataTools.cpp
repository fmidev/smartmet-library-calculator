// ======================================================================
/*!
 * \file
 * \brief Implementation of namespace QueryDataTools
 */
// ======================================================================
/*!
 * \namespace TextGen::QueryDataTools
 *
 * \brief Various small querydata related utility functions
 *
 * The namespace contains various useful utility functions
 * operating on querydata. The functions are not directly
 * available in newbase, but we do not wish to increase
 * the size of newbase unnecessarily with utility functions
 * which are mostly useful only in the text generator.
 *
 */
// ======================================================================

#include "QueryDataTools.h"
#include "TextGenPosixTime.h"
#include <newbase/NFmiFastQueryInfo.h>
#include <newbase/NFmiMetTime.h>
#include <newbase/NFmiQueryData.h>
#include <newbase/NFmiTimeDescriptor.h>
#include <algorithm>
#include <memory>
#include <vector>

namespace TextGen
{
namespace QueryDataTools
{
// ----------------------------------------------------------------------
/*!
 * \brief Find integration index range
 *
 * The NFmiFastQueryInfo Time and ValidTime methods are
 * too slow to be used in loops, it is much better to use
 * the TimeIndex method. This function calculates
 * the desired loop indexes so that if you set the returned
 * start index, the querydata valid time is the first one
 * greater than or equal to the desired start time.
 * The end index is the first time greater than the
 * end time.
 *
 * \param theQI The query info
 * \param theStartTime The desired integration start time
 * \param theEndTime The desired end time
 * \param theStartIndex The variable into which the start index is stored
 * \param theEndIndex The variable into which the end index is stored
 * \return True, if both indexes were found
 */
// ----------------------------------------------------------------------

bool findIndices(NFmiFastQueryInfo& theQI,
                 const TextGenPosixTime& theStartTime,
                 const TextGenPosixTime& theEndTime,
                 unsigned long& theStartIndex,
                 unsigned long& theEndIndex)
{
  const auto invalid = static_cast<unsigned long>(-1);

  if (!firstTime(theQI, theStartTime, theEndTime))
    return false;
  theStartIndex = theQI.TimeIndex();
  if (!lastTime(theQI, theEndTime))
    return false;
  theEndIndex = theQI.TimeIndex();

  return (theStartIndex != invalid && theEndIndex != invalid);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the first integration time
 *
 * This effectively sets active the first time greater than or equal
 * to the given time. If there is no such time, false is returned.
 *
 * This is needed because newbase does not provide an equivalent
 * interface.
 *
 * \param theQI The query info
 * \param theTime The time to set
 * \param theEndTime The end time of the desired range
 * \return True if the time was set successfully
 */
// ----------------------------------------------------------------------

bool firstTime(NFmiFastQueryInfo& theQI,
               const TextGenPosixTime& theTime,
               const TextGenPosixTime& theEndTime)
{
  // Abort if endtime is before start of date
  if (theQI.TimeDescriptor().FirstTime() > theEndTime)
    return false;

  theQI.FirstTime();
  unsigned long idx1 = theQI.TimeIndex();
  theQI.LastTime();
  unsigned long idx2 = theQI.TimeIndex();

  while (idx1 != idx2)
  {
    unsigned long idx = (idx1 + idx2) / 2;
    if (!theQI.TimeIndex(idx))
      return false;
    if (!theQI.IsValidTime())
      return false;
    if (theQI.ValidTime() >= theTime)
      idx2 = idx;
    else
      idx1 = idx + 1;
  }
  theQI.TimeIndex(idx1);

  return (theQI.IsValidTime() && theQI.ValidTime() >= theTime);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the last integration time
 *
 * This effectively sets active the last time greater than
 * to the given time. If there is no such time, false is returned.
 *
 * This is needed because newbase does not provide an equivalent
 * interface.
 *
 * \param theQI The query info
 * \param theTime The time to set
 * \return True if the time was set successfully
 */
// ----------------------------------------------------------------------

bool lastTime(NFmiFastQueryInfo& theQI, const TextGenPosixTime& theTime)
{
  theQI.FirstTime();
  unsigned long idx1 = theQI.TimeIndex();
  theQI.LastTime();
  unsigned long idx2 = theQI.TimeIndex();

  while (idx1 != idx2)
  {
    unsigned long idx = (idx1 + idx2) / 2;
    if (!theQI.TimeIndex(idx))
      return false;

    if (!theQI.IsValidTime())
      return false;
    if (theQI.ValidTime() > theTime)
      idx2 = idx;
    else
      idx1 = idx + 1;
  }
  theQI.TimeIndex(idx1);
  return (theQI.IsValidTime() && theQI.ValidTime() >= theTime);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return a thread specific NFmiFastQueryInfo for the data
 *
 * Constructing a NFmiFastQueryInfo copies all the descriptors of the
 * data, which becomes expensive when a story makes thousands of
 * analysis calls. Hence each thread reuses the info it created for
 * the data earlier. The info is reset to the state it has after
 * construction.
 *
 * \param theData The querydata
 * \return The info, valid until the next call from the same thread
 */
// ----------------------------------------------------------------------

NFmiFastQueryInfo& cachedInfo(const std::shared_ptr<NFmiQueryData>& theData)
{
  struct CachedInfo
  {
    std::weak_ptr<NFmiQueryData> data;
    std::unique_ptr<NFmiFastQueryInfo> info;
  };

  const std::size_t max_cache_size = 8;

  thread_local std::vector<CachedInfo> cache;

  for (auto& item : cache)
  {
    if (item.data.lock() == theData)
    {
      item.info->First();
      return *item.info;
    }
  }

  // Forget data which no longer exists, and the oldest data if there are too many

  cache.erase(
      std::remove_if(
          cache.begin(), cache.end(), [](const CachedInfo& item) { return item.data.expired(); }),
      cache.end());

  if (cache.size() >= max_cache_size)
    cache.erase(cache.begin());

  CachedInfo item;
  item.data = theData;
  item.info.reset(new NFmiFastQueryInfo(theData.get()));
  cache.push_back(std::move(item));

  return *cache.back().info;
}

}  // namespace QueryDataTools
}  // namespace TextGen

// ======================================================================
