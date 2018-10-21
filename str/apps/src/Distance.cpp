/**
 * @file Distance.cpp
 * @brief Distanceクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "Distance.h"

std::int32_t Distance::getDistanceTotal(std::int32_t countL, std::int32_t countR)
{
  leftMotorDegTotal = countL;
  rightMotorDegTotal = countR;
  return (leftMotorDegTotal + rightMotorDegTotal) / 2;
}

std::int32_t Distance::getDistanceCurrent(std::int32_t countL, std::int32_t countR)
{
  std::int32_t leftMotorDeg = countL - leftMotorDegOld;
  std::int32_t rightMotorDeg = countR - rightMotorDegOld;

  leftMotorDegOld = countL;
  rightMotorDegOld = countR;

  return (leftMotorDeg + rightMotorDeg) / 2;
}

std::int32_t Distance::getAngleCurrent(std::int32_t countL, std::int32_t countR)
{
  std::int32_t leftMotorDeg = countL - leftMotorDegOld;
  std::int32_t rightMotorDeg = countR - rightMotorDegOld;

  leftMotorDegOld = countL;
  rightMotorDegOld = countR;

  return (rightMotorDeg - leftMotorDeg);
}

void Distance::resetDistance(std::int32_t countL, std::int32_t countR)
{
  getDistanceTotal(countL, countR);
  leftMotorDegOld = leftMotorDegTotal;
  rightMotorDegOld = rightMotorDegTotal;
}
