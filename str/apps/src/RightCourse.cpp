/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"
#include "Distinguisher.h"
#include "BasicWalker.h"
#include "Lifter.h"
#include "LineTracerWalker.h"


/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::run(int16_t brightness, int16_t black, int16_t white)
{
  LineTracerWalker lineTracer;
  runFirst(brightness);
 // runNormalCourse(brightness);
  runPuzzle(brightness);
//runParking(brightness, lineTracer, black, white);
}

void RightCourse::runParking(int16_t brightness, LineTracerWalker lineTracer, int16_t black,
                             int16_t white)
{
  Parking parking{ controller };
  parking.runParpendicular(brightness, lineTracer, black, white);
}

void RightCourse::runFirst(int16_t target_brightness){
  Controller controller;
  Distinguisher d{controller};
  BasicWalker basic{controller};
  Lifter lifter{controller};
  LineTracerWalker lineTracerWalker;
  Distance distance;
  bool isAlreadyChangedGear = false;

  lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 90.0);
  lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.14, target_brightness);  
  walker.reset();
  while(1){
    Color result=d.getColor();      
    auto luminance = controller.getBrightness();
    lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
    walker.run(lineTracerWalker.getForward(), lineTracerWalker.getTurn());
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, result);
    if(result==Color::RED)  break;
    if(!isAlreadyChangedGear && distance.getDistanceTotal(walker.get_count_L(), walker.get_count_R())>1750){
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 35.0);
      lineTracerWalker.turnControl.setPid(2.0, 1.0, 0.14, target_brightness);
      controller.speakerPlayTone(controller.noteFs6, 100);
      isAlreadyChangedGear = true;
    }
    controller.tslpTsk(4);
  }
}

void RightCourse::runPuzzle(int16_t target_brightness){
  Controller controller;
  Distinguisher d{controller};
  BasicWalker basic{controller};
  Lifter lifter{controller};
  LineTracerWalker lineTracerWalker;

  lineTracerWalker.speedControl.setPid(2.0, 0.8, 0.8, 60.0);
  lineTracerWalker.turnControl.setPid(2.0, 1.5, 1.0, target_brightness);  

  walker.reset();
  while(1){
    Color result=d.getColor();      
    auto luminance = controller.getBrightness();
    lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
    walker.run(lineTracerWalker.getForward(), lineTracerWalker.getTurn());
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, result);
    controller.printDisplay(6, "out the loop, Color: %d", static_cast<int>(result));
    if(result==Color::RED){
      controller.printDisplay(6, "in the loop, Color: %d", static_cast<int>(result));
      controller.speakerPlayTone(controller.noteFs4, 100);
      basic.reset();
      basic.setPidWithoutTarget(6.5, 0.5, 1.0);
      basic.backStraight(15, 45);
      lifter.liftUp(45, 10);
      lifter.liftDown(0, 3);
      lifter.liftUp(2.5);
      basic.reset();
      basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
      basic.goStraight(15, 180);
    }//L82R74//
    if(result==Color::YELLOW){
      controller.printDisplay(6, "in the loop, Color: %d", static_cast<int>(result));
      controller.speakerPlayTone(controller.noteFs4, 100);
      basic.reset();
      basic.setPidWithoutTarget(6.5, 0.5, 1.0);
      basic.backStraight(15, 45);
      basic.reset();
      basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
      basic.goStraight(15, 210);
      basic.spin(basic.SPIN_RIGHT, 85, 10);
      basic.goStraight(15, 90); 
      basic.spin(basic.SPIN_RIGHT, 78, 10);
      //while(result!=Color::BLACK){
        basic.goStraight(15, 320);
     // }
    } 
    if(result==Color::BLUE){
      //Right
      controller.speakerPlayTone(controller.noteFs4, 100);
      break;
      basic.reset();
      basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
      basic.goStraight(15, 130);
      basic.spin(basic.SPIN_RIGHT, 74,10);
      basic.goStraight(15, 50);
    }
    if(result==Color::GREEN){
      controller.speakerPlayTone(controller.noteFs6, 100);
      //Left
            break;
      basic.reset();
      basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
      basic.goStraight(15, 130);
      basic.spin(basic.SPIN_LEFT, 82,10);
      basic.goStraight(15, 50);
    }

  }
  controller.tslpTsk(4);
}


void RightCourse::runNormalCourse(int16_t brightness)
{
  RightNormalCourse normalCourse;
  bool isNormalCourse;

  // NormalCourseを抜けるまでループする
  while(1) {
    sl.update(walker.get_count_L(), walker.get_count_R());
    auto luminance = controller.getBrightness();
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, brightness);
    if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
      controller.speakerPlayTone(controller.noteFs6, 100);
    isNormalCourse = normalCourse.runNormalCourse(brightness);
    normalCourse.lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);

    normalCourse.runOrStop(walker);
    if(!isNormalCourse) {
      walker.run(0, 0);
      break;
    }
    if(controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }

    controller.tslpTsk(4);  // 4msec周期起動
  }
}
