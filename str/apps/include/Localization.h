/**
 *  @file  Localization.h
 *  @brief オドメトリ(Wheel Odometry)手法を用いた自己位置推定クラス
 *  @author T.Miyaji
 */
#ifndef LOCALIZATION_H
#define LOCALIZATION_H
#include "Distance.h"
#include <cstdint>

class Localization {
 private:
   Distance angle_calculator;
   const float radius_wheel;    // 車輪半径
   const float between_wheels;  // 左右車輪の幅(トレッド幅)
   std::int32_t radius; // 走行体の旋回半径
   std::int32_t arg;  // 走行体の旋回角度
   float delta; // 周期
 public:
   Localization(float diameter = 9.8, float tread = 100.0, float cycle = 0.04)
    : angle_calculator(), radius_wheel(diameter / 2.0), between_wheels(tread), radius(0), arg(0), delta(cycle) { }
   //! 走行体の旋回速度を求める
   std::int32_t velocity(std::int32_t left_motor, std::int32_t right_motor);
   //! 走行体の旋回角速度を求める
   std::int32_t angularVelocity(std::int32_t left_motor, std::int32_t right_motor);
   //! 走行体の走行距離を求める
   std::int32_t distance(std::int32_t left_motor, std::int32_t right_motor);
   //! 走行体の走行距離を返す
   std::int32_t distance();
   //! 走行体の旋回角度を求める
   std::int32_t angle(std::int32_t left_motor, std::int32_t right_motor);
   //! 走行体の旋回角度を返す
   std::int32_t angle();
 };

#endif
