/**
 * @file LeftNormalCourse.cpp
 * @brief LeftNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
 
#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse():
    isChangedEdge(false),
    time_count(0){
    lineTracerWalker.isLeftsideLine(true);
    status = old_status = LeftStatus::STRAIGHT;
}

bool LeftNormalCourse::runNormalCourse(int32_t countL, int32_t countR, int8_t light_value, int8_t target_brightness){
    switch(status){
        case LeftStatus::STRAIGHT: 
            lineTracerWalker.speedControl.setPid ( 2.0, 4.8, 0.024, 180.0 );
            lineTracerWalker.turnControl.setPid ( 3.0, 1.0, 0.5, target_brightness );
            lineTracerWalker.runLine(countL, countR, light_value);
            break;

        case LeftStatus::STRAIGHT_SLOW: 
            lineTracerWalker.speedControl.setPid ( 2.0, 2.0, 0.024, 0.0 );
            lineTracerWalker.turnControl.setPid ( 3.0, 1.0, 0.5, target_brightness );
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::NEUTRAL:
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.08, 70.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.048, target_brightness - 5.0 );
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::EDGE_CHANGE:
            lineTracerWalker.setForward(15);
            lineTracerWalker.setTurn(-2);
            lineTracerWalker.isLeftsideLine(false);
            time_count++;
            if(light_value > CENTER_BRIGHTNESS && time_count > 125) isChangedEdge = true;
            break;

        case LeftStatus::EDGE_RESET:
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.08, 10.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.048, target_brightness - 5.0 );
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::CURVE_RIGHT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.08, 80.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.1, target_brightness + 5.0 );
            //lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::CURVE_LEFT_SHORT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, target_brightness - 5.0 );
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::CURVE_LEFT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, target_brightness - 5.0 ); 
            lineTracerWalker.runLine(countL, countR, light_value);            
            break;

        case LeftStatus::STOP: stop(); break;
        default: stop();
    }
    if (status == LeftStatus::STOP) return false;
    return true;
}

bool LeftNormalCourse::statusCheck(int32_t countL, int32_t countR){
    distanse_total = distance.getDistanceTotal(countL, countR);
    old_status = status;
    if(distanse_total < 3000)status = LeftStatus::STRAIGHT_SLOW;
    else if(distanse_total < 4000)status = LeftStatus::STRAIGHT_SLOW;
    else if(distanse_total < 5200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 7500)status = LeftStatus::CURVE_LEFT_SHORT;
    else if(distanse_total < 11000)status = LeftStatus::CURVE_LEFT;
    else if(distanse_total < 12200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 14750)status = LeftStatus::NEUTRAL;
    else status = LeftStatus::EDGE_CHANGE;
    if(isChangedEdge){
        status = LeftStatus::STOP;
    }
    if(old_status != status) return true;
    return false;
}

int LeftNormalCourse::getStatus(){
    return (int)status;
}