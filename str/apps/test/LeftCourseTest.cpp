/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LeftCourseTest.cpp ../src/LeftCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "LeftCourse.h"  // このヘッダファイルのcppファイルをテスト
#include "Controller.h"
#include <gtest/gtest.h>

class LeftCourseTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  Controller controller;
  LeftCourse lc{ controller };
};

TEST_F(LeftCourseTest, runTest)
{
  lc.run(30);
}