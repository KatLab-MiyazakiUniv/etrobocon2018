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
  solveAiAnser();
  // runGoStraight();
}

void LeftCourse::solveAiAnser()
{
  controller.printDisplay(3, "aiAnswer Start!!");
  controller.speakerPlayTone(NOTE_FS4, 200);
  walker.run(30, 0);
  controller.speakerPlayTone(NOTE_FS4, 200);
  controller.tslpTsk(3300);
  controller.speakerPlayTone(NOTE_FS4, 200);
  // その場に止まる
  walker.reset();
  controller.speakerPlayTone(NOTE_FS4, 200);
  // 反時計回りに90°回転
  walker.angleChange(90, 1);
  controller.speakerPlayTone(NOTE_FS4, 200);
  walker.run(30, 0);
  controller.tslpTsk(400);
  //  walker.run(0, 0);
  controller.printDisplay(3, "aiAnswer1 Finished");
  // ここから黒線探しの旅
  while(1) {
    // 現在の色取得
    int16_t luminance = controller.getBrightness();
    // 黒検知
    if(luminance <= 21) {
      runGoBlack();
      // lineTracer.speedControl.setPid(5.0, 1.0, 0.1, 90.0);
      // lineTracer.turnControl.setPid(2.0, 1.0, 0.14, target_brightness);
      break;
      // それ以外
    } else {
      walker.run(10, 0);
    }
    if(controller.buttonIsPressedBack()) {
      walker.reset();
      break;
    }
    controller.tslpTsk(4);
  }  // whileのおわり

  // ライントレース
  //   while(1) {
  //     lineTracer.speedControl.setPid(5.0, 1.0, 0.1, 90.0);
  //     lineTracer.turnControl.setPid(2.0, 1.0, 0.14, target_brightness);
  //     if(controller.buttonIsPressedBack()) {
  //       walker.reset();
  //       break;
  //     }
  //     controller.tslpTsk(4);
  // } // whileのおわり
}

// 黒線上を走る
void LeftCourse::runGoBlack()
{
  walker.reset();
  // 時計回りに45°回転
  walker.angleChange(45, -1);
  walker.run(10, 0);
  controller.tslpTsk(1000);
  while(1) {
    // 現在の色取得
    int16_t luminance = controller.getBrightness();
    if(luminance <= 21) {
      // 左に15度回転
      basic.spin(basic.SPIN_LEFT, 30);
      runGoStraight();
      break;
    }
    if(controller.buttonIsPressedBack()) {
      walker.reset();
      break;
    }
    controller.tslpTsk(4);
  }
}

void LeftCourse::runGoStraight()
{
  // // (P, I, D, speed)
  // lineTracer.speedControl.setPid(5.0, 0.9, 0.1, 20.0);
  // // (P, I, D, 境界値)
  // lineTracer.turnControl.setPid(1.0, 0.2, 1.0, target_brightness);

  walker.reset();
  while(1) {
    int16_t luminance = controller.getBrightness();
    lineTracer.speedControl.setPid(5.0, 0.8, 0.2, 20.0);
    lineTracer.turnControl.setPid(2.2, 0.1, 0.35, target_brightness);  // 2.0,0.2,0.4 最高か
    // 走る
    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
    if(lineTracer.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    // controller.printDisplay(4, "Brightness: %d", luminance);
    // if(lineTracer.getForward() < 0) {
    //   walker.reset();
    // } else {
    //   walker.run(lineTracer.getForward(), lineTracer.getTurn());
    //   //walker.run(10, 0);
    // }
    if(controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }
    controller.tslpTsk(4);
  }
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

void LeftCourse::runParallelParking() {}
