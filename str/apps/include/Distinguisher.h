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

/*! @class Hsv Distinguisher.h "Distinguisher.h"
 *  @brief 色とHsv情報を保持するクラス。
 */
struct Hsv {
  explicit Hsv(Color color_, double h_, double s_, double v_, double threshold_distance_,
               double start_h_, double end_h_)
    : color(color_),
      h(h_),
      s(s_),
      v(v_),
      threshold_distance(threshold_distance_),
      start_h(start_h_),
      end_h(end_h_)
  {
  }
  Color color;
  double h;
  double s;
  double v;
  double threshold_distance;
  double start_h;
  double end_h;
};

struct Rgb {
  std::uint16_t r = 0;
  std::uint16_t g = 0;
  std::uint16_t b = 0;
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

  Hsv hsv{ Color::NONE, 0, 0, 0, 400, 0, 0 };

 private:
  void setRawColor2Rgb();
  void convertRgbToHsv(Rgb rgb_);
  void distingishColor();
  void judgement(const Hsv& hsv_, double& min);
  double distanceColor(Hsv target_color);

  Controller controller;
  Color color = Color::NONE;
<<<<<<< HEAD
  Rgb rgb;
  const Hsv RED{ Color::RED, 0, 92, 35, 400, 0, 40 };
  const Hsv AltRED{ Color::RED, 0, 92, 35, 400, 300, 360 };
  const Hsv BLUE{ Color::BLUE, 0, 75, 19, 400, 160, 240 };
  const Hsv GREEN{ Color::GREEN, 0, 81, 27, 400, 100, 150 };
  const Hsv YELLOW{ Color::YELLOW, 0, 90, 36, 400, 50, 80 };
=======
  Color distingishColor();
  void setRawColor2Rgb();
  void judgement(const Rgb& rgb, double& min);
  double distanceColor(Rgb target_color);
  void addAr(Color& color);
  Color getAr();
  const Rgb RED = { Color::RED, 81, 25, 5, 31 };
  const Rgb BLUE = { Color::BLUE, 35, 52, 17, 6 };
  const Rgb GREEN = { Color::GREEN, 13, 61, 12, 18 };
  const Rgb YELLOW = { Color::YELLOW, 88, 88, 12, 44 };
  const Rgb BLACK = { Color::BLACK, 7, 8, 5, 12 };
  const Rgb WHITE = { Color::WHITE, 90, 100, 81, 63 };
  static constexpr std::int8_t limit = 10;
  std::array<Color, limit> ar{ Color::NONE, Color::NONE, Color::NONE, Color::NONE, Color::NONE,
                               Color::NONE, Color::NONE, Color::NONE, Color::NONE, Color::NONE };
  std::int8_t ar_count = 0;
>>>>>>> 751b48e58956ffd3ea049220ab92d433957e4fe9
};

#endif
