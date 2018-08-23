#ifndef __LIFTER__
#define __LIFTER__

#include "Controller.h"

class Lifter {
 public:
  Lifter() = default;
  explicit Lifter(Controller& controller_) : controller(controller_)
  {
    controller.liftMotor.reset();
  }
  void liftUp();
  void liftDown();
  void changeDefault(int angle);
  void defaultSet(int angle);
  void init();
  void terminate();
  void reset();

 private:
  Controller controller;
};

#endif