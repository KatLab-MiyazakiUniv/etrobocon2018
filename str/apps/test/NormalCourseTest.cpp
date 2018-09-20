/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 NormalCourseTest.cpp ../src/NormalCourse.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "NormalCourse.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  class NormalCourseTest : public ::testing::Test {
    friend class NormalCourse;

   protected:
    virtual void SetUp() {}
    NormalCourse nc;
  };

  TEST_F(NormalCourseTest, stopTest)
  {
    nc.stop();
    int forword = nc.lineTracerWalker.getForward();
    ASSERT_EQ(forword, 0);
  }
}  // namespace etrobocon2018_test