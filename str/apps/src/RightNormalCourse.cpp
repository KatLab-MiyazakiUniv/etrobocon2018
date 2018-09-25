/**
 * @file RightNormalCourse.cpp
 * @brief RightNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse()
{
  lineTracerWalker.isLeftsideLine(true);
  status = old_status = RightStatus::STRAIGHT_LONG;
}

/*
 *ここの値を変更して色々調整する（微分が一番重要、積分も入れないとズレていく！？）
 * マイナス値は入れないほうがいい
 *lineTracerWalker.speedControl.setPid ( 2.0, 4.8, 0.024, 速度mm/s );
 */
bool RightNormalCourse::runNormalCourse(int16_t target_brightness)
{
  switch(status) {
    case RightStatus::STRAIGHT_LONG:
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(1.9, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::STRAIGHT_SHORT:
      lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::CURVE_INSIDE_LONG:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::CURVE_INSIDE_SHORT:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::SLOW_DOWN:
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 80.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::TEST0:
      lineTracerWalker.speedControl.setPid(3.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::TEST1:
      lineTracerWalker.speedControl.setPid(2.0, 1.0, 0.12, 120.0);
      lineTracerWalker.turnControl.setPid(2.5, 0.001, 0.27, target_brightness);
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
  
  /*
  if(distanse_total < 2500)
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < 4495)
    status = RightStatus::CURVE_INSIDE_LONG;
  else if(distanse_total < 5056)
    status = RightStatus::STRAIGHT_SHORT;
  else if(distanse_total < 5640)
    status = RightStatus::CURVE_INSIDE_SHORT;
  else if(distanse_total < 6542)
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < 7180)
    status = RightStatus::STRAIGHT_SHORT;
  else if(distanse_total < 8640)
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < 11540)
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < 12430)//ちょうどいい感じ
  //else if(distanse_total < 12630)//灰色を完全に通過
    status = RightStatus::CURVE_INSIDE_SHORT;
  */
   if(distanse_total < 750)
     status = RightStatus::SLOW_DOWN;
   else if(distanse_total < 2250)
     status = RightStatus::SLOW_DOWN;
  else
    status = RightStatus::STOP;
  if(old_status != status) return true;
  return false;
}

int RightNormalCourse::getStatus()
{
  return (int)status;
}
