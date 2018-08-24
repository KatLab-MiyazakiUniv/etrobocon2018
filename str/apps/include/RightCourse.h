/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "Controller.h"
#include "Distance.h"
#include "RightNormalCourse.h"
#include "SelfLocalization.h"
#include "Walker.h"
#include "Parking.h"


/**
 * 走行場所の状態を保持する列挙型
 */
enum struct ShinkansenStatus {
  BEFORE_FIRST_SHINKANSEN,
  FIRST_RAIL,
  FIRST_LINE,
  SECOND_LINE,
  BEFORE_SECOND_SHINKANSEN,
  SECOND_RAIL,
  THIRD_LINE,
  FOURTH_LINE,
  BEFORE_THIRD_SHINKANSEN,
  PRIZE,
  STOP
};

/**
 * Rコースを走らせるときに呼び出されるクラス
 */
class RightCourse {
 public:
  /** コンストラクタ。センサ類の初期化を行う **/
  RightCourse() = default;
  explicit RightCourse(Controller& controller_)
    : walker(controller_),
      sl(walker.get_count_L(), walker.get_count_R(), true),
      controller(controller_)
  {
  } /** 各エリアの処理を呼び出す **/
  void run(int16_t brightness);
  /** NormalCourseエリアの処理 **/
  void runNormalCourse(int16_t brightness);
  
  void runParking(int16_t brightness,LineTracerWalker lineTracer);

 private:
  LineTracerWalker lineTracer;
  Walker walker;
  SelfLocalization sl;
  Controller controller;
};

#endif