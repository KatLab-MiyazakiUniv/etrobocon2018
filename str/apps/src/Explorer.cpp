#include "Explorer.h"
#include "iostream"

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
  std::vector<Node*> currentNeighbors;
  Node* endNode = calculateNeighborCost(blockAreaNodeList->at(start), currentNeighbors, 0, start, end);

  std::vector<int> route = {endNode->getNodeID()};
  Node* parent = endNode->getParentNode();
  while (parent != nullptr)
  {
    route.push_back(parent->getNodeID());
    parent = parent->getParentNode();
  }

  std::reverse(route.begin(), route.end());

  return route;
}

Node* Explorer::calculateNeighborCost(Node* parent, std::vector<Node*> around, std::int32_t realCost, std::int8_t current, std::int8_t end)
{
  for (unsigned int i = 0; i < blockAreaNodeList->at(current)->getNeighbors()->size(); i++)
  {
    auto neighbor = blockAreaNodeList->at(current)->getNeighbors()->at(i);
    if (neighbor == parent->getParentNode()) continue;

    int estimatedCostX = blockAreaNodeList->at(end)->getPositionX() - neighbor->getPositionX();
    int estimatedCostY = blockAreaNodeList->at(end)->getPositionY() - neighbor->getPositionY();
    if (estimatedCostX < 0) estimatedCostX -= estimatedCostX;
    if (estimatedCostY < 0) estimatedCostY -= estimatedCostY;

    int score = realCost + estimatedCostX + estimatedCostY;
    // if (neighbor->hasBlock()) score += 99;

    neighbor->setScore(score);
    neighbor->setRealCost(realCost);
    neighbor->setParentNode(parent);
    neighbor->setBeClosed(true);
    around.push_back(neighbor);
  }

  std::int32_t min = 999;
  std::int32_t minCost = 999;
  Node* minNode = nullptr;

  for (auto neighbor : around)
  {
    int score = neighbor->getScore();
    if (score > min || (score == min && neighbor->getRealCost() >= minCost)) continue;

    min = score;
    minCost = neighbor->getRealCost();
    minNode = neighbor;
  }

  if (minNode->getNodeID() != end)
  {
    minNode = calculateNeighborCost(minNode, around, realCost+1, minNode->getNodeID(), end);
  }

  return minNode;
}

std::vector<Node*>* Explorer::getBlockAreaNodeList()
{
  return blockAreaNodeList;
}

