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
void LeftCourse::run(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  runNormalCourse(brightness);

  controller.printDisplay(3, "Finished NormalArea");

  // Puzzle
  runBlockRange();
  //controller.printDisplay(3, "Finished Puzzle");

  // Park
  controller.printDisplay(5, "> Start ParallelParking <");
  //runParking(brightness, black, white, gray);
  controller.printDisplay(7, "> Finished ParallelParking <");
}

// void LeftCourse::runParking(int16_t brightness, int16_t gray)
void LeftCourse::runParking(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  Parking parking{ controller };
  parking.runParallel(brightness, black, white, gray);
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

void LeftCourse::runBlockRange() {}
