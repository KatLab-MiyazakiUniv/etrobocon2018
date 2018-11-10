/**
 * @file Selector.h
 * @brief ブロック選択クラス
 * @author Keisuke MORI
 */
#ifndef __SELECTOR__
#define __SELECTOR__

#include "Explorer.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

/**
 * <p> ブロック選択クラス <p>
 *
 * <p>
 * ETロボコン2018における、ブロック並べエリアのブロック置き場をノードとした次に処理を行うブロックの選択を行います。
 * {@link Explorer} クラス同様、斜め移動は考慮していません。
 * </p>
 *
 * <p>
 * このクラスを利用して、別のブロック並べエリアを作成する場合は、次の3つの変数値を編集してください。
 * </p>
 *
 * <ul>
 * <li> 各ノードにおける位置コストのリスト (デフォルトコンストラクタ内における {@code nodePositionCostList_} の初期化値)  </li>
 * <li> ブロック並べエリアにおけるノード総数 ({@link #TOTAL_NODE_COUNT}) </li>
 * <li> ブロック並べエリアにおけるブロックの最大数 ({@link #MAX_BLOCK_COUNT}) </li>
 * </ul>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     Selector selector;
 *     std::vector<std::int8_t> blockPositionList{{0, 2, 10, 14}};
 *
 *     // 一度も動かしていない場合
 *     selector.setBlockPositionList(blockPositionList);
 *     auto actual = selector.searchBlockPosition(8); // == 10
 *
 *     // ブロックを移動した場合
 *     blockPositionList = {0, 2, 5, 14};
 *     selector.setBlockPositionList(blockPositionList);
 *     selector.addMovedBlockPosition(5); // 移動済みブロック
 *     auto actual = selector.searchBlockPosition(9); // == 10
 *     }
 * </pre>
 */
class Selector {
 public:
  /**
   * <p> デフォルトコンストラクタ </p>
   *
   * <p>
   * 各ブロック置き場における位置コストのリストを作成し、そのサイズを元にノードリストを初期化しています。
   * </p>
   */
  Selector() :
      blockPositionList(MAX_BLOCK_COUNT),
      movedBlockPositionList(MAX_BLOCK_COUNT),
      nodePositionCostList(TOTAL_NODE_COUNT)
  {
    // 各ノードにおける位置コストのリスト
    std::vector<int> nodePositionCostList_{
        {
            4, 3, 3, 4,
            3, 2, 2, 3,
            1, 2, 2, 3,
            4, 3, 3, 4
        }
    };

    for (unsigned int i = 0; i < nodePositionCostList_.size(); i++)
    {
      nodePositionCostList[i] = nodePositionCostList_[i];
    }

    for (auto itr = movedBlockPositionList.begin(); itr != movedBlockPositionList.end(); itr++)
    {
      (* itr) = EMPTY_ID;
    }

    explorer.createBlockArea();
  }

  std::int8_t searchBlockPosition(std::int8_t currentPosition);

  bool isAlreadyMovedNode(std::int8_t position);

  void setBlockPositionList(std::vector<std::int8_t> list);

  std::vector<std::int8_t> getBlockPositionList();

  void addMovedBlockPosition(std::int8_t list);



 private:
  /**
   * <p> ブロック並べエリアにおけるブロック置き場の総数 </p>
   */
  static const std::int8_t TOTAL_NODE_COUNT = 16;

  /**
   * <p> ブロック並べエリアにおけるブロックの最大数 </p>
   */
  static const std::int8_t MAX_BLOCK_COUNT = 4;

  /**
   * <p> ノードが空であることを示すのノードID </p>
   *
   * <p>
   * {@link #blockPositionList} および {@link #movedBlockPositionList} のリサイズによる例外処理の利用が原因となるメモリ肥大化を防ぐため、
   * ノードが存在しないことを示すIDが必要になりました。
   * </p>
   */
  const std::int8_t EMPTY_ID = -1;

  std::int8_t movedCount = 0;

  std::vector<std::int8_t> blockPositionList;

  std::vector<std::int8_t> movedBlockPositionList;

  std::vector<int> nodePositionCostList;

  Explorer explorer;
};

#endif // SELECTOR
