/**
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

#endif
