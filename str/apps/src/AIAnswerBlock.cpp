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
  lifter.liftUp(55, 30);
  lifter.liftDown(0, 3);
  navigator.spin(150, angle_direction);
}

void AIAnswerBlock::block00()
{
  navigator.moveOnLine(250, target_brightness, 30, true);  // 左エッジ
  navigator.move(100);
  navigator.spin(100, true);                                            // 100度右回転
  navigator.moveToColor(250, target_brightness, Color::RED, 30, true);  // 左エッジ
  throwBlock(false);                                                    // 左に放る

  navigator.moveOnLine(100, target_brightness, 30, false);  // 右エッジ
  navigator.move(100);
  navigator.moveToColor(200, target_brightness, Color::BLUE, 30, false);  // 右エッジ
  throwBlock(true);                                                       // 右に放る

  navigator.moveOnLine(100, target_brightness, 30, false);                // 右エッジ
  navigator.move(50);                                                     // 5cmただ進む
  navigator.spin(100, false);                                             // 100度左回転
  navigator.moveOnLine(200, target_brightness, 30, false);                // 右エッジ
  navigator.move(100);                                                    // 10cmただ進む
  navigator.spin(100, true);                                              // 100度右回転
  navigator.moveToColor(200, target_brightness, Color::GREEN, 30, true);  // 左エッジ
  throwBlock(false);                                                      // 左に放る

  navigator.moveOnLine(100, target_brightness, 30, false);                  // 右エッジ
  navigator.move(150);                                                      // 15cmただ進む
  navigator.moveToColor(100, target_brightness, Color::YELLOW, 30, false);  // 右エッジ
  throwBlock(true);                                                         // 右に放る

  navigator.moveOnLine(100, target_brightness, 30, true);  // 左エッジ
  navigator.spin(100, false);                              // 100度左回転
  navigator.moveOnLine(200, target_brightness, 30, true);  // 左エッジ
  navigator.move(100);
  navigator.spin(100, true);                                            // 100度右回転
  navigator.moveToColor(200, target_brightness, Color::RED, 30, true);  // 左エッジ
  // navigator.move(100);
  throwBlock(false);  // 左に放る

  navigator.moveOnLine(100, target_brightness, 30, false);  // 右エッジ
  navigator.move(150);
  navigator.moveToColor(100, target_brightness, Color::RED, 30, false);  // 右エッジ
  throwBlock(true);                                                      // 右に放る

  navigator.moveOnLine(100, target_brightness, 30, true);  // 左エッジ
  navigator.move(100);
  navigator.spin(100, false);  // 100度左回転
  navigator.moveOnLine(150, target_brightness, 30, true);
}

// ただブロックを00におくだけ
void AIAnswerBlock::block01()
{
  navigator.moveOnLine(250, target_brightness, 30, true);  // 左エッジ
  navigator.move(60);
  navigator.spin(90, true);                                             // 90度右回転
  navigator.moveToColor(250, target_brightness, Color::RED, 30, true);  // 左エッジ
  throwBlock(false);                                                    // 左に放る

  navigator.moveOnLine(60, target_brightness, 30, false);  // 右エッジ
  navigator.move(150);
  navigator.moveToColor(200, target_brightness, Color::BLUE, 30, false);  // 右エッジ
  throwBlock(true);                                                       // 右に放る

  navigator.moveOnLine(100, target_brightness, 30, false);  // 右エッジ
  navigator.move(50);                                       // 5cmただ進む
  navigator.spin(110, false);                               // 110度左回転
  navigator.moveOnLine(750, target_brightness, 30, true);   // 左エッジ
}
