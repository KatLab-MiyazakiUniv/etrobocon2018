/**
 *  @file MotorAngleTest.cpp
 */
#include "MotorAngle.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(MotorAngleTest, absoluteAngleMeanTestPositive)
  {
    MotorAngle angle;
    std::int32_t left = 10;
    std::int32_t right = 20;

    float mean = (left + right) / 2.0f;
    ASSERT_FLOAT_EQ(mean, angle.absoluteAngleMean(left, right));
  }

  TEST(MotorAngleTest, absoluteAngleMeanTestNegative)
  {
    MotorAngle angle;
    std::int32_t left = -10;
    std::int32_t right = 30;

    float mean = (left + right) / 2.0f;
    ASSERT_FLOAT_EQ(mean, angle.absoluteAngleMean(left, right));

    left = 20;
    right = -50;
    mean = (left + right) / 2.0f;
    ASSERT_FLOAT_EQ(mean, angle.absoluteAngleMean(left, right));
  }

  TEST(MotorAngleTest, absoluteAngleMeanTestZero)
  {
    MotorAngle angle;
    std::int32_t left = 0;
    std::int32_t right = 0;

    float mean = (left + right) / 2.0f;
    ASSERT_FLOAT_EQ(mean, angle.absoluteAngleMean(left, right));
  }

  TEST(MotorAngleTest, relativeAngleMeanTestPositive)
  {
    MotorAngle angle;
    std::int32_t left = 10;
    std::int32_t right = 10;
    float mean = (left + right) / 2.0f;

    ASSERT_FLOAT_EQ(mean, angle.relativeAngleMean(left, right));

    std::int32_t left2 = 20;
    std::int32_t right2 = 30;
    float mean2 = ((left2 - left) + (right2 - right)) / 2.0f;

    ASSERT_FLOAT_EQ(mean2, angle.relativeAngleMean(left2, right2));
  }

  TEST(MotorAngleTest, relativeAngleMeanNegative)
  {
    MotorAngle angle;
    std::int32_t left = -10;
    std::int32_t right = -20;
    float mean = (left + right) / 2.0f;
    ASSERT_FLOAT_EQ(mean, angle.relativeAngleMean(left, right));

    std::int32_t left2 = -20;
    std::int32_t right2 = -30;
    float mean2 = ((left2 - left) + (right2 - right)) / 2.0f;

    ASSERT_FLOAT_EQ(mean2, angle.relativeAngleMean(left2, right2));
  }

  TEST(MotorAngleTest, relativeAngleMeanZero)
  {
    MotorAngle angle;
    ASSERT_FLOAT_EQ(0.0f, angle.relativeAngleMean(0, 0));
    ASSERT_FLOAT_EQ(0.0f, angle.relativeAngleMean(0, 0));
  }

  TEST(MotorAngleTest, angularDifferenceTestPositive)
  {
    MotorAngle angle;
    std::int32_t left = 10;
    std::int32_t right = 20;

    ASSERT_FLOAT_EQ(right - left, angle.angularDifference(left, right));
  }

  TEST(MotorAngleTest, angularDifferenceTestNegative)
  {
    MotorAngle angle;
    std::int32_t left = -10;
    std::int32_t right = -20;

    ASSERT_FLOAT_EQ(right - left, angle.angularDifference(left, right));
  }

  TEST(MotorAngleTest, angularDifferenceTestZero)
  {
    MotorAngle angle;
    ASSERT_FLOAT_EQ(0.0f, angle.angularDifference(0, 0));
  }

  TEST(MotorAngleTest, absoluteValueOfAngleTest)
  {
    MotorAngle angle;
    ASSERT_EQ(10, angle.absoluteValueOfAngle(10));
    ASSERT_EQ(10, angle.absoluteValueOfAngle(-10));
  }
}  // namespace etrobocon2018_test
