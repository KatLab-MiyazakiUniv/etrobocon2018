#ifndef __BLOCK_STRATEGY__
#define __BLOCK_STRATEGY__

#include "BlockArea.h"
#include <array>

namespace etrobocon2018_test {
  class BlockStrategyTest;
}

namespace BlockSideBySide {
  static constexpr std::int8_t BLOCK_NUM = 16;

  class BlockStrategy {
    friend class etrobocon2018_test::BlockStrategyTest;

   public:
    BlockStrategy()
    {
      createColorBlockPlace();
      connectColorBlockPlace();
      blockArea.colorBlockPlaceArray = colorBlockPlaceArray;
    }

   private:
    BlockArea blockArea;
    std::array<std::shared_ptr<ColorBlockPlace>, BLOCK_NUM> colorBlockPlaceArray;
    void createColorBlockPlace();
    void connectColorBlockPlace();
  };
}  // namespace BlockSideBySide

#endif