/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 NormalCourseTest.cpp ../src/NormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "NormalCourse.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

TEST(NormalCourseTest, CreateTest)
{
  NormalCourse nc;
}