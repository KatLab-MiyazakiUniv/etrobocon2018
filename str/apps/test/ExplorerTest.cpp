/**
 * ExplorerTest.cpp
 */

#include "Explorer.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  // ノードIDの初期値を返す
  TEST(ExplorerTest, getInitialValueOfBlockAreaNodeListTest)
  {
    Explorer obj;
    std::vector<Node> expectedList = {
        Node, Node{1}, Node{2}, Node{3},
        Node{4}, Node{5}, Node{6}, Node{7},
        Node{8}, Node{9}, Node{10}, Node{11},
        Node{12}, Node{13}, Node{14}, Node{15}};

    auto actual = obj.getBlockAreaNodeList();

    ASSERT_EQ(expectedList.size(), actual->size());
    for (int i = 0; i < expectedList.size(); i++)
    {
      ASSERT_EQ(expectedList[i].getNodeID(), actual->at(i)->getNodeID());
    }
  }

}  // namespace etrobocon2018_test
