/**
 * @file AIAnswer.h
 * @brief AIAnswerクラス
 * @author Keisuke MORI
 */
#ifndef __AIANSWER__
#define __AIANSWER__

#include "BasicWalker.h"
#include "Controller.h"
#include "LineTracerWalker.h"
#include "SpeedControl.h"
#include "Walker.h"
/*! @class Parking Parking.h "Parking.h"
 *  @brief 駐車クラス
 */
class AIAnswer {
 public:
  // 数字を読み取る
  void readAIAnswer(Controller controller, LineTracerWalker lineTracer);

  // 数字に対応したブロックを動かす
  void solveAIAnswer(Controller controller, LineTracerWalker lineTracer, Distance distance);

 private:
}

#endif
