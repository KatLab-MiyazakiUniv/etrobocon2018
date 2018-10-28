#include "EtRobocon2018.h"

/*! \mainpage EtRobocon2018のドキュメント
 *
 * \section intro_sec こんにちは！
 * @b
 * このページは片山研究所モデルベース開発推進事業部が開発している、ETロボコン2017アドバンスドクラス用のプログラムのドキュメントです！
 * 詳しくはコチラ→ https://github.com/KatLab-MiyazakiUniv/etrobocon2018	
 */

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

/**
 * @file Etrobocon2018.cpp
 * @brief Etrobocon2018クラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

EtRobocon2018::EtRobocon2018()
{
  /** TODO Courseクラスに移す */
  controller.speakerSetVolume(100);
}

void EtRobocon2018::start(int bluetooth_command)
{
  UserInterface ui{ controller };
#ifdef IS_RIGHT_COURSE
  ui.inputFirstCode();
  firstCode = ui.getFirstCode();
#else
#endif
  ui.setBrightnessWithColor(light_white, "white");
  ui.setBrightnessWithColor(light_black, "black");
  ui.setBrightnessWithColor(light_gray, "gray");
  target_brightness = (light_black + light_white) / 2;
  controller.printDisplay(7, "Brightness W:%d, B:%d, T:%d", light_white, light_black,
                          target_brightness);
  controller.ledSetColorOrange();
  waitStarter(bluetooth_command);
  controller.ledSetColorGreen();

  loop();
}

void EtRobocon2018::loop()
{
  // Rコースを走らせるときは1, Lコースを走らせるときは0
  auto brightness = target_brightness;
#ifdef IS_RIGHT_COURSE
  RightCourse rightCourse{ controller };
  rightCourse.run(brightness, light_black, light_white, light_gray);
#else
  LeftCourse leftCourse{ controller };
  leftCourse.setFirstCode(firstCode);
  leftCourse.run(brightness, light_black, light_white, light_gray);
#endif
}

void EtRobocon2018::waitStarter(int bluetooth_command)
{
  /* スタート待機 */
  while(1) {
    if(bluetooth_command == 1) {
      break; /* リモートスタート */
    }

    if(controller.touchSensor.isPressed() == 1) {
      controller.tslpTsk(500);
      break; /* タッチセンサが押された */
    }

    controller.tslpTsk(10); /* 10msecウェイト */
  }
}
