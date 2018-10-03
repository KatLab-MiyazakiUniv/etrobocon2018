/**
 *  @file LightFilter.h
 *  @brief 光センサ値に用いるフィルタ処理をまとめたクラス
 *  @author T.Miyaji
 */
#ifndef LIGHT_FILTER_H
#define LIGHT_FILTER_H
#include <cstdint>

/*!
 *  @class LightFilter
 *  @brief 光センサ値に用いるフィルタ処理をまとめたクラス
 */
struct LightFilter {
  // 前回のセンサ値
  std::uint8_t pre_sensor;
  // コンストラクタ
  LightFilter() : pre_sensor(0) { }
  // 現在のセンサ値にフィルタ処理を実行する
  std::uint8_t sensor(std::uint8_t current_sensor);
  // RCフィルタ
  std::uint8_t RCFilter(std::uint8_t current_sensor);
};

#endif
