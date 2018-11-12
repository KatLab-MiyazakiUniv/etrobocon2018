#include <BlockArea.h>

BlockSideBySide::Direction BlockSideBySide::BlockArea::getDirection(std::int8_t n1, std::int8_t n2)
{
  if(n1 % 4 != 3
     && colorBlockPlaceArray[n1]->black_line[BlockSideBySide::Direction::WEST]->getPlaceCord()
            == n2) {
    return BlockSideBySide::Direction::WEST;
  } else if(n1 % 4 != 0
            && colorBlockPlaceArray[n1]
                       ->black_line[BlockSideBySide::Direction::EAST]
                       ->getPlaceCord()
                   == n2) {
    return BlockSideBySide::Direction::EAST;
  } else if(n1 > 3
            && colorBlockPlaceArray[n1]
                       ->black_line[BlockSideBySide::Direction::NORTH]
                       ->getPlaceCord()
                   == n2) {
    return BlockSideBySide::Direction::NORTH;
  } else {
    return BlockSideBySide::Direction::SOUTH;
  }
}