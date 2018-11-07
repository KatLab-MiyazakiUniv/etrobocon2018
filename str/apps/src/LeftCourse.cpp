/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

void LeftCourse::setFirstCode(int32_t code)
{
  firstCode = code;
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
<<<<<<< HEAD
=======
  // getSensor();
>>>>>>> 751b48e58956ffd3ea049220ab92d433957e4fe9
  // runNormalCourse(brightness);

  // controller.printDisplay(3, "Finished NormalArea");

  // Puzzle
  runBlockRange();
  controller.printDisplay(3, "Finished Puzzle");
  target_brightness = brightness;
<<<<<<< HEAD
  // Park
  // solveAiAnser();
  // runParking(brightness, black, white, gray);
  // runGoStraight();
=======
  solveAiAnswer();
  runParking(brightness, black, white, gray);
  runGoStraight();
>>>>>>> 751b48e58956ffd3ea049220ab92d433957e4fe9
}

void LeftCourse::solveAiAnswer() {}

// void LeftCourse::solveAiAnser()
// {
//   controller.printDisplay(3, "aiAnswer Start!!");
//   controller.speakerPlayTone(controller.noteFs4, 200);
//   walker.run(30, 0);
//   controller.speakerPlayTone(controller.noteFs4, 200);
//   controller.tslpTsk(2200);
//   controller.speakerPlayTone(controller.noteFs4, 200);
//   // その場に止まる
//   walker.reset();
//   controller.speakerPlayTone(controller.noteFs4, 200);
//   // 反時計回りに90°回転
//   walker.angleChange(90, 1);
//   controller.speakerPlayTone(controller.noteFs4, 200);
//   walker.run(30, 0);
//   controller.tslpTsk(400);
//   //  walker.run(0, 0);
//   controller.printDisplay(3, "aiAnswer1 Finished");
//   // ここから黒線探しの旅
//   while(1) {
//     // 現在の色取得
//     int16_t luminance = controller.getBrightness();
//     // 黒検知
//     if(luminance <= 11) {
//       runGoBlack();
//       // lineTracer.speedControl.setPid(5.0, 1.0, 0.1, 90.0);
//       // lineTracer.turnControl.setPid(2.0, 1.0, 0.14, target_brightness);
//       break;
//       // それ以外
//     } else {
//       walker.run(10, 0);
//     }
//     if(controller.buttonIsPressedBack()) {
//       walker.reset();
//       break;
//     }
//     controller.tslpTsk(4);
//   }  // whileのおわり
// }

// 黒線上を走る
void LeftCourse::runGoBlack()
{
  walker.reset();
  // 時計回りに45°回転
  walker.angleChange(45, -1);
  walker.run(10, 0);
  controller.tslpTsk(1000);
  while(1) {
    // 現在の色取得
    int16_t luminance = controller.getBrightness();
    if(luminance <= 51) {
      // 左に30度回転
      controller.tslpTsk(100);
      walker.angleChange(30, 1);
      // basic.spin(basic.SPIN_LEFT, 30);
      runGoStraight();
      break;
    }
    if(controller.buttonIsPressedBack()) {
      walker.reset();
      break;
    }
    controller.tslpTsk(4);
  }
}

void LeftCourse::runGoStraight()
{
  walker.reset();
  int16_t luminance = 0;
  int32_t aiDistance = 0;
  lineTracer.speedControl.setPid(2.0, 0.8, 0.1, 20.0);
  lineTracer.turnControl.setPid(1.1, 0.1, 0.2, target_brightness);  // 2.0,0.2,0.4 最高か
  while(1) {
    luminance = controller.getBrightness();
    aiDistance = motor_angle.absoluteAngleMean(walker.get_count_L(), walker.get_count_R());
    // 走る
    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
    controller.printDisplay(4, "%d", aiDistance);
    if(lineTracer.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    if(controller.buttonIsPressedBack()) {
      walker.reset();
      break;
    }
    if(aiDistance >= 1200) {
      walker.reset();

      break;
    }
    controller.tslpTsk(4);
  }
}

// センサの値を取得（7つ）
void LeftCourse::getSensor()
{
  FILE* file;
  Controller controller;
  bool flag = true;
  int16_t luminance;
  int count = 0;
  char log_file_name[16];
  int log_file_number = 0;

  while(flag == true) {
    sprintf(log_file_name, "%s%d%s", "/AIAnswerLog/log", log_file_number, ".csv");
    controller.printDisplay(3, log_file_name);
    file = fopen(log_file_name, "r");
    if(file == NULL) {  // ファイル名がダブらない場合
      fclose(file);
      file = fopen(log_file_name, "a");
      fprintf(file, "1, 2, 3, 4, 5, 6, 7\n");
      flag = false;

    } else {  // 同じlogファイル名が存在する場合
      log_file_number++;
    }
  }
  while(1) {
    luminance = controller.getBrightness();
    controller.printDisplay(5, "Brightness: %d", luminance);
    if(controller.buttonIsPressedBack()) {   // 戻るボタンを押すとlog取得終了
      ev3_speaker_play_tone(NOTE_FS6, 500);  // 終了音
      fclose(file);
      // unl_mtx(LOG);  //処理の終了
      break;
    }
    // 真ん中ボタン
    if(controller.buttonIsPressedEnter()) {
      if(count == 6) {
        fprintf(file, "%d\n", luminance);
        count = 0;
        ev3_speaker_play_tone(NOTE_A5, 200);
        controller.tslpTsk(500);
      } else if(count <= 5 && 0 <= count) {
        fprintf(file, "%d,", luminance);
        ev3_speaker_play_tone(NOTE_A4, 200);
        controller.tslpTsk(500);
        count++;
      }
    }
    // 4msec周期起動
    tslp_tsk(4);
  }
}

// void LeftCourse::runParking(int16_t brightness, int16_t gray)
void LeftCourse::runParking(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  Parking parking{ controller };
  parking.runParallel(brightness, black, white, gray);
}

void LeftCourse::runNormalCourse(int16_t brightness)
{
  LeftNormalCourse normalCourse;
  bool isNormalCourse;
  // NormalCourseを抜けるまでループする
  while(1) {
    auto luminance = controller.getBrightness();
    controller.printDisplay(4, "Brightness: %d, Target: %d", luminance, brightness);
    if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
      controller.speakerPlayTone(controller.noteFs6, 100);
    isNormalCourse = normalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R(),
                                                  luminance, brightness);

    normalCourse.runOrStop(walker);

    if(!isNormalCourse) {
      walker.run(0, 0);
      break;
    }
    if(controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }

    controller.tslpTsk(4);  // 4msec周期起動
  }
}

void LeftCourse::runBlockRange() {}
