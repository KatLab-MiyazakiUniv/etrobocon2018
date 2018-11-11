/**
 *  @file   BlockSolver.cpp
 *  @brief  ブロック並べ解決
 *  @author Futa.H
 */
#include "BlockSolver.h"

void BlockSolver::run()
{
  // 最初の8番までのライントレース
  navigator.moveOnLine(500, targetBrightness, 55);
  moveOnLineToColor(45, targetBrightness - 10, Color::RED, false);

  // ブロックがある0番までの移動
  std::vector<int8_t> route{ 8, 12, 13 };
  moveRoute(route);

  // ブロック読み取り(青だとする。)
  getBlockColor();
  if(blockColor == Color::BLUE) {
    // 青ブロックを10番まで移動。その後、9に戻る
    moveRoute({ 13, 9, 10 });
    byeByeBlock();
  }

  // 9番までの移動とパーキングの方を向く。
  route = { 10, 9, 5, 6, 7, 11 };
  moveRoute(route);
  passCircle(Color::GREEN);
  navigator.spin(90, false);
}

void BlockSolver::byeByeBlock()
{
  std::int8_t returnPlace = blockStrategy.blockArea.colorBlockPlaceArray[nowPlace]
                                ->black_line[getChangeDirection(2)]
                                ->getPlaceCord();
  moveDirection(returnPlace, true);
}

void BlockSolver::moveRoute(std::vector<int8_t> route)
{
  bool isFirst = true;
  for(auto next_n : route) {
    if(isFirst == true) {
      isFirst = false;
      continue;
    } else if(next_n == nowPlace) {
      continue;
    }
    controller.tslpTsk(50);
    moveDirection(next_n);
  }
  controller.speakerPlayTone(controller.noteFs4, 300);
  return;
}

void BlockSolver::moveDirection(const std::int8_t& nextPlace, bool remove_block)
{
  std::int8_t offset = 5;
  auto nextDirection = blockStrategy.blockArea.getDirection(nowPlace, nextPlace);
  auto nowColor = convertColor(blockStrategy.blockArea.colorBlockPlaceArray[nowPlace]->getColor());
  auto nextColor
      = convertColor(blockStrategy.blockArea.colorBlockPlaceArray[nextPlace]->getColor());

  std::int8_t diffDirection
      = static_cast<std::int8_t>(nextDirection) - static_cast<std::int8_t>(nowDirection);
  std::int16_t black_line_length = 250;
  if(nextDirection == BlockSideBySide::Direction::EAST
     || nextDirection == BlockSideBySide::Direction::WEST) {
    black_line_length = 300;
  }
  if(diffDirection == 0) {
    // 前方向に行く場合
    passCircle(nowColor);
  } else if(diffDirection == -1 || diffDirection == 3) {
    // 左方向に行く場合
    passCircle(nowColor);
    navigator.spin(110, false);
    //spinToBlack(false);
    nowDirection = getChangeDirection(-1);
  } else if(diffDirection == 1 || diffDirection == -3) {
    // 右方向に行く場合
    passCircle(nowColor);
    navigator.spin(90, true);

    //spinToBlack(true);
    nowDirection = getChangeDirection(1);
  } else if(remove_block == false) {
    // 後方向に行く場合
    black_line_length -= 100;
    navigator.spin(170, true);

    //spinToBlack(true);
    nowDirection = getChangeDirection(2);
  } else {
    // 後方向に行く場合
    black_line_length -= 200;
    navigator.back(100);
    //spinToBlack(true);
    navigator.spin(170, true);

    nowDirection = getChangeDirection(2);
  }
  controller.speakerPlayTone(controller.noteFs4, 150);
  navigator.moveOnLine(black_line_length - 40, targetBrightness - offset, 30);
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

BlockSideBySide::Direction BlockSolver::getChangeDirection(std::int8_t angle)
{
  std::int8_t tmp = static_cast<std::int8_t>(nowDirection) + angle;
  if(tmp > 3) {
    tmp = tmp % 4;
  } else if(tmp < 0) {
    tmp = 4 + angle;
  }
  return static_cast<BlockSideBySide::Direction>(tmp);
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
  //navigator.move(15);
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
    if(count >= 2 || controller.buttonIsPressedBack()) {
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
  walker.run(5, 0);
  Color tmp;
  std::int8_t count = 0;
  while(1) {
    tmp = distinguisher.getColor();
    if(Color::BLACK == tmp || Color::WHITE == tmp) {
        count++;
    }else{      
      if(count > 0) {
        count--;
      }
    }
    if(count >= 1 || controller.buttonIsPressedBack()) {
      walker.run(0, 0);
      break;
    }
    controller.tslpTsk(4);
  }
  navigator.move(10, 5);
}
