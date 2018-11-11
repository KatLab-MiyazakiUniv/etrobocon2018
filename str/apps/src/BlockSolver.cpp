/**
 *  @file   BlockSolver.cpp
 *  @brief  ブロック並べ解決
 *  @author Futa.H
 */
#include "BlockSolver.h"

void BlockSolver::run()
{
  std::vector<int8_t> route{ 8, 9, 10, 6, 5 };
  std::int8_t i = 4;

  std::int8_t prev_n;
  bool isFirst = true;
  for(auto next_n : route) {
    if(isFirst == true) {
      prev_n = next_n;
      isFirst = false;
      continue;
    }
    controller.printDisplay(
        i, "%d %d",
        static_cast<int>(blockStrategy.blockArea.colorBlockPlaceArray[prev_n]->getColor()),
        static_cast<int>(blockStrategy.blockArea.getDirection(prev_n, next_n)));
    i++;
    prev_n = next_n;
    moveDirection(next_n);
  }
  return;
}

void BlockSolver::moveDirection(const std::int8_t& nextPlace)
{
  std::int8_t offset = 10;
  auto nextDirection = blockStrategy.blockArea.getDirection(nowPlace, nextPlace);
  auto nowColor = convertColor(blockStrategy.blockArea.colorBlockPlaceArray[nowPlace]->getColor());
  auto nextColor
      = convertColor(blockStrategy.blockArea.colorBlockPlaceArray[nextPlace]->getColor());

  std::int8_t diffDirection
      = static_cast<std::int8_t>(nextDirection) - static_cast<std::int8_t>(nowDirection);
  if(diffDirection == 0) {
    // 前方向に行く場合
    passCircle(nowColor);
  } else if(diffDirection == -1 || diffDirection == 3) {
    // 左方向に行く場合
    passCircle(nowColor);
    navigator.spin(100, false);
    changeDirection(-1);
  } else if(diffDirection == 1 || diffDirection == -3) {
    // 右方向に行く場合
    passCircle(nowColor);
    navigator.spin(100, true);
    changeDirection(1);
  } else {
    // 後方向に行く場合
  }
  navigator.moveOnLine(300, targetBrightness - offset, 45);
  moveOnLineToColor(30, targetBrightness - offset, nextColor, false);
  nowPlace = nextPlace;
}

Color BlockSolver::convertColor(const BlockSideBySide::GameColor& gameColor)
{
  if(gameColor == BlockSideBySide::GameColor::RED) {
    return Color::RED;
  } else if(gameColor == BlockSideBySide::GameColor::BLUE) {
    return Color::BLUE;
  } else if(gameColor == BlockSideBySide::GameColor::GREEN) {
    return Color::GREEN;
  } else if(gameColor == BlockSideBySide::GameColor::YELLOW) {
    return Color::YELLOW;
  }
  return Color::NONE;
}

void BlockSolver::changeDirection(std::int8_t angle)
{
  std::int8_t tmp = static_cast<std::int8_t>(nowDirection) + angle;
  if(tmp > 3) {
    tmp = -1 + angle;
  } else if(tmp < 0) {
    tmp = 4 + angle;
  }
  nowDirection = static_cast<BlockSideBySide::Direction>(tmp);
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
  lineTracer.speedControl.setPid(2.0, 0.8, 0.1, pwm);
  lineTracer.turnControl.setPid(1.1, 0.1, 0.2, target);
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
    if(count >= 10 || controller.buttonIsPressedBack()) {
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