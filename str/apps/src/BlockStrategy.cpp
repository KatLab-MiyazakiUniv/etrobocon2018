#include <BlockStrategy.h>

using namespace BlockSideBySide;

void BlockStrategy::createColorBlockPlace()
{
  for(std::int8_t i = 0; i < BLOCK_NUM; i++) {
    std::shared_ptr<ColorBlockPlace> blockPlace
        = std::make_shared<ColorBlockPlace>(ColorArray[i], i);
    colorBlockPlaceArray[i] = blockPlace;
  }
}

void BlockStrategy::connectColorBlockPlace()
{
  for(std::int8_t i = 0; i < BLOCK_NUM; i++) {
    if(i > 3) {  // ブロックエリア1行目以外
      colorBlockPlaceArray[i]->black_line[Direction::NORTH] = colorBlockPlaceArray[i - 4];
    }
    if(i < 12) {  // ブロックエリア4行目以外
      colorBlockPlaceArray[i]->black_line[Direction::SOUTH] = colorBlockPlaceArray[i + 4];
    }
    if(i % 4 != 0) {  // ブロックエリア1列目以外
      colorBlockPlaceArray[i]->black_line[Direction::EAST] = colorBlockPlaceArray[i - 1];
    }
    if(i % 4 != 3) {  // ブロックエリア4列目以外
      colorBlockPlaceArray[i]->black_line[Direction::WEST] = colorBlockPlaceArray[i + 1];
    }
  }
}
