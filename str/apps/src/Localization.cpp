#include "Localization.h"

std::int32_t Localization::radius(std::int32_t left_motor, std::int32_t right_motor)
{
  float radius_wheel = wheel_diameter / 2;
  float transform = 3.14 * radius_wheel / 180.0;
  auto angle = distance.getDistanceTotal(left_motor, right_motor);

  return static_cast<std::int32_t>(transform * angle);
}

std::int32_t Localization::arg(std::int32_t left_motor, std::int32_t right_motor)
{
  float radius_wheel = wheel_diameter / 2;
  float transform = radius_wheel / between_wheels;

  auto angle = distance.getAngleTotal(left_motor, right_motor);

  return static_cast<std::int32_t>(transform * angle);
}
