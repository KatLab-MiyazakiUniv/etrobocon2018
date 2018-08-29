/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 WalkerTest.cpp ../src/Walker.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "Walker.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  TEST(WalkerTest, CreateTest) { Walker walker; }
}  // namespace etrobocon2018_test