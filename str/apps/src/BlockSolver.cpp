/**
 *  @file   BlockSolver.cpp
 *  @brief  ブロック並べ解決
 *  @author Futa.H
 */
#include "BlockSolver.h"

void BlockSolver::run(const std::int16_t& brightness)
{
  // distinguisher.threshold_distance = 200;
  // moveOnLineToColor(50, brightness, Color::GREEN, false);
  auto offset = 10;
  moveOnLineToColor(50, brightness - offset, Color::RED, false);
  getBlockColor();
  passCircle(Color::RED);
  navigator.spin(100, false);
  moveOnLineToColor(50, brightness - offset, Color::BLUE, false);
  // getBlockColor();
  passCircle(Color::BLUE);
  navigator.spin(100, true);
  moveOnLineToColor(50, brightness - offset, Color::GREEN, false);
  // getBlockColor();
  passCircle(Color::GREEN);
  moveOnLineToColor(50, brightness - offset, Color::RED, false);
  // getBlockColor();
  //  navigator.moveOnLine(690, brightness);  // 69cmライントレースで前進
}

void BlockSolver::moveOnLineToColor(std::int8_t pwm, std::int16_t target, const Color& circle_color,
                                    bool isLeft)
{
  std::int8_t buf = 1;
  controller.tslpTsk(50);

  if(isLeft == true) {
    buf = -1;
  }
  walker.reset();
  // ライントレースで用いるPID値のセット
  lineTracer.speedControl.setPid(2.0, 0.0, 0.1, pwm);
  lineTracer.turnControl.setPid(1.1, 0.2, 0.2, target);
  Color tmp;
  std::int8_t count = 0;
  navigator.move(15);
  while(1) {
    tmp = distinguisher.getColor();
    // controller.printDisplay(10, "%4d %4d %4d", pwm, turn, target);
    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), controller.getBrightness());
    if(circle_color == tmp) {
      count++;
    } else {
      if(count > 0) {
        count--;
      }
      walker.run(lineTracer.getForward(), lineTracer.getTurn() * buf);
    }
    if(count >= 5 || controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }
    controller.tslpTsk(4);
  }
  walker.run(0, 0);
  controller.tslpTsk(50);
}

void BlockSolver::getBlockColor()
{
  //ブロックの色をチェックして保持する
  controller.speakerPlayTone(controller.noteFs4, 100);
  lifter.liftUp(45, 10);
  blockColor = distinguisher.getColor();
  lifter.liftDown(0, 3);
  lifter.liftUp(1.5, 5);
}

void BlockSolver::passCircle(const Color& circle_color)
{
  controller.speakerPlayTone(controller.noteFs4, 100);
  navigator.move(90, 5);
  controller.speakerPlayTone(controller.noteFs4, 100);
  walker.run(5, 0);
  Color tmp;
  while(1) {
    tmp = distinguisher.getColor();
    if(Color::BLACK == tmp || Color::WHITE == tmp || controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }
    controller.tslpTsk(4);
  }
  controller.speakerPlayTone(controller.noteFs4, 100);
}

void BlockSolver::turnLeft90()
{
  controller.speakerPlayTone(controller.noteFs4, 100);
  navigator.spin(90);
  controller.speakerPlayTone(controller.noteFs4, 100);
}

void BlockSolver::turnRight90()
{
  //右折する関数
  controller.speakerPlayTone(controller.noteFs4, 100);
  navigator.spin(90, true);
  controller.speakerPlayTone(controller.noteFs4, 100);
}

void BlockSolver::turnRight180()
{
  //運搬後に180度回転して後ろを向く関数
}