#ifndef __BLOCK_STRATEGY__
#define __BLOCK_STRATEGY__

#include "BlockArea.h"
#include "InitialPositionCodeDecoder.h"
#include <array>

namespace etrobocon2018_test {
  class BlockStrategyTest;
}

namespace BlockSideBySide {
  static constexpr std::int8_t BLOCK_NUM = 16;

  class BlockStrategy {
    friend class etrobocon2018_test::BlockStrategyTest;

   public:
    explicit BlockStrategy(std::int32_t ipc_) : initialPositionCode(ipc_)
    {
      createColorBlockPlace();
      putColorBlock();
      connectColorBlockPlace();
      blockArea.colorBlockPlaceArray = colorBlockPlaceArray;
    }
    BlockArea blockArea;
    std::vector<std::int8_t> decodedColorBlockCodeList;

   private:
    std::int32_t initialPositionCode;  // = 1*16^4 + 2*16^3 + 4*16^2 + 5*16^1 + 8
    std::array<std::shared_ptr<ColorBlockPlace>, BLOCK_NUM> colorBlockPlaceArray;
    void createColorBlockPlace();
    void connectColorBlockPlace();
    void putColorBlock();
  };
}  // namespace BlockSideBySide

#endif