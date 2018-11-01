/**
 * DistinguisherTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 DistinguisherTest.cpp ../src/Distinguisher.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "Distinguisher.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  class DistinguisherTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
    Controller controller;
    Distinguisher d{ controller };
    void setMockRgb(std::uint16_t r, std::uint16_t g, std::uint16_t b)
    {
      d.controller.setMockRgb(r, g, b);
    }
    Hsv getRed() { return d.RED; }
  };

  TEST_F(DistinguisherTest, getColorWhiteTest2)
  {
    setMockRgb(128, 158, 93);
    Color result = d.getColor();
    ASSERT_EQ(result, Color::WHITE);
  }

  TEST_F(DistinguisherTest, getColorBlackTest1)
  {
    setMockRgb(0, 0, 0);
    Color result = d.getColor();
    ASSERT_EQ(result, Color::BLACK);
  }

  TEST_F(DistinguisherTest, getColorBlackTest2)
  {
    setMockRgb(14, 19, 5);
    Color result = d.getColor();
    ASSERT_EQ(result, Color::BLACK);
  }

}  // namespace etrobocon2018_test
