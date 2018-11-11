/**
 *  @file   AIAnswerBlock.h
 *  @brief  AIアンサーのブロックを並べる
 *  @author T.N.Revolution
 */

#include "AIAnswerBlock.h"

void AIAnswerBlock::block00()
{
  navigator.moveOnLine(250, target_brightness);
  navigator.move(100);
  navigator.spin(true, 90);
  navigator.moveToColor(250, target_brightness, Color::RED);
}

void AIAnswerBlock::block01() {}
