#include "BasicWalker.h"

void BasicWalker::setPidWithoutTarget(double valueP, double valueI, double valueD)
{
  p_value = valueP;
  i_value = valueI;
  d_value = valueD;
}

void BasicWalker::reset(void)
{
  walker.reset();
}

void BasicWalker::spin(bool rotationalDirection, int32_t angle)
{
  int8_t reverseValue = rotationalDirection == SPIN_RIGHT ? -1 : 1;

  reset();
  while((walker.get_count_R() * reverseValue)
        < (angle / 0.645)) {  // 数値は角度から回転数への変換に必要な値
    walker.run(0, (18 * reverseValue));
    controller.tslpTsk(4);
  }
  walker.run(0, 0);
}

void BasicWalker::spinToCheckBlackLine(bool rotationalDirection, int32_t angle)
{
  int8_t reverseValue = rotationalDirection == SPIN_RIGHT ? -1 : 1;

  reset();
  while((walker.get_count_R() * reverseValue)
        < (angle / 0.645)) {  // 数値は角度から回転数への変換に必要な値
    walker.run(0, (18 * reverseValue));

int16_t now_brightness = controller.getBrightness();
if(now_brightness < 120) {  //白が黒に近ずいたら
      walker.run(0, 0);
      controller.speakerPlayTone(controller.noteFs4, 100);  //音で確認.
      break;
    }
    controller.tslpTsk(4);
  }
  walker.run(0, 0);
}


void BasicWalker::goStraightToCheckBlackLine(int32_t target_forward, int32_t distance, int16_t target_brightness)
{
  speedControl.setPid(p_value, i_value, d_value, target_forward);
  while(((walker.get_count_L() + walker.get_count_R()) / 2) < distance) {
    forward = speedControl.calculateSpeedForPid(walker.get_count_L(), walker.get_count_R());
    walker.run(forward, 0);
    controller.tslpTsk(4);
    //リアルタイムで色を値を取得
    int16_t now_brightness = controller.getBrightness();

    if(now_brightness < 13) {
      walker.run(0, 0);
      controller.speakerPlayTone(controller.noteFs4, 100);  //音で確認.
      break;
    }
  }
  walker.run(0, 0);
}

void BasicWalker::goStraight(int32_t target_forward, int32_t distance, int16_t target_brightness)
{
  speedControl.setPid(p_value, i_value, d_value, target_forward);
  while(((walker.get_count_L() + walker.get_count_R()) / 2) < distance) {
    forward = speedControl.calculateSpeedForPid(walker.get_count_L(), walker.get_count_R());
    walker.run(forward, 0);
    controller.tslpTsk(4);
    //リアルタイムで色を値を取得
    // int16_t now_brightness = controller.getBrightness();
    // 		if(now_brightness<20){
    // walker.run(0,0);
    // 	ev3_speaker_play_tone( NOTE_FS4, 100 ); //音で確認.
    // break;
    // 		}
  }
  walker.run(0, 0);
}

void BasicWalker::backStraight(int32_t target_forward, int32_t distance)
{
  speedControl.setPid(p_value, i_value, d_value, target_forward);
  while(((walker.get_count_L() + walker.get_count_R()) / 2) * -1 < distance) {
    forward = speedControl.calculateSpeedForPid(walker.get_count_L(), walker.get_count_R());
    walker.run(forward, 0);
    controller.tslpTsk(4);
  }
}
