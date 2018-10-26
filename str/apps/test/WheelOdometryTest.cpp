/**
 *  @file WheelOdometryTest.cpp
 *  @author T.Miyaji
 */
#include "WheelOdometry.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(CoordinateTest, updateTest)
  {
    Coordinate coordinate;
    coordinate.update(10.0f, 5.0f);
    ASSERT_FLOAT_EQ(5.0f / 2.0f, coordinate.arg);
    ASSERT_FLOAT_EQ(10.0f, coordinate.radius);
    ASSERT_FLOAT_EQ(10.0f * std::cos(5.0f / 2.0f), coordinate.x);
    ASSERT_FLOAT_EQ(10.0f * std::sin(5.0f / 2.0f), coordinate.y);
  }

  TEST(CoordinateTest, updateTest2)
  {
    Coordinate coordinate;
    coordinate.update(10.0f, 5.0f);
    float radius = 10.0f + 5.0f;
    float arg = 5.0f / 2.0f + 10.0f / 2.0f;
    float x = 10.0f * std::cos(5.0f / 2.0f);
    float y = 10.0f * std::sin(5.0f / 2.0f);
    ASSERT_FLOAT_EQ(x, coordinate.x);
    ASSERT_FLOAT_EQ(y, coordinate.y);

    coordinate.update(5.0f, 10.0f);
    ASSERT_FLOAT_EQ(arg, coordinate.arg);
    ASSERT_FLOAT_EQ(radius, coordinate.radius);
    ASSERT_FLOAT_EQ(5.0f * std::cos(arg) + x, coordinate.x);
    ASSERT_FLOAT_EQ(5.0f * std::sin(arg) + y, coordinate.y);
  }

  TEST(CoordinateTest, resetTest)
  {
    Coordinate coordinate;
    coordinate.update(10.0, 5.0);
    coordinate.reset();
    ASSERT_FLOAT_EQ(0.0, coordinate.arg);
    ASSERT_FLOAT_EQ(0.0, coordinate.radius);
    ASSERT_FLOAT_EQ(0.0, coordinate.x);
    ASSERT_FLOAT_EQ(0.0, coordinate.y);
  }

  TEST(WheelOdometryTest, velocityTest)
  {
    MotorAngle motor_angle;
    float transform = 3.14f * 99.0f / 2.0f / 180.0f / 0.04f;
    float angle = motor_angle.relativeAngleMean(5, 5);

    WheelOdometry odometry;
    ASSERT_FLOAT_EQ(transform * angle, odometry.velocity(5, 5));
  }

  TEST(WheelOdometryTest, angularVelocityTest)
  {
    MotorAngle motor_angle;
    float transform = 99.0f / 2.0f / 147.5f / 0.04f;
    float angle = motor_angle.angularDifference(2, 5);

    WheelOdometry odometry;
    ASSERT_FLOAT_EQ(transform * angle, odometry.angularVelocity(2, 5));
  }

  TEST(WheelOdometryTest, resetTest)
  {
    WheelOdometry odometry;
    odometry.update(10.0f, 5.0f);
    Coordinate& coordinate = odometry.reset();
    ASSERT_FLOAT_EQ(0.0f, coordinate.radius);
    ASSERT_FLOAT_EQ(0.0f, coordinate.arg);
    ASSERT_FLOAT_EQ(0.0f, coordinate.x);
    ASSERT_FLOAT_EQ(0.0f, coordinate.y);
  }

  TEST(WheelOdometryTest, updateTest)
  {
    MotorAngle motor_angle;
    float transform = 3.14f * 99.0f / 2.0f / 180.0f;
    float angle = motor_angle.relativeAngleMean(2, 5);
    float expected_distance = transform * angle;

    transform = 99.0f / 2.0f / 147.5f;
    angle = motor_angle.angularDifference(2, 5);
    float expected_angle = transform * angle;

    WheelOdometry odometry;
    Coordinate& coordinate = odometry.update(2, 5);
    ASSERT_FLOAT_EQ(expected_distance, coordinate.radius);
    ASSERT_FLOAT_EQ(expected_angle / 2.0f, coordinate.arg);
    ASSERT_FLOAT_EQ(expected_distance * std::cos(expected_angle / 2.0f), coordinate.x);
    ASSERT_FLOAT_EQ(expected_distance * std::sin(expected_angle / 2.0f), coordinate.y);
  }

  TEST(WheelOdometryTest, getRotationAngleTest)
  {
    WheelOdometry odometry;
    float transform = 99.0f / 147.5f;
    float angle = (5.0f + 5.0f) / 2.0f;

    ASSERT_FLOAT_EQ(transform * angle, odometry.getRotationAngle(-5, 5));

    float angle2 = (2.0f + 2.0f) / 2.0f;

    ASSERT_FLOAT_EQ(transform * angle2, odometry.getRotationAngle(-2, 2));
  }

  TEST(WheelOdometryTest, getCoordinateTest)
  {
    WheelOdometry odometry;
    Coordinate& coordinate = odometry.getCoordinate();

    ASSERT_FLOAT_EQ(0.0f, coordinate.radius);
    ASSERT_FLOAT_EQ(0.0f, coordinate.arg);
    ASSERT_FLOAT_EQ(0.0f, coordinate.x);
    ASSERT_FLOAT_EQ(0.0f, coordinate.y);

    Coordinate coordinate_copy = odometry.update(2, 5);
    ASSERT_FLOAT_EQ(coordinate.radius, coordinate_copy.radius);
    ASSERT_FLOAT_EQ(coordinate.arg, coordinate_copy.arg);
    ASSERT_FLOAT_EQ(coordinate.x, coordinate_copy.x);
    ASSERT_FLOAT_EQ(coordinate.y, coordinate_copy.y);
  }

  TEST(WheelOdometryTest, getPointXTest)
  {
    WheelOdometry odometry;
    Coordinate& coordinate = odometry.update(2, 5);

    ASSERT_FLOAT_EQ(coordinate.x, odometry.getPointX());
  }

  TEST(WheelOdometryTest, getPointYTest)
  {
    WheelOdometry odometry;
    Coordinate& coordinate = odometry.update(2, 5);

    ASSERT_FLOAT_EQ(coordinate.y, odometry.getPointY());
  }
}
