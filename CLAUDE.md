# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`smartmet-library-calculator` — a C++17 shared library (`libsmartmet-calculator.so`) providing time series and area aggregation calculations over QueryData (FMI's native gridded weather data format). Part of the SmartMet Server ecosystem. All code lives in the `TextGen` namespace.

## Build commands

```bash
make                  # Build libsmartmet-calculator.so
make test             # Build and run all Boost.Test unit tests
make format           # Run clang-format on all source and test files
make clean            # Clean build artifacts and test binaries
make rpm              # Build RPM package
```

Dependencies: `smartmet-library-newbase`, `smartmet-library-macgyver`, Boost. Build config comes from `smartbuildcfg`.

### Running a single test

```bash
cd test
make MeanCalculatorTest && ./MeanCalculatorTest
```

Each `*Test.cpp` compiles to its own executable. The test Makefile links against the locally-built `../libsmartmet-calculator.so`.

## Architecture

The library has three main layers:

### 1. Calculator hierarchy (statistical functions)

`Calculator` is the abstract base class — a stateful accumulator that accepts `float` values via `operator()(float)` and returns a result via `operator()()`. Concrete implementations:

`MeanCalculator`, `MaximumCalculator`, `MinimumCalculator`, `MedianCalculator`, `SumCalculator`, `StandardDeviationCalculator`, `PercentageCalculator`, `CountCalculator`, `ChangeCalculator`, `TrendCalculator`, `PeakCalculator`, `NullCalculator`

Modular variants (`ModMeanCalculator`, `ModChangeCalculator`, etc.) handle cyclic quantities like wind direction.

`CalculatorFactory::create(WeatherFunction)` instantiates the right calculator from the `WeatherFunction` enum.

Each calculator uses an `Acceptor` to filter input values. `DefaultAcceptor` accepts all non-missing values; `RangeAcceptor` accepts a configurable range; `NullAcceptor` accepts everything including missing.

### 2. QueryDataIntegrator (the computational engine)

`QueryDataIntegrator::Integrate()` — a set of overloaded free functions that drive integration over time, space, or both by iterating over `NFmiFastQueryInfo` timesteps/gridpoints and feeding values into Calculator instances. This is the core computation loop.

Key integration patterns:
- **Time integration**: iterate timesteps, feed values into a time calculator
- **Area integration**: iterate grid points via `NFmiIndexMask`, feed into a space calculator
- **Combined**: nest space inside time (or vice versa), with optional sub-time periods via `WeatherPeriodGenerator`

### 3. Analyzer layer (high-level API)

`WeatherAnalyzer` is the abstract entry point — takes data sources, a weather parameter, area/time functions, a geographic area, and time periods, returns a `WeatherResult`. Two concrete implementations:
- `WeatherForecaster` — forecast data from QueryData files
- `GridForecaster` — the actual workhorse that orchestrates parameter analysis

`ParameterAnalyzer` subclasses handle parameter-specific logic (regular parameters, wind chill, maximum wind). `ParameterAnalyzerFactory` selects the right one.

### Supporting abstractions

- `WeatherSource` / `LatestWeatherSource` / `UserWeatherSource` — load and cache QueryData
- `MaskSource` / `RegularMaskSource` — provide spatial masks for area calculations
- `WeatherPeriodGenerator` implementations (`HourPeriodGenerator`, `IntervalPeriodGenerator`, `ListedPeriodGenerator`, `NullPeriodGenerator`) — subdivide time ranges
- `AnalysisSources` — bundles all data sources together for the analyzer
- `Settings` — global key-value configuration (wraps `smartmet-library-macgyver` settings)

## CI

CircleCI builds and tests on RHEL 8 and RHEL 10 using `fmidev/smartmet-cibase-{8,10}` Docker images with the `ci-build` helper.
