#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "Distance.h"
#include "LineTracerWalker.h"
#include "Walker.h"

class NormalCourse {
 public:
  void stop();
  void runOrStop(Walker& walker);
  LineTracerWalker lineTracerWalker;

 protected:
  Distance distance;
  int8_t forward;
  int8_t turn;
  int32_t distanse_total;
};

#endif