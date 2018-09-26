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
  basicWalker.setPidWithoutTarget(17.0, 1.0, 0.1);
  basicWalker.goStraight_b(30, 1000, target_brightness);

  basicWalker.spin(basicWalker.SPIN_LEFT, 44);

  waitThreeTimes();
  // walker.run(1, 3);
  //ライントレース開始
  int count = 0;
  while(1) {
    int16_t now_brightness = controller.getBrightness();
    lineTracer.speedControl.setPid(17.0, 1.0, 0.1, 20.0);
    lineTracer.turnControl.setPid(4.0, 1.0, 0.8, target_brightness);

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

    count++;

    if(count > 800) {
      waitThreeTimes();
      break;
    }
    controller.tslpTsk(4);
  }  // whileのおわり
  // basicWalker.goStraight( 30, 600 );
  // basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
  // waitThreeTimes();

  basicWalker.setPidWithoutTarget(17.0, 1.0, 0.1);
  basicWalker.reset();
  basicWalker.goStraight(30, 350);
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


    if(black + 35 >= luminance) {  //ブラックを読み込んだら
      count = 0;
      //controller.speakerPlayTone(controller.noteFs4, 100);
    } else if(white + 30 >= luminance && white - 70 <= luminance) {
      count++;
    }

    if(controller.ev3_battery_voltage() > 1390 &&  count > 260) { //250
      controller.printDisplay(9, ">>  13 <<<");
      waitThreeTimes();
      basicWalker.reset();
      basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
      basicWalker.goStraight(60, 300);
      break;
    }else if(controller.ev3_battery_voltage() > 1350 &&  count > 270) { //250
      controller.printDisplay(9, ">>  12 <<<");
      waitThreeTimes();
      basicWalker.reset();
      basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
      basicWalker.goStraight(60, 300);
      break;
    }else if(count > 280){
      controller.printDisplay(9, ">>  etc <<<");
      waitThreeTimes();
      basicWalker.reset();
      basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
      basicWalker.goStraight(60, 300);
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
  //sprintf(aa, "%f", controller.ev3_battery_voltage());

  //controller.printDisplay(5, aa);
  basicWalker.reset();
  basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
  basicWalker.spin(basicWalker.SPIN_LEFT, 40);
  // basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
  basicWalker.goStraight(60, 500);
  basicWalker.spin(basicWalker.SPIN_LEFT, 90);
  //basicWalker.goStraight(30, 10);
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
