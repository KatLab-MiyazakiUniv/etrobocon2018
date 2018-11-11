/**
 * BlockSolverTest.cpp
 */

/* コンパイル(平木場)
$ g++-8 BlockStrategyTest.cpp ../src/BlockSolver.cpp ../src/BlockStrategy.cpp gtest_main.o
gtest-all.o -I../include -I~/googletest/googletest/include
*/

#include "BlockSolver.h"  // このヘッダファイルのcppファイルをテスト
#include "Controller.h"
#include "Walker.h"
#include <gtest/gtest.h>

using namespace BlockSideBySide;

namespace etrobocon2018_test {
  /*class BlockStrategyTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    BlockStrategy b{ 00000 };
    std::array<std::shared_ptr<ColorBlockPlace>, BLOCK_NUM> getColorBlockPlaceArray()
    {
      return b.colorBlockPlaceArray;
    }

    // BlockSolver getBlockSolver() { return b.blockArea; }
  };
  */

  TEST(BlockSolverTest, changeDirection)
  {
    Controller controller;
    Walker walker{ controller };
    BlockSolver blockSolver{ controller, walker, 01233, 40 };
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
    blockSolver.changeDirection(1);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 3);
    blockSolver.changeDirection(1);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 0);
    blockSolver.changeDirection(-1);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 3);
    blockSolver.changeDirection(-1);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
    blockSolver.changeDirection(-1);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 1);
    blockSolver.changeDirection(2);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 3);
  }

  TEST(BlockSolverTest, move)
  {
    Controller controller;
    Walker walker{ controller };
    BlockSolver blockSolver{ controller, walker, 01233, 40 };
    blockSolver.moveDirection(9);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
    blockSolver.moveDirection(10);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
    blockSolver.moveDirection(6);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 1);
    blockSolver.moveDirection(5);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 0);
    blockSolver.moveDirection(6);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
  }
  TEST(BlockSolverTest, move2)
  {
    Controller controller;
    Walker walker{ controller };
    BlockSolver blockSolver{ controller, walker, 01233, 40 };
    blockSolver.moveDirection(9);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
    blockSolver.moveDirection(8);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 0);
    blockSolver.moveDirection(4);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 1);
    blockSolver.moveDirection(5);
    ASSERT_EQ(static_cast<int>(blockSolver.nowDirection), 2);
  }
}  // namespace etrobocon2018_test