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
  navigator.move(80, 5);
  controller.speakerPlayTone(controller.noteFs4, 100);
  walker.run(5, 0);
  Color tmp;
  std::int8_t count = 0;

  controller.speakerPlayTone(controller.noteFs4, 100);

  while(1) {
    tmp = distinguisher.getColor();
    if(Color::BLACK == tmp || Color::WHITE == tmp) {
      count++;
    } else {
      count = 0;
    }
    if(count > 3 || controller.buttonIsPressedBack()) {
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