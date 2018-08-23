/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

Parking::Parking():
    colorSensor( PORT_3 ) {
}

void Parking::Parpendicular(int16_t target_brightness,LineTracerWalker lineTracer)   
{
    BasicWalker basicWalker;

	msg_f( "Do ParallelParking...", 0 );
    basicWalker.setPidWithoutTarget(17.0, 1.0, 0.1);
	basicWalker.goStraight( 30, 1000,target_brightness ,colorSensor);
	basicWalker.spin( basicWalker.SPIN_LEFT, 90 );
    //ライントレース開始
lineTracer.speedControl.setPid(17.0, 1.0, 0.1, 180.0);
lineTracer.turnControl.setPid(4.0, 1.0, 0.8, target_brightness);
lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
	//basicWalker.goStraight( 30, 600 );
	//basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );

    waitThreeTimes();
}

void Parking::runParallelrun()
{
    BasicWalker basicWalker;

	msg_f( "Do ParpendicularParking...", 0 );

    basicWalker.reset();
    basicWalker.setPidWithoutTarget( 4.0, 2.0, 0.02 );
  //  basicWalker.goStraight( 150, 450 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
//    basicWalker.goStraight( 50, 150 );
    basicWalker.reset();

    basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
    basicWalker.reset();
    tslp_tsk( 100 );

   // basicWalker.goStraight( 150, 550 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
  //  basicWalker.goStraight( 50, 250 );
    basicWalker.reset();

    waitThreeTimes();
}

void Parking::waitThreeTimes() {
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS5, 800 );
}
