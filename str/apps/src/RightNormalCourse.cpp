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
      lineTracerWalker.speedControl.setPid(8.0, 1.0, 0.1, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      //lineTracerWalker.turnControl.setPid(0.49999, 0.0, 0.0, target_brightness);
      break;

    case RightStatus::STRAIGHT_SHORT:
      lineTracerWalker.speedControl.setPid(2.4, 1.0, 0.1, 180.0);
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

    case RightStatus::CURVE_OUTSIDE:
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::SLOW:
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 165.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      break;

    case RightStatus::START:
      lineTracerWalker.speedControl.setPid(1.5, 0.01, 0.12, 170.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
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
  
  if(distanse_total < 200)                  //Part 1
    status = RightStatus::START;
  else if(distanse_total < 2500)            //Part 1
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < 4495)            //Part 2
    status = RightStatus::CURVE_INSIDE_LONG;
  else if(distanse_total < 5056)            //Part 3
    status = RightStatus::STRAIGHT_SHORT;
  else if(distanse_total < 5640)            //Part 4
    status = RightStatus::CURVE_INSIDE_SHORT;
  else if(distanse_total < 6542)            //Part 5
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < 7100)            //Part 6
    status = RightStatus::SLOW;
  else if(distanse_total < 8680)            //Part 7
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < 11540)           //Part 8
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < 12430)           //Part 9, goal to gray line
  //else if(distanse_total < 12630)//灰色を完全に通過
    status = RightStatus::CURVE_INSIDE_SHORT;
  
  /*
   if(distanse_total < 750)
     status = RightStatus::SLOW_DOWN;
   else if(distanse_total < 2250)
     status = RightStatus::SLOW_DOWN;
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
