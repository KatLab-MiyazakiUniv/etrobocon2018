/**
 * @file Selector.h
 * @brief ブロック選択クラス
 * @author Keisuke MORI
 */
#ifndef __SELECTOR__
#define __SELECTOR__

#include "Explorer.h"
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <vector>

/**
 * <p> ブロック選択クラス <p>
 *
 * <p>
 * ETロボコン2018における、ブロック並べエリアにおけるルート探索、および次の動作の確認を行います。
 * {@link Explorer} クラス同様、斜め移動は考慮していません。
 * </p>
 *
 * <p>
 * このクラスのインスタンス保持者 (以下ユーザ) は、最初に {@link
 * #setBlockPositionList(std::vector<std::int8_t>)}
 * を実行して、このクラスにブロックの位置を設定してください。
 * </p>
 *
 * <p>
 * ユーザは、次の7つのメンバ関数を随時呼出す必要があります。
 * 1つのルート取得関数でルートを取得し、残りの6つの真偽値判定関数で移動前後の振舞いを判定してください。
 * <p>
 *
 * <ul>
 * <li> {@link #exploreNextOperation()} <br />
 *      ユーザは、現在地から目的地へのルートを取得できます。
 *      目的地については、このクラスが責任を持ちます。 </li>
 * <li> {@link #isBacksteppingBeforeNextOperation()} <br />
 *      目的地に移動する前に、バックステップを行う場合は真を返す真偽値を取得できます。
 *      この戻り値が真の場合、ユーザは移動前にバックステップを行う必要があります。 </li>
 * <li> {@link #isBackstepping()} <br />
 *      目的地に到着した後に、バックステップを行う場合は真を返す真偽値を取得できます。 </li>
 *      この戻り値が真の場合、ユーザは移動後にバックステップを行う必要があります。 </li>
 * <li> {@link #isEvacuatingWithNext()} <br />
 *      次の状態が「ブロックの一時避難」の場合は真を返す真偽値を取得できます。
 *      この戻り値が真の場合、ユーザは一時避難状態として動作する必要があります。 </li>
 * <li> {@link #isMovingWithNext()} <br />
 *      次の状態が「次に運搬したいブロック置き場への移動」の場合は真を返す真偽値を取得できます。
 *      この戻り値が真の場合、ユーザは移動状態として動作する必要があります。 </li>
 * <li> {@link #isCarryingWithNext()} </li>
 *      次の状態が「ブロックの運搬」の場合は真を返す真偽値を取得できます。
 *      この戻り値が真の場合、ユーザは運搬状態として動作する必要があります。 </li>
 * <li> {@link #isAlreadyAllBlockMoved()} <br />
 *      全てブロックを運搬し終えた場合は真を返す真偽値を取得できます。
 *      この戻り値が真の場合、位置コード11へのルートを探索するため、ユーザは次の動作に備える必要があります。
 * </li>
 * </ul>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     Selector selector;
 *     std::vector<std::int8_t> initializedBlockPositionList{{0, 2, 10, 14}};
 *
 *     selector.setBlockPositionList(initializedBlockPositionList);
 *
 *     std::int8_t currentPosition = 8;
 *     Selector::BlockColor color = Selector::Undefined;
 *
 *     auto route = obj.exploreNextOperation(currentPosition, color);
 *     bool isBacksteppingBeforeNextOperation = selector.isBacksteppingBeforeNextOperation();
 *     bool isBackstepping = selector.isBackstepping();
 *     bool isEvacuating = selector.isEvacuatingWithNext();
 *     bool isMoving = selector.isMovingWithNext();
 *     bool isCarrying = selector.isCarryingWithNext();
 *     bool isClearGame = selector.isAlreadyAllBlockMoved();
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
  Selector()
    : blockPositionList(MAX_BLOCK_COUNT),
      movedBlockPositionList(MAX_BLOCK_COUNT),
      evacuatedBlockPositionList(MAX_BLOCK_COUNT),
      nodePositionCostList(TOTAL_NODE_COUNT)
  {
    // 各ノードにおける位置コストのリスト
    std::vector<int> nodePositionCostList_{ { 4, 3, 3, 4, 3, 2, 2, 3, 1, 2, 2, 3, 4, 3, 3, 4 } };

    for(unsigned int i = 0; i < nodePositionCostList_.size(); i++) {
      nodePositionCostList[i] = nodePositionCostList_[i];
    }

    for(auto itr = movedBlockPositionList.begin(); itr != movedBlockPositionList.end(); itr++) {
      (*itr) = EMPTY_ID;
    }

    for(auto itr = evacuatedBlockPositionList.begin(); itr != evacuatedBlockPositionList.end();
        itr++) {
      (*itr) = EMPTY_ID;
    }

    explorer.createBlockArea();
  }

  enum NextOperationOfSearchingRouteIs { Evacuating, Moving, Carrying };

  enum BlockColor { Blue, Red, Yellow, Green, Undefined };

  /**
   * <p> 目的地までのルート探索および動作判定を行います。 </p>
   *
   * <p>
   * 現在地とブロックの色を選択すると、次に移動すべきブロック置き場 (目的地)
   * までのルートを取得します。 また、内部変数の真偽値に、次の動作を設定します。
   * </p>
   *
   * <p>
   * この関数を利用する場合は、内部変数の真偽値も参照してください。
   * 詳細は {@link Selector} クラスの説明を参照してください。
   * </p>
   *
   * @param currentPosition 現在地
   * @param color 取得したブロックの色 <br /> 取得していない場合は {@link Selector::Undefined}
   * を設定する必要があります。
   * @return 現在地から目的地までの位置コードのリスト <br /> 最小で要素数1です。
   */
  std::vector<int> exploreNextOperation(std::int8_t currentPosition, BlockColor color);

  std::int8_t searchBlockPosition(std::int8_t currentPosition);

  bool isAlreadyMovedNode(std::int8_t position);

  bool isAlreadyAllBlockMoved();

  void changeBlockPosition(std::int8_t beforePosition, std::int8_t afterPosition);

  void setBlockPositionList(std::vector<std::int8_t> list);

  std::vector<std::int8_t> getBlockPositionList();

  void addMovedBlockPosition(std::int8_t position);

  void pushEvacuatedBlockPosition(std::int8_t position);

  std::int8_t popEvacuatedBlockPosition();

  void prepareSearching(std::vector<std::int8_t> list);

  std::vector<int> searchRoute(std::int8_t start, std::int8_t end);

  void setNext(NextOperationOfSearchingRouteIs next);

  bool isEvacuatingWithNext();

  bool isMovingWithNext();

  bool isCarryingWithNext();

  bool isBacksteppingBeforeNextOperation();

  bool isBackstepping();

  std::int8_t getPositionOfCenterQuadirilateral(BlockColor color);

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
   * {@link #blockPositionList} および {@link #movedBlockPositionList}
   * のリサイズによる例外処理の利用が原因となるメモリ肥大化を防ぐため、
   * ノードが存在しないことを示すIDが必要になりました。
   * </p>
   */
  const std::int8_t EMPTY_ID = -1;

  bool evacuatingFlag = false;

  bool movingFlag = false;

  bool carryingFlag = false;

  bool backsteppingFlag = false;

  bool backsteppingBeforeNextOeperationFlag = false;

  std::int8_t movedCount = 0;

  std::int8_t evacuatedSize = 0;

  std::vector<std::int8_t> blockPositionList;

  std::vector<std::int8_t> movedBlockPositionList;

  std::deque<std::int8_t> evacuatedBlockPositionList;

  std::vector<int> nodePositionCostList;

  Explorer explorer;
};

#endif  // SELECTOR
