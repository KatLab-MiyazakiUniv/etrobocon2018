/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LeftCourseTest.cpp ../src/LeftCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "LeftCourse.h"  // このヘッダファイルのcppファイルをテスト
#include "Worker.h"
#include <gtest/gtest.h>

class LeftCourseTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  Worker worker;
  LeftCourse lc{ worker };
};

TEST_F(LeftCourseTest, runTest)
{
  lc.run(30);
}