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
  // runNormalCourse(brightness);
  aiAnswer();
  // getSensorLog();
}
// int16_t time = get_time();

void LeftCourse::aiAnswer()
{
  // displayの三行目に文字を表示
  controller.printDisplay(3, "aiAnswer Start!!");
  ev3_speaker_play_tone(NOTE_FS4, 200);
  walker.run(30, 0);
  ev3_speaker_play_tone(NOTE_FS4, 200);
  tslp_tsk(3500);
  ev3_speaker_play_tone(NOTE_FS4, 200);
  // その場に止まる
  walker.reset();
  ev3_speaker_play_tone(NOTE_FS4, 200);
  // 反時計回りに90°回転
  walker.angleChange(90, 1);
  ev3_speaker_play_tone(NOTE_FS4, 200);
  walker.run(30, 0);
  tslp_tsk(1000);
  while(1) {
  }
  walker.run(0, 0);
  // vcontroller.tslpTsk(4);
  // walker.run(10,0);
  controller.printDisplay(3, "aiAnswer1 Finished");
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
