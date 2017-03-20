// ======================================================================
/*!
 * \file WindChillQueryInfo.h
 * \brief Interface of class WindChillQueryInfo
 */
// ======================================================================

#pragma once

#include <newbase/NFmiFastQueryInfo.h>

class WindChillQueryInfo : public NFmiFastQueryInfo
{
 public:
  WindChillQueryInfo(const NFmiFastQueryInfo& theInfo);

  float GetFloatValue(unsigned long theIndex) const;

  using NFmiFastQueryInfo::FloatValue;

 private:
  long itsParameterOffset;
};

