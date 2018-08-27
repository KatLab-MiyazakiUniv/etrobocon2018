/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

Parking::Parking() : colorSensor(PORT_3) {}

void Parking::runParpendicular(int16_t target_brightness, LineTracerWalker lineTracer,
                               int16_t black, int16_t white)
{
  BasicWalker basicWalker;

  msg_f("Do ParallelParking...", 0);
  basicWalker.setPidWithoutTarget(17.0, 1.0, 0.1);
  basicWalker.goStraight_b(30, 1000, target_brightness, colorSensor);

  basicWalker.spin(basicWalker.SPIN_LEFT, 44);

  waitThreeTimes();
  // walker.run(1, 3);
  //ライントレース開始
  int count = 0;
  while(1) {
    rgb_raw_t rgb;
    colorSensor.getRawColor(rgb);
    int16_t now_brightness = 0;
    now_brightness = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
    lineTracer.speedControl.setPid(17.0, 1.0, 0.1, 20.0);
    lineTracer.turnControl.setPid(4.0, 1.0, 0.8, target_brightness);

    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), now_brightness);
    if(lineTracer.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    if(ev3_button_is_pressed(BACK_BUTTON)) {
      walker.run(0, 0);
      break;
    }

    //         if(now_brightness>100){ //ライントレースを修了する条件
    // walker.run(0, 0);
    // break;
    //         }

    //  if(black + 40 >= now_brightness){  //ブラックを読み込んだら
    //             count = 0;
    //             ev3_speaker_play_tone( NOTE_CS4, 100 );
    //         }else if( white - 70<= now_brightness){
    //             count++;

    //         }

    count++;

    if(count > 800) {
      waitThreeTimes();
      break;
    }
    tslp_tsk(4);
  }  // whileのおわり
  // basicWalker.goStraight( 30, 600 );
  // basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
  // waitThreeTimes();

  basicWalker.setPidWithoutTarget(17.0, 1.0, 0.1);
  basicWalker.reset();
  basicWalker.goStraight(30, 350, target_brightness, colorSensor);
}

void Parking::runParallelrun()
{
  BasicWalker basicWalker;

  msg_f("Do ParpendicularParking...", 0);

  basicWalker.reset();
  basicWalker.setPidWithoutTarget(4.0, 2.0, 0.02);
  //  basicWalker.goStraight( 150, 450 );
  basicWalker.setPidWithoutTarget(1.0, 2.0, 0.02);
  //    basicWalker.goStraight( 50, 150 );
  basicWalker.reset();

  basicWalker.spin(basicWalker.SPIN_RIGHT, 90);
  basicWalker.reset();
  tslp_tsk(100);

  // basicWalker.goStraight( 150, 550 );
  basicWalker.setPidWithoutTarget(1.0, 2.0, 0.02);
  //  basicWalker.goStraight( 50, 250 );
  basicWalker.reset();

  waitThreeTimes();
}

void Parking::waitThreeTimes()
{
  walker.run(0, 0);
  ev3_speaker_play_tone(NOTE_FS4, 100);
  tslp_tsk(1000);
  ev3_speaker_play_tone(NOTE_FS4, 100);
  tslp_tsk(1000);
  ev3_speaker_play_tone(NOTE_FS4, 100);
  tslp_tsk(1000);
  ev3_speaker_play_tone(NOTE_FS5, 800);
}
