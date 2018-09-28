#include "NormalCourse.h"

void NormalCourse::stop()
{
  lineTracerWalker.setForward(0);
}

void NormalCourse::runOrStop(Walker& walker)
{
  if(lineTracerWalker.getForward() < 0) {
    walker.run(0, 0);
  } else {
    walker.run(lineTracerWalker.getForward(), lineTracerWalker.getTurn());
  }
  
}