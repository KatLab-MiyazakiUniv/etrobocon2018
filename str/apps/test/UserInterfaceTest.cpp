/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ ./UserInterfaceTestLocalBuild.sh
{
    // IntelliSense を使用して利用可能な属性を学べます。
    // 既存の属性の説明をホバーして表示します。
    // 詳細情報は次を確認してください: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(lldb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/str/apps/test/a.out",
            "args": ["--gtest_break_on_failure"],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "lldb"
        }
    ]
}
*/

#include "UserInterface.h"  // このヘッダファイルのcppファイルをテスト
#include "Controller.h"
#include <cstdint>
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  class UserInterfaceTest : public ::testing::Test {
   protected:
    virtual void SetUp() { setControllerBrightness(brightness); }
    Controller controller;
    int brightness = 100;
    void setControllerBrightness(int brightness)
    {
      controller.brightness = brightness;
      controller.colorSensor.brightness = brightness;
    }
  };

  TEST_F(UserInterfaceTest, setBrightnessWithColorTest)
  {
    UserInterface ui{ controller };
    std::int16_t resultBrightness;
    ui.setBrightnessWithColor(resultBrightness, "test");
    ASSERT_EQ(resultBrightness, brightness);
  }

  TEST_F(UserInterfaceTest, setBrightnessTest)
  {
    UserInterface ui{ controller };
    std::int8_t resultBrightness;
    ui.setBrightness(resultBrightness, "test");
    ASSERT_EQ(resultBrightness, brightness);
  }
}  // namespace etrobocon2018_test