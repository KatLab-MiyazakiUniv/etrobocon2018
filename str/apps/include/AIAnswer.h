/**
<<<<<<< HEAD
 *  @file   AIAnswer.h
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#ifndef AI_ANSWER_H
#define AI_ANSWER_H
#include "AIAnswerArray.h"
#include "LineTracerWalker.h"
#include "Navigator.h"
#include <array>
#include <cstdint>

class AIAnswer {
 private:
  AI_Answer::array<int, 6> handwriting;
  AI_Answer::array<int, 6> digital;
  Navigator navigator;
  std::array<std::int16_t, 3> sensor_values;
  Walker walker;
  LineTracerWalker line_tracer;
  Controller controller;
  MotorAngle motor_angle;

 public:
  void run();
  // void goLineTrace(float distance, std::int16_t target_brightness, std::int8_t pwm = 20);
};
=======
 * @file AIAnswer.h
 * @brief AIAnswerクラス
 * @author Tatsumi Nishida
 */
#ifndef __AIANSWER__
#define __AIANSWER__

#include "BasicWalker.h"
#include "LineTracerWalker.h"
#include "Walker.h"
/*! @class Parking Parking.h "Parking.h"
 *  @brief 駐車クラス
 */
class AIAnswer {
 private:
  std::int32_t digital_number;  // 読み取ったデジタル数字
  std::int32_t analog_number;   // 読み取ったアナログ数字
  MotorAngle motor_angle;

 public:
  AIAnswer() : digital_number(0), analog_number(0), motor_angle() {}
  // 数字を読み取る
  void readAIAnswer(Controller controller, LineTracerWalker line_tracer);
  // 数字に対応したブロックを動かす
  void solveAIAnswer(Controller controller, LineTracerWalker line_tracer, MotorAngle motor_angle);
}
>>>>>>> 751b48e58956ffd3ea049220ab92d433957e4fe9

#endif
