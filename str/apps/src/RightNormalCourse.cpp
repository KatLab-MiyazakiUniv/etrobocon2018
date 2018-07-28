/**
 * @file RightNormalCourse.cpp
 * @brief RightNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse(){
    lineTracerWalker.isLeftsideLine(true);
    status = old_status = RightStatus::STRAIGHT;
}

bool RightNormalCourse::runNormalCourse(){
    switch(status){
        case RightStatus::STRAIGHT:
            lineTracerWalker.speedControl.setPid ( 17.0, 1.0, 0.1, 180.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 1.0, 0.8, CENTER_BRIGHTNESS );
            break;
        
        case RightStatus::SLOW:
            lineTracerWalker.speedControl.setPid ( 6.0, 1.0, 0.5, 110.0 );
            lineTracerWalker.turnControl.setPid ( 3.0, 1.0, 1.5, CENTER_BRIGHTNESS );
            break;

        case RightStatus::CURVE_RIGHT:
            lineTracerWalker.speedControl.setPid ( 2.0, 0.5, 1.2, 110.0 );
            lineTracerWalker.turnControl.setPid ( 10.0, 0.5, 1.5, CENTER_BRIGHTNESS );
            break;

        case RightStatus::CURVE_LEFT_SHORT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 110.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, CENTER_BRIGHTNESS - 5.0 );
            break;
        case RightStatus::CURVE_LEFT_SHORT_SLOW: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 30.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, CENTER_BRIGHTNESS - 5.0 );
            break;
        case RightStatus::CURVE_LEFT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, CENTER_BRIGHTNESS - 5.0 );
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
    if(distanse_total < 2850)status = RightStatus::STRAIGHT;
    else if(distanse_total < 4750)status = RightStatus::SLOW;
    else if(distanse_total < 6600)status = RightStatus::STRAIGHT;
    else if(distanse_total < 7400)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 8100)status = RightStatus::STRAIGHT;
    else if(distanse_total < 9000)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 12000)status = RightStatus::STRAIGHT;
 
    //else if(distanse_total < 17000)status = RightStatus::SLOW;
    
    else status = RightStatus::STOP;
    if(old_status != status) return true;
    return false;
}

int RightNormalCourse::getStatus(){
    return (int)status;
}