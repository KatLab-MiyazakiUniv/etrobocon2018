/**
 *  @file   KalmanFilter.h
 *  @brief  線形カルマンフィルタを用いた状態推定器に関するクラス
 *  @note   観測する線形システムに関するパラメータは、LinearSystemクラスにまとめている
 *  @author T.Miyaji
 */
#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H
#include <array>
#include <cstdint>

class KalmanFilter {
 private:
  float x[2];
  float x_est[2];
  float P[2][2];
  float P_est[2][2];

 public:
  KalmanFilter() : x{}, x_est{}, P{ {} }, P_est{ {} } {};
  float getAngle(std::int32_t u, std::int32_t y, float system_noise = 0.0f,
                 float measurement_noise = 0.0f);
  void predict(std::int32_t u, float system_noise);
  void update(std::int32_t y, float measurement_noise);
};

#endif
