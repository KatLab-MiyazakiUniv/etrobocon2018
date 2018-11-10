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
  TEST(SelectorTest, DISABLED_searchNode6Test)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{6, 7, 11}};
    std::int8_t expected = 6;

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

}  // namespace etrobocon2018_test
