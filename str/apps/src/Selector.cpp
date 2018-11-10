#include "Selector.h"

std::int8_t Selector::searchBlockPosition(std::int8_t currentPosition)
{
  std::int8_t blockPosition = -1;
  int minCost = 9999;

  for (auto checkedBlock: blockPositionList)
  {
    if (isAlreadyMovedNode(checkedBlock)) continue;

    explorer.resetBlockArea();
    for (auto position: blockPositionList) explorer.setHasBlockIn(position);

    if (checkedBlock == currentPosition)
    {
      minCost = 0;
      blockPosition = checkedBlock;
      break;
    }

    auto route = explorer.searchRoute(currentPosition, checkedBlock);
    int cost = route.size() - 1 + nodePositionCostList[checkedBlock];

    if (minCost > cost)
    {
      minCost = cost;
      blockPosition = checkedBlock;
    }
  }

  return blockPosition;
}

bool Selector::isAlreadyMovedNode(std::int8_t position)
{
  auto itr = std::find(movedBlockPositionList.begin(), movedBlockPositionList.end(), position);
  return itr != movedBlockPositionList.end();
}

void Selector::setBlockPositionList(std::vector<std::int8_t> list)
{
  for (unsigned int i = 0; i < blockPositionList.size(); i++)
  {
    blockPositionList[i] = list[i];
  }
}

std::vector<std::int8_t> Selector::getBlockPositionList()
{
  return blockPositionList;
}

void Selector::addMovedBlockPosition(std::int8_t position)
{
  movedBlockPositionList[movedCount] = position;
  movedCount++;
}

