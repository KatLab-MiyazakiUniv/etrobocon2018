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
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::EDGE_RESET:
      lineTracerWalker.speedControl.setPid(2.5, 0.01, 0.12, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);      
      break;

    case LeftStatus::SLOW1:
      lineTracerWalker.speedControl.setPid(5.5, 0.01, 0.12, 180.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
      lineTracerWalker.runLine(countL, countR, light_value);
      break;

    case LeftStatus::SLOW2:
      lineTracerWalker.speedControl.setPid(5.5, 0.01, 0.12, 165.0);
      lineTracerWalker.turnControl.setPid(2.0, 0.1, 0.1, target_brightness);
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
  if(distanse_total < 200)
    status = LeftStatus::START;
  else if(distanse_total < 2850)
    status = LeftStatus::STRAIGHT;
  /*
  else if(distanse_total < 2650)        //^^^ Part 1
    status = LeftStatus::SLOW1;
  else if(distanse_total < 2850)        //^^^ Part 1
    status = LeftStatus::SLOW2;
  */

  else if(distanse_total < 4950)        //^^^ Part 2
    status = LeftStatus::EDGE_CHANGE;

  /*
  else if(distanse_total < 5200)        //^^^ Part 3        
    status = LeftStatus::SLOW1;
  */
  else if(distanse_total < 6600)
    status = LeftStatus::STRAIGHT;
  /*
  else if(distanse_total < 6400)
    status = LeftStatus::SLOW1;
  else if(distanse_total < 6600)
    status = LeftStatus::SLOW2;
  */
  else if(distanse_total < 7500)
    status = LeftStatus::EDGE_RESET;    //^^^ Part 4

  /*
  else if(distanse_total < 7600)
    status = LeftStatus::SLOW2;
  else if(distanse_total < 7750)
    status = LeftStatus::SLOW1;
  */
  else if(distanse_total < 8100)        //^^^ Part 5
    status = LeftStatus::STRAIGHT;
  /*
  else if(distanse_total < 7900)
    status = LeftStatus::SLOW1;
  else if(distanse_total < 8100)
    status = LeftStatus::SLOW2;
  */

  else if(distanse_total < 9000)
    status = LeftStatus::EDGE_RESET;    //^^^ Part 6

  /*
  else if(distanse_total < 9200)        //^^^ Part 7
    status = LeftStatus::SLOW2;
  */
  else if(distanse_total < 12000)
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