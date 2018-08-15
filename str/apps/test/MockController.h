#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <cstdlib>

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
  int getBrightness() { return brightness; }
  int brightness = 0;
};

class Controller {
 public:
  Clock clock;
  Motor rightWheel;
  Motor leftWheel;
  TouchSensor touchSensor;
  ColorSensor colorSensor;

  int noteFs6 = 0;
  Controller() {}
  void speakerSetVolume(int volume){};
  void ledSetColorOrange(){};
  void ledSetColorGreen(){};
  int getBrightness() { return brightness; };
  void speakerPlayTone(int frequency, int duration){};
  bool buttonIsPressedBack()
  {
    counter++;
    if(counter >= countLimit) {
      return true;
    }
    return false;
  };
  bool buttonIsPressedUp() { return false; };
  bool buttonIsPressedDown() { return false; };
  bool buttonIsPressedRight() { return false; };
  bool buttonIsPressedLeft() { return false; };
  bool buttonIsPressedEnter()
  {
    static int counter = 0;
    counter++;
    if(counter >= 10) {
      return true;
    }
    return false;
  };
  void tslpTsk(int time)
  {
    exitCounter++;
    if(exitCounter > exitCountLimit) std::exit(1);
  };  // 4msec周期起動
  void printDisplay(int row, const char* format, ...){};
  int countLimit = 100;
  int counter = 0;
  int exitCounter = 0;
  int exitCountLimit = 1000;
  int brightness = 0;
};
#endif
