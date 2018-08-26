#ifndef __LIFTER__
#define __LIFTER__

#include "Controller.h"
#include <cstdint>

class LifterTest;

class Lifter {
  friend class LifterTest;

 public:
  explicit Lifter(Controller& controller_) : controller(controller_) { reset(); }
  void liftUp(std::int8_t angle, std::int8_t pwm = 20);
  void liftDown(std::int8_t angle, std::int8_t pwm = 20);
  void changeDefault(int angle);
  std::int8_t limitPwm(std::int8_t pwm);
  std::int8_t getCurrentAngle();
  void defaultSet(std::int8_t pwm = 20);
  void init();
  void terminate();
  void reset();

 private:
  Controller controller;
  std::int32_t default_count = 0;
};

#endif