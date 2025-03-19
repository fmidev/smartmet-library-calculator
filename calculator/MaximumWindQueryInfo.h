// ======================================================================
/*!
 * \file MaximumWindQueryInfo.h
 * \brief Interface of class MaximumWindQueryInfo
 */
// ======================================================================

#pragma once

#include <newbase/NFmiFastQueryInfo.h>

class MaximumWindQueryInfo : public NFmiFastQueryInfo
{
 public:
  MaximumWindQueryInfo(const NFmiFastQueryInfo& theInfo);

  float GetFloatValue(unsigned long theIndex) const override;

  using NFmiFastQueryInfo::FloatValue;

 private:
  bool itsExact = true;              // Using only HourlyMaximumWindSpeed
  bool itsBasedOnMeanSpeed = false;  // else using at least WindSpeedMS?
  bool itsBasedOnGustToo = false;    // and using also HourlyMaximumGust?
  long itsParameterOffset = 0;       // nonzero offset from WindSpeedMS if gust is used too
};
