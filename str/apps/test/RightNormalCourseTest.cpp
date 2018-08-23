/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 RightNormalCourseTest.cpp ../src/RightNormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "RightNormalCourse.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

TEST(RightNormalCourseTest, CreateTest)
{
  RightNormalCourse rnc;
}