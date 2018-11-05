/**
 *  @file   AIAnswer.cpp
 *  @brief  AIアンサー
 *  @author T.Miyaji
 */
#include "AIAnswer.h"

void AIAnswer::run()
{
  navigator.move(690.0);

  navigator.spin(90);

  navigator.moveWhileDetecting(360.0);

  navigator.spin(135, true);

  navigator.move(150.0);
}
