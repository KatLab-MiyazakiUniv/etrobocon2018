/**
 *  @file   AIAnswer.h
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#ifndef AI_ANSWER_H
#define AI_ANSWER_H
#include "AIAnswerArray.h"
#include "Navigator.h"

class AIAnswer {
 private:
  AI_Answer::array<int, 6> handwriting;
  AI_Answer::array<int, 6> digital;
  Navigator navigator;

 public:
  AIAnswer(Controller& controller, Walker& walker) : navigator(controller, walker) {}
  void run();
};

#endif
