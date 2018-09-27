/**
 * @file LeftNormalCourse.cpp
 * @brief LeftNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse() : isChangedEdge(false), time_count(0)
{
  lineTracerWalker.isLeftsideLine(true);
  status = old_status = LeftStatus::STRAIGHT;
}

bool LeftNormalCourse::runNormalCourse(int32_t countL, int32_t countR, int16_t light_value,
                                       int16_t target_brightness)
{
  switch(status) {    
    case LeftStatus::STRAIGHT:
      lineTracerWalker.speedControl.setPid(8.0, 1.0, 0.1, 200.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::EDGE_CHANGE:
      lineTracerWalker.speedControl.setPid(4.5, 0.01, 0.12, 160.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::SECOND_CURVE:
      lineTracerWalker.speedControl.setPid(2.0, 0.5, 0.6, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.01, 0.12, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);      
      break;

    case LeftStatus::EDGE_RESET:
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);      
      break;

    case LeftStatus::THIRD_CURVE:
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 150.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness - 10);
      break;

    case LeftStatus::STRAIGHT_THIRD:
      lineTracerWalker.speedControl.setPid(8.0, 1.0, 0.1, 160.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness - 10);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;
    
    case LeftStatus::START:
      lineTracerWalker.speedControl.setPid(1.5, 0.01, 0.12, 170.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::STOP:
      stop();
      break;
    default:
      stop();
  }
  if(status == LeftStatus::STOP) return false;
  return true;
}

bool LeftNormalCourse::statusCheck(int32_t countL, int32_t countR)
{
  distanse_total = distance.getDistanceTotal(countL, countR);
  old_status = status;
  if(distanse_total < CALIBRATE_DISTANCE_L)
    status = LeftStatus::START;
  else if(distanse_total < FIRST_STRAIGHT_DISTANCE_L)
    status = LeftStatus::STRAIGHT;
  else if(distanse_total < FIRST_CURVE_DISTANCE_L)
    status = LeftStatus::EDGE_CHANGE;
  else if(distanse_total < SECOND_STRAIGHT_DISTANCE_L)
    status = LeftStatus::STRAIGHT;
  else if(distanse_total < SECOND_CURVE_DISTANCE_L)
    status = LeftStatus::SECOND_CURVE;
  else if(distanse_total < THIRD_STRAIGHT_DISTANCE_L)
    status = LeftStatus::STRAIGHT_THIRD;
  else if(distanse_total < THIRD_CURVE_DISTANCE_L)
    status = LeftStatus::EDGE_RESET;
  else if(distanse_total < FOURTH_STRAIGHT_DISTANCE_L)
    status = LeftStatus::STRAIGHT;
  else
    status = LeftStatus::STOP;
  if(isChangedEdge) {
    status = LeftStatus::STOP;
  }
  if(old_status != status) return true;
  return false;
}

int LeftNormalCourse::getStatus()
{
  return (int)status;
}