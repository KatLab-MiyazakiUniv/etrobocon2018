/**
 * SelectorTest.cpp
 */

#include "Selector.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  // ブロックの位置のリストを設定すると設定値を返す
  TEST(SelectorTest, getBlockPositionListTest)
  {
    Selector obj;
    std::vector<std::int8_t> expected{{0, 1, 2, 3}};

    obj.setBlockPositionList(expected);
    auto actual = obj.getBlockPositionList();

    ASSERT_EQ(expected, actual);
  }

  // ノード8を返す
  TEST(SelectorTest, searchNode8Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{0, 1, 2, 8}};
    std::int8_t expected = 8;

    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(8);

    ASSERT_EQ(expected, actual);
  }

  // ノード9を返す
  TEST(SelectorTest, searchNode9Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{0, 1, 2, 9}};
    std::int8_t expected = 9;

    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(8);

    ASSERT_EQ(expected, actual);
  }

  // ノード1を返す
  TEST(SelectorTest, searchNode1Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{1, 2, 3, 7}};
    std::int8_t expected = 1;

    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(8);

    ASSERT_EQ(expected, actual);
  }

  // ノード10を返す
  TEST(SelectorTest, searchNode10Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{0, 2, 10, 14}};
    std::int8_t expected = 10;

    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(8);

    ASSERT_EQ(expected, actual);
  }

  // ノード6を返す
  TEST(SelectorTest, searchNode6Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{6, 7, 10, 11}};
    std::int8_t expected = 6;

    obj.addMovedBlockPosition(10);
    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(13);

    ASSERT_EQ(expected, actual);
  }

  // ノード0を返す
  TEST(SelectorTest, searchNode0Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{0, 2, 3, 15}};
    std::int8_t expected = 0;

    obj.setBlockPositionList(blockList);
    auto actual = obj.searchBlockPosition(8);

    ASSERT_EQ(expected, actual);
  }

  // 移動済みブロックを設定できているかどうかチェックする
  TEST(SelectorTest, checkWhetherThereIsMovedBlock)
  {
    Selector obj;

    ASSERT_FALSE(obj.isAlreadyMovedNode(1));
    ASSERT_FALSE(obj.isAlreadyMovedNode(10));

    obj.addMovedBlockPosition(1);

    ASSERT_TRUE(obj.isAlreadyMovedNode(1));
    ASSERT_FALSE(obj.isAlreadyMovedNode(10));

    obj.addMovedBlockPosition(10);

    ASSERT_TRUE(obj.isAlreadyMovedNode(1));
    ASSERT_TRUE(obj.isAlreadyMovedNode(10));
  }

  // ノード0を返す
  TEST(SelectorTest, searchNodeInSenarioTest)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{8, 9, 11, 15}};

    obj.setBlockPositionList(blockList);

    // 8を探す
    auto actual8 = obj.searchBlockPosition(8);
    ASSERT_EQ(8, actual8);

    // 9を探す
    blockList = {9, 10, 11, 15};
    obj.setBlockPositionList(blockList);
    obj.addMovedBlockPosition(10);
    auto actual9 = obj.searchBlockPosition(14);
    ASSERT_EQ(9, actual9);

    // 11を探す
    blockList = {6, 10, 11, 15};
    obj.setBlockPositionList(blockList);
    obj.addMovedBlockPosition(6);
    auto actual11 = obj.searchBlockPosition(5);
    ASSERT_EQ(11, actual11);

    // 15を探す
    blockList = {6, 9, 10, 15};
    obj.setBlockPositionList(blockList);
    obj.addMovedBlockPosition(5);
    auto actual15 = obj.searchBlockPosition(15);
    ASSERT_EQ(15, actual15);
  }

}  // namespace etrobocon2018_test
