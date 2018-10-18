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
   Distance distance;
   const float wheel_diameter;
   const float between_wheels;
 public:
   Localization(float diameter = 9.8, float tread = 100.0)
    : distance(), wheel_diameter(diameter), between_wheels(tread) { }
   std::int32_t radius(std::int32_t left_motor, std::int32_t right_motor);
   std::int32_t arg(std::int32_t left_motor, std::int32_t right_motor);
 };




#endif
