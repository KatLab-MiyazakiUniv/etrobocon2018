/**
 * @file Pid.h
 * @brief PID制御の計算を行うクラス
 * @author Futa HIRAKOBA, T.Miyaji
 */
#ifndef PID_H
#define PID_H

/*!
 *  @class PidParameter
 *  @brief  PID制御で用いるパラメータをまとめたリテラルクラス
 *  @param  p_gain_ Kp
 *  @param  i_gain_ Ki
 *  @param  d_gain_ Kd
 *  @param  del_    1周期
 */
struct PidParameter {
  double p_gain;
  double i_gain;
  double d_gain;
  double del;
  constexpr PidParameter(double p_gain_ = 0.0, double i_gain_ = 0.0, double d_gain_ = 0.0,
                         double del_ = 0.004)
    : p_gain(p_gain_), i_gain(i_gain_), d_gain(d_gain_), del(del_)
  {
  }
  void set(double p_gain_, double i_gain_, double d_gain_)
  {
    p_gain = p_gain_;
    i_gain = i_gain_;
    d_gain = d_gain_;
  }
};

/*! @class Pid Pid.h "Pid.h"
 *  @brief PID制御の計算を行うクラス
 */
class Pid {
 public:
  /** コンストラクタ */
  Pid(double p_gain_, double i_gain_, double d_gain_, double target_);
  Pid(double p_gain_, double i_gain_, double d_gain_, double diff_, double integral_,
      double target_, double output_);

  /** Kp, Ki, Kd, 目標値を設定する
   * @param _p_gain Kp
   * @param _i_gain Ki
   * @param _d_gain Kd
   * @param _target 目標値 */
  void setPid(double p_gain_, double i_gain_, double d_gain_, double target_);

 protected:
  /** PID制御の計算をする
   * @param light_value 現在の値 */
  void calculate(double light_value);

  /** PID計算値を取得する
   * @return 計算値 */
  double get_output();

  /** PID計算値を制限する
   * @param PID計算値
   * @return PID計算値 */
  double limitOutput(double pid_value);

 private:
  PidParameter param;
  double old_diff;
  double integral;
  double target;
  double output;
};

#endif
