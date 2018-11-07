/**
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

#endif
