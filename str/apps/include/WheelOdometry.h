/**
 *  @file WheelOdometry.h
 *  @brief オドメトリ(Wheel odometry)手法を用いた速度/角度/自己位置推定
 *  @author T.Miyaji
 */
#ifndef WHEEL_ODOMETRY_H
#define WHEEL_ODOMETRY_H
#include "MotorAngle.h"
#include "RobotProperty.h"
#include <cmath>
#include <cstdint>

/**
 *  @brief 走行体の位置情報をまとめた構造体
 */
struct Coordinate {
  float radius;  // [極座標] 走行体の移動半径(走行体の移動距離で近似)
  float arg;     // [極座標] 走行体の移動角度
  float x;       // [直交座標] 走行体の位置(x座標)
  float y;       // [直交座標] 走行体の位置(y座標)
  Coordinate() : radius(0.0f), arg(0.0f), x(0.0f), y(0.0f) {}
  //! 走行体の位置情報を更新する
  void update(float distance, float angle);
  //! 走行体の位置情報を初期化する
  void reset();
};

class WheelOdometry {
 private:
  MotorAngle motor_angle;  // モータ角度の情報
  RobotProperty property;  // 走行体の情報
  Coordinate coordinate;   // 走行体の現在位置の情報

 public:
  WheelOdometry(float diameter = 99.0, float tread = 147.5, float cycle = 0.04)
    : motor_angle(), property(diameter, tread, cycle), coordinate()
  {
  }
  //! 走行体の旋回速度を求める
  float velocity(std::int32_t left_motor, std::int32_t right_motor);
  //! 走行体の旋回角速度を求める
  float angularVelocity(std::int32_t left_motor, std::int32_t right_motor);
  //! 走行体の位置情報を初期化する
  Coordinate& reset();
  //! 走行体の位置情報を更新する
  Coordinate& update(std::int32_t left_motor, std::int32_t right_motor);
  //! 走行体の回転角度を返す
  float getRotationAngle(std::int32_t left_motor, std::int32_t right_motor);
  //! 走行体の位置情報を返す
  Coordinate& getCoordinate();
  //! 走行体の位置x座標を返す
  float getPointX();
  //! 走行体の位置y座標を返す
  float getPointY();
};

#endif
