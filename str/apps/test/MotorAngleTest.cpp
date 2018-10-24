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

  TEST(MotorAngleTest, absoluteAngleMeanTestFilter)
  {
    MotorAngle angle;
    std::int32_t left = 10;
    std::int32_t right = 20;

    // LPFは初期値では、通しても通さなくても値が変わらない
    ASSERT_FLOAT_EQ(angle.absoluteAngleMean(left, right),
                    angle.absoluteAngleMean(left, right, true));

    float left2 = 20;
    float left2_filtered = left2 * 0.1 + left * 0.9;
    float right2 = 30;
    float right2_filtered = right2 * 0.1 + right * 0.9;
    float mean = (left2_filtered + right2_filtered) / 2.0f;

    ASSERT_FLOAT_EQ(mean, angle.absoluteAngleMean(left2, right2, true));
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

  TEST(MotorAngleTest, relativeAngleMeanFilter)
  {
    MotorAngle angle;
    std::int32_t left = 10;
    std::int32_t right = 10;
    float mean = (left + right) / 2.0f;
    // LPFは初期値では、通しても通さなくても値が変わらない
    ASSERT_FLOAT_EQ(mean, angle.relativeAngleMean(left, right, true));

    std::int32_t left2 = 20;
    std::int32_t right2 = 20;
    float left2_filtered = left2 * 0.1 + left * 0.9;
    float right2_filtered = right2 * 0.1 + right * 0.9;
    float mean2_filtered = ((left2_filtered - left) + (right2_filtered - right)) / 2.0f;
    ASSERT_FLOAT_EQ(mean2_filtered, angle.relativeAngleMean(left2, right2, true));
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
