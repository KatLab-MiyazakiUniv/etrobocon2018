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

class Worker {
 public:
  Worker() {}
  void speakerSetVolume(int volume){};
  void ledSetColorOrange(){};
  void ledSetColorGreen(){};
  int getBrightness(){};
  void speakerPlayTone(int frequency, int duration){};
  bool buttonIsPressedBack(){};
  bool buttonIsPressedUp(){};
  bool buttonIsPressedDown(){};
  bool buttonIsPressedRight(){};
  bool buttonIsPressedLeft(){};
  bool buttonIsPressedEnter(){};
  void tslpTsk(int time){};  // 4msec周期起動
  void printDisplay(int row, const char* format, ...){};
};
#endif
