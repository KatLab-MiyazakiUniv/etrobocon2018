/**
 * @file LeftCourse.h
 * @brief Lコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __LEFT_COURSE__
#define __LEFT_COURSE__

#define IS_SHORT_CUT 0

#include "BasicWalker.h"
#include "Controller.h"
#include "LeftNormalCourse.h"
#include "Parking.h"
#include "Walker.h"

/**
 * Lコースを走らせるときに呼び出されるクラス
 */
class LeftCourse {
 public:
  /** コンストラクタ。センサ類の初期化を行う */
  LeftCourse() = default;
  explicit LeftCourse(Controller& controller_)
    : walker(controller_),
      controller(controller_)
  {
  }

  /**
   * このクラスのインスタンスを保持しているインスタンスまたはメンバ関数が、
   * UserInterfaceクラスのgetFirstCodeメンバ関数から
   * 取得した初期位置コードを入力する。
   * @param 初期位置コード 0から99999まで
   */
  void setFirstCode(int32_t);

  /** 各エリアの処理を呼び出す */
  void run(int16_t brightness, int16_t black, int16_t white, int16_t gray);
  /** NormalCourseエリアの処理 */
  void runNormalCourse(int16_t brightness);
  /**
   * ブロック並べを行う。
   * PuzzleFieldクラスに依存する。
   */
  void runBlockRange();

  /**
   * 縦列駐車を行う。
   * Parkingクラスに依存する。
   */
  void runParking(int16_t brightness, int16_t black, int16_t white, int16_t gray);

  void solveAiAnser();

  void runGoBlack();

  void runGoStraight();

 private:
  Walker walker;
  Controller controller;
  int16_t target_brightness;
  LineTracerWalker lineTracer;
  BasicWalker basic{ controller };
  MotorAngle motor_angle;
  // BasicWalker basicWalker;
  // Motor motor;
  // GyroSensor gyro_sensor;

  /**
   * UserInterfaceの初期位置コードを記録する。
   * ブロック並べに用いる。
   */
  int32_t firstCode;
};

#endif
