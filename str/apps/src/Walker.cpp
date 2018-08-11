#include "Walker.h"

void Walker::init()
{
  // init_f("Walker");
}

void Walker::terminate()
{
  worker.printDisplay(1, "Stopped.");
  worker.leftWheel.stop();
  worker.rightWheel.stop();
}

void Walker::reset()
{
  worker.leftWheel.reset();
  worker.rightWheel.reset();
}

void Walker::stop()
{
  run(0, 0);

  worker.printDisplay(1, "stopping...");
  worker.leftWheel.reset();
  worker.rightWheel.reset();
}

void Walker::run(std::int8_t pwm, std::int8_t turn)
{
  worker.printDisplay(1, "running...");
  setBrakeMotor(false);
  /* left = p-t, right = p+t -> 右 */
  /* left = p+t, right = p-t -> 左 */
  // pwmは int型の -100 ~ 100
  worker.leftWheel.setPWM(pwm - turn);
  worker.rightWheel.setPWM(pwm + turn);
}

void Walker::setBrakeMotor(bool brake)
{
  // 0でフロート
  // 1でブレーク
  worker.leftWheel.setBrake(brake);
  worker.rightWheel.setBrake(brake);
}

std::int32_t Walker::get_count_L()
{
  return worker.leftWheel.getCount();
}

std::int32_t Walker::get_count_R()
{
  return worker.rightWheel.getCount();
}

int Walker::edgeChange()
{
  if(leftRight == 1) {
    run(10, 5);
    worker.clock.sleep(10);
    leftRight = -1;
  } else {
    run(10, 5);
    worker.clock.sleep(10);
    leftRight = 1;
  }

  return leftRight;
}

/*
 * 車輪の回転角分だけ進む
 */
void Walker::moveAngle(std::int8_t pwm, int angle)
{
  worker.leftWheel.reset();
  worker.rightWheel.reset();

  worker.leftWheel.setPWM(pwm);
  worker.rightWheel.setPWM(pwm);

  while(1) {
    if(worker.leftWheel.getCount() >= angle && worker.rightWheel.getCount() >= angle) break;
    worker.clock.sleep(4);
  }

  worker.leftWheel.reset();
  worker.rightWheel.reset();
}

/*
 * 主機能:45度単位で回転
 * rotation = 1 -> 反時計回り, rotation = -1 -> 時計回り
 *
 * beta機能:5度単位で回転
 * 精度はあまりよろしくない
 */
void Walker::angleChange(int angle, int rotation)
{
  int32_t defaultAngleL;
  int8_t dAngle = 75;  // 45度におけるモーター回転数（床材によって変わる？）

  if(rotation >= 0) {
    if(leftRight == 1) {
      rotation = 1;
    } else {
      rotation = -1;
    }
  } else {
    if(leftRight == 1) {
      rotation = -1;
    } else {
      rotation = 1;
    }
  }

  /*
   * 本来は45度単位だから、angleは45で割る
   * ベータ機能として5度単位でも曲がれるようにしている
   * そのため、もしangleが5度単位である場合はdAngleを9分割する
   */
  if(angle % 5 == 0 && angle % 45 != 0) {
    dAngle = 8;
    angle /= 5;
  } else {
    angle -= angle % 45;
    angle /= 45;
  }

  defaultAngleL = worker.leftWheel.getCount();

  while(1) {
    run(0, 10 * rotation);
    if(rotation >= 0) {
      if(worker.leftWheel.getCount() - defaultAngleL < -dAngle * angle * rotation
         || worker.leftWheel.getCount() - defaultAngleL > dAngle * angle * rotation) {
        break;
      }
    } else {
      if(worker.leftWheel.getCount() - defaultAngleL > -dAngle * angle * rotation
         || worker.leftWheel.getCount() - defaultAngleL < dAngle * angle * rotation) {
        break;
      }
    }
    worker.clock.sleep(4);
  }
  stop();
}
