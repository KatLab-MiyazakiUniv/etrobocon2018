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
<<<<<<< HEAD

  controller.printDisplay(3, "Finished NormalArea");

  // Puzzle
  runBlockRange();
  //controller.printDisplay(3, "Finished Puzzle");

  // Park
  controller.printDisplay(5, "> Start ParallelParking <");
  //runParking(brightness, black, white, gray);
  controller.printDisplay(7, "> Finished ParallelParking <");
=======
  solveAiAnser();
  // Park
  runParking(brightness, black, white, gray);
}

// int16_t time = get_time();

void LeftCourse::solveAiAnser()
{
  controller.printDisplay(3, "aiAnswer Start!!");
  controller.speakerPlayTone(controller.noteFs4, 200);
  walker.run(30, 0);
  controller.speakerPlayTone(controller.noteFs4, 200);
  controller.tslpTsk(3500);
  controller.speakerPlayTone(controller.noteFs4, 200);
  // その場に止まる
  walker.reset();
  controller.speakerPlayTone(controller.noteFs4, 200);
  // 反時計回りに90°回転
  walker.angleChange(90, 1);
  controller.speakerPlayTone(controller.noteFs4, 200);
  walker.run(30, 0);
  controller.tslpTsk(1000);
  walker.run(0, 0);
  controller.printDisplay(3, "aiAnswer1 Finished");
>>>>>>> fbc63a97409954f4c6b93c89d0895dcd95b8400f
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
