#ifndef __LINETRACERWALKER__
#define __LINETRACERWALKER__

#include "SpeedControl.h"
#include "TurnControl.h"

/**
 int main(){
    lineTracerWalker.speedControl.setPid(6.0, 1.0, 0.5, 110.0);
    lineTracerWalker.turnControl.setPid(3.0, 1.0, 1.5, target_brightness);
    while(1){
        auto luminance = controller.getBrightness();
        lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), luminance);
        walker.run(lineTracerWalker.getForward(), lineTracerWalker.getTurn());

        controller.tlspTsk(4);
    }
}
*/

class LineTracerWalker {
 public:
  LineTracerWalker();
  void runLine(int32_t countL, int32_t countR, int8_t light_value);
  void setForward(int8_t setValue);
  void setTurn(int8_t setValue);
  int8_t getForward();
  int8_t getTurn();
  void isLeftsideLine(bool b);
  TurnControl turnControl;
  SpeedControl speedControl;
  int8_t minus;

 protected:
  int8_t forward;
  int8_t turn;
};

#endif
