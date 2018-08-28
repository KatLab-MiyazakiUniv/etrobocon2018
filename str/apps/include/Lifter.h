/**
 * @file Lifter.h
 * @brief 走行体のアームを操作するクラス。
 * @author Futa HIRAKOBA
 */

#ifndef __LIFTER__
#define __LIFTER__

#include "Controller.h"
#include <cstdint>

namespace etrobocon2018_test {
  class LifterTest;
}

/*! @class Lifter Lifter.h "Lifter.h"
 *  @brief 走行体のアームを操作するクラス。
 */
class Lifter {
  friend class etrobocon2018_test::LifterTest;

 public:
  /** コンストラクタ
   * @param controller_ ev3apiを持つControllerクラス。 */
  explicit Lifter(Controller& controller_) : controller(controller_) { reset(); }

  /** アームを上げる。
   * @param angle 変化する角度。
   * @param pwm アームを動かすPWM値 */
  void liftUp(std::uint8_t angle, std::int8_t pwm = 20);

  /** アームを下げる。
   * @param angle 変化する角度。
   * @param pwm アームを動かすPWM値 */
  void liftDown(std::uint8_t angle, std::int8_t pwm = 20);

  /** 現在の角度取得。
   * @return 現在の角度取得。 */
  std::int8_t getCurrentAngle();

  /** アームを初期位置にもどす。
   * @param pwm アームを動かすPWM値 */
  void defaultSet(std::int8_t pwm = 20);

 private:
  Controller controller;
  std::int32_t default_count = 0;
  std::int8_t limitPwm(std::int8_t pwm);
  void init();
  void terminate();
  void reset();
};

#endif