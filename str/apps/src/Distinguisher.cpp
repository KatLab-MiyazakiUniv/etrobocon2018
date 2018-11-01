#include "Distinguisher.h"
#include <cmath>

Color Distinguisher::getColor()
{
  setRawColor2Rgb();
  convertRgbToHsv(rgb);
  distingishColor();
  return color;
}

void Distinguisher::distingishColor()
{
  color = Color::NONE;
  double min_distance = threshold_distance;
  std::int8_t black_threthold = 10;
  std::int8_t white_threthold = 40;

  judgement(RED, min_distance);
  judgement(AltRED, min_distance);
  judgement(BLUE, min_distance);
  judgement(YELLOW, min_distance);
  judgement(GREEN, min_distance);
  if(color == Color::YELLOW) {
    black_threthold = 20;
  } else if(color == Color::GREEN) {
    white_threthold = 35;
    if(hsv.s < 40) {
      color = Color::WHITE;
    }
  }
  if(hsv.v < black_threthold) {
    color = Color::BLACK;
  } else if(hsv.v > white_threthold) {
    color = Color::WHITE;
  }
}

void Distinguisher::judgement(const Hsv& hsv_, double& min)
{
  double tmp = std::abs((hsv_.start_h + hsv_.end_h) / 2 - hsv.h);
  if(min > tmp) return;
  if(hsv_.start_h < hsv.h && hsv_.end_h > hsv.h) {
    min = tmp;
    color = hsv_.color;
  }
}

double Distinguisher::distanceColor(Hsv target_color)
{
  std::uint16_t pow_h = std::pow(hsv.h - target_color.h, 2);
  std::uint16_t pow_s = std::pow(hsv.s - target_color.s, 2);
  std::uint16_t pow_v = std::pow(hsv.v - target_color.v, 2);
  return std::sqrt(pow_h + pow_s + pow_v);
}

void Distinguisher::setRawColor2Rgb()
{
  std::uint32_t total_r, total_g, total_b;
  std::int8_t times = 10;

  total_r = total_g = total_b = 0;
  for(int i = 0; i < times; i++) {
    controller.getRawColor(rgb.r, rgb.g, rgb.b);
    total_r += rgb.r;
    total_g += rgb.g;
    total_b += rgb.b;
  }
  rgb.r = total_r / times;
  rgb.g = total_g / times;
  rgb.b = total_b / times;
}

void Distinguisher::convertRgbToHsv(Rgb rgb_)
{
  double max = std::max((std::max(rgb_.r, rgb_.g)), rgb_.b);
  double min = std::min((std::min(rgb_.r, rgb_.g)), rgb_.b);
  hsv.v = max / 256 * 100;

  if(max == min) {
    hsv.h = 0;
    hsv.s = 0;
  } else {
    if(max == rgb_.r)
      hsv.h = 60.0 * (rgb_.g - rgb_.b) / (max - min) + 0;
    else if(max == rgb_.g)
      hsv.h = 60.0 * (rgb_.b - rgb_.r) / (max - min) + 120.0;
    else if(max == rgb_.b)
      hsv.h = 60.0 * (rgb_.r - rgb_.g) / (max - min) + 240.0;

    if(hsv.h > 360.0) {
      hsv.h = hsv.h - 360.0;
    } else if(hsv.h < 0) {
      hsv.h = hsv.h + 360.0;
    }
    hsv.s = (max - min) / max * 100.0;
  }
}
