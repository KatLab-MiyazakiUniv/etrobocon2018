/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "Controller.h"
#include "Distinguisher.h"
#include "Parking.h"
#include "RightNormalCourse.h"
#include "Walker.h"
#include <cstdint>

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
      controller(controller_)
  {
  } /** 各エリアの処理を呼び出す **/
  /** NormalCourseエリアの処理 **/
  void runNormalCourse(std::int16_t brightness);
  void run(std::int16_t brightness, std::int16_t black, std::int16_t white, std::int16_t gray);
  void runParking(std::int16_t brightness, LineTracerWalker lineTracer, std::int16_t black,
                  std::int16_t white);
  void runPuzzle(std::int16_t target_brightness);
  void moveBlockAreaTo8(std::int16_t target_brightness);
  Color checkPuzzle();
  void throughArea();
  void goLeft();
  void goRight();
  void rotat180Degree();
  void carryBlockToBack();
  void runNormalCourse(std::int16_t brightness, std::int16_t black, std::int16_t white,
                       std::int16_t gray);

 private:
  LineTracerWalker lineTracer;
  Walker walker;
  Controller controller;
};

#endif
