#include "Selector.h"

std::vector<int> Selector::exploreNextOperation(std::int8_t currentPosition, BlockColor color)
{
  const std::int8_t shelterWhenPathBlocked = 12;
  const std::int8_t shelterWhenAllNodeInitialPositionsIsFromCenter = 12;
  const std::int8_t goal = 11;
  auto nextBlock = searchBlockPosition(currentPosition);
  auto nextMovedPosition = getPositionOfCenterQuadirilateral(color);
  auto routeBeforeOne = extractRoute();
  auto next = nextBlock;
  auto start = currentPosition;
  backsteppingFlag = false;
  backsteppingBeforeNextOeperationFlag = false;
  isClearGame = !isAlreadyMovedNode(EMPTY_ID);



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
      }
      else if (explorer.hasBlock(nextMovedPosition))
      {
        setNext(Evacuating);
        next = searchMostPoorCostShelter(currentPosition);
        pushEvacuatedBlockPosition(next);
      }
      // else if (explorer.hasBlock(4) && explorer.hasBlock(9) && explorer.hasBlock(12))
      // {
      //   // もし最初の位置コード8のブロックを囲むように周りにブロックが存在した場合
      //   // 現在は未実装
      // }
      else
      {
        setNext(Carrying);
        next = nextMovedPosition;
      }
    }
  }
  else if (lastBlock != EMPTY_ID && std::distance(movedBlockPositionList.begin(), std::find(movedBlockPositionList.begin(), movedBlockPositionList.end(), EMPTY_ID)) == 3)
  {
    setNext(Moving);
    next = lastBlock;
    lastBlock = EMPTY_ID;
  }
  else if (!isClearGame)
  {
    if (color == Undefined)
    {
      if (evacuatedSize > 0 && carryingFlag)
      {
        setNext(Moving);
        next = popEvacuatedBlockPosition();
      }
      else if (evacuatedSize > 0 && isCarriedToShelter)
      {
        setNext(Moving);
        next = popEvacuatedBlockPosition();
        isCarriedToShelter = false;
      }
      else
      {
        setNext(Moving);
      }
    }
    else
    {
      if (explorer.hasBlock(5) && explorer.hasBlock(6) && explorer.hasBlock(9) && explorer.hasBlock(10))
      {
        setNext(Evacuating);
        next = shelterWhenAllNodeInitialPositionsIsFromCenter;
        lastBlock = shelterWhenAllNodeInitialPositionsIsFromCenter;
      }
      else if (explorer.hasBlock(nextMovedPosition))
      {
        if (canFindBlockInEvacuatedList(nextMovedPosition))
        {
          next = searchMostPoorCostShelter(currentPosition);
          setNext(Evacuating);
          isCarriedToShelter = true;
        }
        else
        {
          pushEvacuatedBlockPosition(currentPosition);
          start = routeBeforeOne[routeBeforeOne.size() - 2];
          next = nextMovedPosition;
          setNext(Moving);
          backsteppingBeforeNextOeperationFlag = true;
        }
      }
      else
      {
        setNext(Carrying);
        next = nextMovedPosition;
      }
    }
  }
  else // if (isClearGame)
  {
    setNext(Moving);
    next = goal;
  }



  if (evacuatingFlag || carryingFlag) backsteppingFlag = true;

  if ((evacuatingFlag || carryingFlag) && !backsteppingBeforeNextOeperationFlag)
      changeBlockPosition(currentPosition, next);

  explorer.resetBlockArea();
  for (auto position: blockPositionList) explorer.setHasBlockIn(position);
  std::vector<int> route = searchRoute(start, next);

  // updateRoute(route);
  {
    // updateRoute(std::vector<int>)を利用するとメモリ肥大化をしてしまう
    // おそらく仮引数routeへの代入が問題
    // 関数内の文字列をまるまるコピペし、中括弧でくくる突貫工事で対応した
    for (auto itr = routeBeforeOne_.begin(); itr != routeBeforeOne_.end(); itr++)
        (* itr) = EMPTY_ID;

    int count = 0;

    for (auto node : route)
    {
      routeBeforeOne_[count] = node;
      count++;
    }
  }

  if (carryingFlag) addMovedBlockPosition(next);

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

std::int8_t Selector::searchMostPoorCostShelter(std::int8_t currentPosition)
{
  std::int8_t blockPosition = -1;
  int minCost = 9999;
  std::vector<std::int8_t> shelters = {0, 3, 12, 15};

  for (auto shelter: shelters)
  {
    explorer.resetBlockArea();
    for (auto position: blockPositionList) explorer.setHasBlockIn(position);

    if (explorer.hasBlock(shelter)) continue;

    if (shelter == currentPosition)
    {
      minCost = 0;
      blockPosition = shelter;
      break;
    }

    auto route = explorer.searchRoute(currentPosition, shelter);
    int cost = route.size() - 1;

    if (minCost > cost)
    {
      minCost = cost;
      blockPosition = shelter;
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
  return isClearGame;
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

bool Selector::canFindBlockInEvacuatedList(std::int8_t position)
{
  auto itr = std::find(evacuatedBlockPositionList.begin(), evacuatedBlockPositionList.end(), position);
  return itr != evacuatedBlockPositionList.end();
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
