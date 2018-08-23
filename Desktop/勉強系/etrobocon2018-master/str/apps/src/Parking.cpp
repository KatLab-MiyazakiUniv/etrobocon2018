/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

Parking::Parking():
    colorSensor( PORT_3 ) {
}

void Parking::runParallel(int16_t brightness, int16_t black, int16_t white, int16_t gray)
{
    rgb_raw_t rgb;
    int count = 0;
    int16_t  grayBrightness = (gray + white) / 2;

    msg_f( ">>>>> Do ParallelParking... <<<<<", 6 );
    while(1){
        colorSensor.getRawColor(rgb);
        int16_t luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;

        lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), luminance);

        if(lineTracer.getForward() < 0) {
            walker.run(0, 0);
        } else {
            walker.run(lineTracer.getForward(),
                lineTracer.getTurn());
        }
        if(ev3_button_is_pressed(BACK_BUTTON)) {
            walker.run(0, 0);
            break;
        }

        
        /*if(gray + 2 >= luminance && gray - 2 <= luminance){  //グレーを読み込んだら
            count++;
            ev3_speaker_play_tone( NOTE_FS4, 100 );
        }else{
            count = 0;
        }*/

        if(black + 35 >= luminance){  //ブラックを読み込んだら
            count = 0;
            ev3_speaker_play_tone( NOTE_CS4, 100 );
        }else if(white + 30>= luminance && white - 70<= luminance){
            count++;
           
        }

        if(count > 250){
             waitThreeTimes();
            break;
        }

        lineTracer.speedControl.setPid(17.0, 1.0, 0.1, 30.0);
        
        if(grayBrightness + 3 >= luminance && grayBrightness - 1 <= luminance){
            lineTracer.turnControl.setPid(4.0, 1.0, 0.8, grayBrightness);
        }else{
            lineTracer.turnControl.setPid(4.0, 1.0, 0.8, brightness);
        }
        tslp_tsk(4);

    }
    basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
	basicWalker.goStraight( 60, 600 );
    basicWalker.spin( basicWalker.SPIN_LEFT, 40 );
    //basicWalker.setPidWithoutTarget(14.0, 1.0, 0.1);
	basicWalker.goStraight( 60, 580 );
	basicWalker.spin( basicWalker.SPIN_LEFT, 90 );
	basicWalker.goStraight( 30, 10 );
	//basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );

}

void Parking::runParpendicular()
{

	msg_f( "Do ParpendicularParking...", 0 );

    basicWalker.reset();
    basicWalker.setPidWithoutTarget( 4.0, 2.0, 0.02 );
    basicWalker.goStraight( 150, 450 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
    basicWalker.goStraight( 50, 150 );
    basicWalker.reset();

    basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
    basicWalker.reset();
    tslp_tsk( 100 );

    basicWalker.goStraight( 150, 550 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
    basicWalker.goStraight( 50, 250 );
    basicWalker.reset();

    waitThreeTimes();
}

void Parking::waitThreeTimes() {
    walker.run(0,0);
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS5, 800 );
}
