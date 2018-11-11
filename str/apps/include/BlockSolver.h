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
#include "Walker.h"
#include <cstdint>
#include <vector>

class BlockSolver {
 public:
  BlockSolver() = default;
  explicit BlockSolver(Controller& controller_, Walker& walker_, const std::int32_t& ipc)
    : controller(controller_),
      walker(walker_),
      distinguisher(controller_),
      lifter(controller_),
      navigator(controller_, walker_),
      blockStrategy(ipc)
  {
  }

  void run(const std::int16_t& brightness);
  void getBlockColor();
  void passCircle(const Color& circle_color);
  void moveOnLineToColor(std::int8_t pwm, std::int16_t target, const Color& circle_color,
                         bool isLeft);
  void turnLeft90();
  void turnRight90();
  void turnRight180();

 private:
  Controller controller;
  Walker walker;
  Distinguisher distinguisher;
  Lifter lifter;
  Navigator navigator;
  LineTracerWalker lineTracer;
  Color blockColor = Color::NONE;
  BlockSideBySide::BlockStrategy blockStrategy;
};

#endif