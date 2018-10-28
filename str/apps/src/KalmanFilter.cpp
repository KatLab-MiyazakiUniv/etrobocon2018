#include "KalmanFilter.h"

float KalmanFilter::getAngle(std::int32_t u, std::int32_t y, float system_noise,
                             float measurement_noise)
{
  predict(u, system_noise);
  update(y, measurement_noise);

  return x[0];
}

void KalmanFilter::predict(std::int32_t u, float system_noise)
{
  // xの予測
  x_est[0] = x[0];
  x_est[1] = 0.06 * u - x[1];

  // Pの予測
  P_est[0][0] = P[1][1] + system_noise;
  P_est[0][1] = -P[1][1];
  P_est[1][0] = -P[1][1];
  P_est[1][1] = P[1][1] + system_noise;
}

void KalmanFilter::update(std::int32_t y, float measurement_noise)
{
  float s = P_est[0][0] + measurement_noise;
  // カルマンゲインの更新
  float K[2] = { P_est[0][0] / s, P_est[1][0] / s };

  // xの更新
  x[0] += x_est[0] + K[0] * (y - x_est[0]);
  x[1] += x_est[1] + K[1] * (y - x_est[0]);

  // Pの更新
  P[0][0] += P_est[0][0] - (P_est[0][0] * P_est[0][0]) / s;
  P[0][1] += P_est[0][1] - (P_est[0][0] * P_est[0][1]) / s;
  P[1][0] += -(P_est[1][0] * P_est[0][0]) / s + P_est[1][0];
  P[1][1] += -(P_est[1][0] * P_est[0][1]) / s + P_est[1][1];
}
