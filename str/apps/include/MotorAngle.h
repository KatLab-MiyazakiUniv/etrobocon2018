/**
 *  @file MotorAngle.h
 *  @brief 左右モータの回転角に関するクラス(旧Distance.h, SelfLocalization内のMotorAngle)
 *  @author T.Miyaji, Futa HIRAKOBA
 */
#ifndef MOTOR_ANGLE_H
#define MOTOR_ANGLE_H
#include <cstdint>

class MotorAngle {
 private:
  std::int32_t pre_left_motor;   //! 左モータ角度の過去値
  std::int32_t pre_right_motor;  //! 右モータ角度の過去値

 public:
  MotorAngle() : pre_left_motor(0), pre_right_motor(0) {}
  //! 左右モータ角度の過去値を現在値へ更新する
  void update(std::int32_t left_motor, std::int32_t right_motor);
  //! 左右モータ角度の過去値を0にリセットする
  void reset();
  //! 左右モータの絶対角度の平均値を計算する
  float absoluteAngleMean(std::int32_t left_motor, std::int32_t right_motor);
  //! 左右モータの相対角度の平均値を計算する
  float relativeAngleMean(std::int32_t current_left_motor, std::int32_t current_right_motor);
  //! 左右モータ角度の差を計算する(右手系/反時計回りが正)
  float angularDifference(std::int32_t left_motor, std::int32_t right_motor);
  //! モータ角度の絶対値を計算する
  std::int32_t absoluteValueOfAngle(std::int32_t motor);
};

#endif
