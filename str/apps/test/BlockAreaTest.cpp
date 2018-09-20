/**
 * BlockAreaTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 BlockAreaTest.cpp ../src/BlockArea.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "BlockArea.h"  // このヘッダファイルのcppファイルをテスト
#include <array>
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(ColorBlockTest, createColorBlock)
  {
    ColorBlock redBlock(GameColor::RED);
    ColorBlock blueBlock(GameColor::BLUE);
    ColorBlock yellowBlock(GameColor::YELLOW);
    ColorBlock greenBlock(GameColor::GREEN);

    ASSERT_EQ(redBlock.color, GameColor::RED);
    ASSERT_EQ(blueBlock.color, GameColor::BLUE);
    ASSERT_EQ(yellowBlock.color, GameColor::YELLOW);
    ASSERT_EQ(greenBlock.color, GameColor::GREEN);
  }

  TEST(ColorBlockPlaceTest, createColorBlockPlace)
  {
    ColorBlockPlace blockPlace00(GameColor::RED, 0);
    ASSERT_EQ(blockPlace00.getPlaceCord(), 0);
    ASSERT_EQ(blockPlace00.getColor(), GameColor::RED);
  }

  TEST(ColorBlockPlaceTest, setColorBlock)
  {
    std::shared_ptr<ColorBlock> colorBlock0 = std::make_shared<ColorBlock>(GameColor::UNKNOWN);
    ColorBlockPlace blockPlace00(GameColor::RED, 0);
    blockPlace00.block = colorBlock0;
    ASSERT_EQ(blockPlace00.block->color, GameColor::UNKNOWN);
    blockPlace00.block->color = GameColor::BLUE;
    ASSERT_EQ(blockPlace00.block->color, GameColor::BLUE);
  }

  TEST(ColorBlockPlaceTest, connectColorBlockPlace)
  {
    std::shared_ptr<ColorBlockPlace> blockPlace00
        = std::make_shared<ColorBlockPlace>(GameColor::RED, 0);
    std::shared_ptr<ColorBlockPlace> blockPlace01
        = std::make_shared<ColorBlockPlace>(GameColor::YELLOW, 1);

    blockPlace00->black_line["north"] = blockPlace01;
    blockPlace01->black_line["south"] = blockPlace00;
    ASSERT_EQ(blockPlace00->black_line["north"]->getColor(), GameColor::YELLOW);
    ASSERT_EQ(blockPlace01->black_line["south"]->getColor(), GameColor::RED);
  }

  TEST(ColorBlockPlaceTest, dynamicCreateColorBlockPlace)
  {
    std::array<GameColor, 16> colorArray{ GameColor::RED,    GameColor::YELLOW, GameColor::BLUE,
                                          GameColor::GREEN,  GameColor::BLUE,   GameColor::GREEN,
                                          GameColor::RED,    GameColor::YELLOW, GameColor::RED,
                                          GameColor::YELLOW, GameColor::BLUE,   GameColor::GREEN,
                                          GameColor::BLUE,   GameColor::GREEN,  GameColor::RED,
                                          GameColor::YELLOW };

    std::array<std::shared_ptr<ColorBlockPlace>, 16> colorBlockPlaceArray;
    for(std::int8_t i = 0; i < 16; i++) {
      std::shared_ptr<ColorBlockPlace> blockPlace
          = std::make_shared<ColorBlockPlace>(colorArray[i], i);
      colorBlockPlaceArray[i] = blockPlace;
    }
  }

}  // namespace etrobocon2018_test
