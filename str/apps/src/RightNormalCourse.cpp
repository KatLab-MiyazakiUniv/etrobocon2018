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
        case RightStatus::R1:
            lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 200.0);
            lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);       
            break;
        
        case RightStatus::R2:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.12, 150.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.1, target_brightness );
            break;

        case RightStatus::R3:
            lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 200.0);
            lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);       
            break;

        case RightStatus::R4:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.14, target_brightness);
            break;

        case RightStatus::R5:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 2.4, 1.0, 0.14, target_brightness - 5.0);
            break;

        case RightStatus::R6:
            lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 200.0);
            lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);       
            break;

        case RightStatus::R7:
            lineTracerWalker.speedControl.setPid ( 2.0, 1.0, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 1.9, 0.8, 0.1, target_brightness);
            break;

        case RightStatus::R8:
            lineTracerWalker.speedControl.setPid(10.0, 1.0, 0.1, 200.0);
            lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.1, target_brightness);       
            break;

        case RightStatus::R9:
            lineTracerWalker.speedControl.setPid ( 10.0, 1.0, 0.12, 80.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.1, target_brightness );
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
    if(distanse_total < 2500)status = RightStatus::R1;
    else if(distanse_total < 4495)status = RightStatus::R2;
    else if(distanse_total < 5256)status = RightStatus::R3;
    else if(distanse_total < 5840)status = RightStatus::R4;
    else if(distanse_total < 6542)status = RightStatus::R5;
    else if (distanse_total < 7280)status = RightStatus::R6;
    else if(distanse_total < 8590)status = RightStatus::R7;
    else if(distanse_total < 11740)status = RightStatus::R8;
    else if(distanse_total < 12500)status = RightStatus::R9;

    else status = RightStatus::STOP;
    if(old_status != status) return true;
    return false;
}

int RightNormalCourse::getStatus()
{
  return (int)status;
}