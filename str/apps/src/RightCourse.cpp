/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

RightCourse::RightCourse() : colorSensor(PORT_3),
                             sonarSensor(PORT_2),
                             sl(walker.get_count_L(), walker.get_count_R())
{
}

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::run(int16_t brightness)
{
    runNormalCourse(brightness);
    runShinkansen();
    //Park
}

void RightCourse::runShinkansen()
{
}

void RightCourse::runNormalCourse(int16_t brightness)
{
    RightNormalCourse normalCourse;
    bool isNormalCourse;
    // NormalCourseを抜けるまでループする
    while (1)
    {
        sl.update(walker.get_count_L(), walker.get_count_R());
        rgb_raw_t rgb;
        colorSensor.getRawColor(rgb);
        int16_t luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
        char msg[32];
        sprintf(msg, "LightValue: %d, Target: %d", luminance, brightness);
        msg_f(msg, 4);
        if (normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R()))
            ev3_speaker_play_tone(NOTE_FS6, 100);
        isNormalCourse = normalCourse.runNormalCourse(brightness);
        normalCourse.lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);

        if (normalCourse.lineTracerWalker.getForward() < 0)
        {
            walker.run(0, 0);
        }
        else
        {
            walker.run(normalCourse.lineTracerWalker.getForward(), normalCourse.lineTracerWalker.getTurn());
        }
        if (!isNormalCourse)
        {
            walker.run(0, 0);
            break;
        }
        if (ev3_button_is_pressed(BACK_BUTTON))
        {
            walker.run(0, 0);
            break;
        }

        tslp_tsk(4); // 4msec周期起動
    }
}