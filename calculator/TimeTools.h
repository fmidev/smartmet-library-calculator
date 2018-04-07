// ======================================================================
/*!
 * \file
 * \brief Interface of namespace TextGen::TimeTools
 */
// ======================================================================

#pragma once

#include <ctime>

class TextGenPosixTime;

namespace TextGen
{
namespace TimeTools
{
bool isSameDay(const TextGenPosixTime& theDate1, const TextGenPosixTime& theDate2);
bool isNextDay(const TextGenPosixTime& theDate1, const TextGenPosixTime& theDate2);
bool isSeveralDays(const TextGenPosixTime& theDate1, const TextGenPosixTime& theDate2);

TextGenPosixTime dayStart(const TextGenPosixTime& theDate);
TextGenPosixTime dayEnd(const TextGenPosixTime& theDate);
TextGenPosixTime nextDay(const TextGenPosixTime& theDate);
TextGenPosixTime addHours(const TextGenPosixTime& theDate, int theHours);
}  // namespace TimeTools
}  // namespace TextGen

// ======================================================================
