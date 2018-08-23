#include "Distinguisher.h"
#include <cmath>

Color Distinguisher::getColor()
{
  setRawColor2Rgb();
  auto color = distingishColor();
  return color;
}

void Distinguisher::setRawColor2Rgb()
{
  std::uint32_t total_r, total_g, total_b;
  std::int8_t times = 10;

  total_r = total_g = total_b = 0;
  for(int i = 0; i < times; i++) {
    controller.getRawColor(raw_color.r, raw_color.g, raw_color.b);
    total_r += raw_color.r;
    total_g += raw_color.g;
    total_b += raw_color.b;
  }
  raw_color.r = total_r / times;
  raw_color.g = total_g / times;
  raw_color.b = total_b / times;
}

Color Distinguisher::distingishColor()
{
  color = Color::NONE;
  double min_distance = threshold_distance;

  judgement(RED, min_distance);
  judgement(BLUE, min_distance);
  judgement(YELLOW, min_distance);
  judgement(GREEN, min_distance);
  judgement(WHITE, min_distance);
  judgement(BLACK, min_distance);
  return color;
}

void Distinguisher::judgement(const Rgb& rgb, double& min)
{
  double tmp = last_distance = distanceColor(rgb);
  if(tmp < min) {
    color = rgb.color;
    min = tmp;
  }
}

double Distinguisher::distanceColor(Rgb target_color)
{
  std::uint16_t pow_r = std::pow(raw_color.r - target_color.r, 2);
  std::uint16_t pow_g = std::pow(raw_color.g - target_color.g, 2);
  std::uint16_t pow_b = std::pow(raw_color.b - target_color.b, 2);
  return std::sqrt(pow_r + pow_g + pow_b);
}
