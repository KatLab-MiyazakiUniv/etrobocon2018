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
  moveblockAreato8(brightness);
 // runNormalCourse(brightness);
//runParking(brightness, lineTracer, black, white);
}

void RightCourse::runParking(int16_t brightness, LineTracerWalker lineTracer, int16_t black,
                             int16_t white)
{
  Parking parking{ controller };
  parking.runParpendicular(brightness, lineTracer, black, white);
}

void RightCourse::moveblockAreato8(int16_t target_brightness){
  Controller controller;
  Distinguisher d{controller};
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
      lineTracerWalker.speedControl.setPid(5.0, 1.0, 0.1, 25.0);
      lineTracerWalker.turnControl.setPid(1.0, 1.0, 0.14, target_brightness);
      controller.speakerPlayTone(controller.noteFs6, 100);
      isAlreadyChangedGear = true;
    }
    controller.tslpTsk(4);
  }
}

void RightCourse::runPuzzle(int16_t target_brightness){
  Controller controller;
  Distinguisher d{controller};
  LineTracerWalker lineTracerWalker;

  lineTracerWalker.speedControl.setPid(1.0, 0.8, 0.8, 60.0);
  lineTracerWalker.turnControl.setPid(1.0, 1.7, 0.6, target_brightness);  
  walker.reset();
  Color result=d.getColor(); 
  controller.printDisplay(6, "in the loop, Color: %d", static_cast<int>(result));
  controller.speakerPlayTone(controller.noteFs4, 100);
  while(1){
    Color result=d.getColor();      
    auto luminance = controller.getBrightness();
    lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
    walker.run(lineTracerWalker.getForward(), lineTracerWalker.getTurn());
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, result);
    controller.printDisplay(6, "out the loop, Color: %d", static_cast<int>(result));
  }
  controller.tslpTsk(4);
}

Color RightCourse::checkPuzzle(){
  //パズルの色をチェックして保持する
  Controller controller;  
  controller.speakerPlayTone(controller.noteFs4, 100);
  Distinguisher d{controller};
  BasicWalker basic{controller};
  Lifter lifter{controller};
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(6.5, 0.5, 1.0);
  basic.backStraight(15, 45);
  lifter.liftUp(45, 10);
  Color check=d.getColor(); 
  lifter.liftDown(0, 3);
  lifter.liftUp(1.5,5);
  basic.goStraight(15, 45);
  return check;
}

void RightCourse::throughArea(){
  //ブロックエリアを通り過ぎる関数
  BasicWalker basic{controller};
  Controller controller;  
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
  basic.goStraight(15, 140);
}

void RightCourse::goleft(){
  //左折する関数
  BasicWalker basic{controller};
  Controller controller;  
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
  basic.goStraight(15, 130);
  basic.spin(basic.SPIN_LEFT, 82,10);
  basic.goStraight(15, 50);
}

void RightCourse::goright(){
  //右折する関数
  BasicWalker basic{controller};
  Controller controller;  
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
  basic.goStraight(15, 130);
  basic.spin(basic.SPIN_RIGHT, 74,10);
  basic.goStraight(15, 50);
}

void RightCourse::rotat180Degree(){
  //運搬後に180度回転して後ろを向く関数
  BasicWalker basic{controller};
  Controller controller;  
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(6.5, 0.5, 1.0);
  basic.backStraight(15, 120);
  basic.reset();
  basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
  basic.spin(basic.SPIN_RIGHT, 165, 10);
  basic.goStraight(15, 75);

}

void RightCourse::carryblockToback(){
  //ブロックを保持した状態で後ろに移動する
  BasicWalker basic{controller};
  controller.speakerPlayTone(controller.noteFs4, 100);
  basic.reset();
  basic.setPidWithoutTarget(6.5, 0.5, 1.0);
  basic.backStraight(15, 45);
  basic.reset();
  basic.setPidWithoutTarget(5.0, 1.0, 0.1);      
  basic.goStraight(15, 210);
  basic.spin(basic.SPIN_RIGHT, 87, 10);
  basic.goStraight(15, 90); 
  basic.spin(basic.SPIN_RIGHT, 82, 10);
  basic.goStraight(15, 300);
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
