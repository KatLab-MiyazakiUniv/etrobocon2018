/**
 * @file Distinguisher.h
 * @brief 走行体のカラーセンサを用いて、RGB情報より色を推定するクラス。
 * @author Futa HIRAKOBA
 */

#ifndef __DISTINGUISHER_H__
#define __DISTINGUISHER_H__

#include "Controller.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <map>

enum struct Color { NONE, BLACK, WHITE, RED, BLUE, YELLOW, GREEN };

/*! @class Rgb Distinguisher.h "Distinguisher.h"
 *  @brief 色とRGB情報を保持するクラス。
 */
struct Rgb {
  Color color;
  std::uint16_t r;
  std::uint16_t g;
  std::uint16_t b;
  double threshold_distance;
};

namespace etrobocon2018_test {
  class DistinguisherTest;
}

/*! @class Distinguisher Distinguisher.h "Distinguisher.h"
 *  @brief 走行体のカラーセンサを用いて、RGB情報より色を推定するクラス。
 */
class Distinguisher {
  friend class etrobocon2018_test::DistinguisherTest;

 public:
  /** コンストラクタ
   * @param controller_ ev3apiを持つControllerクラス。 */
  explicit Distinguisher(Controller& controller_) : controller(controller_) {}

  /** カラーセンサ先の色を取得する。
   * @return 色 */
  Color getColor();

  /** 最後にgetColorした際の色距離 */
  double last_distance = 0.0;

  /** getColorする際の最低限必要な色距離 */
  double threshold_distance = 400;

  Rgb raw_color = { Color::NONE, 0, 0, 0, 400 };

 private:
  Controller controller;
  Color color = Color::NONE;
  Color distingishColor();
  void setRawColor2Rgb();
  void judgement(const Rgb& rgb, double& min);
  double distanceColor(Rgb target_color);
  void addAr(Color& color);
  Color getAr();
  const Rgb RED = { Color::RED, 112, 13, 9, 40 };
  const Rgb BLUE = { Color::BLUE, 18, 47, 50, 20 };
  const Rgb GREEN = { Color::GREEN, 24, 77, 13, 20 };
  const Rgb YELLOW = { Color::YELLOW, 116, 120, 15, 50 };
  const Rgb BLACK = { Color::BLACK, 14, 19, 5, 30 };
  const Rgb WHITE = { Color::WHITE, 128, 158, 93, 210 };
  static constexpr std::int8_t limit = 10;
  std::array<Color, limit> ar{ Color::NONE, Color::NONE, Color::NONE, Color::NONE, Color::NONE,
                               Color::NONE, Color::NONE, Color::NONE, Color::NONE, Color::NONE };
  std::int8_t ar_count = 0;
};

#endif