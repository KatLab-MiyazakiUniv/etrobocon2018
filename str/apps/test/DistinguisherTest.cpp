/**
 * DistinguisherTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 DistinguisherTest.cpp ../src/Distinguisher.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "Distinguisher.h"  // このヘッダファイルのcppファイルをテスト
#include <gtest/gtest.h>

class DistinguisherTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  Controller controller;
  Distinguisher d{ controller };
  void setMockRgb(std::uint16_t r, std::uint16_t g, std::uint16_t b)
  {
    d.controller.setMockRgb(r, g, b);
  }
  Rgb getRed() { return d.RED; }
};

TEST_F(DistinguisherTest, getColorRedTest1)
{
  setMockRgb(255, 0, 0);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::RED);
}

/*
TEST_F(DistinguisherTest, getColorRedTest2)
{
  setMockRgb(220, 62, 56);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::RED);
}
*/

TEST_F(DistinguisherTest, getColorRedTest3)
{
  setMockRgb(112, 13, 9);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::RED);
}

TEST_F(DistinguisherTest, getColorBlueTest1)
{
  setMockRgb(0, 0, 255);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::BLUE);
}

/*
TEST_F(DistinguisherTest, getColorBlueTest2)
{
  setMockRgb(40, 106, 165);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::BLUE);
}
*/

TEST_F(DistinguisherTest, getColorBlueTest3)
{
  setMockRgb(18, 47, 50);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::BLUE);
}

/*
TEST_F(DistinguisherTest, getColorYellowTest1)
{
  setMockRgb(255, 255, 0);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::YELLOW);
}

TEST_F(DistinguisherTest, getColorYellowTest2)
{
  setMockRgb(255, 229, 18);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::YELLOW);
}
*/

TEST_F(DistinguisherTest, getColorYellowTest3)
{
  setMockRgb(116, 120, 15);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::YELLOW);
}

/*
TEST_F(DistinguisherTest, getColorGreenTest1)
{
  setMockRgb(0, 255, 0);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::GREEN);
}
*/

TEST_F(DistinguisherTest, getColorGreenTest2)
{
  setMockRgb(22, 167, 72);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::GREEN);
}

TEST_F(DistinguisherTest, getColorGreenTest3)
{
  setMockRgb(24, 77, 13);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::GREEN);
}

TEST_F(DistinguisherTest, getColorWhiteTest1)
{
  setMockRgb(255, 255, 255);
  Color result = d.getColor();
  ASSERT_EQ(result, Color::WHITE);
}

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

TEST_F(DistinguisherTest, distanceColorRedTest1)
{
  setMockRgb(255, 0, 0);
  d.setRawColor2Rgb();
  d.distanceColor(getRed());
}
