#include "MaximumWindQueryInfo.h"

MaximumWindQueryInfo::MaximumWindQueryInfo(const NFmiFastQueryInfo& theInfo)
    : NFmiFastQueryInfo(theInfo)
{
  First();

  // Use parameter directly if available

  if (Param(kFmiHourlyMaximumWindSpeed))
  {
    std::cerr << "MaxWind is available!\n";
    return;
  }

  // Else must use at least mean wind speed
  itsExact = false;

  // And possibly hourly maximum gust
  long gust_idx = -1;
  if (Param(kFmiHourlyMaximumGust))
    gust_idx = Index();

  if (!Param(kFmiWindSpeedMS))
    return;  // all booleans are now false, and kFloatMissing will be returned always

  itsBasedOnMeanSpeed = true;
  if (gust_idx >= 0)
  {
    itsBasedOnGustToo = true;
    itsParameterOffset = gust_idx - Index();  // offset from WindSpeedMS to HourlyMaximumGust
  }

  // FMI meteorologists say the current gust forecasts are too unreliable
  itsBasedOnGustToo = false;
}

// ----------------------------------------------------------------------
/*!
 * Get the maximum wind speed
 *
 * \return The value
 */
// ----------------------------------------------------------------------

float MaximumWindQueryInfo::GetFloatValue(unsigned long theIndex) const
{
  // If maximum wind is available, use it
  if (itsExact)
    return NFmiFastQueryInfo::GetFloatValue(theIndex);

  // If mean wind speed is not available, nothing to do
  if (!itsBasedOnMeanSpeed)
    return kFloatMissing;

  float wspd = NFmiFastQueryInfo::GetFloatValue(theIndex);

  if (wspd == kFloatMissing)
    return kFloatMissing;

  // If gust is not available, just use mean wind speed

  const float wspd_multiplier_to_wmax = 1.07;  // Magic constant used by FMI meteorogists

  if (!itsBasedOnGustToo)
    return wspd_multiplier_to_wmax * wspd;

  float gust = NFmiFastQueryInfo::IndexFloatValue(theIndex + itsParameterOffset);
  if (gust == kFloatMissing)
    return wspd_multiplier_to_wmax * wspd;  // Magic constant used by FMI meteorogists

  // Now wspd and gust are both available. The following is based on an approximate formula
  // which interpolates between wspd and gust. The formula is based on ChatGPT discussions, which
  // refer for example to
  //
  //  https://www.ijsetr.com/uploads/621345IJSETR1044-354.pdf
  //  https://www.systemsengineeringaustralia.com.au/download/WMO_TC_Wind_Averaging_27_Aug_2010.pdf
  //  https://www.acsev.org.au/images/document/47_1.pdf
  //  https://ijrat.org/downloads/Vol-6/march-2018/paper%20ID-63201839.pdf
  //
  // For wspd = 5 m/s, 0.55 - 0.01 * 5  = 0.50  slow speeds more turbulent (bigger WG/WMAX)
  //           15 m/s, 0.55 - 0.01 * 15 = 0.45
  //           20 m/s, 0.55 - 0.01 * 20 = 0.35  high speeds less turbulent (smaller WG/WMAX)
  //           30 m/s, 0.55 - 0.01 * 30 = 0.25  practical max in Finland

  return wspd + (0.55 - 0.01 * wspd) * (gust - wspd);
}
