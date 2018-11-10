#include "Selector.h"

std::int8_t Selector::searchBlockPosition(std::int8_t currentPosition)
{
  std::int8_t blockPosition = -1;
  int minCost = 9999;

  for (unsigned int i = 0; i < blockPositionList.size(); i++)
  {
    std::int8_t checkedBlock = blockPositionList[i];
    explorer.resetBlockArea();
    for (auto position: blockPositionList) explorer.setHasBlockIn(position);

    if (checkedBlock == currentPosition) {
      minCost = 0;
      blockPosition = checkedBlock;
      break;
    }

    auto route = explorer.searchRoute(currentPosition, checkedBlock);
    int cost = route.size() - 1 + nodePositionCostList[checkedBlock];

    if (minCost > cost) {
      minCost = cost;
      blockPosition = checkedBlock;
    }
  }

  return blockPosition;
}

void Selector::setBlockPositionList(std::vector<std::int8_t> list)
{
  for (unsigned int i = 0; i < blockPositionList.size(); i++)
  {
    if (list.size() >= i)
    {
      blockPositionList[i] = list[i];
    }
    else
    {
      blockPositionList[i] = EMPTY_ID;
    }
  }
}

std::vector<std::int8_t> Selector::getBlockPositionList()
{
  return blockPositionList;
}

