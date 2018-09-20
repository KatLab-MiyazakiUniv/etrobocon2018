/**
 * BlockAreaTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 BlockAreaTest.cpp ../src/BlockArea.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "BlockStrategy.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

using namespace BlockSideBySide;

namespace etrobocon2018_test {
  class BlockStrategyTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    BlockStrategy b;
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

}  // namespace etrobocon2018_test
