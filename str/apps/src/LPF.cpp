#include "LPF.h"

/**
 *  [LPF::sensor]
 *  @brief  現在のセンサ値にフィルタ処理を実行する
 *  @param  current_sensor 現在のセンサ値
 *  @return               フィルタ処理を実行したセンサ値
 */
std::uint8_t LPF::sensor(std::uint8_t current_sensor)
{
  // pre_sensorの初期化
  if(pre_sensor == 0){
    pre_sensor = current_sensor;
    return current_sensor;
  }

  // RCフィルタ処理
  return RCFilter(current_sensor);
}

/**
 *  [LPF::RCFilter]
 *  @brief  RCフィルタ(ローパスフィルタ)処理
 *  @param  current_sensor 現在のセンサ値
 *  @return                フィルタ処理を実行したセンサ値
 */
std::uint8_t LPF::RCFilter(std::uint8_t current_sensor)
{
  // RCフィルタにおける係数(通常、0.8 or 0.9)
  constexpr double coefficient = 0.9;
  auto filtered = coefficient * pre_sensor + (1 - coefficient) * current_sensor;

  // センサ値の上書き
  pre_sensor = current_sensor;

  return static_cast<std::uint8_t>(filtered);
}
