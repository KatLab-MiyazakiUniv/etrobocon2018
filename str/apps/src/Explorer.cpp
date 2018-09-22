#include "Explorer.h"

void Explorer::createBlockArea()
{
  int nodeCount = neighborsIDList.size();

  // ノードのポインタのリストを作成
  for (int i = 0; i < nodeCount; i++)
  {
    nodeList[i].setNodeID(i);
    nodePtrs[i] = &nodeList[i];
  }

  // 隣接ノードのポインタのリストをノード分リスト化
  for (int i = 0; i < nodeCount; i++)
  {
    for (int nodeID : neighborsIDList[i])
    {
      neighbors[i].push_back(nodePtrs[nodeID]);
    }
  }

  // 隣接ノードのポインタのリストを格納
  for (int i = 0; i < nodeCount; i++)
  {
    nodePtrs[i]->setNeighbors(&neighbors[i]);
    nodePtrs[i]->setPosition(positionList[i].x, positionList[i].y);
  }

  // 各ノードのポインタを格納
  blockAreaNodeList = &nodePtrs;

}

std::vector<int> Explorer::searchRoute(std::int8_t start, std::int8_t end)
{
  std::vector<int> route = {start};
  std::vector<Node*> currentNeighbors;
  Node* minNode = nullptr;

  for (unsigned int i = 0; i < blockAreaNodeList->at(start)->getNeighbors()->size(); i++)
  {
    auto neighbor = blockAreaNodeList->at(start)->getNeighbors()->at(i);
    int realCost = 0;
    int estimatedCostX =
        blockAreaNodeList->at(end)->getPositionX() - neighbor->getPositionX();
    int estimatedCostY =
        blockAreaNodeList->at(end)->getPositionY() - neighbor->getPositionY();
    if (estimatedCostX < 0) estimatedCostX -= estimatedCostX;
    if (estimatedCostY < 0) estimatedCostY -= estimatedCostY;
    int score = realCost + estimatedCostX + estimatedCostY;

    neighbor->setScore(score);
    neighbor->setRealCost(realCost);
    currentNeighbors.push_back(neighbor);
  }

  int min = 9999;
  int minCost = 9999;

  for (auto neighbor : currentNeighbors)
  {
    int score = neighbor->getScore();
    if (score > min || (score == min && neighbor->getRealCost() >= minCost)) continue;

    min = score;
    minCost = neighbor->getRealCost();
    minNode = neighbor;
  }

  route.push_back(minNode->getNodeID());

  return route;
}

std::vector<Node*>* Explorer::getBlockAreaNodeList()
{
  return blockAreaNodeList;
}

