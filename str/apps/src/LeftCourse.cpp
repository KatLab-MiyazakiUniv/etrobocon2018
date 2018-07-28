/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse():
#if IS_SHORT_CUT
    navi(walker.get_count_L(), walker.get_count_R()),
#endif
    colorSensor( PORT_3 ), 
    sl(walker.get_count_L(), walker.get_count_R(), true){
}

void LeftCourse::setFirstCode( int32_t code ) {
    firstCode = code;
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(int8_t brightness){
	runNormalCourse(brightness);
  
    msg_f("Finished NormalArea", 3);
  
	// Puzzle
    runBlockRange();
    msg_f("Finished BlockRange", 3);
  
	// Park
    runParallelParking();
    msg_f("Finished ParallelParking", 3);
    
}

void LeftCourse::runNormalCourse(int8_t brightness){
    char msg[32];

    LeftNormalCourse normalCourse;
    bool isNormalCourse;
    // NormalCourseを抜けるまでループする
    while ( 1 ) {
        sprintf ( msg, "LightValue: %d, Target: %d", colorSensor.getBrightness(), brightness);
        msg_f ( msg, 4 ) ;
        sl.update(walker.get_count_L(), walker.get_count_R());
        if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R())) ev3_speaker_play_tone (NOTE_FS6, 100);
        isNormalCourse = normalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness(), brightness);

        if(normalCourse.lineTracerWalker.getForward() < 0){
            walker.run(0, 0);
        }else{
            walker.run( normalCourse.lineTracerWalker.getForward(), normalCourse.lineTracerWalker.getTurn());
        }
        if(! isNormalCourse){
            walker.run(0, 0);
            break;
        }
        if(ev3_button_is_pressed(BACK_BUTTON)){
            walker.run(0, 0);
            break;
        }

        tslp_tsk(4); // 4msec周期起動
    }
}

void LeftCourse::runBlockRange(){
}

void LeftCourse::runParallelParking(){
}
