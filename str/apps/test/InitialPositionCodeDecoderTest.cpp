/**
 * InitialPositionCodeDecoderTest.cpp
 */

/* コンパイル(平木場)
$ g++-7 InitialPositionCodeDecoderTest.cpp ../src/InitialPositionCodeDecoder.cpp gtest_main.o gtest-all.o -I../include
-I../../googletest/googletest/include
*/

#include "InitialPositionCodeDecoder.h"
#include <random>
#include <gtest/gtest.h>

namespace etrobocon2018_test {

  // 初期値を返す
  TEST(InitialPositionCodeDecoderTest, getInitialPositionCodeListTest1)
  {
    InitialPositionCodeDecoder obj;
    std::vector<std::int8_t> expected = {0, 0, 0, 0};

    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected, actual);
  }

  // パワーブロックの初期値を返す
  TEST(InitialPositionCodeDecoderTest, getInitialPositionPowerBlockCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    int8_t expected = 0;

    auto actual = obj.getInitialPositionPowerBlockCode();

    ASSERT_EQ(expected, actual);
  }

  // 0未満の引数に対して初期値を返す
  TEST(InitialPositionCodeDecoderTest, returnInitialPositionCodeListByNegativeIntegerTest)
  {
    InitialPositionCodeDecoder obj;
    std::vector<std::int8_t> expected = {0, 0, 0, 0};

    obj.decode(-1);
    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected, actual);
  }

  // パワーブロックの初期位置コードをデコードする
  TEST(InitialPositionCodeDecoderTest, decodePowerBlockCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    std::int32_t codeList = 1;
    int8_t expected = 1;

    obj.decode(codeList);
    auto actual = obj.getInitialPositionPowerBlockCode();

    ASSERT_EQ(expected, actual);
  }

  // カラーブロックの初期位置コードの1番目をデコードする
  TEST(InitialPositionCodeDecoderTest, decodeFirstColorBlockOfCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    std::int32_t codeList = 65538;
    std::vector<std::int8_t> expected = {1, 0, 0, 0};

    obj.decode(codeList);
    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected.at(0), actual.at(0));
  }

  // カラーブロックの初期位置コードの2番目をデコードする
  TEST(InitialPositionCodeDecoderTest, decodeSecondColorBlockOfCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    std::int32_t codeList = 135171;
    std::vector<std::int8_t> expected = {2, 1, 0, 0};

    obj.decode(codeList);
    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected.at(1), actual.at(1));
  }

  // カラーブロックの初期位置コードの3番目をデコードする
  TEST(InitialPositionCodeDecoderTest, decodeThirdColorBlockOfCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    std::int32_t codeList = 205060;
    std::vector<std::int8_t> expected = {3, 2, 1, 0};

    obj.decode(codeList);
    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected.at(2), actual.at(2));
  }

  // カラーブロックの初期位置コードの4番目をデコードする
  TEST(InitialPositionCodeDecoderTest, decodeFourthColorBlockOfCodeTest1)
  {
    InitialPositionCodeDecoder obj;
    std::int32_t codeList = 274965;
    std::vector<std::int8_t> expected = {4, 3, 2, 1};

    obj.decode(codeList);
    auto actual = obj.getInitialPositionCodeList();

    ASSERT_EQ(expected.at(3), actual.at(3));
  }

  // ランダムの数値をデコードする
  TEST(InitialPositionCodeDecoderTest, decodeRandomCodeTest)
  {
    InitialPositionCodeDecoder obj;

    std::vector<std::int32_t> power16 = {1, 16, 16*16, 16*16*16, 16*16*16*16};
    // 乱数を生成する
    std::mt19937 mt{ std::random_device{}() };
    // カラーブロックの乱数範囲を定める
    std::uniform_int_distribution<std::int8_t> distC(1, 15);
    // パワーブロックの乱数範囲を定める
    std::uniform_int_distribution<std::int8_t> distP(1, 8);

    for(int i = 0; i < 100; i++) {
      std::vector<std::int8_t> expectedC = {distC(mt), distC(mt), distC(mt), distC(mt)};
      std::int8_t expectedP = distP(mt);
      std::int32_t expected =
          expectedC[0] * power16[4] +
          expectedC[1] * power16[3] +
          expectedC[2] * power16[2] +
          expectedC[3] * power16[1] +
          expectedP * power16[0];

      obj.decode(expected);
      auto actual = obj.getInitialPositionCode();
      auto actualC = obj.getInitialPositionCodeList();
      auto actualP = obj.getInitialPositionPowerBlockCode();

      EXPECT_EQ(expected, actual);
      EXPECT_EQ(expectedC, actualC);
      EXPECT_EQ(expectedP, actualP);
    }
  }

}  // namespace etrobocon2018_test
