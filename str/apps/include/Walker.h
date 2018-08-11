#ifndef __WALKER__
#define __WALKER__

#include "Worker.h"
#include <cstdint>

class Walker {
 public:
  Walker() = default;
  explicit Walker(Worker& worker_) : worker(worker_) { reset(); }
  void stop();
  void run(std::int8_t pwm, std::int8_t turn);
  int edgeChange();
  void moveAngle(std::int8_t pwm, int angle);
  void angleChange(int angle, int rotation);
  std::int32_t get_count_L();
  std::int32_t get_count_R();
  void init();
  void terminate();
  void reset();
  void setBrakeMotor(bool brake);

 private:
  Worker worker;
  std::int8_t leftRight = 1;  // 1 -> 右, -1 -> 左
};

#endif
