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
  for (auto itr = blockAreaNodeList->begin(); itr != blockAreaNodeList->end(); itr++)
  {
    (*itr)->setBeClosed(false);
    (*itr)->setHasBlock(false);
    (*itr)->setScore(0);
    (*itr)->setRealCost(0);
    (*itr)->setParentNode(nullptr);
  }
}

void Explorer::setHasBlockIn(std::int8_t blockID)
{
  auto itr = blockAreaNodeList->begin() + blockID;
  (*itr)->setHasBlock(true);
}

std::vector<int> Explorer::searchRoute(std::int8_t start, std::int8_t end)
{
  auto startItr = blockAreaNodeList->begin() + start;
  auto endItr = blockAreaNodeList->begin() + end;

  int estimatedCostX = std::abs((*endItr)->getPositionX() - (*startItr)->getPositionX());
  int estimatedCostY = std::abs((*endItr)->getPositionY() - (*startItr)->getPositionY());
  int score = estimatedCostX + estimatedCostY;
  if ((*startItr)->hasBlock()) score += 99;

  (*startItr)->setScore(score);
  (*startItr)->setRealCost(0);
  (*startItr)->setParentNode(nullptr);

  std::vector<Node*> around;
  Node* endNode = calculateNeighborCost((*startItr), &around, 1, end);

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
  auto currentItr = blockAreaNodeList->begin() + parent->getNodeID();
  auto endItr = blockAreaNodeList->begin() + end;

  parent->setBeClosed(true);

  for (auto itr = (*currentItr)->getNeighbors()->begin(); itr != (*currentItr)->getNeighbors()->end(); itr++)
  {
    if ((*itr)->isClosed() || (*itr) == parent->getParentNode()) continue;

    int estimatedCostX = std::abs((*endItr)->getPositionX() - (*itr)->getPositionX());
    int estimatedCostY = std::abs((*endItr)->getPositionY() - (*itr)->getPositionY());
    int score = realCost + estimatedCostX + estimatedCostY;
    if ((*itr)->hasBlock() && (*itr)->getNodeID() != end) score += 99;

    (*itr)->setScore(score);
    (*itr)->setRealCost(realCost);
    (*itr)->setParentNode(parent);
    around->push_back((*itr));
  }

  std::int32_t min = 999;
  std::int32_t minCost = 999;
  Node* minNode = nullptr;

  for (auto itr = around->begin(); itr != around->end(); itr++)
  {
    if ((*itr)->isClosed() || (*itr) == parent->getParentNode()) continue;

    int score = (*itr)->getScore();
    if (score > min || (score == min && (*itr)->getRealCost() >= minCost)) continue;

    min = score;
    minCost = (*itr)->getRealCost();
    minNode = (*itr);
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

