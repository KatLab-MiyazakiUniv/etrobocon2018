/**
 *  @file AIAnswerArrayTest.cpp
 *  @author T.Miyaji
 */

#include "AIAnswerArray.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(AIAnswerArrayTest, construct)
  {
    AIAnswer::array<int> array;
  }

  TEST(AIAnswerArrayTest, constructSpecifiedSize)
  {
    AIAnswer::array<int, 2> array;
  }

  TEST(AIAnswerArrayTest, constructSpecifiedType)
  {
    AIAnswer::array<double, 2> array;
    AIAnswer::array<AIAnswer::array<int, 2>> arrayarray;
  }

  TEST(AIAnswerArrayTest, sizeTest)
  {
    AIAnswer::array<int> array;
    ASSERT_EQ(6, array.size());

    AIAnswer::array<int, 1> list;
    ASSERT_EQ(1, list.size());
  }

  TEST(AIAnswerArrayTest, positionTest)
  {
    AIAnswer::array<int> array;
    ASSERT_EQ(0, array.position());

    array.push_back(1);
    ASSERT_EQ(1, array.position());

    array.push_back(20);
    ASSERT_EQ(2, array.position());
  }

  TEST(AIAnswerArrayTest, atTest)
  {
    AIAnswer::array<int> array;
    ASSERT_EQ(0, array.at(0));

    array.push_back(100);
    ASSERT_EQ(100, array.at(0));

    array.push_back(200);
    ASSERT_EQ(200, array.at(1));
  }

  TEST(AIAnswerArrayTest, atTestDouble)
  {
    AIAnswer::array<double> array;
    ASSERT_DOUBLE_EQ(0.0, array.at(0));

    array.push_back(1.2);
    ASSERT_DOUBLE_EQ(1.2, array.at(0));
  }

  TEST(AIAnswerArrayTest, operatorTest)
  {
    AIAnswer::array<int> array;
    ASSERT_EQ(0, array[0]);

    array.push_back(100);
    ASSERT_EQ(100, array[0]);

    array.push_back(200);
    ASSERT_EQ(200, array[1]);
  }

  TEST(AIAnswerArrayTest, castTest)
  {
    AIAnswer::array<int> array;
    ASSERT_EQ(0, array.cast(0));
  }

  TEST(AIAnswerArrayTest, probsTest)
  {
    AIAnswer::array<int> array;
    array.push_back({1, 0, 1, 1, 0, 1});
    array.handwriting();

    ASSERT_EQ(1.0, array.probs[2]);
  }


  TEST(AIAnswerArrayTest, handwritingTest)
  {
    AIAnswer::array<int> array;
    array.push_back({0, 0, 1, 1, 1, 1});

    ASSERT_EQ(0, array.handwriting());

    AIAnswer::array<int> array1;
    array1.push_back({0, 0, 0, 1, 0, 1});
    ASSERT_EQ(1, array1.handwriting());

    AIAnswer::array<int> array2;
    array2.push_back({1, 0, 1, 1, 0, 1});
    ASSERT_EQ(2, array2.handwriting());

    AIAnswer::array<int> array3;
    array3.push_back({1, 0, 0, 1, 1, 1});
    ASSERT_EQ(3, array3.handwriting());

    AIAnswer::array<int> array4;
    array4.push_back({1, 1, 1, 0, 1, 1});
    ASSERT_EQ(4, array4.handwriting());

    AIAnswer::array<int> array5;
    array5.push_back({1, 1, 0, 1, 1, 1});
    ASSERT_EQ(5, array5.handwriting());

    AIAnswer::array<int> array6;
    array6.push_back({1, 1, 1, 1, 1, 1});
    ASSERT_EQ(6, array6.handwriting());

    AIAnswer::array<int> array7;
    array7.push_back({1, 0, 0, 1, 0, 1});
    ASSERT_EQ(7, array7.handwriting());
  }


}
