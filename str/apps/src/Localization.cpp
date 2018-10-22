#include "Localization.h"

/**
 *  [Localization::velocity]
 *  @brief  左右モータの回転角から走行体の速度を算出する
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の前進速度
 */
std::int32_t Localization::velocity(std::int32_t left_motor, std::int32_t right_motor)
{
  // 回転速度から走行体の速度へ変換するときに必要な係数
  float transform = 3.14 * radius_wheel / 180.0;
  // 走行体の回転角の差を求める
  auto angle = angle_calculator.getDistanceCurrent(left_motor, right_motor);

  return static_cast<std::int32_t>(transform * angle / delta);
}

/**
 *  [Localization::angularVelocity]
 *  @brief  左右モータの回転角から走行体の角速度を求める
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の角速度
 */
std::int32_t Localization::angularVelocity(std::int32_t left_motor, std::int32_t right_motor)
{
  // 回転速度から角速度へ変換するときに必要な係数
  float transform = radius_wheel / between_wheels;

  // 走行体の回転角の差を求める(右モータ - 左モータ)
  auto angle = angle_calculator.getAngleCurrent(left_motor, right_motor);

  return static_cast<std::int32_t>(transform * angle / delta);
}

/**
 *  [Localization::distance]
 *  @brief  走行体の走行距離を算出する
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の走行距離
 */
std::int32_t Localization::distance(std::int32_t left_motor, std::int32_t right_motor)
{
  // 走行体の速度を求める
  auto v = velocity(left_motor, right_motor);
  // 走行体の速度を積分(加算)する
  radius += v * delta;

  // 求めた距離を返す
  return distance();
}

/**
 *  [Localization::distance]
 *  @brief  走行体の走行距離を返す
 *  @return 走行体の走行距離
 */
std::int32_t Localization::distance()
{
  return radius;
}

/**
 *  [Localization::distance]
 *  @brief  走行体の旋回角度を算出する
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の旋回角度
 */
std::int32_t Localization::angle(std::int32_t left_motor, std::int32_t right_motor)
{
  // 走行体の角速度を求める
  auto angular_velocity = angularVelocity(left_motor, right_motor);
  // 走行体の角速度を積分(加算)する
  arg += angular_velocity * delta;

  // 求めた角度を返す
  return angle();
}

/**
 *  [Localization::distance]
 *  @brief  走行体の旋回角度を返す
 *  @return 走行体の旋回角度
 */
std::int32_t Localization::angle()
{
  return arg;
}
