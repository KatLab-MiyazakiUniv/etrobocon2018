/**
 *  @file   AIAnswer.cpp
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#include "AIAnswer.h"

void AIAnswer::run()
{
  // moveToDigitalNumber();  // 数字の箇所まで進む
  // solveDigitalNumber();
  // shiftAIAnswerBlock(0, 0);
  // navigator.moveToColor(1000, target_brightness, Color::RED);
  ai_answer_block.block00();
}

/**
 *  [AIAnswer::moveToDigitalNumber]
 *  @brief デジタル数字の場所まで行く
 */
void AIAnswer::moveToDigitalNumber()
{
  navigator.moveOnLine(500, target_brightness, 30);  // 40cmライントレースしながら進む
  navigator.move(190);                               // 29cm前進
  navigator.spin(45, true);                          // 45度右回転
  navigator.move(200);                               // 30cm前進
  navigator.spin(135);                               // 135度左回転
  // navigator.spin(90);                            // 90度左回転
}

/**
 *  [AIAnswer::solveDigitalNumber]
 *  @brief 数字を読み取る
 */
void AIAnswer::solveDigitalNumber()
{
  navigator.moveWhileDetecting(530, black);  // 37cm進む
  navigator.spin(135, true);                 // 135度右回転
  navigator.moveWhileDetecting(160, black);  // 16cm進む
  navigator.spin(90, true);                  // 90度右回転
  navigator.moveWhileDetecting(460, black);  // 26cm進む
  navigator.spin(135);                       // 135度左回転
  navigator.move(500);                       // ここ適当
}

/**
 *  [AIAnswer::shiftAIAnswerBlock]
 *  @brief 読み取った数字に対してブロックを動かす
 */

void AIAnswer::shiftAIAnswerBlock(std::int8_t analog_number, std::int8_t digital_number)
{
  // アナログ数字を10の位，デジタル数字を1の位に変換
  solve_number = (analog_number * 10) + digital_number;
  // 読み取った数字に応じて分岐
  switch(solve_number) {
    case 0:
      ai_answer_block.block00();
      break;

    default:
      ai_answer_block.block00();
      break;
  }
}
