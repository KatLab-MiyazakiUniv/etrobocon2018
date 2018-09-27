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

    case LeftStatus::START:
       lineTracerWalker.speedControl.setPid(1.5, 0.01, 0.12, 170.0);
       lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
       lineTracerWalker.runLine(countL, countR, light_value);
       break;

    case LeftStatus::STRAIGHT:
      lineTracerWalker.speedControl.setPid(8.0, 1.0, 0.1, 200.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::EDGE_CHANGE:
      lineTracerWalker.speedControl.setPid(3.5, 0.01, 0.12, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::EDGE_RESET:
      lineTracerWalker.speedControl.setPid(2.0, 0.5, 0.6, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.01, 0.12, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::CURVE_LEFT:
      lineTracerWalker.speedControl.setPid(2.0, 0.5, 0.6, 180.0);
      lineTracerWalker.turnControl.setPid(5.0, 0.05, 0.5, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;
    /*
    case LeftStatus::STRAIGHT_SLOW:
      lineTracerWalker.setForward(15);
      lineTracerWalker.setTurn(-2);
      lineTracerWalker.isLeftsideLine(false);
      time_count++;
      if(light_value > target_brightness && time_count > 125) isChangedEdge = true;
      break;

    case LeftStatus::NEUTRAL:
      lineTracerWalker.speedControl.setPid(4.0, 0.2, 0.08, 100.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.048, target_brightness - 5.0);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::CURVE_RIGHT:
      lineTracerWalker.speedControl.setPid(4.0, 0.8, 0.08, 10.0);
      lineTracerWalker.turnControl.setPid(4.0, 2.0, 0.1, target_brightness + 5.0);
      // lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::CURVE_LEFT_SHORT:
      lineTracerWalker.speedControl.setPid(4.0, 0.8, 0.1, 100.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.5, 0.048, target_brightness - 5.0);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::CURVE_LEFT:
      lineTracerWalker.speedControl.setPid(4.0, 0.8, 0.1, 100.0);
      lineTracerWalker.turnControl.setPid(4.0, 2.0, 0.096, target_brightness - 5.0);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;*/

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
  if(distanse_total < 300){
    status = LeftStatus::START;
  }else if(distanse_total < 2850)
    status = LeftStatus::STRAIGHT;
  else if(distanse_total < 4750)
    status = LeftStatus::EDGE_CHANGE;
  else if(distanse_total < 6600)
    status = LeftStatus::STRAIGHT;
  else if(distanse_total < 7400)
    status = LeftStatus::EDGE_RESET;
  else if(distanse_total < 8100)
    status = LeftStatus::STRAIGHT;
  else if(distanse_total < 9000)
    status = LeftStatus::CURVE_LEFT;
  else if(distanse_total < 13000)
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