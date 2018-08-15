/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 UserInterfaceTest.cpp ../src/UserInterface.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "UserInterface.h"  // このヘッダファイルのcppファイルをテスト
#include "Worker.h"
#include <gtest/gtest.h>

TEST(UserInterfaceTest, CreateTest)
{
  Worker worker;
  UserInterface ui{ worker };
}