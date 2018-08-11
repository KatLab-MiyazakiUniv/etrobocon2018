#ifndef __WORKER__
#define __WORKER__

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

class Motor {
 public:
  int getCount() { return 0; };
  void setPWM(int pwm){};
  void stop(){};
  void reset(){};
  void setBrake(bool isBrake){};
};

class Clock {
 public:
  void sleep(int time){};
};

class TouchSensor {
 public:
  bool isPressed() { return false; }
};

class ColorSensor {
 public:
  int getBrightness() { return 0; }
};

class Worker {
 public:
  Clock clock;
  Motor rightWheel;
  Motor leftWheel;
  TouchSensor touchSensor;
  ColorSensor colorSensor;

  int noteFs6 = 0;
  Worker() {}
  void speakerSetVolume(int volume){};
  void ledSetColorOrange(){};
  void ledSetColorGreen(){};
  int getBrightness() { return 0; };
  void speakerPlayTone(int frequency, int duration){};
  bool buttonIsPressedBack() { return false; };
  bool buttonIsPressedUp() { return false; };
  bool buttonIsPressedDown() { return false; };
  bool buttonIsPressedRight() { return false; };
  bool buttonIsPressedLeft() { return false; };
  bool buttonIsPressedEnter() { return false; };
  void tslpTsk(int time){};  // 4msec周期起動
  void printDisplay(int row, const char* format, ...){};
};
#endif
