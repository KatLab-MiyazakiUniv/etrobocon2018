#include "WheelOdometry.h"

/**
 *  [Coordinate::update]
 *  @brief 走行体の位置情報を更新する
 *  @param 走行体の移動距離(円弧) [mm]
 *  @param 走行体の旋回半径 [deg]
 */
void Coordinate::update(float distance, float angle)
{
  // 移動角度
  float theta = angle / 2.0f;

  // 直交座標の更新
  x += distance * std::cos(arg + theta);
  y += distance * std::sin(arg + theta);

  //! @note 走行体は円弧運動をするが、周期で見れば直線運動に近似できる
  radius += distance;
  //! @note argは走行体が移動したときの角度(移動前の走行体の位置を原点とする)
  arg += theta;
}

/**
 *  [Coordinate::reset]
 *  @brief 走行体の位置情報を初期化する
 */
void Coordinate::reset()
{
  radius = 0.0f;
  arg = 0.0f;
  x = 0.0f;
  y = 0.0f;
}

/**
 *  [WheelOdometry::velocity]
 *  @brief  左右モータの回転角から走行体の速度を算出する
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の前進速度 [mm / sec]
 */
float WheelOdometry::velocity(std::int32_t left_motor, std::int32_t right_motor)
{
  // 回転速度から走行体の速度へ変換するときに必要な係数
  float transform = 3.14f * property.radius_wheel / 180.0f;
  // 走行体の回転角の差を求める(LPF処理つき)
  float angle = motor_angle.relativeAngleMean(left_motor, right_motor, true);

  return transform * angle / property.dt;
}

/**
 *  [WheelOdometry::angularVelocity]
 *  @brief  左右モータの回転角から走行体の角速度を求める
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の角速度 [deg / sec]
 */
float WheelOdometry::angularVelocity(std::int32_t left_motor, std::int32_t right_motor)
{
  // 回転速度から角速度へ変換するときに必要な係数
  float transform = property.radius_wheel / property.between_wheels;

  // 走行体の回転角の差を求める(右モータ - 左モータ), LPF処理つき
  float angle = motor_angle.angularDifference(left_motor, right_motor, true);

  return transform * angle / property.dt;
}

/**
 *  [WheelOdometry::reset]
 *  @brief  走行体の位置情報を初期化する
 */
Coordinate& WheelOdometry::reset()
{
  coordinate.reset();
  return coordinate;
}

/**
 *  [WheelOdometry::update]
 *  @brief  走行体の位置情報を更新する
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の位置情報
 */
Coordinate& WheelOdometry::update(std::int32_t left_motor, std::int32_t right_motor)
{
  // 走行体の移動距離を計算する
  float distance = velocity(left_motor, right_motor) * property.dt;
  // 走行体の旋回角度を計算する
  float angle = angularVelocity(left_motor, right_motor) * property.dt;
  // 走行体の位置情報を更新する
  coordinate.update(distance, angle);

  return coordinate;
}

/**
 *  [WheelOdometry::getRotationAngle]
 *  @brief  走行体の回転角度を返す
 *  @param  left_motor  左モータの回転角
 *  @param  right_motor 右モータの回転角
 *  @return 走行体の回転角度 [deg]
 */
float WheelOdometry::getRotationAngle(std::int32_t left_motor, std::int32_t right_motor)
{
  // モータの角度から回転角度へ変換するときに必要な係数
  float transform = 2.0f * property.radius_wheel / property.between_wheels;

  // モータの角度を絶対値で取得する
  left_motor = motor_angle.absoluteValueOfAngle(left_motor);
  right_motor = motor_angle.absoluteValueOfAngle(right_motor);

  // モータの角度の平均値を求める
  float mean = motor_angle.absoluteAngleMean(left_motor, right_motor);

  return transform * mean;
}

/**
 *  [WheelOdometry::getCoordinate]
 *  @brief 走行体の位置情報を返す
 */
Coordinate& WheelOdometry::getCoordinate()
{
  return coordinate;
}

/**
 *  [WheelOdometry::getPointX]
 *  @brief 走行体の位置x座標を返す
 */
float WheelOdometry::getPointX()
{
  return coordinate.x;
}

/**
 *  [WheelOdometry::getPointY]
 *  @brief 走行体の位置y座標を返す
 */
float WheelOdometry::getPointY()
{
  return coordinate.y;
}
