#include "Selector.h"

std::vector<int> Selector::exploreNextOperation(std::int8_t currentPosition, BlockColor color)
{
  const std::int8_t shelterWhenPathBlocked = 12;
  const std::int8_t goal = 11;
  auto nextBlock = searchBlockPosition(currentPosition);
  auto nextMovedPosition = getPositionOfCenterQuadirilateral(color);
  auto routeBeforeOne = extractRoute();
  auto next = nextBlock;
  auto start = currentPosition;
  bool isGoingToCarryBlock = false;
  bool isGoingToEvacuateBlock = false;
  backsteppingFlag = false;
  backsteppingBeforeNextOeperationFlag = false;

  if (currentPosition == 8 && nextBlock == 8)
  {
    if (color == Undefined)
    {
      setNext(Moving);
    }
    else
    {
      if (explorer.hasBlock(4) && explorer.hasBlock(9) && explorer.hasBlock(13))
      {
        setNext(Evacuating);
        next = shelterWhenPathBlocked;
        pushEvacuatedBlockPosition(shelterWhenPathBlocked);
        isGoingToEvacuateBlock = true;
      }
      else if (explorer.hasBlock(nextMovedPosition))
      {
        setNext(Evacuating);
        next = shelterWhenPathBlocked;
        pushEvacuatedBlockPosition(shelterWhenPathBlocked);
        isGoingToEvacuateBlock = true;
      }
      else
      {
        setNext(Carrying);
        next = nextMovedPosition;
        isGoingToCarryBlock = true;
      }
    }
  }
  else if (isAlreadyAllBlockMoved())
  {
    setNext(Moving);
    next = goal;
  }
  else
  {
    if (color == Undefined)
    {
      if (evacuatedSize > 0 && (!evacuatingFlag || carryingFlag))
      {
        setNext(Moving);
        next = popEvacuatedBlockPosition();
      }
      else
      {
        setNext(Moving);
      }
    }
    else
    {
      if (explorer.hasBlock(nextMovedPosition))
      {
        pushEvacuatedBlockPosition(currentPosition);
        start = routeBeforeOne[routeBeforeOne.size() - 2];
        next = nextMovedPosition;
        setNext(Moving);
        backsteppingBeforeNextOeperationFlag = true;
      }
      else
      {
        setNext(Carrying);
        next = nextMovedPosition;
        isGoingToCarryBlock = true;
      }
    }
  }

  if (evacuatingFlag || carryingFlag) backsteppingFlag = true;

  if ((isGoingToCarryBlock || isGoingToEvacuateBlock) && !backsteppingBeforeNextOeperationFlag)
  {
    changeBlockPosition(currentPosition, next);
  }

  explorer.resetBlockArea();
  for (auto position: blockPositionList) explorer.setHasBlockIn(position);
  std::vector<int> route = searchRoute(start, next);

  // updateRoute(route);
  {
    for (auto itr = routeBeforeOne_.begin(); itr != routeBeforeOne_.end(); itr++)
        (* itr) = EMPTY_ID;

    int count = 0;

    for (auto node : route)
    {
      routeBeforeOne_[count] = node;
      count++;
    }
  }

  if (isGoingToCarryBlock)
  {
    addMovedBlockPosition(next);
  }

  return route;
}

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

bool Selector::isAlreadyAllBlockMoved()
{
  return !isAlreadyMovedNode(EMPTY_ID);
}

void Selector::changeBlockPosition(std::int8_t beforePosition, std::int8_t afterPosition)
{
  auto itr = std::find(blockPositionList.begin(), blockPositionList.end(), beforePosition);
  auto index = std::distance(blockPositionList.begin(), itr);

  blockPositionList[index] = afterPosition;
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

void Selector::pushEvacuatedBlockPosition(std::int8_t position)
{
  evacuatedBlockPositionList[evacuatedSize] = position;
  evacuatedSize++;
}

std::int8_t Selector::popEvacuatedBlockPosition()
{
  evacuatedSize--;
  return evacuatedBlockPositionList[evacuatedSize];
}

void Selector::prepareSearching(std::vector<std::int8_t> list)
{
  explorer.resetBlockArea();

  for (auto id : list)
  {
    explorer.setHasBlockIn(id);
  }
}

std::vector<int> Selector::searchRoute(std::int8_t start, std::int8_t end)
{
  if (start == end)
  {
    std::vector<int> only{1};
    only[0] = start;
    return only;
  }
  else
  {
    return explorer.searchRoute(start, end);
  }
}

void Selector::setNext(NextOperationOfSearchingRouteIs next)
{
  switch(next)
  {
  case Evacuating:
    evacuatingFlag = true;
    movingFlag = false;
    carryingFlag = false;
    break;

  case Moving:
    evacuatingFlag = false;
    movingFlag = true;
    carryingFlag = false;
    break;

  case Carrying:
    evacuatingFlag = false;
    movingFlag = false;
    carryingFlag = true;
    break;

  default:
    break;
  }
}

bool Selector::isEvacuatingWithNext()
{
  return evacuatingFlag;
}

bool Selector::isMovingWithNext()
{
  return movingFlag;
}

bool Selector::isCarryingWithNext()
{
  return carryingFlag;
}

bool Selector::isBackstepping()
{
  return backsteppingFlag;
}

bool Selector::isBacksteppingBeforeNextOperation()
{
  return backsteppingBeforeNextOeperationFlag;
}

std::int8_t Selector::getPositionOfCenterQuadirilateral(BlockColor color)
{
  std::int8_t node;

  switch(color)
  {
  case Blue:
    node = 10;
    break;

  case Red:
    node = 6;
    break;

  case Yellow:
    node = 9;
    break;

  case Green:
    node = 5;
    break;

  case Undefined:
  default:
    node = EMPTY_ID;
    break;
  }

  return node;
}

[[deprecated("memory is enlarged if this is used!!!")]]
void Selector::updateRoute(std::vector<int> route)
{
  for (auto itr = routeBeforeOne_.begin(); itr != routeBeforeOne_.end(); itr++)
      (* itr) = EMPTY_ID;

  int count = 0;

  for (auto node : route)
  {
    routeBeforeOne_[count] = node;
    count++;
  }
}

std::vector<int> Selector::extractRoute()
{
  std::vector<int> route(TOTAL_NODE_COUNT, EMPTY_ID);

  for (int i = 0; i < TOTAL_NODE_COUNT; i++)
  {
    if (routeBeforeOne_[i] == EMPTY_ID)
        route.pop_back();
    else
        route[i] = routeBeforeOne_[i];
  }

  return route;
}
