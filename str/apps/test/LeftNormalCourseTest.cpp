/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 LeftNormalCourseTest.cpp ../src/LeftNormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "LeftNormalCourse.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

TEST(LeftNormalCourseTest, CreateTest)
{
  LeftNormalCourse lnc;
}