/**
 *  @file   BlockSolver.cpp
 *  @brief  ブロック並べ解決
 *  @author Futa.H
 */
#include "BlockSolver.h"

void BlockSolver::run(std::int16_t brightness)
{
  passCircle(Color::RED);
  turnLeft90();
  controller.tslpTsk(50);
  moveOnLineToColor(10, brightness, Color::BLUE, false);
  //  navigator.moveOnLine(690, brightness);  // 69cmライントレースで前進
}

void BlockSolver::moveOnLineToColor(std::int8_t pwm, std::int16_t target, const Color& circle_color,
                                    bool isLeft)
{
  std::int8_t buf = 1;
  if(isLeft == true) {
    buf = -1;
  }
  walker.reset();
  // ライントレースで用いるPID値のセット
  lineTracer.speedControl.setPid(2.0, 0.8, 0.1, pwm);
  lineTracer.turnControl.setPid(1.1, 0.1, 0.2, target);
  Color tmp;
  while(1) {
    tmp = distinguisher.getColor();
    // controller.printDisplay(10, "%4d %4d %4d", pwm, turn, target);
    lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), controller.getBrightness());
    if(circle_color == tmp || controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    } else {
      walker.run(lineTracer.getForward(), lineTracer.getTurn());
    }
    controller.tslpTsk(4);
  }
  walker.run(0, 0);
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

  controller.speakerPlayTone(controller.noteFs4, 100);

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
  navigator.spin(90);
}

void BlockSolver::turnRight90()
{
  //右折する関数
}

void BlockSolver::turnRight180()
{
  //運搬後に180度回転して後ろを向く関数
}