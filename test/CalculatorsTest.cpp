// ======================================================================
/*!
 * \file
 * \brief Regression tests for the count, median, peak and percentage calculators
 */
// ======================================================================

#include "CountCalculator.h"
#include "MedianCalculator.h"
#include "PeakCalculator.h"
#include "PercentageCalculator.h"
#include "RangeAcceptor.h"
#include <newbase/NFmiGlobals.h>
#include <regression/tframe.h>
#include <string>
#include <vector>

using namespace std;

namespace CalculatorsTest
{
template <typename Calculator>
float feed(Calculator& calc, const std::vector<float>& values)
{
  calc.reset();
  for (float value : values)
    calc(value);
  return calc();
}

std::string str(float value)
{
  return value == kFloatMissing ? "missing" : std::to_string(value);
}

#define CHECK(name, result, expected)                                                     \
  if ((result) != (expected))                                                             \
  TEST_FAILED(std::string(name) + ": expected " + str(expected) + ", got " + str(result))

// ----------------------------------------------------------------------

void range_acceptor()
{
  using namespace TextGen;
  RangeAcceptor acceptor;
  if (!acceptor.accept(-1000) || !acceptor.accept(1000))
    TEST_FAILED("Without limits all values should be accepted");
  if (acceptor.accept(kFloatMissing))
    TEST_FAILED("Missing values should never be accepted");

  acceptor.lowerLimit(0);
  acceptor.upperLimit(10);
  if (!acceptor.accept(0) || !acceptor.accept(10) || !acceptor.accept(5))
    TEST_FAILED("The limits are inclusive");
  if (acceptor.accept(-0.1F) || acceptor.accept(10.1F))
    TEST_FAILED("Values outside the limits should be rejected");
  TEST_PASSED();
}

// ----------------------------------------------------------------------

void count()
{
  using namespace TextGen;
  CountCalculator calc;
  CHECK("count of nothing", feed(calc, {}), kFloatMissing);

  // Without a condition every accepted value is counted
  CHECK("count", feed(calc, {1, 2, kFloatMissing, 3}), 3);

  RangeAcceptor positive;
  positive.lowerLimit(0.5);
  calc.condition(positive);
  CHECK("conditional count", feed(calc, {-1, 0, 1, 2, kFloatMissing}), 2);
  // No values pass the condition, but some were accepted
  CHECK("conditional count of none", feed(calc, {-1, -2}), 0);
  TEST_PASSED();
}

// ----------------------------------------------------------------------

void percentage()
{
  using namespace TextGen;
  PercentageCalculator calc;
  CHECK("percentage of nothing", feed(calc, {}), kFloatMissing);

  RangeAcceptor rain;
  rain.lowerLimit(0.1F);
  calc.condition(rain);
  CHECK("rain percentage", feed(calc, {0, 0, 0.5, 1.2}), 50);
  CHECK("rain percentage with missing", feed(calc, {0, kFloatMissing, 0.5, 1.2}), 100 * 2.0F / 3);

  // The acceptor restricts the values which are considered at all
  RangeAcceptor land;
  land.upperLimit(100);
  calc.acceptor(land);
  CHECK("acceptor filters values", feed(calc, {0, 0.5, 200, 300}), 50);
  TEST_PASSED();
}

// ----------------------------------------------------------------------

void median()
{
  using namespace TextGen;
  MedianCalculator calc;
  CHECK("median of nothing", feed(calc, {}), kFloatMissing);
  CHECK("median of one", feed(calc, {7}), 7);
  CHECK("median of three", feed(calc, {3, 1, 2}), 2);
  CHECK("median of five", feed(calc, {5, 1, 4, 2, 3}), 3);
  // For an even count the lower one of the middle values is used
  CHECK("median of two", feed(calc, {2, 1}), 1);
  CHECK("median of four", feed(calc, {4, 1, 3, 2}), 2);
  CHECK("median ignores missing", feed(calc, {kFloatMissing, 3, 1, 2}), 2);
  TEST_PASSED();
}

// ----------------------------------------------------------------------

void peak()
{
  using namespace TextGen;
  PeakCalculator calc;
  CHECK("peak of nothing", feed(calc, {}), kFloatMissing);

  // Fewer than 10 values: the maximum
  CHECK("peak of few values", feed(calc, {1, 5, 3}), 5);

  // Otherwise the 95% fractile, for 20 values the index 95*20/100 = 19 is still the maximum
  std::vector<float> values;
  for (int i = 1; i <= 19; i++)
    values.push_back(i);
  values.push_back(1000);
  CHECK("peak of 20 values", feed(calc, values), 1000);
  values.push_back(20);
  values.push_back(21);
  values.push_back(22);
  values.push_back(23);
  values.push_back(24);
  values.push_back(25);
  // 26 values, index 95*26/100 = 24 of the sorted values 1..25,1000 is 25 and ignores the outlier
  CHECK("peak is the 95% fractile", feed(calc, values), 25);
  TEST_PASSED();
}

// ----------------------------------------------------------------------

class tests : public tframe::tests
{
  const char* error_message_prefix() const override { return "\n\t"; }
  void test() override
  {
    TEST(range_acceptor);
    TEST(count);
    TEST(percentage);
    TEST(median);
    TEST(peak);
  }
};

}  // namespace CalculatorsTest

int main()
{
  cout << endl << "Calculators tester" << endl << "==================" << endl;
  CalculatorsTest::tests t;
  return t.run();
}
