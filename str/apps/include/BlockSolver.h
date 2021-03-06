/**
 *  @file   BlockSolver.h
 *  @brief  ブロック並べ解決
 *  @author Futa.H
 */
#ifndef BLOCK_SOLVER_H
#define BLOCK_SOLVER_H

#include "BlockStrategy.h"
#include "Controller.h"
#include "Distinguisher.h"
#include "Lifter.h"
#include "Navigator.h"
#include "Selector.h"
#include "Walker.h"
#include <cstdint>
#include <vector>

class BlockSolver {
 public:
  BlockSolver() = default;
  explicit BlockSolver(Controller& controller_, Walker& walker_, std::int32_t ipc_,
                       const std::int16_t& targetBrightness_)
    : controller(controller_),
      walker(walker_),
      distinguisher(controller_),
      lifter(controller_),
      navigator(controller_, walker_),
      blockStrategy(ipc_),
      targetBrightness(targetBrightness_),
      ipc(ipc_)
  {
  }

  //! デモです。アリアに従って移動します。
  void demo();

  //! ブロック並べを攻略します。
  void run();

  //! ルートを移動します。
  void moveRoute(std::vector<int>& route);

  //! ブロックの色を取得し、blockColorに格納します。
  void getBlockColor();

  //! ブロック置き場を乗り越えます。
  void passCircle(const Color& circle_color);

  //! 指定した色のブロック置き場までライントレースします。
  void moveOnLineToColor(std::int8_t pwm, std::int16_t target, const Color& circle_color,
                         bool isRight);

  //! 指定した方角へ移動します。
  void moveDirection(const std::int8_t& nextPlace, bool remove_block = false);

  //! 今向いてる方角です。
  BlockSideBySide::Direction nowDirection = BlockSideBySide::Direction::WEST;

  //! バックして180ど回転し、来た方向へ戻ります。ブロックを放置するときに使います。
  void byeByeBlock();

  //! 次に向かうべき方角を切り替えます。
  BlockSideBySide::Direction getChangeDirection(std::int8_t angle);

  Selector::BlockColor convertSelectorColor(const Color& gameColor);
  void spinParkingArea();

 private:
  Controller controller;
  Walker walker;
  Distinguisher distinguisher;
  Lifter lifter;
  Navigator navigator;
  LineTracerWalker lineTracer;
  Color blockColor = Color::NONE;
  BlockSideBySide::BlockStrategy blockStrategy;
  std::int16_t targetBrightness;
  std::int8_t nowPlace = 8;
  std::int32_t ipc;
  Color convertColor(const BlockSideBySide::GameColor& gameColor);
};

#endif