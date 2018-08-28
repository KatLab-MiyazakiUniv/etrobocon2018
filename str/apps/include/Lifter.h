#ifndef __LIFTER__
#define __LIFTER__

#include "Controller.h"
#include <cstdint>

namespace etrobocon2018_test {
  class LifterTest;
}

class Lifter {
  friend class etrobocon2018_test::LifterTest;

 public:
  explicit Lifter(Controller& controller_) : controller(controller_) { reset(); }
  void liftUp(std::uint8_t angle, std::int8_t pwm = 20);
  void liftDown(std::uint8_t angle, std::int8_t pwm = 20);
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