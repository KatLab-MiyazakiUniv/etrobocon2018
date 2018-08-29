/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 TurnControlTest.cpp ../src/TurnControl.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "TurnControl.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  TEST(TurnControlTest, CreateTest) { TurnControl tc; }
}  // namespace etrobocon2018_test