/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::run(int16_t brightness, int16_t black, int16_t white)
{
  LineTracerWalker lineTracer;
 // runNormalCourse(brightness);
  runParking(brightness, lineTracer, black, white);
}

void RightCourse::runParking(int16_t brightness, LineTracerWalker lineTracer, int16_t black,
                             int16_t white)
{
  Parking parking{ controller };
  parking.runParpendicular(brightness, lineTracer, black, white);
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