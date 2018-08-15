/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

void LeftCourse::setFirstCode(int32_t code)
{
  firstCode = code;
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(int16_t brightness)
{
  runNormalCourse(brightness);

  controller.printDisplay(3, "Finished NormalArea");

  // Puzzle
  runBlockRange();
  controller.printDisplay(3, "Finished Puzzle");

  // Park
  runParallelParking();
  controller.printDisplay(3, "Finished Parking");
}

void LeftCourse::runNormalCourse(int16_t brightness)
{
  LeftNormalCourse normalCourse;
  bool isNormalCourse;
  // NormalCourseを抜けるまでループする
  while(1) {
    sl.update(walker.get_count_L(), walker.get_count_R());
    auto luminance = controller.getBrightness();
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, brightness);
    if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
      controller.speakerPlayTone(controller.noteFs6, 100);
    isNormalCourse = normalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R(),
                                                  luminance, brightness);

    if(normalCourse.lineTracerWalker.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(normalCourse.lineTracerWalker.getForward(),
                 normalCourse.lineTracerWalker.getTurn());
    }
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

void LeftCourse::runBlockRange() {}

void LeftCourse::runParallelParking() {}
