#ifndef __BASIC_WALKER__
#define __BASIC_WALKER__

#include "Controller.h"
#include "SpeedControl.h"
#include "Walker.h"

class BasicWalker {
 public:
  explicit BasicWalker(Controller& controller_) : controller(controller_)
  {
    controller.speakerSetVolume(100);
  }
  void reset(void);
  void parkingLeft(void);
  void setPidWithoutTarget(double, double, double);
  void spin(bool, int32_t, int32_t turn = 18);
  void goStraight(int32_t, int32_t);
  void goStraight_b(int32_t, int32_t, int16_t);
  void spinToCheckBlackLine(bool, int32_t);
  void goStraightToCheckBlackLine(int32_t, int32_t, int16_t);
  void backStraight(int32_t, int32_t);
  const bool SPIN_LEFT = false;
  const bool SPIN_RIGHT = true;

 private:
  Controller controller;
  Walker walker;
  SpeedControl speedControl;
  int32_t forward;
  int32_t leftReverseValue;
  int32_t rightReverseValue;
  double p_value;
  double i_value;
  double d_value;
};

#endif
