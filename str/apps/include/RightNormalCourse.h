/**
 * @file RightNormalCourse.h
 * @brief RコースのNormalCourseの処理を行うクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHTNORMALCOURSE__
#define __RIGHTNORMALCOURSE__

#include "NormalCourse.h"

/**
 * 走行場所の状態を保持する列挙型
 */
enum struct RightStatus {
  STRAIGHT_LONG,
  STRAIGHT_SHORT,
  SLOW,
  START,

  CURVE_INSIDE_LONG,
  CURVE_INSIDE_SHORT,
  CURVE_OUTSIDE,

  TRANSFER_ZONE,
  STOP,
};

/**
 * RコースのNormalCourseの処理を行うクラス
 */
class RightNormalCourse : public NormalCourse {
 public:
  /** コンストラクタ。 右エッジである設定をしている*/
  RightNormalCourse();

  /**
   * 走行場所でのPID値を設定する
   * @return Goalしたかどうか
   */
  bool runNormalCourse(int16_t target_brightness, int16_t black, int16_t white, int16_t gray);

  /**
   * 現在の走行場所の状態を設定する
   * @param[in] countL 左タイヤの回転角
   * @param[in] countR 右タイヤの回転角
   * @return 走行場所の状態が変わったかどうか
   */
  bool statusCheck(int32_t countL, int32_t countR);

  /**
   * 現在の走行場所の状態を取得する
   * @return 現在の走行場所の状態(int型)
   */
  int getStatus();

 private:
  RightStatus status;
  RightStatus old_status;

  #define CALIBRATE_DISTANCE_R 300
  #define FIRST_STRAIGHT_DISTANCE_R 2500
  #define FIRST_CURVE_DISTANCE_R 4495
  #define SECOND_STRAIGHT_DISTANCE_R 5056
  #define SECOND_CURVE_DISTANCE_IN_R 5640
  #define SECOND_CURVE_DISTANCE_OUT_R 6542
  #define THIRD_STRAIGHT_DISTANCE_R 7100
  #define THIRD_CURVE_DISTANCE_R 8680
  #define FOURTH_STRAIGHT_DISTANCE_R 11657

  #define AFTER_GOAL_CURVE_R 12000
  #define GRAY_FIND_AREA_R 12450
};

#endif