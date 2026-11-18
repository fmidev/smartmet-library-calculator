// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::QueryDataTools
 */
// ======================================================================

#pragma once

#include <memory>

class NFmiFastQueryInfo;
class NFmiQueryData;
class TextGenPosixTime;

namespace TextGen
{
namespace QueryDataTools
{
bool findIndices(NFmiFastQueryInfo& theQI,
                 const TextGenPosixTime& theStartTime,
                 const TextGenPosixTime& theEndTime,
                 unsigned long& theStartIndex,
                 unsigned long& theEndIndex);

bool firstTime(NFmiFastQueryInfo& theQI,
               const TextGenPosixTime& theTime,
               const TextGenPosixTime& theEndTime);

bool lastTime(NFmiFastQueryInfo& theQI, const TextGenPosixTime& theTime);

NFmiFastQueryInfo& cachedInfo(const std::shared_ptr<NFmiQueryData>& theData);
}  // namespace QueryDataTools
}  // namespace TextGen

// ======================================================================
