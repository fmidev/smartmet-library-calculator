# calculator developer guide

This guide is for developers who change `smartmet-library-calculator`, or use it.
calculator answers questions like "what is the maximum over Uusimaa of the mean temperature
between 12 and 18 local time": it aggregates QueryData over time periods and areas. It is
the analysis layer of textgen (the automatic forecast text generator), both the textgen
library and the textgen plugin. All code is in the `TextGen` namespace.

[CLAUDE.md](../CLAUDE.md) has the class overview.

## Contents

1. [Building and testing](#1-building-and-testing)
2. [An analysis](#2-an-analysis)
3. [Calculators and acceptors](#3-calculators-and-acceptors)
4. [How the integration is nested](#4-how-the-integration-is-nested)
5. [Areas](#5-areas)
6. [Times and periods](#6-times-and-periods)
7. [Settings](#7-settings)
8. [Compatibility](#8-compatibility)
9. [Known pitfalls](#9-known-pitfalls)

---

## 1. Building and testing

```bash
make
make test
make -C test MeanCalculatorTest && ./test/MeanCalculatorTest
```

The tests use `regression/tframe.h` (not Boost.Test) and the QueryData, map and coordinate
files in `test/`.

## 2. An analysis

```cpp
GridForecaster forecaster;
WeatherResult r = forecaster.analyze(sources,
                                     Temperature,      // WeatherParameter
                                     Maximum,          // area function
                                     Mean,             // time function
                                     NullFunction,     // sub-time function (unused here)
                                     WeatherArea("uusimaa"),
                                     HourPeriodGenerator(period, "textgen::part1::day"),
                                     DefaultAcceptor(), DefaultAcceptor(), DefaultAcceptor());
```

1. `ParameterAnalyzerFactory` picks the analyzer for the `WeatherParameter`: regular
   parameters, modular ones (wind direction, modulo 360), wind chill, maximum wind.
2. The analyzer finds the data and the newbase parameter from the **settings** (§7):
   `<name>_forecast` names the data set, falling back to `textgen::default_forecast`; `<name>`
   can override the parameter name.
3. `AnalysisSources` supplies the data (`WeatherSource`) and the masks (`MaskSource`s
   for the full area, land, coast, inland and the four compass halves).
4. `QueryDataIntegrator::Integrate()` runs the calculators over the data (§4).
5. The result is a `WeatherResult(value, error)`. With `Mean` as the area function, `error`
   is the spatial standard deviation, computed with a second integration pass; otherwise it
   is 0. A missing result is `(kFloatMissing, 0)`.

## 3. Calculators and acceptors

A `Calculator` accumulates values (`operator()(float)`) and gives the result
(`operator()()`); `reset()` starts over and `clone()` copies it. `CalculatorFactory` creates
one per `WeatherFunction`: `Mean`, `Maximum`, `Minimum`, `Median`, `Sum`,
`StandardDeviation`, `Percentage`, `Count`, `Change`, `Trend`, `Peak`, `NullFunction`.
Modular variants (`ModMean`, `ModChange`, `ModTrend`, `ModStandardDeviation`) handle
directions.

**Acceptors** decide which values a calculator takes: `DefaultAcceptor` rejects missing
values, `RangeAcceptor` takes a value range, `NullAcceptor` takes everything. The **tester**
acceptor is the condition for `Percentage` and `Count`: for example, the percentage of the
area where precipitation is at least 0.1 mm is a `Percentage` area function with a
`RangeAcceptor(0.1, …)` tester.

## 4. How the integration is nested

For an area, the integration runs **per grid point first, over time, and then over the
area**:

```
for each grid point in the mask:
    for each period from the period generator:
        sub-time calculator over the time steps of the period
        -> feeds the time calculator
    time result -> feeds the area calculator
result = area calculator
```

So `Maximum` (area) of `Mean` (time) is the largest of the point means, not the mean of
the hourly area maxima. A point analysis does the time part only, at the grid point nearest
to the point.

If the period generator is undivided (`undivided()`, for example `NullPeriodGenerator`),
the sub-time calculator is not used and the time calculator runs over the whole period.

## 5. Areas

`WeatherArea(spec)` accepts:

* a **map file**: an SVG path, found as the name itself, `name.svg`, or in
  `textgen::mappath` (with or without `.svg`);
* a **location name** known to `LocationSource`;
* **`lon,lat`**;
* any of these followed by **`:radius`** in kilometres, which expands the area (or turns a
  point into a small area).

`type()` restricts the area to its land, coast, inland, northern, southern, eastern or
western part; the masks are built by `RegularMaskSource` from the data's grid with
`NFmiIndexMaskTools` and cached.

## 6. Times and periods

`TextGenPosixTime` is textgen's time type. `WeatherPeriod(localStart, localEnd)` takes
local times and stores the UTC times too; the conversion uses the **thread's time zone**,
set with `TextGenPosixTime::SetThreadTimeZone(tz)` (UTC if not set). The period generators
(`HourPeriodGenerator`, `IntervalPeriodGenerator`, `ListedPeriodGenerator`,
`NullPeriodGenerator`) split a period into sub-periods, configured by settings.

Periods are **inclusive**: both the start and end time steps belong to the period.

## 7. Settings

`Settings` (`Settings::require_string()`, `optional_int()`, …, `Settings::set()`) is a
key-value store that is **thread-local** (`Fmi::Config` in `Config.cpp`). The textgen plugin
fills it for each request, and calls `Settings::release()` at the end, in the same thread.

## 8. Compatibility

The headers are installed and used by the textgen library and plugin. Most classes have
virtual methods (calculators, acceptors, analyzers, sources); add new virtual methods at
the end, and rebuild textgen when a class layout changes.

## 9. Known pitfalls

* **Settings and the time zone are per thread.** Set them in the thread that runs the
  analysis, and clear them afterwards, or the next request on the thread sees them.
* **`GetZoneDifferenceHour()` truncates to whole hours.** `UtcTime()` and `LocalTime()`
  use the full offset, but code using the hour difference directly is off by 30 minutes
  in zones like `Asia/Kolkata` (+05:30).
* **Any empty sub-period makes the whole result missing.**
* **`Mean` area results cost two passes** because of the error estimate (§2).
* **Point analyses use the nearest grid point**, without interpolation.
* **`Settings::set("key=value\n...")` splits each line at its first `=`.** The value may
  contain further `=` characters and may be empty.
