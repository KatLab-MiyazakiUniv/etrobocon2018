/**
 *  @file RobotProperty.h
 *  @brief 走行体の車輪半径やトレッド幅等をまとめた構造体
 *  @author T.Miyaji
 */
#ifndef ROBOT_PROPERTY_H
#define ROBOT_PROPERTY_H

struct RobotProperty {
  const float radius_wheel;    // 車輪半径
  const float between_wheels;  // 左右車輪の幅(トレッド幅)
  float dt;                    // 周期

  /**
   *  [RobotProperty::RobotProperty]
   *  @brief RobotPropertyのコンストラクタ
   *  @param diameter 車輪の直径
   *  @param tread    左右車輪の幅(トレッド幅)
   *  @param cycle    周期
   */
  constexpr RobotProperty(float diameter = 100.0f, float tread = 148.0f, float cycle = 0.04f)
    : radius_wheel(diameter / 2.0f), between_wheels(tread), dt(cycle)
  {
  }
};

#endif
