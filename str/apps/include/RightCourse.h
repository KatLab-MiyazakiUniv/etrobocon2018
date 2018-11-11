/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "BlockSolver.h"
#include "Controller.h"
#include "Distinguisher.h"
#include "Explorer.h"
#include "Parking.h"
#include "RightNormalCourse.h"
#include "Walker.h"
#include <cstdint>

/**
 * Rコースを走らせるときに呼び出されるクラス
 */
class RightCourse {
 public:
  /** コンストラクタ。センサ類の初期化を行う **/
  RightCourse() = default;
  explicit RightCourse(Controller& controller_, std::vector<std::int8_t> ipcv)
    : walker(controller_), controller(controller_), initialPositionCodeVector(ipcv)
  {
  } /** 各エリアの処理を呼び出す **/
  /** NormalCourseエリアの処理 **/
  void runNormalCourse(std::int16_t brightness);
  void run(std::int16_t brightness, std::int16_t black, std::int16_t white, std::int16_t gray);
  void runParking(std::int16_t brightness, LineTracerWalker lineTracer, std::int16_t black,
                  std::int16_t white);
  void runPuzzle(std::int16_t target_brightness);
  void moveBlockAreaTo8(std::int16_t target_brightness);
  void throughArea();
  void runNormalCourse(std::int16_t brightness, std::int16_t black, std::int16_t white,
                       std::int16_t gray);
  void solveBlockPuzzle(std::int16_t brightness);

 private:
  LineTracerWalker lineTracer;
  Walker walker;
  Controller controller;
  Explorer explorer;
  std::vector<std::int8_t> initialPositionCodeVector;
};

#endif
