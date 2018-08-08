#include "EtRobocon2018.h"

/*! \mainpage EtRobocon2018のドキュメント
 *
 * \section intro_sec こんにちは！
 * @b
 * このページは片山研究所モデルベース開発推進事業部が開発している、ETロボコン2017アドバンスドクラス用のプログラムのドキュメントです！
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

EtRobocon2018::EtRobocon2018() : touchSensor(PORT_1), colorSensor(PORT_3)
{
  /** TODO Courseクラスに移す */
  ev3_speaker_set_volume(100);
}

void EtRobocon2018::start(int bluetooth_command)
{
#ifdef IS_RIGHT_COURSE
#else
  ui.inputFirstCode();
  firstCode = ui.getFirstCode();
#endif
  ui.setBrightnessWithColor(colorSensor, light_white, "white");
  ui.setBrightnessWithColor(colorSensor, light_black, "black");
  target_brightness = (light_black + light_white) / 2;
  char msg[32];
  sprintf(msg, "Brightness W:%d, B:%d, T:%d", light_white, light_black, target_brightness);
  msg_f(msg, 7);
  ev3_led_set_color(LED_ORANGE);
  waitStarter(bluetooth_command);

  ev3_led_set_color(LED_GREEN); /* スタート通知 */

  loop();
}

void EtRobocon2018::loop()
{
  // Rコースを走らせるときは1, Lコースを走らせるときは0
  auto brightness = target_brightness;
#ifdef IS_RIGHT_COURSE
  rightCourse.run(brightness);
#else
  leftCourse.setFirstCode(firstCode);
  leftCourse.run(brightness);
#endif
}

void EtRobocon2018::waitStarter(int bluetooth_command)
{
  /* スタート待機 */
  while(1) {
    if(bluetooth_command == 1) {
      break; /* リモートスタート */
    }

    if(touchSensor.isPressed() == 1) {
      tslp_tsk(500);
      break; /* タッチセンサが押された */
    }

    tslp_tsk(10); /* 10msecウェイト */
  }
}
