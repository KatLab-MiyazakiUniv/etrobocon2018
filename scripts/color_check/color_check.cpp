/**
 * ファイル名 : app.c
 *
 * 概要 : ETロボコンのTOPPERS/HRP2用Cサンプルプログラム
 *
 * 注記 : Bluetooth通信リモートスタート機能付き
 */

#include "Controller.h"
#include "Distinguisher.h"
#include "app.h"
#include "ev3api.h"
#include "util.h"

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

  msg_f("ET-Robocon2018", 1);
  msg_f(" create from github.com/korosuke613/etrobocon2018", 2);

  Controller controller;
  Distinguisher distinguisher{ controller };
  const char* color_name[7] = { "NONE", "BLACK", "WHITE", "RED", "BLUE", "YELLOW", "GREEN" };
  while(1) {
    if(controller.buttonIsPressedBack()) {
      break;
    }
    int result = static_cast<int>(distinguisher.getColor());
    controller.printDisplay(4, "RGB: %d, %d, %d", distinguisher.raw_color.r,
                            distinguisher.raw_color.g, distinguisher.raw_color.b);
    controller.printDisplay(5, "Color Distance: %lf", distinguisher.last_distance);
    controller.printDisplay(6, "Color Number: %d", result);
    controller.printDisplay(7, "Color Name: %s", color_name[result]);

    controller.tslpTsk(4);
  }

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
