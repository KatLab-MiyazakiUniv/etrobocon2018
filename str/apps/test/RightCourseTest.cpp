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
#include <vector>

namespace etrobocon2018_test {

  class RightCourseTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    Controller controller;
    std::vector<std::int8_t> ipcv;
    RightCourse rc{ controller, ipcv };
  };

  //TEST_F(RightCourseTest, runTest) { rc.run(30, 0, 100, 50); }
}  // namespace etrobocon2018_test
