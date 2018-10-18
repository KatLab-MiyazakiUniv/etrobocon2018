#include "Localization.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(LocalizationTest, constructTest)
  {
    Localization localization;
  }

  TEST(LocalizationTest, radiusTest)
  {
    Localization localization;
    ASSERT_EQ(static_cast<std::int32_t>(3.14 * 9.8 / 180.0), localization.radius(1, 1));

    ASSERT_EQ(static_cast<std::int32_t>(3.14 * 9.8 * 2 / 180.0), localization.radius(1, 3));
  }

  TEST(LocalizationTest, argTest)
  {
    Localization localization;
    ASSERT_EQ(static_cast<std::int32_t>(9.8 / 100.0), localization.arg(1, 2));

    ASSERT_EQ(static_cast<std::int32_t>(9.8 * 2 / 100.0), localization.arg(1, 3));
  }

}
