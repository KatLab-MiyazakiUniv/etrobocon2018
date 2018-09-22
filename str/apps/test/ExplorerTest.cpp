/**
 * ExplorerTest.cpp
 */

#include "Explorer.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  // ブロック置き場ノードリストの初期値を返す
  TEST(ExplorerTest, getInitialValueOfBlockAreaNodeListTest)
  {
    Explorer obj;

    auto actual = obj.getBlockAreaNodeList();

    ASSERT_EQ(nullptr, actual);
  }

  // ブロック置き場ノードリストの設定値を返す
  TEST(ExplorerTest, getValueOfBlockAreaNodeListTest)
  {
    Explorer obj;
    std::vector<Node> expectedList = {
        Node{}, Node{1}, Node{2}, Node{3},
        Node{4}, Node{5}, Node{6}, Node{7},
        Node{8}, Node{9}, Node{10}, Node{11},
        Node{12}, Node{13}, Node{14}, Node{15}};
    std::vector<std::vector<int>> expectedPositionList = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},

        {0, 1},
        {1, 1},
        {2, 1},
        {3, 1},

        {0, 2},
        {1, 2},
        {2, 2},
        {3, 2},

        {0, 3},
        {1, 3},
        {2, 3},
        {3, 3}};

    obj.createBlockArea();
    auto actual = obj.getBlockAreaNodeList();

    ASSERT_EQ(expectedList.size(), actual->size());

    for (unsigned int i = 0; i < expectedList.size(); i++)
    {
      ASSERT_EQ(expectedList[i].getNodeID(), actual->at(i)->getNodeID());
      ASSERT_EQ(expectedPositionList[i][0], actual->at(i)->getPositionX());
      ASSERT_EQ(expectedPositionList[i][1], actual->at(i)->getPositionY());
    }
  }

  // ノード0からノード1のルートを返す
  TEST(ExplorerTest, searchRouteFrom0To1Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {0, 1};

    obj.createBlockArea();
    auto actual = obj.searchRoute(0, 1);

    ASSERT_EQ(expectedSize, actual.size());

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      ASSERT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }
  }

  // ノード1からノード0のルートを返す
  TEST(ExplorerTest, searchRouteFrom1To0Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {1, 0};

    obj.createBlockArea();
    auto actual = obj.searchRoute(1, 0);

    ASSERT_EQ(expectedSize, actual.size());

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      ASSERT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }
  }

  // ノード11からノード10のルートを返す
  TEST(ExplorerTest, searchRouteFrom11To10Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {11, 10};

    obj.createBlockArea();
    auto actual = obj.searchRoute(11, 10);

    ASSERT_EQ(expectedSize, actual.size());

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      ASSERT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }
  }

  // ノード0からノード2のルートを返す
  TEST(ExplorerTest, searchRouteFrom0To2Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 3;
    std::vector<int> expectedList = {0, 1, 2};

    obj.createBlockArea();
    auto actual = obj.searchRoute(0, 2);

    ASSERT_EQ(100, actual[2]);
    ASSERT_EQ(expectedSize, actual.size());

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      ASSERT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }
  }

  // ノード2からノード0のルートを返す
  TEST(ExplorerTest, searchRouteFrom2To0Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 3;
    std::vector<int> expectedList = {2, 1, 0};

    obj.createBlockArea();
    auto actual = obj.searchRoute(2, 0);

    ASSERT_EQ(expectedSize, actual.size());

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      ASSERT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }
  }

}  // namespace etrobocon2018_test
