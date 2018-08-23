/**
 * @file Parking.h
 * @brief 縦列駐車クラス
 * @author Keisuke MORI
 */
#ifndef __PARKING__
#define __PARKING__

#include "BasicWalker.h"
#include "LineTracerWalker.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "SpeedControl.h"
#include "ev3api.h"

/*! @class Parking Parking.h "Parking.h"
 *  @brief 駐車クラス
 */
class Parking {
public:
    /**
     * コンストラクタ
     * カラーセンサを初期化する。
     */
    Parking();

    /**
     * 縦列駐車を実行する。
     * 実行開始時にBasicWalkerクラスのインスタンスを生成し、
     * goStraightメンバ関数とspinメンバ関数に依存する。
     */
    void runParpendicular(int16_t target_brightness,LineTracerWalker lineTracer);

    /**
     * 直角駐車を実行する。
     * 実行開始時にBasicWalkerクラスのインスタンスを生成し、
     * goStraightメンバ関数とspinメンバ関数に依存する。
     */
   void runParallelrun();

    /**
     * 3秒間待機する。
     * 駐車完了後に使う。
     * その際、1秒ごとに音を鳴らす。
     * EV3APIに依存する。
     */
    void waitThreeTimes();

private:
    ColorSensor colorSensor;
    Walker walker;
};


#endif
