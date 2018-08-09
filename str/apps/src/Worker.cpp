#include "Worker.h"

void Worker::speakerSetVolume(uint8_t volume)
{
  ev3_speaker_set_volume(volume);
}

void Worker::speakerPlayTone(uint16_t frequency, int32_t duration)
{
  ev3_speaker_play_tone(frequency, duration);
}

void Worker::ledSetColorOrange()
{
  ev3_led_set_color(LED_ORANGE);
}

void Worker::ledSetColorGreen()
{
  ev3_led_set_color(LED_GREEN);
}

bool Worker::buttonIsPressedBack()
{
  return ev3_button_is_pressed(BACK_BUTTON);
}

int16_t Worker::getBrightness()
{
  colorSensor.getRawColor(rgb);
  int16_t luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
  return luminance;
}

void Worker::tslpTsk(int8_t time)
{
  tslp_tsk(time);
}

void Worker::printDisplay(int8_t row, const char* format, ...)
{
  va_list arg;

  va_start(arg, format);
  vsprintf(msg, format, arg);
  va_end(arg);

  msg_f(msg, row);
}