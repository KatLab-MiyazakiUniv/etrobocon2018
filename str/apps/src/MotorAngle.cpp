/**
 *  @file MotorAngle.cpp
 *  @brief 左右モータの回転角に関するクラス
 *  @author T.Miyaji, Futa HIRAKOBA
 */
#include "MotorAngle.h"

/**
 *  [MotorAngle::update]
 *  @brief MotorAngleメンバ変数のpre_left_motorとpre_right_motorの値を現在値に更新する
 *  @param  current_left_motor  左モータ角度の現在値
 *  @param  current_right_motor 右モータ角度の現在値
 */
void MotorAngle::update(std::int32_t current_left_motor, std::int32_t current_right_motor)
{
  // 左モータ角度の過去値を更新
  pre_left_motor = current_left_motor;
  // 右モータ角度の過去値を更新
  pre_right_motor = current_right_motor;
}

/**
 *  [MotorAngle::filterMotorNoise]
 *  @brief 左右モータの角度にローパスフィルタを通す
 *  @param  current_left_motor  左モータ角度の現在値
 *  @param  current_right_motor 右モータ角度の現在値
 */
void MotorAngle::filterMotorNoise(std::int32_t& current_left_motor,
                                  std::int32_t& current_right_motor)
{
  current_left_motor = left_filter.sensor(current_left_motor);
  current_right_motor = right_filter.sensor(current_right_motor);
}

/**
 *  [MotorAngle::reset]
 *  @brief 左モータと右モータの角度の過去値を0にリセットする
 */
void MotorAngle::reset()
{
  pre_left_motor = 0;
  pre_right_motor = 0;
}

/**
 *  [MotorAngle::absoluteAngleMean]
 *  @brief 左モータと右モータの絶対角度の平均値を計算する
 *  @param  current_left_motor  左モータ角度の現在値
 *  @param  current_right_motor 右モータ角度の現在値
 *  @param  filter              フィルタ処理をするかどうか
 *  @return 左右モータの絶対角度の平均値
 */
float MotorAngle::absoluteAngleMean(std::int32_t current_left_motor,
                                    std::int32_t current_right_motor, bool filter)
{
  if(filter == true) filterMotorNoise(current_left_motor, current_right_motor);
  return (current_left_motor + current_right_motor) / 2.0f;
}

/**
 *  [MotorAngle::relativeAngleMean]
 *  @brief 左モータと右モータの相対角度の平均値を計算する
 *  @param  current_left_motor  左モータ角度の現在値
 *  @param  current_right_motor 右モータ角度の現在値
 *  @param  filter              フィルタ処理をするかどうか
 *  @return 左右モータの相対角度の平均値
 */
float MotorAngle::relativeAngleMean(std::int32_t current_left_motor,
                                    std::int32_t current_right_motor, bool filter)
{
  if(filter == true) filterMotorNoise(current_left_motor, current_right_motor);
  // 左モータの相対角度を求める
  std::int32_t left_motor = current_left_motor - pre_left_motor;
  // 右モータの相対角度を求める
  std::int32_t right_motor = current_right_motor - pre_right_motor;

  // 左右モータの過去値を現在値に更新
  update(current_left_motor, current_right_motor);

  return (left_motor + right_motor) / 2.0f;
}

/**
 *  [MotorAngle::angularDifference]
 *  @brief 左右モータの回転角の差を計算する(右手系/反時計回りが正)
 *  @param  current_left_motor  左モータ角度の現在値
 *  @param  current_right_motor 右モータ角度の現在値
 *  @return 左右モータの絶対角度の差
 */
float MotorAngle::angularDifference(std::int32_t current_left_motor,
                                    std::int32_t current_right_motor, bool filter)
{
  if(filter == true) filterMotorNoise(current_left_motor, current_right_motor);

  return current_right_motor - current_left_motor;
}

/**
 *  [MotorAngle::absoluteValueOfAngle]
 *  @brief モータ角度の絶対値を計算する
 *  @param  モータ角度
 *  @return モータ角度の絶対値
 */
std::int32_t MotorAngle::absoluteValueOfAngle(std::int32_t motor)
{
  return (motor > 0) ? motor : -motor;
}
