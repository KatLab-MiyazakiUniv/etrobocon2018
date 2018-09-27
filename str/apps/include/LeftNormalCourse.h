/**
 * @file LeftNormalCourse.h
 * @brief LコースのNormalCourseの処理を行うクラス
 * @author Futa HIRAKOBA
 */

#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"

/**
 * 走行場所の状態を保持する列挙型
 */
enum struct LeftStatus {
  STRAIGHT_THIRD,
  START,

  CURVE_INSIDE_LONG,
  CURVE_INSIDE_SHORT,
  CURVE_OUTSIDE,
  THIRD_CURVE,

  SECOND_CURVE,

  STRAIGHT,
  CURVE_RIGHT,
  CURVE_LEFT,
  CURVE_LEFT_SHORT,
  NEUTRAL,
  EDGE_CHANGE,
  EDGE_RESET,
  STOP
};

/**
 * LコースのNormalCourseの処理を行うクラス
 */
class LeftNormalCourse : public NormalCourse {
 public:
  /** コンストラクタ。 左エッジである設定をしている*/
  LeftNormalCourse();

  /**
   * 走行場所でのPID値を設定する
   * @return Goalしたかどうか
   */
  bool runNormalCourse(int32_t countL, int32_t countR, int16_t light_value,
                       int16_t target_brightness);

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
  LeftStatus status;
  LeftStatus old_status;
  bool isChangedEdge;
  int16_t time_count;
  
  #define CALIBRATE_DISTANCE_L 300  
  #define FIRST_STRAIGHT_DISTANCE_L 2850
  #define FIRST_CURVE_DISTANCE_L 4950
  #define SECOND_STRAIGHT_DISTANCE_L 6600
  #define SECOND_CURVE_DISTANCE_L 7500
  #define THIRD_STRAIGHT_DISTANCE_L 7900
  #define THIRD_CURVE_DISTANCE_L 9600
  #define FOURTH_STRAIGHT_DISTANCE_L 12000
};

#endif

