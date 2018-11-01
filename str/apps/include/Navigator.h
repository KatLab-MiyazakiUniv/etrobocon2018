/**
 *  @file  Navigator.h
 *  @brief 走行制御と回転制御を実行するクラス
 *  @author T.Miyaji
 */
#ifndef NAVIGATOR_H
#define NAVIGATOR_H
#include "Controller.h"
#include "WheelOdometry.h"
#include "Walker.h"
#include <cstdint>
#include <algorithm>

class Navigator {
 private:
  Controller controller;
  Walker walker;
  WheelOdometry odometry;
 public:
  Navigator(const Controller& controller_, const Walker& walker_)
   : controller(controller_), walker(walker_), odometry() { }
  Navigator(const Controller& controller_)
   : controller(controller_), walker(), odometry() { }
  Navigator()
   : controller(), walker(), odometry() { }
  //! 座標とエンコーダの値を初期化する
  void reset();
  //! 指定した角度まで走行体を回転させる
  void spin(float angle, std::int8_t pwm = 10, bool clockwise = false);
  //! 指定した距離まで走行体を移動させる
  void move(float distance, std::int8_t pwm = 20);
  //! 指定した距離まで黒色の点を検出しながら走行体を移動させる
  void moveWhileDetecting(float distance, std::int8_t pwm = 10);
  //! 光センサの値を取得する
  std::int16_t getBrightness();
  //! 現在位置の周辺における光センサ値を取得する
  std::int8_t getNearbyBrightness(float distance = 20.0f);
  //! 2値化処理を実行する
  bool binarization();
};

#endif
