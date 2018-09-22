#ifndef __BLOCK_AREA__
#define __BLOCK_AREA__

#include <cstdint>
#include <list>
#include <map>
#include <memory>

namespace BlockSideBySide {
  enum struct GameColor { UNKNOWN, RED, YELLOW, BLUE, GREEN };

  const std::array<GameColor, 16> ColorArray{
    GameColor::RED,  GameColor::YELLOW, GameColor::BLUE, GameColor::GREEN,
    GameColor::BLUE, GameColor::GREEN,  GameColor::RED,  GameColor::YELLOW,
    GameColor::RED,  GameColor::YELLOW, GameColor::BLUE, GameColor::GREEN,
    GameColor::BLUE, GameColor::GREEN,  GameColor::RED,  GameColor::YELLOW
  };

  enum struct Direction { EAST, NORTH, WEST, SOUTH };

  class ColorBlock {
   public:
    ColorBlock() = default;
    GameColor color = GameColor::UNKNOWN;
  };

  class ColorBlockPlace {
   public:
    ColorBlockPlace(GameColor color_, std::int8_t place_cord_)
      : color(color_), place_cord(place_cord_)
    {
    }
    std::shared_ptr<ColorBlock> block;
    std::map<Direction, std::shared_ptr<ColorBlockPlace>> black_line;
    GameColor getColor() { return color; }
    std::int8_t getPlaceCord() { return place_cord; }
    bool hasBlock()
    {
      if(block) {
        return true;
      }
      return false;
    }

   private:
    GameColor color = GameColor::UNKNOWN;
    std::int8_t place_cord = -1;
  };

  class BlockArea {
   public:
    // void calculateFirstCord();
    std::array<std::shared_ptr<ColorBlockPlace>, 16> colorBlockPlaceArray;

   private:
    std::unique_ptr<std::weak_ptr<ColorBlockPlace>> colorBlockPlaces;
    std::int32_t first_cord;
    std::list<ColorBlockPlace> waitTransportBlock;
    std::int8_t finishColorBlockNum = 0;
  };

}  // namespace BlockSideBySide
#endif