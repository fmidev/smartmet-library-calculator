// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::QueryDataTools
 */
// ======================================================================

#pragma once

class NFmiFastQueryInfo;
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
}
}


// ======================================================================
