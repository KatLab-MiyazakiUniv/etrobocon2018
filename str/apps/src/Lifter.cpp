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
  default_count = controller.liftMotor.getCount();
}

std::int8_t Lifter::getCurrentAngle()
{
  std::int32_t current_angle = controller.liftMotor.getCount();
  return current_angle - default_count;
}

std::int8_t Lifter::limitPwm(std::int8_t pwm)
{
  if(pwm > 100) {
    return 100;
  } else if(pwm < 1) {
    return pwm = 1;
  } else {
    return pwm;
  }
}

void Lifter::liftUp(std::uint8_t angle, std::int8_t pwm)
{
  while(1) {
    if(getCurrentAngle() > angle) {
      break;
    }
    controller.liftMotor.setPWM(limitPwm(pwm));
    controller.tslpTsk(4);
  }
  controller.liftMotor.setPWM(0);
}

void Lifter::liftDown(std::uint8_t angle, std::int8_t pwm)
{
  while(1) {
    if(getCurrentAngle() < -angle) {
      break;
    }
    controller.liftMotor.setPWM(-limitPwm(pwm));
    controller.tslpTsk(4);
  }
  controller.liftMotor.setPWM(0);
}

void Lifter::defaultSet(std::int8_t pwm)
{
  std::int8_t sign;
  if(getCurrentAngle() < 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  while(1) {
    if((sign == 1 && getCurrentAngle() >= 0) || (sign == -1 && getCurrentAngle() <= 0)) {
      break;
    }
    controller.liftMotor.setPWM(sign * limitPwm(pwm));
    controller.tslpTsk(4);
  }
  controller.liftMotor.setPWM(0);
}