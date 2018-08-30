/**
 * ファイル名 : app.c
 *
 * 概要 : ETロボコンのTOPPERS/HRP2用Cサンプルプログラム
 *
 * 注記 : Bluetooth通信リモートスタート機能付き
 */

#include "ev3api.h"
#include "app.h"
#include "util.h"
#include "EtRobocon2018.h" // ETロボコン2017
#include "SelfLocalization.h"

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

static int  g_bluetooth_command = 0; // Bluetoothコマンド 1:リモートスタート
static FILE *g_bluetooth = NULL;     // Bluetoothファイルハンドル

/* メインタスク */
void main_task( intptr_t unused )
{
    /* Open Bluetooth file */
    g_bluetooth = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( g_bluetooth != NULL );

    /* Bluetooth通信タスクの起動 */
    act_tsk( BT_TASK );


    msg_f("ET-Robocon2018", 1);
    msg_f(" create from github.com/korosuke613/etrobocon2018", 2);

    EtRobocon2018 etrobocon;
    etrobocon.start( g_bluetooth_command );



    ter_tsk( BT_TASK );
    fclose( g_bluetooth );

    ext_tsk();
}

/**
 * 概要 : Bluetooth通信によるリモートスタート。
 *        Tera Termなどのターミナルソフトから、
 *        ASCIIコードで1を送信すると、リモートスタートする。
 * 引数 : unused
 * 返り値 : なし
 */
void bt_task( intptr_t unused )
{
    while( 1 )
    {
        uint8_t c = fgetc( g_bluetooth ); /* 受信 */
        switch( c )
        {
        case '1':
            g_bluetooth_command = 1;
            break;
        default:
            break;
        }
        fputc( c, g_bluetooth ); /* エコーバック */
    }
}
/**
 * Logフォルダにlog数字.csvという名前でファイルを保存していく
 * Logフォルダを消すと動かなくなる
 * 消すときはcsvファイルだけを消すように
 * 
 * volt バッテリの電圧取得
 * amp  アンペア取得
 * motor_power モータのパワーを取得
 * motor_angle モータの角位置を取得(PORT_3)
**/
void sensor_log_task( intptr_t unused )
{
  FILE *file;
  int volt = 0;
  int amp  = 0;
  //int motor_power = 0;
  //int motor_angle = 0;
  int count = 0;
  int log_file_number = 0;
  char log_file_name[16];
  bool flag = true;
  while(flag == true){
    sprintf(log_file_name, "%s%d%s", "/Log/log", log_file_number, ".csv");
    msg_f(log_file_name, 3);
    file = fopen(log_file_name, "r");
    if(file == NULL) { // ファイル名がダブらない場合
    fclose(file);
    file = fopen(log_file_name, "a");
    fprintf(file, "Count, Voltage, Ampere\n");
    flag = false;

    } else { // 同じlogファイル名が存在する場合
    log_file_number++;
    }
  }
  ev3_speaker_play_tone( NOTE_FS4, 200 );
  while(1){
    if(ev3_button_is_pressed(BACK_BUTTON)){ // 戻るボタンを押すとlog取得終了
    ev3_speaker_play_tone( NOTE_FS4, 500 );
    fclose(file);
    unl_mtx(LOG); //処理の終了
    break;
    }
    count++;
    volt = ev3_battery_voltage_mV();
    amp  = ev3_battery_current_mA();
    //motor_power = ev3_motor_get_power();
    // motor_angle = ev3_motor_get_counts(PORT_3);
    // ファイル書き込み
    // fprintf(file, "%d,%d,%d,%d,%d\n", volt, amp, motor_power, motor_angle);
    fprintf(file, "%d,%d,%d\n", count, volt, amp);
    // 12msec周期起動
    // tslp_tsk(12);
  }
}
