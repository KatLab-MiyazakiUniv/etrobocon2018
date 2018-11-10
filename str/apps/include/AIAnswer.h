/**
 *  @file   AIAnswer.h
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#ifndef AI_ANSWER_H
#define AI_ANSWER_H
#include "AIAnswerArray.h"
#include "Navigator.h"
#include <array>
#include <cstdint>

class AIAnswer {
 private:
  AI_Answer::array<int, 6> handwriting;
  AI_Answer::array<int, 6> digital;
  Navigator navigator;
  std::int16_t white;
  std::int16_t black;
  std::int16_t target_brightness;

 public:
  AIAnswer(Controller& controller, Walker& walker, std::int16_t white_, std::int16_t black_,
           std::int16_t brightness_)
    : navigator(controller, walker), white(white_), black(black_), brightness(brightness_)
  {
  }
  void run();
};

#endif
