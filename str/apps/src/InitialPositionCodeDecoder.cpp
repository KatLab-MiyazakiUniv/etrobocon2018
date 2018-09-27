/**
 * @file InitialPositionCodeDecoder.cpp
 * @brief InitialPositionCodeDecoderクラスの関数を定義
 * @author Keisuke MORI
 */

#include "InitialPositionCodeDecoder.h"

void InitialPositionCodeDecoder::decode(std::int32_t code) {
  if (code < 0) return;

  std::int8_t remainder = 0;
  initialPositionCode = code;
  std::int32_t sumCurrentCode = 0;
  std::int32_t codeBeforeDecoded = 0;

  std::vector<std::int32_t> power16 = {1, 16, 16*16, 16*16*16, 16*16*16*16};

  remainder = code % power16[4] % power16[3] % power16[2] % power16[1];
  initialPositionPowerBlockCode = remainder;
  sumCurrentCode = remainder;

  codeBeforeDecoded = (code - sumCurrentCode) % power16[4] % power16[3] % power16[2];
  initialPositionCodeList[3] = codeBeforeDecoded / power16[1];
  sumCurrentCode += codeBeforeDecoded;

  codeBeforeDecoded = (code - sumCurrentCode) % power16[4] % power16[3];
  initialPositionCodeList[2] = codeBeforeDecoded / power16[2];
  sumCurrentCode += codeBeforeDecoded;

  codeBeforeDecoded = (code - sumCurrentCode) % power16[4];
  initialPositionCodeList[1] = codeBeforeDecoded / power16[3];
  sumCurrentCode += codeBeforeDecoded;

  codeBeforeDecoded = (code - sumCurrentCode);
  initialPositionCodeList[0] = codeBeforeDecoded / power16[4];
}

std::int32_t InitialPositionCodeDecoder::getInitialPositionCode() {
  return initialPositionCode;
}

std::vector<std::int8_t> InitialPositionCodeDecoder::getInitialPositionCodeList() {
  return initialPositionCodeList;
}

std::int8_t InitialPositionCodeDecoder::getInitialPositionPowerBlockCode() {
  return initialPositionPowerBlockCode;
}
