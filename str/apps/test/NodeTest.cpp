/**
 * NodeTest.cpp
 */

#include "Node.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  // ノードIDの初期値を返す
  TEST(NodeTest, getInitialValueOfNodeIDTest)
  {
    Node obj;
    std::int8_t expected = 0;

    auto actual = obj.getNodeID();

    ASSERT_EQ(expected, actual);
  }

  // ブロック存在性の初期値を返す
  TEST(NodeTest, getInitialValueOfBlockExistsTest)
  {
    Node obj;

    auto actual = obj.hasBlock();

    ASSERT_FALSE(actual);
  }

  // 位置コードの初期値を返す
  TEST(NodeTest, getInitialValueOfPositionTest)
  {
    Node obj;
    std::int8_t expectedX = 0;
    std::int8_t expectedY = 0;

    auto actualX = obj.getPositionX();
    auto actualY = obj.getPositionY();

    ASSERT_EQ(expectedX, actualX);
    ASSERT_EQ(expectedY, actualY);
  }

  // ノードIDの設定値を返す
  TEST(NodeTest, getValueOfNodeIDTest)
  {
    Node obj;
    std::int8_t expected = 10;

    obj.setNodeID(10);
    auto actual = obj.getNodeID();

    ASSERT_EQ(expected, actual);
  }

  // ノードIDの初期設定値を返す
  TEST(NodeTest, initializeValueOfNodeIDTest)
  {
    std::int8_t expected = 9;

    Node obj(9);
    auto actual = obj.getNodeID();

    ASSERT_EQ(expected, actual);
  }

  // ブロック存在性の設定値を返す
  TEST(NodeTest, getValueOfBlockExistsTest)
  {
    Node obj;

    obj.setHasBlock(true);
    auto actual = obj.hasBlock();

    ASSERT_TRUE(actual);
  }

  // 位置コードの設定値を返す
  TEST(NodeTest, getValueOfPositionTest)
  {
    Node obj;
    std::int8_t expectedX = 5;
    std::int8_t expectedY = 8;

    obj.setPosition(5, 8);
    auto actualX = obj.getPositionX();
    auto actualY = obj.getPositionY();

    ASSERT_EQ(expectedX, actualX);
    ASSERT_EQ(expectedY, actualY);
  }

  // 隣接ノードリストの設定値を返す
  TEST(NodeTest, getValueOfNeighborListTest)
  {
    Node nodeA;
    Node nodeB;
    nodeA.setNodeID(1);
    nodeB.setNodeID(2);
    std::vector<Node*> expected = {&nodeA, &nodeB};
    Node obj{&expected};

    auto actual = obj.getNeighbors();

    ASSERT_EQ(&expected, actual);
    ASSERT_EQ(expected.at(0), actual->at(0));

    expected.at(0)->setNodeID(3);
    ASSERT_EQ(&expected, actual);
    ASSERT_EQ(expected.at(0), actual->at(0));
    ASSERT_EQ(expected.at(0)->getNodeID(), actual->at(0)->getNodeID());
  }

  // 3隣接ノードリストの設定値を返す
  TEST(NodeTest, getValueOf3NeighborListTest)
  {
    Node node1(1);
    Node node2(2);
    Node node3(3);

    std::vector<Node*> neighbors1 = {&node2};
    std::vector<Node*> neighbors2 = {&node1, &node3};
    std::vector<Node*> neighbors3 = {&node2};

    node1.setNeighbors(&neighbors1);
    node2.setNeighbors(&neighbors2);
    node3.setNeighbors(&neighbors3);

    auto actual1 = node1.getNeighbors();
    auto actual2 = node2.getNeighbors();
    auto actual3 = node3.getNeighbors();

    ASSERT_EQ(&neighbors1, actual1);
    ASSERT_EQ(&neighbors2, actual2);
    ASSERT_EQ(&neighbors3, actual3);

    ASSERT_EQ(&node1, actual1->at(0)->getNeighbors()->at(0));
    ASSERT_EQ(&node2, actual2->at(0)->getNeighbors()->at(0));
    ASSERT_EQ(&node2, actual2->at(1)->getNeighbors()->at(0));
    ASSERT_EQ(&node3, actual3->at(0)->getNeighbors()->at(1));
  }

  // 3x3の隣接ノードリストを返す
  TEST(NodeTest, getValueOfNeighborListOf3x3Test)
  {
    std::vector<Node*> blockAreaNodePtrList(9);
    std::vector<Node> blockAreaNodeList(9);

    for (std::int8_t i = 0; i < 9; i++)
    {
      Node currentNode(i);
      blockAreaNodeList[i] = currentNode;
      blockAreaNodePtrList[i] = &blockAreaNodeList[i];
    }
    std::vector<Node*>* blockAreaNodePtrListPtr = &blockAreaNodePtrList;


    std::vector<Node*> neighborsOfNode0;
    std::vector<Node*> neighborsOfNode1;
    std::vector<Node*> neighborsOfNode2;

    std::vector<Node*> neighborsOfNode3;
    std::vector<Node*> neighborsOfNode4;
    std::vector<Node*> neighborsOfNode5;

    std::vector<Node*> neighborsOfNode6;
    std::vector<Node*> neighborsOfNode7;
    std::vector<Node*> neighborsOfNode8;


    int numbers0[2] = {1, 3};
    for (int i = 0; i < 2; i++)
    {
      neighborsOfNode0.push_back(blockAreaNodePtrListPtr->at(numbers0[i]));
    }
    int numbers1[3] = {0, 2, 4};
    for (int i = 0; i < 3; i++)
    {
      neighborsOfNode1.push_back(blockAreaNodePtrListPtr->at(numbers1[i]));
    }
    int numbers2[2] = {1, 5};
    for (int i = 0; i < 2; i++)
    {
      neighborsOfNode2.push_back(blockAreaNodePtrListPtr->at(numbers2[i]));
    }


    int numbers3[3] = {0, 4, 6};
    for (int i = 0; i < 3; i++)
    {
      neighborsOfNode3.push_back(blockAreaNodePtrListPtr->at(numbers3[i]));
    }
    int numbers4[4] = {1, 3, 5, 7};
    for (int i = 0; i < 4; i++)
    {
      neighborsOfNode4.push_back(blockAreaNodePtrListPtr->at(numbers4[i]));
    }
    int numbers5[3] = {2, 4, 8};
    for (int i = 0; i < 3; i++)
    {
      neighborsOfNode5.push_back(blockAreaNodePtrListPtr->at(numbers5[i]));
    }


    int numbers6[2] = {3, 7};
    for (int i = 0; i < 2; i++)
    {
      neighborsOfNode6.push_back(blockAreaNodePtrListPtr->at(numbers6[i]));
    }
    int numbers7[3] = {4, 6, 8};
    for (int i = 0; i < 3; i++)
    {
      neighborsOfNode7.push_back(blockAreaNodePtrListPtr->at(numbers7[i]));
    }
    int numbers8[2] = {5, 7};
    for (int i = 0; i < 2; i++)
    {
      neighborsOfNode8.push_back(blockAreaNodePtrListPtr->at(numbers8[i]));
    }


    blockAreaNodePtrListPtr->at(0)->setNeighbors(&neighborsOfNode0);
    blockAreaNodePtrListPtr->at(1)->setNeighbors(&neighborsOfNode1);
    blockAreaNodePtrListPtr->at(2)->setNeighbors(&neighborsOfNode2);

    blockAreaNodePtrListPtr->at(3)->setNeighbors(&neighborsOfNode3);
    blockAreaNodePtrListPtr->at(4)->setNeighbors(&neighborsOfNode4);
    blockAreaNodePtrListPtr->at(5)->setNeighbors(&neighborsOfNode5);

    blockAreaNodePtrListPtr->at(6)->setNeighbors(&neighborsOfNode6);
    blockAreaNodePtrListPtr->at(7)->setNeighbors(&neighborsOfNode7);
    blockAreaNodePtrListPtr->at(8)->setNeighbors(&neighborsOfNode8);


    ASSERT_EQ(blockAreaNodePtrListPtr->at(0)->getNodeID(), blockAreaNodeList[1].getNeighbors()->at(0)->getNodeID());

    ASSERT_EQ(&blockAreaNodeList[0], blockAreaNodeList[1].getNeighbors()->at(0));
    ASSERT_EQ(&blockAreaNodeList[0], neighborsOfNode1[0]);
    ASSERT_EQ(blockAreaNodeList[1].getNodeID(), blockAreaNodeList[0].getNeighbors()->at(0)->getNodeID());
    ASSERT_EQ(&blockAreaNodeList[1], blockAreaNodeList[0].getNeighbors()->at(0));

    // 中央は4方の隣接ノードと等しい
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(1)->getNeighbors()->at(2));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(3)->getNeighbors()->at(1));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(5)->getNeighbors()->at(1));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(7)->getNeighbors()->at(0));

    // 中央は4隅の隣接ノードの隣接ノードと等しい
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(0)->getNeighbors()->at(0)->getNeighbors()->at(2));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(2)->getNeighbors()->at(1)->getNeighbors()->at(1));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(6)->getNeighbors()->at(0)->getNeighbors()->at(1));
    ASSERT_EQ(blockAreaNodePtrListPtr->at(4), blockAreaNodePtrListPtr->at(8)->getNeighbors()->at(1)->getNeighbors()->at(0));
  }

  // 4x4の隣接ノードリストを返す
  TEST(NodeTest, getValueOfNeighborListOf4x4Test)
  {
    Node node0;
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);
    Node node7(7);
    Node node8(8);
    Node node9(9);
    Node node10(10);
    Node node11(11);
    Node node12(12);
    Node node13(13);
    Node node14(14);
    Node node15(15);

    std::vector<Node*> neighbors0 = {&node1, &node4};
    std::vector<Node*> neighbors1 = {&node0, &node2, &node5};
    std::vector<Node*> neighbors2 = {&node1, &node3, &node6};
    std::vector<Node*> neighbors3 = {&node2, &node7};
    std::vector<Node*> neighbors4 = {&node0, &node5, &node8};
    std::vector<Node*> neighbors5 = {&node1, &node4, &node6, &node9};
    std::vector<Node*> neighbors6 = {&node2, &node5, &node7, &node10};
    std::vector<Node*> neighbors7 = {&node3, &node6, &node11};
    std::vector<Node*> neighbors8 = {&node4, &node9, &node12};
    std::vector<Node*> neighbors9 = {&node5, &node8, &node10, &node13};
    std::vector<Node*> neighbors10 = {&node6, &node9, &node11, &node14};
    std::vector<Node*> neighbors11 = {&node7, &node10, &node15};
    std::vector<Node*> neighbors12 = {&node8, &node13};
    std::vector<Node*> neighbors13 = {&node9, &node12, &node14};
    std::vector<Node*> neighbors14 = {&node10, &node13, &node15};
    std::vector<Node*> neighbors15 = {&node11, &node14};

    node0.setNeighbors(&neighbors0);
    node1.setNeighbors(&neighbors1);
    node2.setNeighbors(&neighbors2);
    node3.setNeighbors(&neighbors3);
    node4.setNeighbors(&neighbors4);
    node5.setNeighbors(&neighbors5);
    node6.setNeighbors(&neighbors6);
    node7.setNeighbors(&neighbors7);
    node8.setNeighbors(&neighbors8);
    node9.setNeighbors(&neighbors9);
    node10.setNeighbors(&neighbors10);
    node11.setNeighbors(&neighbors11);
    node12.setNeighbors(&neighbors12);
    node13.setNeighbors(&neighbors13);
    node14.setNeighbors(&neighbors14);
    node15.setNeighbors(&neighbors15);

    auto actual0 = node0.getNeighbors();
    auto actual1 = node1.getNeighbors();
    auto actual2 = node2.getNeighbors();
    auto actual3 = node3.getNeighbors();
    auto actual4 = node4.getNeighbors();
    auto actual5 = node5.getNeighbors();
    auto actual6 = node6.getNeighbors();
    auto actual7 = node7.getNeighbors();
    auto actual8 = node8.getNeighbors();
    auto actual9 = node9.getNeighbors();
    auto actual10 = node10.getNeighbors();
    auto actual11 = node11.getNeighbors();
    auto actual12 = node12.getNeighbors();
    auto actual13 = node13.getNeighbors();
    auto actual14 = node14.getNeighbors();
    auto actual15 = node15.getNeighbors();

    ASSERT_EQ(&neighbors0, actual0);
    ASSERT_EQ(&neighbors1, actual1);
    ASSERT_EQ(&neighbors2, actual2);
    ASSERT_EQ(&neighbors3, actual3);
    ASSERT_EQ(&neighbors4, actual4);
    ASSERT_EQ(&neighbors5, actual5);
    ASSERT_EQ(&neighbors6, actual6);
    ASSERT_EQ(&neighbors7, actual7);
    ASSERT_EQ(&neighbors8, actual8);
    ASSERT_EQ(&neighbors9, actual9);
    ASSERT_EQ(&neighbors10, actual10);
    ASSERT_EQ(&neighbors11, actual11);
    ASSERT_EQ(&neighbors12, actual12);
    ASSERT_EQ(&neighbors13, actual13);
    ASSERT_EQ(&neighbors14, actual14);
    ASSERT_EQ(&neighbors15, actual15);
  }

  // ETロボコン2018ブロック並べエリアにおける隣接ノードリストを返す
  TEST(NodeTest, getValueOfNeighborListOfETRobocon2018Test)
  {
    std::vector<std::vector<int>> neighborsIDList = {
        {1, 4},
        {0, 2, 5},
        {1, 3, 6},
        {2, 7},
        {0, 5, 8},
        {1, 4, 6, 9},
        {2, 5, 7, 10},
        {3, 6, 11},
        {4, 9, 12},
        {5, 8, 10, 13},
        {6, 9, 11, 14},
        {7, 10, 15},
        {8, 13},
        {9, 12, 14},
        {10, 13, 15},
        {11, 14}};
    int nodeCount = neighborsIDList.size();

    std::vector<Node> nodes(nodeCount);
    std::vector<Node*> nodePtrs(nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
      nodes[i].setNodeID(i);
      nodePtrs[i] = &nodes[i];
    }

    std::vector<std::vector<Node*>> neighbors(nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
      for (int nodeID : neighborsIDList[i])
      {
        neighbors[i].push_back(nodePtrs[nodeID]);
      }
    }
    for (int i = 0; i < nodeCount; i++)
    {
      nodePtrs[i]->setNeighbors(&neighbors[i]);
    }

    auto actual0 = nodePtrs[0]->getNeighbors();
    auto actual1 = nodePtrs[1]->getNeighbors();
    auto actual2 = nodePtrs[2]->getNeighbors();
    auto actual3 = nodePtrs[3]->getNeighbors();
    auto actual4 = nodePtrs[4]->getNeighbors();
    auto actual5 = nodePtrs[5]->getNeighbors();
    auto actual6 = nodePtrs[6]->getNeighbors();
    auto actual7 = nodePtrs[7]->getNeighbors();
    auto actual8 = nodePtrs[8]->getNeighbors();
    auto actual9 = nodePtrs[9]->getNeighbors();
    auto actual10 = nodePtrs[10]->getNeighbors();
    auto actual11 = nodePtrs[11]->getNeighbors();
    auto actual12 = nodePtrs[12]->getNeighbors();
    auto actual13 = nodePtrs[13]->getNeighbors();
    auto actual14 = nodePtrs[14]->getNeighbors();
    auto actual15 = nodePtrs[15]->getNeighbors();

    ASSERT_EQ(&neighbors[0], actual0);
    ASSERT_EQ(&neighbors[1], actual1);
    ASSERT_EQ(&neighbors[2], actual2);
    ASSERT_EQ(&neighbors[3], actual3);
    ASSERT_EQ(&neighbors[4], actual4);
    ASSERT_EQ(&neighbors[5], actual5);
    ASSERT_EQ(&neighbors[6], actual6);
    ASSERT_EQ(&neighbors[7], actual7);
    ASSERT_EQ(&neighbors[8], actual8);
    ASSERT_EQ(&neighbors[9], actual9);
    ASSERT_EQ(&neighbors[10], actual10);
    ASSERT_EQ(&neighbors[11], actual11);
    ASSERT_EQ(&neighbors[12], actual12);
    ASSERT_EQ(&neighbors[13], actual13);
    ASSERT_EQ(&neighbors[14], actual14);
    ASSERT_EQ(&neighbors[15], actual15);

    ASSERT_EQ(&neighbors[10], actual0->at(1)->getNeighbors()->at(1)->getNeighbors()->at(2)->getNeighbors()->at(3)->getNeighbors());
  }

  // ループを利用したETロボコン2017ブロック並べエリアにおける隣接ノードリストを返す
  TEST(NodeTest, getValueOfNeighborListOfETRobocon2017Test)
  {
    std::vector<std::vector<int>> neighborsIDList = {
        {1, 4, 9},
        {0, 2, 4, 5},
        {1, 3, 5, 6},
        {2, 6, 10},
        {0, 1, 7, 9},
        {1, 2, 7, 8},
        {2, 3, 8, 9},
        {4, 5, 11, 12},
        {5, 6, 13, 14},
        {0, 4, 11},
        {3, 6, 14},
        {7, 9, 12},
        {7, 11, 13},
        {8, 12, 14},
        {8, 10, 13}};
    int nodeCount = neighborsIDList.size();

    std::vector<Node> nodes(nodeCount);
    std::vector<Node*> nodePtrs(nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
      nodes[i].setNodeID(i);
      nodePtrs[i] = &nodes[i];
    }

    std::vector<std::vector<Node*>> neighbors(nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
      for (int nodeID : neighborsIDList[i])
      {
        neighbors[i].push_back(nodePtrs[nodeID]);
      }
    }
    for (int i = 0; i < nodeCount; i++)
    {
      nodePtrs[i]->setNeighbors(&neighbors[i]);
    }

    auto actual0 = nodePtrs[0]->getNeighbors();
    auto actual1 = nodePtrs[1]->getNeighbors();
    auto actual2 = nodePtrs[2]->getNeighbors();
    auto actual3 = nodePtrs[3]->getNeighbors();
    auto actual4 = nodePtrs[4]->getNeighbors();
    auto actual5 = nodePtrs[5]->getNeighbors();
    auto actual6 = nodePtrs[6]->getNeighbors();
    auto actual7 = nodePtrs[7]->getNeighbors();
    auto actual8 = nodePtrs[8]->getNeighbors();
    auto actual9 = nodePtrs[9]->getNeighbors();
    auto actual10 = nodePtrs[10]->getNeighbors();
    auto actual11 = nodePtrs[11]->getNeighbors();
    auto actual12 = nodePtrs[12]->getNeighbors();
    auto actual13 = nodePtrs[13]->getNeighbors();
    auto actual14 = nodePtrs[14]->getNeighbors();

    ASSERT_EQ(&neighbors[0], actual0);
    ASSERT_EQ(&neighbors[1], actual1);
    ASSERT_EQ(&neighbors[2], actual2);
    ASSERT_EQ(&neighbors[3], actual3);
    ASSERT_EQ(&neighbors[4], actual4);
    ASSERT_EQ(&neighbors[5], actual5);
    ASSERT_EQ(&neighbors[6], actual6);
    ASSERT_EQ(&neighbors[7], actual7);
    ASSERT_EQ(&neighbors[8], actual8);
    ASSERT_EQ(&neighbors[9], actual9);
    ASSERT_EQ(&neighbors[10], actual10);
    ASSERT_EQ(&neighbors[11], actual11);
    ASSERT_EQ(&neighbors[12], actual12);
    ASSERT_EQ(&neighbors[13], actual13);
    ASSERT_EQ(&neighbors[14], actual14);
  }

}  // namespace etrobocon2018_test
