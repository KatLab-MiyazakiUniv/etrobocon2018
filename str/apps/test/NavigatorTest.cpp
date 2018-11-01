/**
 *  @file NavigatorTest.cpp
 *  @author T.Miyaji
 */
#include "Navigator.h"
#include <gtest/gtest.h>

namespace etrobocon2018_test {
  TEST(NavigatorTest, resetTest)
  {
    Navigator navigator;
    navigator.move(10);
  }
}
