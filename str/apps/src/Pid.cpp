#include "Pid.h"

// Constructor
Pid::Pid(double p_gain_, double i_gain_, double d_gain_, double target_)
  : Pid(p_gain_, i_gain_, d_gain_, 0.0, 0.0, target_, 0.0)
{
}

Pid::Pid(double p_gain_, double i_gain_, double d_gain_, double diff_, double integral_,
         double target_, double output_)
  : param(p_gain_, i_gain_, d_gain_, 0.004),
    old_diff(diff_),
    integral(integral_),
    target(target_),
    output(output_)
{
}

void Pid::calculate(double current_value)
{
  double p, i, d;
  double diff = current_value - target;

  integral += (old_diff + diff) / 2 * param.del;
  p = param.p_gain * diff;
  i = param.i_gain * integral;
  d = param.d_gain * (diff - old_diff) / param.del;
  old_diff = diff;
  output = p + i + d;
}

double Pid::get_output()
{
  return output;
}

/*
 * PID値を入力する
 */
void Pid::setPid(double p_gain_, double i_gain_, double d_gain_, double target_)
{
  param.set(p_gain_, i_gain_, d_gain_);
  target = target_;
}

double Pid::limitOutput(double pid_value)
{
  if(pid_value > 100.0) return 100.0;
  if(pid_value < -100.0) return -100.0;
  return pid_value;
}
