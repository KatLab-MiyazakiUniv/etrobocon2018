/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "ev3api.h"
#include "util.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "RightNormalCourse.h"
#include "Distance.h"
#include "SelfLocalization.h"

using namespace ev3api;

/**
* 走行場所の状態を保持する列挙型
*/
enum struct ShinkansenStatus {
    BEFORE_FIRST_SHINKANSEN,
    FIRST_RAIL,
	FIRST_LINE,
	SECOND_LINE,
	BEFORE_SECOND_SHINKANSEN,
	SECOND_RAIL,
	THIRD_LINE,
	FOURTH_LINE,
	BEFORE_THIRD_SHINKANSEN,
	PRIZE,
    STOP
};

/**
* Rコースを走らせるときに呼び出されるクラス
*/
class RightCourse {
public:
	/** コンストラクタ。センサ類の初期化を行う **/
	RightCourse();
	/** 各エリアの処理を呼び出す **/
	void run(int8_t brightness);
	/** NormalCourseエリアの処理 **/
    void runNormalCourse(int8_t brightness);
	/** Shinkansenエリアの処理 */
	void runShinkansen();
private:
	LineTracerWalker lineTracer;
	Walker walker;
	ColorSensor colorSensor;
	SonarSensor sonarSensor;
	SelfLocalization sl;	
};

#endif