/**
 * @file RightNormalCourse.cpp
 * @brief RightNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse()
{
  lineTracerWalker.isLeftsideLine(true);
  status = old_status = RightStatus::STRAIGHT;
}

/*
 *ここの値を変更して色々調整する（微分が一番重要、積分も入れないとズレていく！？）
 * マイナス値は入れないほうがいい
 *lineTracerWalker.speedControl.setPid ( 2.0, 4.8, 0.024, 速度mm/s );
 */
bool RightNormalCourse::runNormalCourse(int16_t target_brightness)
{
  switch(status) {
    case RightStatus::R1:
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      break;

    case RightStatus::R2:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      break;

    case RightStatus::R3:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      break;

    case RightStatus::R4:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      break;

    case RightStatus::R5:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(4.0, 0.001, 0.27, target_brightness);
      break;

    case RightStatus::R6:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.2, 0.1, target_brightness);
      break;

    case RightStatus::R7:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(3.28, 0.001, 0.27, target_brightness);
      break;

    case RightStatus::R8:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.2, 0.1, target_brightness);
      break;

    case RightStatus::R9:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.2, 1.0, 0.11, target_brightness);
      break;

    case RightStatus::TEST0:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 200.0);
      lineTracerWalker.turnControl.setPid(0.6, 0.0, 0.0, target_brightness);
      break;

    case RightStatus::TEST1:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.1, 100.0);
      lineTracerWalker.turnControl.setPid(1.6, 0.0, 0.1, target_brightness - 20.0);
      break;

    case RightStatus::STOP:
      stop();
      break;
    default:
      stop();
  }
  if(status == RightStatus::STOP) return false;
  return true;
}

bool RightNormalCourse::statusCheck(int32_t countL, int32_t countR)
{
  distanse_total = distance.getDistanceTotal(countL, countR);
  old_status = status;
  if(distanse_total < 2500)
    status = RightStatus::R1;
  else if(distanse_total < 4495)
    status = RightStatus::R2;
  else if(distanse_total < 5056)
    status = RightStatus::R3;
  else if(distanse_total < 5640)
    status = RightStatus::R4;
  else if(distanse_total < 6542)
    status = RightStatus::R5;
  else if(distanse_total < 7180)
    status = RightStatus::R6;
  else if(distanse_total < 8640)
    status = RightStatus::R7;
  else if(distanse_total < 11540)
    status = RightStatus::R8;
  else if(distanse_total < 12230)
    status = RightStatus::R9;
  /*
   if(distanse_total < 750)
     status = RightStatus::TEST0;
   else if(distanse_total < 2250)
     status = RightStatus::TEST1;
    */
  else
    status = RightStatus::STOP;
  if(old_status != status) return true;
  return false;
}

int RightNormalCourse::getStatus()
{
  return (int)status;
}
