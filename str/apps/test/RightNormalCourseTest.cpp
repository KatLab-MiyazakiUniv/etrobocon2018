/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 RightNormalCourseTest.cpp ../src/RightNormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "RightNormalCourse.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  TEST(RightNormalCourseTest, CreateTest) { RightNormalCourse rnc; }

  TEST(RightNormalCourseTest, runTest)
  {
    RightNormalCourse rnc;
    for(int i = 0; i < 13000; i++) {
      rnc.statusCheck(i, i);
      rnc.runNormalCourse(30, 30, 30, 30);
    }
  }
}  // namespace etrobocon2018_test