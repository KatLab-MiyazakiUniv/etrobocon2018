#ifndef __WORKER__
#define __WORKER__

#include "Clock.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"
#include "ev3api.h"

/*
 * touch_sensor = EV3_PORT_1;
 * sonar_sensor = EV3_PORT_2;
 * color_sensor = EV3_PORT_3;
 * gyro_sensor  = EV3_PORT_4;
 *
 * left_motor   = EV3_PORT_C;
 * right_motor  = EV3_PORT_B;
 * lift_motor   = EV3_PORT_A;
 * tail_motor   = EV3_PORT_D;
 */

using namespace ev3api;

class Worker {
 public:
  Worker()
    : touchSensor(PORT_1),
      colorSensor(PORT_3),
      liftMotor(PORT_A),
      rightWheel(PORT_B),
      leftWheel(PORT_C),
      tailMotor(PORT_D)
  {
  }
  uint16_t noteFs6 = NOTE_FS6;
  TouchSensor touchSensor;
  ColorSensor colorSensor;
  Motor liftMotor;
  Motor rightWheel;
  Motor leftWheel;
  Motor tailMotor;
  Clock clock;
  void speakerSetVolume(uint8_t volume);
  void ledSetColorOrange();
  void ledSetColorGreen();
  int16_t getBrightness();
  void speakerPlayTone(uint16_t frequency, int32_t duration);
  bool buttonIsPressedBack();
  void tslpTsk(int8_t time);  // 4msec周期起動

 private:
  rgb_raw_t rgb;
};
#endif
