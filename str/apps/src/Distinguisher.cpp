#include "Distinguisher.h"
#include <cmath>

Color Distinguisher::getColor()
{
  setRawColor2Rgb();
  auto color = distingishColor();
  //addAr(color);
  //color = getAr();
  return color;
}

void Distinguisher::addAr(Color& color)
{
  ar[ar_count] = color;
  ar_count++;
  if(ar_count >= limit) {
    ar_count = 0;
  }
}

Color Distinguisher::getAr()
{
  std::map<Color, std::int8_t> mp;
  for(std::int8_t i = 0; i < limit; i++) {
    mp[ar[i]]++;
  }
  std::int8_t max = 0;
  Color result = Color::NONE;
  for(auto x : mp) {
    if(max < x.second) {
      result = x.first;
    }
  }

  return result;
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
  double tmp = distanceColor(rgb);
  if(tmp < min && tmp < rgb.threshold_distance) {
    color = rgb.color;
    min = last_distance = tmp;
  }
}

double Distinguisher::distanceColor(Rgb target_color)
{
  std::uint16_t pow_r = std::pow(raw_color.r - target_color.r, 2);
  std::uint16_t pow_g = std::pow(raw_color.g - target_color.g, 2);
  std::uint16_t pow_b = std::pow(raw_color.b - target_color.b, 2);
  return std::sqrt(pow_r + pow_g + pow_b);
}
