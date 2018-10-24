#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracerWalker.h"
#include "MotorAngle.h"
#include "Walker.h"

class NormalCourse {
 public:
  NormalCourse() : motor_angle(), forward(0), turn(0) {}
  void stop();
  void runOrStop(Walker& walker);
  LineTracerWalker lineTracerWalker;

 protected:
  MotorAngle motor_angle;
  int8_t forward;
  int8_t turn;
};

#endif
