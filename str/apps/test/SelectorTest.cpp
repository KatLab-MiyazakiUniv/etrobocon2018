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

  // Explorerクラスを用いた同じリストを返す
  TEST(SelectorTest, searchRouteByExplorerTest)
  {
    Selector obj;
    std::vector<int> expected{{11, 7, 3, 2, 1, 5}};
    std::vector<std::int8_t> nodeHadBlockList{{6, 9, 10}};

    obj.prepareSearching(nodeHadBlockList);
    auto actual = obj.searchRoute(11, 5);

    for (unsigned int i = 0; i < actual.size(); i++)
    {
      EXPECT_EQ(actual[i], expected[i]);
    }

    ASSERT_EQ(expected.size(), actual.size());
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

  // 初期値において次の動作は全て偽とする
  TEST(SelectorTest, checkNextOperationIsAllFalseInInitialStageTest)
  {
    Selector obj;

    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
  }

  // 次の動作を設定するとそれ以外の動作は全て偽とする
  TEST(SelectorTest, checkNextOperationIsAllFalseWithoutSetNextWhenNextIsSetTest)
  {
    Selector obj;

    obj.setNext(Selector::Evacuating);
    ASSERT_TRUE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());

    obj.setNext(Selector::Moving);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());

    obj.setNext(Selector::Carrying);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
  }

  // 色を設定すると中央四角形における次に置くべき位置コードを取得する
  TEST(SelectorTest, getNextPositionInCenterIfColorSetInNodeIDTest)
  {
    Selector obj;

    auto actual = obj.getPositionOfCenterQuadirilateral(Selector::Blue);
    ASSERT_EQ(10, actual);

    actual = obj.getPositionOfCenterQuadirilateral(Selector::Red);
    ASSERT_EQ(6, actual);

    actual = obj.getPositionOfCenterQuadirilateral(Selector::Yellow);
    ASSERT_EQ(9, actual);

    actual = obj.getPositionOfCenterQuadirilateral(Selector::Green);
    ASSERT_EQ(5, actual);

    actual = obj.getPositionOfCenterQuadirilateral(Selector::Undefined);
    ASSERT_EQ(-1, actual);
  }

  // 疑似キュー配列のプッシュ機能およびポップ機能を確認する
  TEST(SelectorTest, checkPushingAndPoppingByPseudoQueueTest)
  {
    Selector obj;

    obj.pushEvacuatedBlockPosition(10);
    obj.pushEvacuatedBlockPosition(20);
    obj.pushEvacuatedBlockPosition(30);

    auto actual = obj.popEvacuatedBlockPosition();
    ASSERT_EQ(10, actual);
    actual = obj.popEvacuatedBlockPosition();
    ASSERT_EQ(20, actual);

    obj.pushEvacuatedBlockPosition(40);

    actual = obj.popEvacuatedBlockPosition();
    ASSERT_EQ(30, actual);
    actual = obj.popEvacuatedBlockPosition();
    ASSERT_EQ(40, actual);
  }

  // シナリオテストでノードを探索する
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

  // シナリオテストで一連のルートを探索する
  TEST(SelectorTest, searchRouteInSenarioTest)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{8, 9, 11, 15}};
    // 8->Blue, 9->Red, 11->Yellow, 15->Green
    std::vector<int> expectedMovingToBlue = {8};
    std::vector<int> expectedCarryingBlue = {8, 12, 13, 14, 10};
    std::vector<int> expectedMovingToRed = {14, 13, 9};
    std::vector<int> expectedCarryingRed = {9, 5, 6};
    std::vector<int> expectedMovingToYellow = {5, 1, 2, 3, 7, 11};
    std::vector<int> expectedCarryingYellow = {11, 7, 3, 2, 1, 5, 9};
    std::vector<int> expectedMovingToGreen = {5, 4, 8, 12, 13, 14, 15};
    std::vector<int> expectedCarryingGreen = {15, 14, 13, 12, 8, 4, 5};
    std::vector<int> expectedMovingTo11 = {4, 0, 1, 2, 3, 7, 11};

    obj.setBlockPositionList(blockList);

    // 8に移動する
    auto actualMovingToBlue = obj.exploreNextOperation(8, Selector::Undefined);

    ASSERT_EQ(expectedMovingToBlue.size(), actualMovingToBlue.size());
    for (unsigned int i = 0; i < actualMovingToBlue.size(); i++)
        EXPECT_EQ(actualMovingToBlue[i], expectedMovingToBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(8, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(11, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 10に運搬する
    auto actualCarryingBlue = obj.exploreNextOperation(8, Selector::Blue);

    ASSERT_EQ(expectedCarryingBlue.size(), actualCarryingBlue.size());
    for (unsigned int i = 0; i < actualCarryingBlue.size(); i++)
        EXPECT_EQ(actualCarryingBlue[i], expectedCarryingBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(11, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 9に移動する
    auto actualMovingToRed = obj.exploreNextOperation(14, Selector::Undefined);

    ASSERT_EQ(expectedMovingToRed.size(), actualMovingToRed.size());
    for (unsigned int i = 0; i < actualMovingToRed.size(); i++)
        EXPECT_EQ(actualMovingToRed[i], expectedMovingToRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(11, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 6に運搬する
    auto actualCarryingRed = obj.exploreNextOperation(9, Selector::Red);

    ASSERT_EQ(expectedCarryingRed.size(), actualCarryingRed.size());
    for (unsigned int i = 0; i < actualCarryingRed.size(); i++)
        EXPECT_EQ(actualCarryingRed[i], expectedCarryingRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(11, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 11に移動する
    auto actualMovingToYellow = obj.exploreNextOperation(5, Selector::Undefined);

    ASSERT_EQ(expectedMovingToYellow.size(), actualMovingToYellow.size());
    for (unsigned int i = 0; i < actualMovingToYellow.size(); i++)
        EXPECT_EQ(actualMovingToYellow[i], expectedMovingToYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(11, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 9に運搬する
    auto actualCarryingYellow = obj.exploreNextOperation(11, Selector::Yellow);

    ASSERT_EQ(expectedCarryingYellow.size(), actualCarryingYellow.size());
    for (unsigned int i = 0; i < actualCarryingYellow.size(); i++)
        EXPECT_EQ(actualCarryingYellow[i], expectedCarryingYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 15に移動する
    auto actualMovingToGreen = obj.exploreNextOperation(5, Selector::Undefined);

    ASSERT_EQ(expectedMovingToGreen.size(), actualMovingToGreen.size());
    for (unsigned int i = 0; i < actualMovingToGreen.size(); i++)
        EXPECT_EQ(actualMovingToGreen[i], expectedMovingToGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(15, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 5に運搬する
    auto actualCarryingGreen = obj.exploreNextOperation(15, Selector::Green);

    ASSERT_EQ(expectedCarryingGreen.size(), actualCarryingGreen.size());
    for (unsigned int i = 0; i < actualCarryingGreen.size(); i++)
        EXPECT_EQ(actualCarryingGreen[i], expectedCarryingGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());

    // 11に移動する
    auto actualMovingTo11 = obj.exploreNextOperation(4, Selector::Undefined);

    ASSERT_EQ(expectedMovingTo11.size(), actualMovingTo11.size());
    for (unsigned int i = 0; i < actualMovingTo11.size(); i++)
        EXPECT_EQ(actualMovingTo11[i], expectedMovingTo11[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(10, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());
  }

  // 経路が塞がれてる場合の一連のルートを探索する
  TEST(SelectorTest, searchRouteWhenPathBlocked)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{4, 8, 9, 13}};
    // 8->Blue, 9->Red, 13->Yellow, 4->Green
    // std::vector<int> expectedMovingToBlue = {8};
    std::vector<int> expectedEvacuatingBlue = {8, 12};
    std::vector<int> expectedMovingToRed = {8, 9};
    std::vector<int> expectedCarryingRed = {9, 10, 6};
    std::vector<int> expectedReturningToBlue = {10, 9, 8, 12};
    std::vector<int> expectedCarryingBlue = {12, 8, 9, 10};
    std::vector<int> expectedMovingToYellow = {9, 13};
    std::vector<int> expectedCarryingYellow = {13, 9};
    std::vector<int> expectedMovingToGreen = {13, 12, 8, 4};
    std::vector<int> expectedCarryingGreen = {4, 5};
    std::vector<int> expectedMovingTo11 = {4, 0, 1, 2, 3, 7, 11};

    obj.setBlockPositionList(blockList);

    // 8に移動する
    obj.exploreNextOperation(8, Selector::Undefined);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 12に一時避難する
    auto actualEvacuatingBlue = obj.exploreNextOperation(8, Selector::Blue);

    ASSERT_EQ(expectedEvacuatingBlue.size(), actualEvacuatingBlue.size());
    for (unsigned int i = 0; i < actualEvacuatingBlue.size(); i++)
        EXPECT_EQ(actualEvacuatingBlue[i], expectedEvacuatingBlue[i]);
    ASSERT_TRUE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(12, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 9に移動する
    auto actualMovingToRed = obj.exploreNextOperation(8, Selector::Undefined);

    ASSERT_EQ(expectedMovingToRed.size(), actualMovingToRed.size());
    for (unsigned int i = 0; i < actualMovingToRed.size(); i++)
        EXPECT_EQ(actualMovingToRed[i], expectedMovingToRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(12, obj.getBlockPositionList()[1]);
    ASSERT_EQ(9, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 6に運搬する
    auto actualCarryingRed = obj.exploreNextOperation(9, Selector::Red);

    ASSERT_EQ(expectedCarryingRed.size(), actualCarryingRed.size());
    for (unsigned int i = 0; i < actualCarryingRed.size(); i++)
        EXPECT_EQ(actualCarryingRed[i], expectedCarryingRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(12, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 12に戻る
    auto actualReturningToBlue = obj.exploreNextOperation(10, Selector::Undefined);

    ASSERT_EQ(expectedReturningToBlue.size(), actualReturningToBlue.size());
    for (unsigned int i = 0; i < actualReturningToBlue.size(); i++)
        EXPECT_EQ(actualReturningToBlue[i], expectedReturningToBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(12, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 10に運搬する
    auto actualCarryingBlue = obj.exploreNextOperation(12, Selector::Blue);

    ASSERT_EQ(expectedCarryingBlue.size(), actualCarryingBlue.size());
    for (unsigned int i = 0; i < actualCarryingBlue.size(); i++)
        EXPECT_EQ(actualCarryingBlue[i], expectedCarryingBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 13に移動する
    auto actualMovingToYellow = obj.exploreNextOperation(9, Selector::Undefined);

    // ASSERT_EQ(expectedMovingToYellow.size(), actualMovingToYellow.size());
    for (unsigned int i = 0; i < actualMovingToYellow.size(); i++)
        EXPECT_EQ(actualMovingToYellow[i], expectedMovingToYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(13, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 9に運搬する
    auto actualCarryingYellow = obj.exploreNextOperation(13, Selector::Yellow);

    ASSERT_EQ(expectedCarryingYellow.size(), actualCarryingYellow.size());
    for (unsigned int i = 0; i < actualCarryingYellow.size(); i++)
        EXPECT_EQ(actualCarryingYellow[i], expectedCarryingYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(9, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 4に移動する
    auto actualMovingToGreen = obj.exploreNextOperation(13, Selector::Undefined);

    ASSERT_EQ(expectedMovingToGreen.size(), actualMovingToGreen.size());
    for (unsigned int i = 0; i < actualMovingToGreen.size(); i++)
        EXPECT_EQ(actualMovingToGreen[i], expectedMovingToGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(4, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(9, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 5に運搬する
    auto actualCarryingGreen = obj.exploreNextOperation(4, Selector::Green);

    ASSERT_EQ(expectedCarryingGreen.size(), actualCarryingGreen.size());
    for (unsigned int i = 0; i < actualCarryingGreen.size(); i++)
        EXPECT_EQ(actualCarryingGreen[i], expectedCarryingGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(5, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(9, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());

    // 11に移動する
    auto actualMovingTo11 = obj.exploreNextOperation(4, Selector::Undefined);

    ASSERT_EQ(expectedMovingTo11.size(), actualMovingTo11.size());
    for (unsigned int i = 0; i < actualMovingTo11.size(); i++)
        EXPECT_EQ(actualMovingTo11[i], expectedMovingTo11[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(5, obj.getBlockPositionList()[0]);
    ASSERT_EQ(10, obj.getBlockPositionList()[1]);
    ASSERT_EQ(6, obj.getBlockPositionList()[2]);
    ASSERT_EQ(9, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());
  }

  // 運搬先が1箇所埋まっている場合の一連のルートを探索する
  TEST(SelectorTest, searchRouteWhenNextMovedPositionIsBuried)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{3, 6, 8, 10}};
    // 8->Blue, 3->Red, 6->Yellow, 10->Green
    // std::vector<int> expectedMovingToBlue = {8};
    std::vector<int> expectedEvacuatingBlue = {8, 12};
    std::vector<int> expectedMovingToGreen = {8, 9, 10};
    std::vector<int> expectedCarryingGreen = {10, 9, 5};
    std::vector<int> expectedReturningToBlue = {9, 13, 12};
    std::vector<int> expectedCarryingBlue = {12, 13, 14, 10};
    std::vector<int> expectedMovingToYellow = {14, 15, 11, 7, 6};
    std::vector<int> expectedCarryingYellow = {6, 7, 11, 15, 14, 13, 9};
    std::vector<int> expectedMovingToRed = {13, 14, 15, 11, 7, 3};
    std::vector<int> expectedCarryingRed = {3, 7, 6};
    std::vector<int> expectedMovingTo11 = {7, 11};

    obj.setBlockPositionList(blockList);

    // 8に移動する
    obj.exploreNextOperation(8, Selector::Undefined);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 12に一時避難する
    auto actualEvacuatingBlue = obj.exploreNextOperation(8, Selector::Blue);

    ASSERT_EQ(expectedEvacuatingBlue.size(), actualEvacuatingBlue.size());
    for (unsigned int i = 0; i < actualEvacuatingBlue.size(); i++)
        EXPECT_EQ(actualEvacuatingBlue[i], expectedEvacuatingBlue[i]);
    ASSERT_TRUE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    ASSERT_EQ(10, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 10に移動する
    auto actualMovingToGreen = obj.exploreNextOperation(8, Selector::Undefined);

    ASSERT_EQ(expectedMovingToGreen.size(), actualMovingToGreen.size());
    for (unsigned int i = 0; i < actualMovingToGreen.size(); i++)
        EXPECT_EQ(actualMovingToGreen[i], expectedMovingToGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    ASSERT_EQ(10, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 5に運搬する
    auto actualCarryingGreen = obj.exploreNextOperation(10, Selector::Green);

    ASSERT_EQ(expectedCarryingGreen.size(), actualCarryingGreen.size());
    for (unsigned int i = 0; i < actualCarryingGreen.size(); i++)
        EXPECT_EQ(actualCarryingGreen[i], expectedCarryingGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 12に移動する
    auto actualReturningToBlue = obj.exploreNextOperation(9, Selector::Undefined);

    ASSERT_EQ(expectedReturningToBlue.size(), actualReturningToBlue.size());
    for (unsigned int i = 0; i < actualReturningToBlue.size(); i++)
        EXPECT_EQ(actualReturningToBlue[i], expectedReturningToBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 10に運搬する
    auto actualCarryingBlue = obj.exploreNextOperation(12, Selector::Blue);

    ASSERT_EQ(expectedCarryingBlue.size(), actualCarryingBlue.size());
    for (unsigned int i = 0; i < actualCarryingBlue.size(); i++)
        EXPECT_EQ(actualCarryingBlue[i], expectedCarryingBlue[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 6に移動する
    auto actualMovingToYellow = obj.exploreNextOperation(14, Selector::Undefined);

    ASSERT_EQ(expectedMovingToYellow.size(), actualMovingToYellow.size());
    for (unsigned int i = 0; i < actualMovingToYellow.size(); i++)
        EXPECT_EQ(actualMovingToYellow[i], expectedMovingToYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 9に運搬する
    auto actualCarryingYellow = obj.exploreNextOperation(6, Selector::Yellow);

    ASSERT_EQ(expectedCarryingYellow.size(), actualCarryingYellow.size());
    for (unsigned int i = 0; i < actualCarryingYellow.size(); i++)
        EXPECT_EQ(actualCarryingYellow[i], expectedCarryingYellow[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 3に移動する
    auto actualMovingToRed = obj.exploreNextOperation(13, Selector::Undefined);

    ASSERT_EQ(expectedMovingToRed.size(), actualMovingToRed.size());
    for (unsigned int i = 0; i < actualMovingToRed.size(); i++)
        EXPECT_EQ(actualMovingToRed[i], expectedMovingToRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 6に運搬する
    auto actualCarryingRed = obj.exploreNextOperation(3, Selector::Red);

    ASSERT_EQ(expectedCarryingRed.size(), actualCarryingRed.size());
    for (unsigned int i = 0; i < actualCarryingRed.size(); i++)
        EXPECT_EQ(actualCarryingRed[i], expectedCarryingRed[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(6, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());

    // 11に移動する
    auto actualMovingTo11 = obj.exploreNextOperation(7, Selector::Undefined);

    ASSERT_EQ(expectedMovingTo11.size(), actualMovingTo11.size());
    for (unsigned int i = 0; i < actualMovingTo11.size(); i++)
        EXPECT_EQ(actualMovingTo11[i], expectedMovingTo11[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_TRUE(obj.isMovingWithNext());
    ASSERT_FALSE(obj.isCarryingWithNext());
    ASSERT_FALSE(obj.isBackstepping());
    ASSERT_EQ(6, obj.getBlockPositionList()[0]);
    ASSERT_EQ(9, obj.getBlockPositionList()[1]);
    ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_TRUE(obj.isAlreadyAllBlockMoved());
  }

  // 運搬先の運搬先の運搬先が埋まっている場合の一連のルートを探索する
  TEST(SelectorTest, searchRouteWhenNextOfNextOfNextMovedPositionIsBuried)
  {
    Selector obj;
    std::vector<std::int8_t> blockList{{5, 6, 8, 10}};
    // 8->Blue, 10->Red, 5->Yellow, 6->Green
    // std::vector<int> expectedMovingToBlue = {8};
    // std::vector<int> expectedEvacuatingBlue = {8, 12};
    // std::vector<int> expectedMovingToRed = {8, 9, 10};
    std::vector<int> expectedMovingToGreen = {9, 13, 14, 15, 11, 7, 6};
    std::vector<int> expectedCarryingGreen = {10, 9, 5};
    std::vector<int> expectedReturningToBlue = {9, 13, 12};
    std::vector<int> expectedCarryingBlue = {12, 13, 14, 10};
    std::vector<int> expectedMovingToYellow = {14, 15, 11, 7, 6};
    std::vector<int> expectedCarryingYellow = {6, 7, 11, 15, 14, 13, 9};
    std::vector<int> expectedMovingToRed = {13, 14, 15, 11, 7, 3};
    std::vector<int> expectedCarryingRed = {3, 7, 6};
    std::vector<int> expectedMovingTo11 = {7, 11};

    obj.setBlockPositionList(blockList);

    // 8に移動する
    obj.exploreNextOperation(8, Selector::Undefined);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 12に一時避難する
    obj.exploreNextOperation(8, Selector::Blue);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 10に移動する
    obj.exploreNextOperation(8, Selector::Undefined);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // 5に移動する
    auto actualCarryingGreen = obj.exploreNextOperation(10, Selector::Green);

    ASSERT_TRUE(obj.isBacksteppingBeforeNextOperation());
    ASSERT_EQ(expectedCarryingGreen.size(), actualCarryingGreen.size());
    for (unsigned int i = 0; i < actualCarryingGreen.size(); i++)
        EXPECT_EQ(actualCarryingGreen[i], expectedCarryingGreen[i]);
    ASSERT_FALSE(obj.isEvacuatingWithNext());
    ASSERT_FALSE(obj.isMovingWithNext());
    ASSERT_TRUE(obj.isCarryingWithNext());
    ASSERT_TRUE(obj.isBackstepping());
    ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

    // // 12に移動する
    // auto actualReturningToBlue = obj.exploreNextOperation(9, Selector::Undefined);
    //
    // ASSERT_EQ(expectedReturningToBlue.size(), actualReturningToBlue.size());
    // for (unsigned int i = 0; i < actualReturningToBlue.size(); i++)
    //     EXPECT_EQ(actualReturningToBlue[i], expectedReturningToBlue[i]);
    // ASSERT_FALSE(obj.isEvacuatingWithNext());
    // ASSERT_TRUE(obj.isMovingWithNext());
    // ASSERT_FALSE(obj.isCarryingWithNext());
    // ASSERT_FALSE(obj.isBackstepping());
    // ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    // ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    // ASSERT_EQ(12, obj.getBlockPositionList()[2]);
    // ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    // ASSERT_FALSE(obj.isAlreadyAllBlockMoved());
    //
    // // 10に運搬する
    // auto actualCarryingBlue = obj.exploreNextOperation(12, Selector::Blue);
    //
    // ASSERT_EQ(expectedCarryingBlue.size(), actualCarryingBlue.size());
    // for (unsigned int i = 0; i < actualCarryingBlue.size(); i++)
    //     EXPECT_EQ(actualCarryingBlue[i], expectedCarryingBlue[i]);
    // ASSERT_FALSE(obj.isEvacuatingWithNext());
    // ASSERT_FALSE(obj.isMovingWithNext());
    // ASSERT_TRUE(obj.isCarryingWithNext());
    // ASSERT_TRUE(obj.isBackstepping());
    // ASSERT_EQ(3, obj.getBlockPositionList()[0]);
    // ASSERT_EQ(6, obj.getBlockPositionList()[1]);
    // ASSERT_EQ(10, obj.getBlockPositionList()[2]);
    // ASSERT_EQ(5, obj.getBlockPositionList()[3]);
    // ASSERT_FALSE(obj.isAlreadyAllBlockMoved());

  }

}  // namespace etrobocon2018_test
