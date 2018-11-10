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

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード1からノード0のルートを返す
  TEST(ExplorerTest, searchRouteFrom1To0Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {1, 0};

    obj.createBlockArea();
    auto actual = obj.searchRoute(1, 0);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード8からノード9のルートを返す
  TEST(ExplorerTest, searchRouteFrom8To9Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {8, 9};

    obj.createBlockArea();
    auto actual = obj.searchRoute(8, 9);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード11からノード10のルートを返す
  TEST(ExplorerTest, searchRouteFrom11To10Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 2;
    std::vector<int> expectedList = {11, 10};

    obj.createBlockArea();
    auto actual = obj.searchRoute(11, 10);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード0からノード2のルートを返す
  TEST(ExplorerTest, searchRouteFrom0To2Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 3;
    std::vector<int> expectedList = {0, 1, 2};

    obj.createBlockArea();
    auto actual = obj.searchRoute(0, 2);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード2からノード0のルートを返す
  TEST(ExplorerTest, searchRouteFrom2To0Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 3;
    std::vector<int> expectedList = {2, 1, 0};

    obj.createBlockArea();
    auto actual = obj.searchRoute(2, 0);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード11からノード5の最短ルートを返す
  TEST(ExplorerTest, searchShortestRouteFrom11To5Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 4;
    std::vector<int> expectedList = {11, 10, 9, 5};

    obj.createBlockArea();
    auto actual = obj.searchRoute(11, 5);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード11からノード5のノード6迂回ルートを返す
  TEST(ExplorerTest, searchRouteFrom11To5Circumventing6Test)
  {
    Explorer obj;
    unsigned long int expectedSize = 4;
    std::vector<int> expectedList = {11, 10, 9, 5};

    obj.createBlockArea();
    obj.getBlockAreaNodeList()->at(6)->setHasBlock(true);
    auto actual = obj.searchRoute(11, 5);

    for (unsigned int i = 0; i < expectedSize; i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expectedList[i]);
    }

    ASSERT_EQ(expectedSize, actual.size());
  }

  // ノード11からノード5のノード6とノード10迂回ルートを返す
  TEST(ExplorerTest, searchRouteFrom11To5Circumventing6And10Test)
  {
    Explorer obj;
    std::vector<int> expected = {11, 15, 14, 13, 9, 5};

    obj.createBlockArea();
    obj.getBlockAreaNodeList()->at(6)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(10)->setHasBlock(true);
    auto actual = obj.searchRoute(11, 5);

    for (unsigned int i = 0; i < expected.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expected[i]);
    }

    ASSERT_EQ(expected.size(), actual.size());
  }

  // ノード13からノード6のノード10迂回ルートを返す
  TEST(ExplorerTest, searchRouteFrom13To6Circumventing10Test)
  {
    Explorer obj;
    std::vector<int> expected = {13, 9, 5, 6};

    obj.createBlockArea();
    obj.getBlockAreaNodeList()->at(6)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(7)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(10)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(11)->setHasBlock(true);
    auto actual = obj.searchRoute(13, 6);

    for (unsigned int i = 0; i < expected.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expected[i]);
    }

    ASSERT_EQ(expected.size(), actual.size());
  }

  // ノード11からノード5のノード6とノード10とノード9迂回ルートを返す
  TEST(ExplorerTest, searchRouteFrom11To5Circumventing6And9And10Test)
  {
    Explorer obj;
    std::vector<int> expected = {11, 7, 3, 2, 1, 5};

    obj.createBlockArea();
    obj.getBlockAreaNodeList()->at(6)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(9)->setHasBlock(true);
    obj.getBlockAreaNodeList()->at(10)->setHasBlock(true);
    auto actual = obj.searchRoute(11, 5);

    for (unsigned int i = 0; i < expected.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actual[i])->getNodeID(), expected[i]);
    }

    ASSERT_EQ(expected.size(), actual.size());
  }

  // 簡単なシナリオルートを返す
  TEST(ExplorerTest, searchRouteInSenarioTest)
  {
    Explorer obj;
    // 8->Blue, 9->Red, 11->Yellow, 15->Green
    std::vector<int> expectedCartingBlue = {8, 12, 13, 14, 10};
    std::vector<int> expectedMovingToRed = {14, 13, 9};
    std::vector<int> expectedCartingRed = {9, 5, 6};
    std::vector<int> expectedMovingToYellow = {5, 1, 2, 3, 7, 11};
    std::vector<int> expectedCartingYellow = {11, 7, 3, 2, 1, 5, 9};
    std::vector<int> expectedMovingToGreen = {5, 4, 8, 12, 13, 14, 15};
    std::vector<int> expectedCartingGreen = {15, 14, 13, 12, 8, 4, 5};
    std::vector<int> expectedMovingTo11 = {4, 0, 1, 2, 3, 7, 11};

    obj.createBlockArea();
    obj.resetBlockArea();
    obj.setHasBlockIn(8);
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(11);
    obj.setHasBlockIn(15);

    // Blue 8->10
    auto actualCartingBlue = obj.searchRoute(8, 10);

    for (unsigned int i = 0; i < expectedCartingBlue.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualCartingBlue[i])->getNodeID(), expectedCartingBlue[i]);
    }
    EXPECT_EQ(expectedCartingBlue.size(), actualCartingBlue.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(11);
    obj.setHasBlockIn(15);

    // 14->9
    auto actualMovingToRed = obj.searchRoute(14, 9);
    for (unsigned int i = 0; i < expectedMovingToRed.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualMovingToRed[i])->getNodeID(), expectedMovingToRed[i]);
    }
    EXPECT_EQ(expectedMovingToRed.size(), actualMovingToRed.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(11);
    obj.setHasBlockIn(15);

    // Red 9->6
    auto actualCartingRed = obj.searchRoute(9, 6);
    for (unsigned int i = 0; i < expectedCartingRed.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualCartingRed[i])->getNodeID(), expectedCartingRed[i]);
    }
    EXPECT_EQ(expectedCartingRed.size(), actualCartingRed.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(6);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(11);
    obj.setHasBlockIn(15);

    // 5->11
    auto actualMovingToYellow = obj.searchRoute(5, 11);
    for (unsigned int i = 0; i < expectedMovingToYellow.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualMovingToYellow[i])->getNodeID(), expectedMovingToYellow[i]);
    }
    EXPECT_EQ(expectedMovingToYellow.size(), actualMovingToYellow.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(6);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(11);
    obj.setHasBlockIn(15);

    // Yellow 11->9
    auto actualCartingYellow = obj.searchRoute(11, 9);
    for (unsigned int i = 0; i < expectedCartingYellow.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualCartingYellow[i])->getNodeID(), expectedCartingYellow[i]);
    }
    EXPECT_EQ(expectedCartingYellow.size(), actualCartingYellow.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(6);
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(15);

    // 5->15
    auto actualMovingToGreen = obj.searchRoute(5, 15);
    for (unsigned int i = 0; i < expectedMovingToGreen.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualMovingToGreen[i])->getNodeID(), expectedMovingToGreen[i]);
    }
    EXPECT_EQ(expectedMovingToGreen.size(), actualMovingToGreen.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(6);
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(10);
    obj.setHasBlockIn(15);

    // Green 15->5
    auto actualCartingGreen = obj.searchRoute(15, 5);
    for (unsigned int i = 0; i < expectedCartingGreen.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualCartingGreen[i])->getNodeID(), expectedCartingGreen[i]);
    }
    EXPECT_EQ(expectedCartingYellow.size(), actualCartingGreen.size());

    obj.resetBlockArea();
    obj.setHasBlockIn(5);
    obj.setHasBlockIn(6);
    obj.setHasBlockIn(9);
    obj.setHasBlockIn(10);

    // 4->11
    auto actualMovingTo11 = obj.searchRoute(4, 11);
    for (unsigned int i = 0; i < expectedMovingTo11.size(); i++)
    {
      EXPECT_EQ(obj.getBlockAreaNodeList()->at(actualMovingTo11[i])->getNodeID(), expectedMovingTo11[i]);
    }
    EXPECT_EQ(expectedMovingTo11.size(), actualMovingTo11.size());
  }

}  // namespace etrobocon2018_test
