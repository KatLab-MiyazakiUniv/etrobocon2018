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

void Explorer::resetBlockArea()
{
  for (unsigned int i = 0; i < blockAreaNodeList->size(); i++)
  {
    blockAreaNodeList->at(i)->setBeClosed(false);
    blockAreaNodeList->at(i)->setHasBlock(false);
    blockAreaNodeList->at(i)->setScore(0);
    blockAreaNodeList->at(i)->setRealCost(0);
    blockAreaNodeList->at(i)->setParentNode(nullptr);
  }
}

void Explorer::setHasBlockIn(std::int8_t blockID)
{
  blockAreaNodeList->at(blockID)->setHasBlock(true);
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

  std::vector<Node*> around;
  Node* endNode = calculateNeighborCost(blockAreaNodeList->at(start), &around, 1, end);

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

Node* Explorer::calculateNeighborCost(Node* parent, std::vector<Node*>* around, std::int32_t realCost, std::int8_t end)
{
  std::int8_t current = parent->getNodeID();
  parent->setBeClosed(true);

  for (unsigned int i = 0; i < blockAreaNodeList->at(current)->getNeighbors()->size(); i++)
  // for (auto neighbor : blockAreaNodeList->at(parent->getNodeID())->getNeighbors())
  {
    auto neighbor = blockAreaNodeList->at(current)->getNeighbors()->at(i);
    if (neighbor->isClosed() || neighbor == parent->getParentNode()) continue;

    int estimatedCostX = std::abs(blockAreaNodeList->at(end)->getPositionX() - neighbor->getPositionX());
    int estimatedCostY = std::abs(blockAreaNodeList->at(end)->getPositionY() - neighbor->getPositionY());
    int score = realCost + estimatedCostX + estimatedCostY;
    if (neighbor->hasBlock() && neighbor->getNodeID() != end) score += 99;

    neighbor->setScore(score);
    neighbor->setRealCost(realCost);
    neighbor->setParentNode(parent);
    around->push_back(neighbor);
  }

  std::int32_t min = 999;
  std::int32_t minCost = 999;
  Node* minNode = nullptr;

  for (unsigned int i = 0; i < around->size(); i++)
  // for (auto neighbor : blockAreaNodeList->at(parent->getNodeID())->getNeighbors())
  {
    auto neighborhood = around->at(i);
    if (neighborhood->isClosed() || neighborhood == parent->getParentNode()) continue;

    int score = neighborhood->getScore();
    if (score > min || (score == min && neighborhood->getRealCost() >= minCost)) continue;

    min = score;
    minCost = neighborhood->getRealCost();
    minNode = neighborhood;
  }

  if (minNode->getNodeID() != end)
  {
    std::int8_t cost = 0;
    Node* node = minNode;
    while (node->getParentNode() == nullptr)
    {
      cost++;
      node = node->getParentNode();
    }
    minNode = calculateNeighborCost(minNode, around, realCost+1, end);
  }

  return minNode;
}

std::vector<Node*>* Explorer::getBlockAreaNodeList()
{
  return blockAreaNodeList;
}

