/**
 *  @file LPF.h
 *  @brief LPF(Low-Pass Filter)をまとめたクラス
 *  @author T.Miyaji
 */
#ifndef LPF_H
#define LPF_H
#include <cstdint>

/*!
 *  @class LPF
 *  @brief LPF(Low-Pass Filter)をまとめたクラス
 */
struct LPF {
  // 前回のセンサ値
  std::uint8_t pre_sensor;
  // コンストラクタ
  LPF() : pre_sensor(0) { }
  // 現在のセンサ値にフィルタ処理を実行する
  std::uint8_t sensor(std::uint8_t current_sensor);
  // RCフィルタ
  std::uint8_t RCFilter(std::uint8_t current_sensor);
};

#endif
