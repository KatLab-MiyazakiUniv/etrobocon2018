/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LineTracerWalkerTest.cpp ../src/LineTracerWalker.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "LineTracerWalker.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

class LineTracerWalkerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  LineTracerWalker ltw;
};

TEST_F(LineTracerWalkerTest, runLineTest)
{
  ltw.runLine(0, 0, 0);
}

TEST_F(LineTracerWalkerTest, setForwardTest)
{
  auto forword = 80;
  auto turn = 30;
  ltw.setForward(forword);
  ltw.setTurn(turn);
  auto resultForword = ltw.getForward();
  ASSERT_EQ(forword, resultForword);
  auto resultTurn = ltw.getTurn();
  ASSERT_EQ(turn, resultTurn);
}