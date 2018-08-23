#ifndef __DISTINGUISHER_H__
#define __DISTINGUISHER_H__

#include "Controller.h"
#include <cstdint>

enum struct Color { NONE, BLACK, WHITE, RED, BLUE, YELLOW, GREEN };

struct Rgb {
  Color color;
  std::uint16_t r;
  std::uint16_t g;
  std::uint16_t b;
};

class DistinguisherTest;

class Distinguisher {
  friend class DistinguisherTest;

 public:
  Distinguisher() = default;
  explicit Distinguisher(Controller controller_) : controller(controller_) {}
  Color getColor();
  Color distingishColor();
  void setRawColor2Rgb();
  void judgement(const Rgb& rgb, double& min);
  double distanceColor(Rgb target_color);
  double last_distance = 0.0;
  double threshold_distance = 400;

 private:
  Controller controller;
  Color color = Color::NONE;
  Rgb raw_color = { Color::NONE, 0, 0, 0 };
  const Rgb RED = { Color::RED, 255, 0, 0 };
  const Rgb BLUE = { Color::BLUE, 0, 0, 255 };
  const Rgb GREEN = { Color::GREEN, 0, 255, 0 };
  const Rgb YELLOW = { Color::YELLOW, 255, 255, 0 };
  const Rgb BLACK = { Color::BLACK, 0, 0, 0 };
  const Rgb WHITE = { Color::WHITE, 255, 255, 255 };
};

#endif