/**
 *  @file   AIAnswerBlock.h
 *  @brief  AIアンサーのブロックを並べる
 *  @author T.N.Revolution
 */

#include "AIAnswerBlock.h"

/**
 *  [AIAnswerBlock::throwBlock]
 *  @brief ブロックを指定した方向へ放った後，後ろを向き直す
 *  @param angle_direction [false = 左回転，true = 右回転]
 */
void AIAnswerBlock::throwBlock(bool angle_direction)
{
  navigator.spin(35, angle_direction);
  lifter.liftUp(45, 10);
  lifter.liftDown(0, 3);
  navigator.spin(145, angle_direction);
}

void AIAnswerBlock::block00()
{
  navigator.moveOnLine(250, target_brightness, 30);
  navigator.move(100);
  navigator.spin(90, true);
  navigator.moveToColor(250, target_brightness, Color::RED, 30);
  throwBlock(false);

  navigator.moveOnLine(150, target_brightness, 30);
  navigator.moveToColor(250, target_brightness, Color::BLUE, 30);
  throwBlock(true);

  navigator.moveOnLine(150, target_brightness, 30);
  navigator.spin(90);
  navigator.moveOnLine(100, target_brightness, 30);
  navigator.moveToColor(200, target_brightness, Color::GREEN, 30);
  throwBlock(false);

  navigator.moveOnLine(100, target_brightness, 30);
  navigator.moveToColor(200, target_brightness, Color::YELLOW, 30);
  throwBlock(true);

  navigator.moveOnLine(100, target_brightness, 30);
  navigator.spin(90);
  navigator.moveToColor(200, target_brightness, Color::RED, 30);
  throwBlock(false);
}

void AIAnswerBlock::block01() {}
