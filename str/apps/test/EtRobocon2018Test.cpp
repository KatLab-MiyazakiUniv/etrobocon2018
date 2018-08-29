/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 EtRobocon2018Test.cpp ../src/EtRobocon2018.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "EtRobocon2018.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  TEST(EtRobocon2018Test, CreateTest)
  {
    EtRobocon2018 et;
    //  et.start(1);
  }
}  // namespace etrobocon2018_test