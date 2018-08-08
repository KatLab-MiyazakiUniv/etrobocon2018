/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse()
  :
#if IS_SHORT_CUT
    navi(walker.get_count_L(), walker.get_count_R()),
#endif
    colorSensor(PORT_3),
    sl(walker.get_count_L(), walker.get_count_R(), true)
{
}

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

  msg_f("Finished NormalArea", 3);

  // Puzzle
  runBlockRange();
  msg_f("Finished BlockRange", 3);

  // Park
  runParallelParking();
  msg_f("Finished ParallelParking", 3);
}

void LeftCourse::runNormalCourse(int16_t brightness)
{
  char msg[32];

  LeftNormalCourse normalCourse;
  bool isNormalCourse;
  // NormalCourseを抜けるまでループする
  while(1) {
    sl.update(walker.get_count_L(), walker.get_count_R());
    rgb_raw_t rgb;
    colorSensor.getRawColor(rgb);
    int16_t luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
    sprintf(msg, "Brightness: %d, Target: %d", luminance, brightness);
    msg_f(msg, 4);
    if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
      ev3_speaker_play_tone(NOTE_FS6, 100);
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
    if(ev3_button_is_pressed(BACK_BUTTON)) {
      walker.run(0, 0);
      break;
    }

    tslp_tsk(4);  // 4msec周期起動
  }
}

void LeftCourse::runBlockRange() {}

void LeftCourse::runParallelParking() {}
