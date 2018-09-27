/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::run(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  LineTracerWalker lineTracer;
  runNormalCourse(brightness, black, white, gray);
  //runParking(brightness, lineTracer, black, white);
}

void RightCourse::runParking(int16_t brightness, LineTracerWalker lineTracer, int16_t black,
                             int16_t white)
{
  Parking parking{ controller };
  parking.runParpendicular(brightness, lineTracer, black, white);
}

void RightCourse::runNormalCourse(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  RightNormalCourse normalCourse;
  bool isNormalCourse;

  /*灰色を検知用*/
  /* 
  int8_t counter = 0;
  int16_t target_brightness_gray = (white + gray) / 2;
  */

  // NormalCourseを抜けるまでループする
  while(1) {
    sl.update(walker.get_count_L(), walker.get_count_R());
    auto luminance = controller.getBrightness();

    /*灰色を検知用*/
    /*
    auto distance_total_r = (walker.get_count_L() + walker.get_count_R()) / 2;
    */
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, brightness);
    if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
      controller.speakerPlayTone(controller.noteFs6, 100);
    isNormalCourse = normalCourse.runNormalCourse(brightness, black, white, gray);
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
    /*灰色を検知したら止まる*/ 
  /*
  const std::int16_t AFTER_GOAL_CURVE_R = 11900;
    if(distance_total_r > AFTER_GOAL_CURVE_R && target_brightness_gray + 20 > luminance && luminance > target_brightness_gray - 3){
      if(counter > 10){
        controller.printDisplay(4, "Find Gray Line¥n Brightness: %d, Target: %d", luminance, brightness);
        controller.speakerPlayTone(controller.noteFs6, 100); 
      }
      controller.speakerPlayTone(controller.noteFs6, 20); 
      counter++;
    }else{
      counter = 0;      
    }
  */
    controller.tslpTsk(4);  // 4msec周期起動
  }
}