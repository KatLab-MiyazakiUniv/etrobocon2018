/**
 * @file Parking.h
 * @brief 縦列駐車クラス
 * @author Keisuke MORI
 */
#ifndef __PARKING__
#define __PARKING__

#include "BasicWalker.h"
#include "Controller.h"
#include "LineTracerWalker.h"
#include "SpeedControl.h"
#include "Walker.h"

/*! @class Parking Parking.h "Parking.h"
 *  @brief 駐車クラス
 */
class Parking {
 public:
  /**
   * コンストラクタ
   * カラーセンサを初期化する。
   */
  explicit Parking(Controller& controller_) : controller(controller_){};

  /**
   * 縦列駐車を実行する。
   * 実行開始時にBasicWalkerクラスのインスタンスを生成し、
   * goStraightメンバ関数とspinメンバ関数に依存する。
   */
  void runParpendicular(int16_t target_brightness, LineTracerWalker lineTracer, int16_t black,
                        int16_t white);

  /**
   * 直角駐車を実行する。
   * 実行開始時にBasicWalkerクラスのインスタンスを生成し、
   * goStraightメンバ関数とspinメンバ関数に依存する。
   */
  void runParallel(int16_t brightness, int16_t black, int16_t white, int16_t gray);

  /**
   * 3秒間待機する。
   * 駐車完了後に使う。
   * その際、1秒ごとに音を鳴らす。
   * EV3APIに依存する。
   */
  void waitThreeTimes();

  void ev3_remaining_amount();

 private:
  Controller controller;
  Walker walker;
  float remaining_amount;
  //char *aa;
};

#endif
