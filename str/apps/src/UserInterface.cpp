/**
 * @file UserInterface.cpp
 * @brief 走行体が走り出す前にユーザが入力するインターフェースを提供するクラス
 * @author Keisuke MORI
 */

#include "UserInterface.h"

void UserInterface::setBrightness(int8_t& brightness, const char* str)
{
  worker.tslpTsk(500);
  while(1) {
    // ENTERボタンが押されたらループを抜ける
    if(worker.buttonIsPressedEnter()) {
      worker.speakerPlayTone(1000, 100);
      break;
    }
    worker.printDisplay(7, "%s LightValue: %d", str, worker.colorSensor.getBrightness());
    worker.tslpTsk(4);
  }
  int16_t mean_brightness = 0;
  int8_t times = 10;
  for(int8_t i = 0; i < times; i++) {
    mean_brightness += worker.colorSensor.getBrightness();
    worker.tslpTsk(4);
  }
  worker.speakerPlayTone(2000, 100);
  brightness = mean_brightness / times;
}

void UserInterface::setBrightnessWithColor(int16_t& brightness, const char* str)
{
  worker.tslpTsk(500);

  while(1) {
    // ENTERボタンが押されたらループを抜ける
    if(worker.buttonIsPressedEnter()) {
      worker.speakerPlayTone(1000, 100);
      break;
    }
    int16_t luminance = worker.getBrightness();
    worker.printDisplay(7, "%s LightValue: %d", str, luminance);
    // sprintf(msg, "RGB R:%3d G:%3d B:%3d", rgb.r, rgb.g, rgb.b);
    // msg_f(msg, 8);
    worker.tslpTsk(4);
  }
  int16_t mean_brightness = 0;
  int8_t times = 10;
  for(int8_t i = 0; i < times; i++) {
    mean_brightness += worker.getBrightness();
    worker.tslpTsk(4);
  }
  worker.speakerPlayTone(2000, 100);
  brightness = mean_brightness / times;
}

void UserInterface::inputFirstCode()
{
  int digit = 0;
  bool isChangedFirstCode = false;

  // 初期位置コードを入力してください
  worker.printDisplay(4, "Please set first code");

  // 初期位置コードの初期値と操作している桁数の初期位置を表示する
  worker.printDisplay(5, "%05ld", firstCode.getFirstCode());

  digit = firstCode.getDigit();
  worker.printDisplay(6, getCurrentDigitText(digit));

  worker.speakerSetVolume(20);
  worker.speakerPlayTone(200, 500);

  // 初期位置コードを入力
  while(1) {
    // ENTERボタンが押されたらループを抜ける
    if(worker.buttonIsPressedEnter()) {
      isChangedFirstCode = true;
      break;
    }

    if(worker.buttonIsPressedUp()) {
      firstCode.upDigit(digit);
      isChangedFirstCode = true;
    }
    if(worker.buttonIsPressedDown()) {
      firstCode.downDigit(digit);
      isChangedFirstCode = true;
    }
    if(worker.buttonIsPressedRight()) {
      firstCode.changeRightDigit();
      isChangedFirstCode = true;
    }
    if(worker.buttonIsPressedLeft()) {
      firstCode.changeLeftDigit();
      isChangedFirstCode = true;
    }

    digit = firstCode.getDigit();

    // ボタンが押された時に限り画面表示を変更する
    if(isChangedFirstCode) {
      worker.speakerPlayTone(1000, 100);
      worker.printDisplay(5, "%05ld", firstCode.getFirstCode());
      worker.printDisplay(6, getCurrentDigitText(digit));
      worker.tslpTsk(500);
    }

    isChangedFirstCode = false;
    worker.tslpTsk(4);
  }

  // 終了
  worker.printDisplay(4, "Input first code for <%05ld>.", firstCode.getFirstCode());

  worker.speakerPlayTone(1500, 50);
  worker.tslpTsk(100);
  worker.speakerPlayTone(1500, 50);
}

int32_t UserInterface::getFirstCode()
{
  return firstCode.getFirstCode();
}

char* UserInterface::getCurrentDigitText(int8_t currentDigit)
{
  static char text[32];

  if(currentDigit == 1) {
    sprintf(text, "    -");
  } else if(currentDigit == 2) {
    sprintf(text, "   - ");
  } else if(currentDigit == 3) {
    sprintf(text, "  -  ");
  } else if(currentDigit == 4) {
    sprintf(text, " -   ");
  } else if(currentDigit == 5) {
    sprintf(text, "-    ");
  } else {
    // もし1桁から5桁以外を選択している場合
    sprintf(text, "-----");
  }

  return text;
}
