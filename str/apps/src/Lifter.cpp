#include "Lifter.h"

void Lifter::terminate()
{
  //    msg_f("Stopped.", 1);
  controller.liftMotor.stop();
}

void Lifter::reset()
{
  controller.liftMotor.reset();
  controller.liftMotor.setBrake(true);
  controller.liftMotor.setBrake(false);
}

void Lifter::liftUp()
{
  controller.liftMotor.setPWM(20);
  controller.clock.sleep(1000);
  controller.liftMotor.setBrake(true);
}

void Lifter::liftDown()
{
  controller.liftMotor.setPWM(-20);
  controller.clock.sleep(1000);
  controller.liftMotor.setBrake(true);
}

void Lifter::changeDefault(int angle)
{
  Lifter::defaultSet(angle);
  Lifter::reset();
}

void Lifter::defaultSet(int angle)
{
  int i = 0;
  for(i = 0; i < 300; i++) {
    controller.liftMotor.setPWM(-((controller.liftMotor.getCount() - angle) % 360));
    controller.clock.sleep(1);
  }
  controller.liftMotor.setPWM(0);
  controller.liftMotor.setBrake(true);
}