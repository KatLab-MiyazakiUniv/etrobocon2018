/**
<<<<<<< HEAD
 *  @file   AIAnswer.cpp
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#include "AIAnswer.h"

void AIAnswer::run()
{
  // 20cm進む
  navigator.getNearbyBrightness(50);
}

// void AIAnswer::goLineTrace(float distance, std::int16_t target_brightness, std::int8_t pwm)
// {
//   float measure_distance = 0;
//   std::int16_t luminance = 0;
//   line_tracer.speedControl.setPid(2.0, 0.8, 0.1, pwm);
//   line_tracer.turnControl.setPid(1.1, 0.1, 0.2, target_brightness);
//   while(distance >= measure_distance) {
//     luminance = controller.getBrightness();
//     measure_distance = motor_angle.absoluteAngleMean(walker.get_count_L(), walker.get_count_R());
//     line_tracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
//     controller.printDisplay(5, "distance: %f", measure_distance);
//     if(line_tracer.getForward() < 0) {
//       walker.run(0, 0);
//     } else {
//       walker.run(line_tracer.getForward(), line_tracer.getTurn());
//     }
//     controller.tslpTsk(4); // 4msec周期
//   }
//   walker.reset();
// }
=======
*@file AIAnswer.cpp* @brief AIAnswerクラス* @author Tatsumi NISHIDA* /

#include "AIAnswer.h"

    // AIAnswerの数字を読み取る
    void AIAnswer::readAIAnswer(Controller controller)
{
}

// 数字に対応したブロックを動かす
void AIAnswer::solveAIAnswer(Controller controller, LineTracerWalker lineTracerWalker,
                             Distance distance)
{
}
>>>>>>> 751b48e58956ffd3ea049220ab92d433957e4fe9
