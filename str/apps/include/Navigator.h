/**
 *  @file  Navigator.h
 *  @brief 走行制御と回転制御を実行するクラス
 *  @author T.Miyaji
 */
#ifndef NAVIGATOR_H
#define NAVIGATOR_H
#include "Controller.h"
#include "Distinguisher.h"
#include "LineTracerWalker.h"
#include "Walker.h"
#include "WheelOdometry.h"
#include <algorithm>
#include <cstdint>

class Navigator {
 private:
  Controller controller;
  Walker walker;
  WheelOdometry odometry;
  LineTracerWalker line_tracer;
  Distinguisher distinguisher;
  Color color;

 public:
  Navigator(const Controller& controller_, const Walker& walker_)
    : controller(controller_),
      walker(walker_),
      odometry(),
      line_tracer(),
      distinguisher(controller),
      color(Color::NONE)
  {
  }
  Navigator(const Controller& controller_)
    : controller(controller_),
      walker(),
      odometry(),
      line_tracer(),
      distinguisher(controller),
      color(Color::NONE)
  {
  }
  Navigator()
    : controller(),
      walker(),
      odometry(),
      line_tracer(),
      distinguisher(controller),
      color(Color::NONE)
  {
  }
  //! 座標とエンコーダの値を初期化する
  void reset();
  //! 指定した角度まで走行体を回転させる(基本左エッジ)
  void spin(float angle, bool clockwise = false, std::int8_t pwm = 10);
  //! 指定した距離まで走行体を移動させる
  void move(float distance, std::int8_t pwm = 20);
  //! 指定した距離まで走行体を後退させる
  void back(float distance, std::int8_t pwm = 10);
  //! 指定した距離まで黒色の点を検出しながら走行体を移動させる
  void moveWhileDetecting(float distance, std::int16_t target, std::int8_t pwm = 10);
  //! 指定した距離だけライントレースする
  void moveOnLine(float distance, std::int16_t target, std::int8_t pwm = 20,
                  bool is_leftside_line = true);
  //! 指定した距離分ライントレースして指定した色があると停止する
  void moveToColor(float distance, std::int16_t target_brightness, Color target_color,
                   std::int8_t speed = 20, bool is_leftside_line = true);
  //! 光センサの値を取得する
  std::int16_t getBrightness();
  //! 現在位置の周辺における光センサ値を取得する
  std::int8_t getNearbyBrightness(float distance = 20.0f);
  //! 2値化処理を実行する
  bool binarization(std::int16_t target);
};

#endif
