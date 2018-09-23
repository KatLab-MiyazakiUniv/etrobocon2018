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
      neighborPtrs[i].push_back(nodePtrs[nodeID]);
    }
  }

  // 隣接ノードのポインタのリストを格納
  for (int i = 0; i < nodeCount; i++)
  {
    nodePtrs[i]->setNeighbors(&neighborPtrs[i]);
    nodePtrs[i]->setPosition(positionList[i].x, positionList[i].y);
  }

  // 各ノードのポインタを格納
  blockAreaNodeList = &nodePtrs;

}

std::vector<int> Explorer::searchRoute(std::int8_t start, std::int8_t end)
{
  int estimatedCostX = std::abs(blockAreaNodeList->at(end)->getPositionX() - blockAreaNodeList->at(start)->getPositionX());
  int estimatedCostY = std::abs(blockAreaNodeList->at(end)->getPositionY() - blockAreaNodeList->at(start)->getPositionY());
  int score = estimatedCostX + estimatedCostY;
  if (blockAreaNodeList->at(start)->hasBlock()) score += 99;

  blockAreaNodeList->at(start)->setScore(score);
  blockAreaNodeList->at(start)->setRealCost(0);
  blockAreaNodeList->at(start)->setParentNode(nullptr);
  blockAreaNodeList->at(start)->setBeClosed(true);
  Node* endNode = calculateNeighborCost(blockAreaNodeList->at(start), 1, end);

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

Node* Explorer::calculateNeighborCost(Node* parent, std::int32_t realCost, std::int8_t end)
{
  std::int8_t current = parent->getNodeID();

  for (unsigned int i = 0; i < blockAreaNodeList->at(current)->getNeighbors()->size(); i++)
  // for (auto neighbor : blockAreaNodeList->at(parent->getNodeID())->getNeighbors())
  {
    auto neighbor = blockAreaNodeList->at(current)->getNeighbors()->at(i);
    if (neighbor == parent->getParentNode()) continue;

    int estimatedCostX = std::abs(blockAreaNodeList->at(end)->getPositionX() - neighbor->getPositionX());
    int estimatedCostY = std::abs(blockAreaNodeList->at(end)->getPositionY() - neighbor->getPositionY());
    int score = realCost + estimatedCostX + estimatedCostY;
    if (neighbor->hasBlock()) score += 99;

    neighbor->setScore(score);
    neighbor->setRealCost(realCost);
    neighbor->setParentNode(parent);
    neighbor->setBeClosed(true);
    // neighbors.push_back(neighbor);
  }

  std::int32_t min = 999;
  std::int32_t minCost = 999;
  Node* minNode = nullptr;

  for (unsigned int i = 0; i < blockAreaNodeList->at(current)->getNeighbors()->size(); i++)
  // for (auto neighbor : blockAreaNodeList->at(parent->getNodeID())->getNeighbors())
  {
    auto neighbor = blockAreaNodeList->at(current)->getNeighbors()->at(i);
    if (neighbor == parent->getParentNode()) continue;

    int score = neighbor->getScore();
    if (score > min || (score == min && neighbor->getRealCost() >= minCost)) continue;

    min = score;
    minCost = neighbor->getRealCost();
    minNode = neighbor;
  }

  if (minNode->getNodeID() != end)
  {
    minNode = calculateNeighborCost(minNode, realCost+1, end);
  }

  return minNode;
}

std::vector<Node*>* Explorer::getBlockAreaNodeList()
{
  return blockAreaNodeList;
}

