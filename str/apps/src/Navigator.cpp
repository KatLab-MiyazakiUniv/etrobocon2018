/**
 *  @file Navigator.cpp
 *  @brief 走行制御と回転制御を実行するクラス
 *  @author T.Miyaji
 */
#include "Navigator.h"

void Navigator::reset()
{
  walker.reset();
  odometry.reset();
}

void Navigator::spin(float angle, std::int8_t pwm, bool clockwise)
{
  // 測定角度の初期化
  reset();

  while(odometry.getRotationAngle(walker.get_count_L(), walker.get_count_R()) < angle){
    // 時計回りのときは-pwmを渡す
    walker.run(0, clockwise ? -pwm : pwm);
  }

  // 回転停止
  walker.run(0, 0);
  reset();
}

void Navigator::move(float distance, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();

  while(odometry.update(walker.get_count_L(), walker.get_count_R()).radius < distance){
    walker.run(pwm, 0);
  }

  // 移動停止
  walker.run(0, 0);
  reset();
}

void Navigator::moveWhileDetecting(float distance, std::int8_t pwm)
{
  // 測定距離の初期化
  reset();
  while(odometry.update(walker.get_count_L(), walker.get_count_R()).radius < distance){
    walker.run(pwm, 0);
    if(binarization() == false)  controller.speakerPlayTone(controller.noteFs4, 100);
  }

  walker.run(0, 0);
  reset();
}

std::int16_t Navigator::getBrightness()
{
  return controller.getBrightness();
}

std::int8_t Navigator::getNearbyBrightness(float distance)
{
  auto center = getBrightness();

  // distanceだけ前に移動した点のセンサ値を取る
  move(distance);
  auto front = getBrightness();
  move(-distance);

  // distanceだけ後ろに移動した点のセンサ値を取る
  move(-distance);
  auto back = getBrightness();
  move(distance);

  return std::min({front, center, back});
}

bool Navigator::binarization()
{
  auto brightness = getBrightness();
  return (brightness < 13)? false : true;
}
