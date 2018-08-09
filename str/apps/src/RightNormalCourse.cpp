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
bool RightNormalCourse::runNormalCourse(int16_t target_brightness){
    switch(status){
        case RightStatus::STRAIGHT:
            lineTracerWalker.speedControl.setPid(17.0, 1.0, 0.1, 200.0);
            lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);       
            break;

        case RightStatus::SLOW:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.14, target_brightness - 5.0);
            break;
        
        case RightStatus::CURVE_RIGHT:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.1, 130.0 );
            lineTracerWalker.turnControl.setPid ( 1.8, 1.0, 0.08, target_brightness - 5.0);
            break;


        case RightStatus::MIDDLE_SPEED:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.12, 150.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.1, target_brightness );
            break;

        case RightStatus::SLOW_DOWN:
          lineTracerWalker.speedControl.setPid ( 10.0, 1.0, 0.1, 150.0 );
          lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.1, target_brightness );
          break;

        /**/
        case RightStatus::CURVE_LEFT_SHORT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 110.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, target_brightness - 5.0 );
            break;

        case RightStatus::CURVE_LEFT_SHORT_SLOW: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 40.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, target_brightness - 5.0 );
            break;

        case RightStatus::CURVE_LEFT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, target_brightness - 5.0 );
            break;
        
        case RightStatus::ACCELERATE:
            lineTracerWalker.speedControl.setPid ( 12.0, 5.0, 0.1, 200.0 );
            lineTracerWalker.turnControl.setPid ( 9.0, 4.0, 2.0, target_brightness);
            break;
        
        case RightStatus::STOP: stop(); break;
        default: stop();
    }
    if (status == RightStatus::STOP) return false;
    return true;
}

bool RightNormalCourse::statusCheck(int32_t countL, int32_t countR){
    distanse_total = distance.getDistanceTotal(countL, countR);
    old_status = status;
    if(distanse_total < 2500)status = RightStatus::STRAIGHT;
    else if(distanse_total < 4495)status = RightStatus::MIDDLE_SPEED;
    else if(distanse_total < 5256)status = RightStatus::STRAIGHT;
    else if(distanse_total < 5855)status = RightStatus::SLOW;
    else if(distanse_total < 6542)status = RightStatus::CURVE_RIGHT;
    else if (distanse_total < 7334)status = RightStatus::STRAIGHT;
    else if(distanse_total < 8576)status = RightStatus::SLOW;
    else if(distanse_total < 11710)status = RightStatus::STRAIGHT;
    else status = RightStatus::STOP;
    if(old_status != status) return true;
    return false;
}

int RightNormalCourse::getStatus()
{
  return (int)status;
}