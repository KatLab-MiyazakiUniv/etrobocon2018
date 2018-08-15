/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 RightCourseTest.cpp ../src/RightCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "RightCourse.h"  // このヘッダファイルのcppファイルをテスト
#include "Controller.h"
#include <gtest/gtest.h>

class RightCourseTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  Controller controller;
  RightCourse rc{ controller };
};

TEST_F(RightCourseTest, runTest)
{
  rc.run(30);
}