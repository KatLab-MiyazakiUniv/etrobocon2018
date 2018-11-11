/**
 * BlockAreaTest.cpp
 */

/* コンパイル(平木場)
$ g++-8 BlockStrategyTest.cpp ../src/BlockArea.cpp ../src/BlockStrategy.cpp gtest_main.o gtest-all.o
-I../include -I~/googletest/googletest/include
*/

#include "BlockStrategy.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

using namespace BlockSideBySide;

namespace etrobocon2018_test {
  class BlockStrategyTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    BlockStrategy b{ 00000 };
    std::array<std::shared_ptr<ColorBlockPlace>, BLOCK_NUM> getColorBlockPlaceArray()
    {
      return b.colorBlockPlaceArray;
    }

    // BlockArea getBlockArea() { return b.blockArea; }
  };

  TEST_F(BlockStrategyTest, createColorBlockPlace)
  {
    auto b = getColorBlockPlaceArray();
    ASSERT_EQ(b[0]->getColor(), GameColor::RED);
    ASSERT_EQ(b[2]->getColor(), GameColor::BLUE);
    ASSERT_EQ(b[5]->getColor(), GameColor::GREEN);
    ASSERT_EQ(b[7]->getColor(), GameColor::YELLOW);
    ASSERT_EQ(b[9]->getColor(), GameColor::YELLOW);
    ASSERT_EQ(b[11]->getColor(), GameColor::GREEN);
    ASSERT_EQ(b[12]->getColor(), GameColor::BLUE);
    ASSERT_EQ(b[14]->getColor(), GameColor::RED);
  }

  TEST_F(BlockStrategyTest, connectColorBlockPlace)
  {
    auto b = getColorBlockPlaceArray();
    ASSERT_EQ(b[0]->black_line[Direction::WEST], b[1]);
    ASSERT_EQ(b[2]->black_line[Direction::EAST], b[1]);
    ASSERT_EQ(b[5]->black_line[Direction::SOUTH], b[9]);
    ASSERT_EQ(b[7]->black_line[Direction::NORTH], b[3]);
    ASSERT_EQ(b[9]->black_line[Direction::EAST], b[8]);
    ASSERT_EQ(b[11]->black_line[Direction::SOUTH], b[15]);
    ASSERT_EQ(b[12]->black_line[Direction::WEST], b[13]);
    ASSERT_EQ(b[14]->black_line[Direction::NORTH], b[10]);
  }

  TEST_F(BlockStrategyTest, putColorBlockPlace)
  {
    BlockStrategy b{ 84722 };
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[1]->hasBlock(), true);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[4]->hasBlock(), true);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[10]->hasBlock(), true);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[15]->hasBlock(), true);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[2]->hasBlock(), false);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[6]->hasBlock(), false);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[8]->hasBlock(), false);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[9]->hasBlock(), false);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[11]->hasBlock(), false);
    ASSERT_EQ(b.blockArea.colorBlockPlaceArray[13]->hasBlock(), false);
  }

  TEST_F(BlockStrategyTest, getDirection)
  {
    BlockStrategy b{ 84722 };
    ASSERT_EQ(b.blockArea.getDirection(1, 2), Direction::WEST);
    ASSERT_EQ(b.blockArea.getDirection(1, 5), Direction::SOUTH);
    ASSERT_EQ(b.blockArea.getDirection(1, 0), Direction::EAST);
    ASSERT_EQ(b.blockArea.getDirection(8, 4), Direction::NORTH);
  }
}  // namespace etrobocon2018_test
