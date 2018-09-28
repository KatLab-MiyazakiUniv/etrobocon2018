/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

void Parking::runParpendicular(int16_t target_brightness, LineTracerWalker lineTracer,
                               int16_t black, int16_t white)
{
  BasicWalker basicWalker{ controller };

  controller.printDisplay(0, "Do ParallelParking...");
  basicWalker.setPidWithoutTarget(5.0, 0.8, 0.2);
  basicWalker.goStraightToCheckBlackLine(30, 1000, target_brightness);

  basicWalker.spin(basicWalker.SPIN_LEFT, 70);
  // waitThreeTimes();
  basicWalker.spinToCheckBlackLine(basicWalker.SPIN_RIGHT, 70);
  basicWalker.reset();

  // waitThreeTimes();

  //ライントレース開始
  int count = 0;
  while(1) {
    int16_t now_brightness = controller.getBrightness();
    lineTracer.speedControl.setPid(5.0, 0.8, 0.2, 20.0);
    lineTracer.turnControl.setPid(2.2, 0.1, 0.35, target_brightness);  // 2.0,0.2,0.4 最高か

    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), now_brightness);
    if(lineTracer.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    if(controller.buttonIsPressedBack()) {
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

    if(count > 950) {
      waitThreeTimes();
      break;
    }
    controller.tslpTsk(4);
  }  // whileのおわり

  basicWalker.setPidWithoutTarget(5.0, 0.8, 0.2);
  basicWalker.reset();
  basicWalker.goStraight(30, 380);
  waitThreeTimes();
}

void Parking::runParallel(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
  LineTracerWalker lineTracer;
  BasicWalker basicWalker{ controller };
  int count = 0;
  int16_t grayBrightness = (gray + white) / 2;

  controller.printDisplay(6, ">>>>> Do ParallelParking... <<<<<");
  while(1) {
    int16_t luminance = controller.getBrightness();
    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);

    if(lineTracer.getForward() < 0) {
      walker.run(0, 0);
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    if(controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }

    /*if(gray + 2 >= luminance && gray - 2 <= luminance){  //グレーを読み込んだら
        count++;
        ev3_speaker_play_tone( NOTE_FS4, 100 );
    }else{
        count = 0;
    }*/

    if(black + 35 >= luminance) {  //ブラックを読み込んだら
      count = 0;
      controller.speakerPlayTone(controller.noteFs4, 100);
    } else if(white + 30 >= luminance && white - 70 <= luminance) {
      count++;
    }

    if(count > 250) {
      waitThreeTimes();
      break;
    }

    lineTracer.speedControl.setPid(17.0, 1.0, 0.1, 30.0);

    if(grayBrightness + 3 >= luminance && grayBrightness - 1 <= luminance) {
      lineTracer.turnControl.setPid(4.0, 1.0, 0.8, grayBrightness);
    } else {
      lineTracer.turnControl.setPid(4.0, 1.0, 0.8, brightness);
    }
    controller.tslpTsk(4);
  }
  basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
  basicWalker.goStraight(60, 600);
  basicWalker.spin(basicWalker.SPIN_LEFT, 40);
  // basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
  basicWalker.goStraight(60, 580);
  basicWalker.spin(basicWalker.SPIN_LEFT, 90);
  basicWalker.goStraight(30, 10);
  // basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
}

void Parking::waitThreeTimes()
{
  walker.run(0, 0);
  controller.speakerPlayTone(controller.noteFs4, 100);
  controller.tslpTsk(1000);
  controller.speakerPlayTone(controller.noteFs4, 100);
  controller.tslpTsk(1000);
  controller.speakerPlayTone(controller.noteFs4, 100);
  controller.tslpTsk(1000);
  controller.speakerPlayTone(controller.noteFs4, 800);
}
