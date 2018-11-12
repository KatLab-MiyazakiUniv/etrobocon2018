/**
 *  @file   AIAnswer.h
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#ifndef AI_ANSWER_H
#define AI_ANSWER_H
#include "AIAnswerArray.h"
#include "AIAnswerBlock.h"
#include "Navigator.h"
#include <array>
#include <cstdint>

class AIAnswer {
 private:
  AI_Answer::array<int, 6> handwriting;
  AI_Answer::array<int, 6> digital;
  Navigator navigator;
  AIAnswerBlock ai_answer_block;
  std::int16_t white;
  std::int16_t black;
  std::int16_t gray;
  std::int16_t target_brightness;
  std::int8_t solve_number;

 public:
  AIAnswer(Controller& controller, Walker& walker, std::int16_t white_, std::int16_t black_,
           std::int16_t gray_, std::int16_t brightness)
    : navigator(controller, walker),
      ai_answer_block(controller, walker, brightness),
      white(white_),
      black(black_),
      gray(gray_),
      target_brightness(brightness),
      solve_number(0)
  {
  }
  void run();
  //! デジタル数字の場所まで行く
  void moveToDigitalNumber();
  //! デジタル数字を読み取る
  void solveDigitalNumber();
  //! 数字に応じてブロックを動かす
  void shiftAIAnswerBlock(std::int8_t analog_number, std::int8_t digital_number);
  //! 数字を無視してAIアンサーのブロック並べへ行く
  void throughNumber();
};

#endif
