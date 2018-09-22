/**
 * @file InitialPositionCodeDecoder.h
 * @brief 初期位置コードデコーダークラス
 * @author Keisuke MORI
 */
#ifndef __INITIAL_POSITION_CODE_DECODER__
#define __INITIAL_POSITION_CODE_DECODER__

#include <cstdint>
#include <vector>

/**
 * <p> 5桁から6桁の初期位置コードを初期の位置コードリストにデコードするクラス </p>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     InitialPositionCodeDecoder ipcd;
 *     std::int32_t initialPositionCode = 74840; // = 1*16^4 + 2*16^3 + 4*16^2 + 5*16^1 + 8
 *
 *     ipcd.decode(initialPositionCode);
 *
 *     std::vector<std::int8_t> decodedColorBlockCodeList = ipcd.getInitialPositionCodeList(); // = {1, 2, 4, 5}
 *     std::int8_t decodedPowerBlockCode = ipcd.getInitialPositionPowerBlockCode(); // = 8
 *     }
 * </pre>
 */
class InitialPositionCodeDecoder {
 public:
  /**
   * <p> 初期位置コードをデコードする </p>
   *
   * @param code 初期位置コード <br> 0未満はこのクラスで定義している初期値を返す
   */
  void decode(std::int32_t code);

  /**
   * <p> 初期位置コードを取得する </p>
   *
   * @return 初期位置コード
   */
  std::int32_t getInitialPositionCode();

  /**
   * <p> 初期の位置コードリストを取得する </p>
   *
   * @return 初期の位置コードリスト
   */
  std::vector<std::int8_t> getInitialPositionCodeList();

  /**
   * <p> パワーブロックの初期の位置コードを取得する </p>
   *
   * <p>
   * パワーブロックの初期位置は、1～8のみを取る。
   * 計算外の場合は0を返す。
   * 計算上、1～15までの値を取る可能性はあるが、9以上の場合は動作未検証である。
   * </p>
   *
   * @return パワーブロックの初期の位置コード <br> 1~8のみ、 {@link #decode(std::int32_t)} の実行前は0を返す
   */
  std::int8_t getInitialPositionPowerBlockCode();

 private:
  /**
   * 初期位置コード
   */
  std::int32_t initialPositionCode;

  /**
   * 初期の位置コードリスト
   */
  std::vector<std::int8_t> initialPositionCodeList = {0, 0, 0, 0};

  /**
   * パワーブロックの初期位置コード
   */
  std::int8_t initialPositionPowerBlockCode = 0;
};

#endif
