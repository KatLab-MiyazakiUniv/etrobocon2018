/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 RightCourseTest.cpp ../src/RightCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "RightCourse.h"  // このヘッダファイルのcppファイルをテスト
#include "Worker.h"
#include <gtest/gtest.h>

TEST(RightCourseTest, CreateTest)
{
  Worker worker;
  RightCourse rc{ worker };
}