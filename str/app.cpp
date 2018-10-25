/**
 * ファイル名 : app.c
 *
 * 概要 : ETロボコンのTOPPERS/HRP2用Cサンプルプログラム
 *
 * 注記 : Bluetooth通信リモートスタート機能付き
 */
#include "ev3api.h"
#include "app.h"
#include "Controller.h"
#include "EtRobocon2018.h"  // ETロボコン2017

// 参考: https://devkitpro.org/viewtopic.php?f=13&t=8643&start=10
extern "C" void __sync_synchronize() {}

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

static int g_bluetooth_command = 0;  // Bluetoothコマンド 1:リモートスタート
static FILE* g_bluetooth = NULL;     // Bluetoothファイルハンドル

/* メインタスク */
void main_task(intptr_t unused)
{
  /* Open Bluetooth file */
  g_bluetooth = ev3_serial_open_file(EV3_SERIAL_BT);
  assert(g_bluetooth != NULL);

  /* Bluetooth通信タスクの起動 */
  act_tsk(BT_TASK);
  Controller controller;
  controller.printDisplay(1, "ET-Robocon2018");
  controller.printDisplay(2, " create from github.com/korosuke613/etrobocon2018");

  EtRobocon2018 etrobocon;
  etrobocon.start(g_bluetooth_command);

  ter_tsk(BT_TASK);
  fclose(g_bluetooth);

  ext_tsk();
}

/**
 * 概要 : Bluetooth通信によるリモートスタート。
 *        Tera Termなどのターミナルソフトから、
 *        ASCIIコードで1を送信すると、リモートスタートする。
 * 引数 : unused
 * 返り値 : なし
 */
void bt_task(intptr_t unused)
{
  while(1) {
    uint8_t c = fgetc(g_bluetooth); /* 受信 */
    switch(c) {
      case '1':
        g_bluetooth_command = 1;
        break;
      default:
        break;
    }
    fputc(c, g_bluetooth); /* エコーバック */
  }
}
rgb_raw_t rgb;
void sensor_log_task(intptr_t unused)
{
  FILE* file;
  Controller controller;
  int volt = 0;
  int amp = 0;
  int time_now = 0;                // 開始時間からの経過時間を取得
  int32_t left_motor_counts = 0;   //左モータのオフセット付き角位置取得
  int32_t right_motor_counts = 0;  //右モータのオフセット付き角位置取得
  int log_file_number = 0;
  char log_file_name[16];
  bool flag = true;
  while(flag == true) {
    sprintf(log_file_name, "%s%d%s", "/Log/log", log_file_number, ".csv");
    controller.printDisplay(3, log_file_name);
    file = fopen(log_file_name, "r");
    if(file == NULL) {  // ファイル名がダブらない場合
      fclose(file);
      file = fopen(log_file_name, "a");
      fprintf(file, "Time(msec), Voltage, Ampere, leftMotorCounts, rightMotorCounts\n");
      flag = false;

    } else {  // 同じlogファイル名が存在する場合
      log_file_number++;
    }
  }
  ev3_speaker_play_tone(NOTE_FS6, 200);
  while(1) {
    if(ev3_button_is_pressed(BACK_BUTTON)) {  // 戻るボタンを押すとlog取得終了
      ev3_speaker_play_tone(NOTE_FS6, 500);   // 終了音
      fclose(file);
      unl_mtx(LOG);  //処理の終了
      break;
    }
    time_now = controller.clock.now();
    volt = ev3_battery_voltage_mV();
    amp = ev3_battery_current_mA();
    left_motor_counts = controller.leftWheel.getCount();
    right_motor_counts = controller.rightWheel.getCount();
    fprintf(file, "%d,%d,%d,%ld,%ld\n", time_now, volt, amp, left_motor_counts, right_motor_counts);
    // 20msec周期起動
    tslp_tsk(20);
  }
}
