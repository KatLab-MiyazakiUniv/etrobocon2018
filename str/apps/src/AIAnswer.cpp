/**
 *  @file   AIAnswer.cpp
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#include "AIAnswer.h"

void AIAnswer::run()
{
  moveToAIAnswer();  // 数字の箇所まで進む
  solve();
  // shiftAIAnswerBlock(0, 0);
}

/**
 *  [AIAnswer::moveToAIAnswer]
 *  @brief 数字の場所まで行く
 */
void AIAnswer::moveToAIAnswer()
{
  navigator.moveOnLine(300, target_brightness);  // 10cmライントレースしながら進む
  navigator.move(490);                           // 59cm前進
  navigator.spin(90);                            // 90度左回転
}

/**
 *  [AIAnswer::solve]
 *  @brief 数字を読み取る
 */
void AIAnswer::solve()
{
  navigator.moveWhileDetecting(370, black);  // 37cm進む
  navigator.spin(135, true);                 // 135度右回転
  navigator.moveWhileDetecting(160, black);  // 16cm進む
  navigator.spin(45, true);                  // 45度右回転
  navigator.moveWhileDetecting(260, black);  // 26cm進む
  navigator.spin(45);                        // 45度左回転
}

/**
 *  [AIAnswer::shiftAIAnswerBlock]
 *  @brief 読み取った数字に対してブロックを動かす
 */

void AIAnswer::shiftAIAnswerBlock(std::int8_t analog_number, std::int8_t digital_number)
{
  // 読み取った数字を
  solve_number = (analog_number * 10) + digital_number;
  switch(solve_number) {
    case 0:
      ai_answer_block.block00();
      break;

    default:
      ai_answer_block.block00();
      break;
  }
}
