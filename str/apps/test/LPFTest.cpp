/**
 *  @file LPFTest.cpp
 *  @author T.Miyaji
 */

#include "LPF.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  TEST(LPF, sensorTest)
  {
    LPF filter;
    std::uint8_t sensor = 24;  // This is 適当

    // 前回のセンサ値がない場合は、入力値をそのまま返す
    ASSERT_EQ(sensor, filter.sensor(sensor));

    // フィルタ処理
    std::uint8_t current_sensor = 77; // This is 適当
    std::uint8_t expected = 0.9 * sensor + 0.1 * current_sensor;
    ASSERT_EQ(expected, filter.sensor(current_sensor));
  }
}
