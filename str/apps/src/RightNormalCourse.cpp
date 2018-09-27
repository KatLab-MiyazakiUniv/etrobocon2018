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
bool RightNormalCourse::runNormalCourse(int16_t target_brightness, int16_t black, int16_t white, int16_t gray)
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
    
    case RightStatus::TRANSFER_ZONE:
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.12, 80.0);
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
  
  if(distanse_total < CALIBRATE_DISTANCE_R)
    status = RightStatus::START;
  else if(distanse_total < FIRST_STRAIGHT_DISTANCE_R)
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < FIRST_CURVE_DISTANCE_R)
    status = RightStatus::CURVE_INSIDE_LONG;
  else if(distanse_total < SECOND_STRAIGHT_DISTANCE_R)
    status = RightStatus::STRAIGHT_SHORT;
  else if(distanse_total < SECOND_CURVE_DISTANCE_IN_R)
    status = RightStatus::CURVE_INSIDE_SHORT;
  else if(distanse_total < SECOND_CURVE_DISTANCE_OUT_R)
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < THIRD_STRAIGHT_DISTANCE_R)
    status = RightStatus::SLOW;
  else if(distanse_total < THIRD_CURVE_DISTANCE_R)
    status = RightStatus::CURVE_OUTSIDE;
  else if(distanse_total < FOURTH_STRAIGHT_DISTANCE_R)
    status = RightStatus::STRAIGHT_LONG;
  else if(distanse_total < AFTER_GOAL_CURVE_R)
  //else if(distanse_total < 12630)//灰色を完全に通過
    status = RightStatus::TRANSFER_ZONE;
  else
    status = RightStatus::STOP;
  if(old_status != status) return true;
  return false;
}

int RightNormalCourse::getStatus()
{
  return (int)status;
}
