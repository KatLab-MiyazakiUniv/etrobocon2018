/**
 * @file EtRobocon2018.h
 * @brief main的なクラス
 * @author Futa HIRAKOBA
 */
#ifndef __ETROBOCON2018__
#define __ETROBOCON2018__

//この下の行のコメントは消すな！
//変更してもいけない
//#define IS_RIGHT_COURSE

#include "LeftCourse.h"
#include "RightCourse.h"
#include "UserInterface.h"
#include "Worker.h"

/**
 * main的なクラス
 */
class EtRobocon2018 {
 public:
  /** コンストラクタ。各センサー等の初期化を行う */
  EtRobocon2018();
  /** タッチセンサが押されたときに行われる処理 */
  void start(int);
  /** スイッチを入れたときに行われる処理 */
  void waitStarter(int);
  /** 実際にマシンを動かすときの処理 */
  void loop();

 private:
  Worker worker;
  int16_t light_white;
  int16_t light_black;
  int16_t target_brightness;
  int32_t firstCode;
};

#endif
