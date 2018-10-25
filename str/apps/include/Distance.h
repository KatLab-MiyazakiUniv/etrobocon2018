/**
 * @file Distance.h
 * @brief タイヤの進んだ距離（回転角）に関するクラス
 * @author Futa HIRAKOBA
 */
#ifndef __DISTANCE__
#define __DISTANCE__

#include <cstdint>

/**
 * タイヤの進んだ距離（回転角）に関するクラス
 */
class Distance {
 public:
  Distance() : leftMotorDegTotal(0), rightMotorDegTotal(0), leftMotorDegOld(0), rightMotorDegOld(0)
  {
  }
  /** @return スタートしてからの回転角の合計 */
  std::int32_t getDistanceTotal(std::int32_t countL, std::int32_t countR);

  /** @return 左右モータの回転速度の差を返す */
  std::int32_t getAngleCurrent(std::int32_t countL, std::int32_t countR);

  /** @return 左右モータの回転速度の平均を返す */
  std::int32_t getDistanceCurrent(std::int32_t countL, std::int32_t countR);

  /** 相対的な回転角の現在地を0にする */
  void resetDistance(int32_t countL, int32_t countR);

 private:
  /** 絶対的な回転角（右タイヤ） */
  std::int32_t leftMotorDegTotal;
  /** 絶対的な回転角（左タイヤ） */
  std::int32_t rightMotorDegTotal;
  /** 相対的な回転角を計算するときに使う変数（右タイヤ） */
  std::int32_t leftMotorDegOld;
  /** 相対的な回転角を計算するときに使う変数（左タイヤ） */
  std::int32_t rightMotorDegOld;
};

#endif
