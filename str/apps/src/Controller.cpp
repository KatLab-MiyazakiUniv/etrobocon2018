#include "Controller.h"

void Controller::speakerSetVolume(uint8_t volume)
{
  ev3_speaker_set_volume(volume);
}

void Controller::speakerPlayTone(uint16_t frequency, int32_t duration)
{
  ev3_speaker_play_tone(frequency, duration);
}

void Controller::ledSetColorOrange()
{
  ev3_led_set_color(LED_ORANGE);
}

void Controller::ledSetColorGreen()
{
  ev3_led_set_color(LED_GREEN);
}

bool Controller::buttonIsPressedBack()
{
  return ev3_button_is_pressed(BACK_BUTTON);
}

bool Controller::buttonIsPressedEnter()
{
  return ev3_button_is_pressed(ENTER_BUTTON);
}

bool Controller::buttonIsPressedUp()
{
  return ev3_button_is_pressed(UP_BUTTON);
}

bool Controller::buttonIsPressedDown()
{
  return ev3_button_is_pressed(DOWN_BUTTON);
}

bool Controller::buttonIsPressedRight()
{
  return ev3_button_is_pressed(RIGHT_BUTTON);
}

bool Controller::buttonIsPressedLeft()
{
  return ev3_button_is_pressed(LEFT_BUTTON);
}

int16_t Controller::getBrightness()
{
  colorSensor.getRawColor(rgb);
  int16_t luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
  return luminance;
}

void Controller::getRawColor(uint16_t& r, uint16_t& g, uint16_t& b)
{
  colorSensor.getRawColor(rgb);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
}

void Controller::tslpTsk(int16_t time)
{
  tslp_tsk(time);
}

void Controller::printDisplay(int8_t row, const char* format, ...)
{
  va_list arg;

  va_start(arg, format);
  vsprintf(msg, format, arg);
  va_end(arg);

  msg_f(msg, row);
}
