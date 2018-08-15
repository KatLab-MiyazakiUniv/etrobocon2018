/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LineTracerWalkerTest.cpp ../src/LineTracerWalker.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "LineTracerWalker.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

TEST(LineTracerWalkerTest, CreateTest)
{
  LineTracerWalker ltw;
}