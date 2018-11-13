/**
 * @file Explorer.h
 * @brief ルート探索クラス
 * @author Keisuke MORI
 */
#ifndef __EXPLORER__
#define __EXPLORER__

#include "Node.h"
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>

/**
 * <p> ルート探索クラス <p>
 *
 * <p>
 * ETロボコン2018における、ブロック並べエリアのブロック置き場をノードとしたルート探索を行います。
 * 斜め移動は考慮していません。
 * </p>
 *
 * <p>
 * このクラスを利用して、別のブロック並べエリアを作成する場合は、次の4つの変数値を編集してください。
 * </p>
 *
 * <ul>
 * <li> 隣接ノードIDのリスト (デフォルトコンストラクタ内における {@code neighborsIDList_}
 * の初期化値) </li> <li> 相対的なノード位置のリスト (デフォルトコンストラクタ内における {@code
 * currentPosition} の初期化値)  </li> <li> ブロック並べエリアにおけるノード総数 ({@link
 * #TOTAL_NODE_COUNT}) </li> <li>
 * ブロック並べエリアにおける各ブロック置き場が隣接するブロック置き場の最大数 ({@link
 * #MAX_NEIGHBOR_COUNT}) </li>
 * </ul>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     Explorer explorer;
 *     explorer.createBlockArea();
 *
 *     explorer.resetBlockArea(); // 内部のフラグを初期化
 *     explorer.setHasBlockIn(8);
 *     explorer.setHasBlockIn(9);
 *     explorer.setHasBlockIn(11);
 *     explorer.setHasBlockIn(15);
 *     auto route = explorer.searchRoute(8, 10); // == {8, 12, 13, 14, 10}
 *     }
 * </pre>
 */
class Explorer {
  /**
   * <p> ポジション構造体 </p>
   */
  struct Position {
    /**
     * <p> ノード位置のX軸 </p>
     */
    std::int8_t x;
    /**
     * <p> ノード位置のY軸 </p>
     */
    std::int8_t y;
    Position() : x(0), y(0) {}
  };

 public:
  /**
   * <p> デフォルトコンストラクタ </p>
   *
   * <p>
   * 各ブロック置き場における隣接ノードIDのリスト、およびノード位置リストを作成し、そのサイズを元にノードリストを初期化しています。
   * </p>
   */
  Explorer()
    : blockAreaNodeList(nullptr), neighborPtrs(TOTAL_NODE_COUNT), neighborsIDList(TOTAL_NODE_COUNT)
  {
    // 隣接ノードIDのリスト
    std::vector<std::array<std::int8_t, MAX_NEIGHBOR_COUNT>> neighborsIDList_{
      { { 1, 4, EMPTY_ID, EMPTY_ID },
        { 0, 2, 5, EMPTY_ID },
        { 1, 3, 6, EMPTY_ID },
        { 2, 7, EMPTY_ID, EMPTY_ID },

        { 0, 5, 8, EMPTY_ID },
        { 1, 4, 6, 9 },
        { 2, 5, 7, 10 },
        { 3, 6, 11, EMPTY_ID },

        { 4, 9, 12, EMPTY_ID },
        { 5, 8, 10, 13 },
        { 6, 9, 11, 14 },
        { 7, 10, 15, EMPTY_ID },

        { 8, 13, EMPTY_ID, EMPTY_ID },
        { 9, 12, 14, EMPTY_ID },
        { 10, 13, 15, EMPTY_ID },
        { 11, 14, EMPTY_ID, EMPTY_ID } }
    };

    // 相対的なノード位置のリスト
    std::vector<std::array<std::int8_t, 2>> currentPosition
        = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 },

            { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 },

            { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 },

            { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 } };

    //
    // 以降は触れなくてよい
    //

    for(unsigned int i = 0; i < neighborsIDList_.size(); i++) {
      neighborsIDList[i] = neighborsIDList_[i];
    }

    for(unsigned int i = 0; i < neighborsIDList.size(); i++) {
      Position position;
      position.x = currentPosition[i][0];
      position.y = currentPosition[i][1];
      positionList.push_back(position);
    }
  }

  /**
   * <p> ブロックエリアのノードリストを作成します </p>
   *
   * <p>
   * 作成方法は、 {@link Node} クラスのドキュメントを参考にしました。
   * </p>
   */
  void createBlockArea();

  /**
   * <p> ブロックエリアのノードリストにおける探索時のフラグなどを初期化します </p>
   */
  void resetBlockArea();

  /**
   * <p> ブロックが存在するブロック置き場の位置コードを設定します </p>
   *
   * @param blockID ブロック置き場の位置コード
   */
  void setHasBlockIn(std::int8_t blockID);

  /**
   * <p> ブロック置き場のノードがブロックを保持している場合は真を返す真偽値判定を行います </p>
   *
   * <p>
   * 引数でブロックの数以上の数値を入力した場合、何かしらのエラーが発生します。
   * それに関する責任をこの関数は持ちません。
   * </p>
   *
   * @param id ブロック置き場のノードID
   * @return ブロック置き場のノードがブロックを保持している場合は真を返す真偽値
   */
  bool hasBlock(std::int8_t id);

  /**
   * <p> ブロック置き場エリアにおける移動ルートを探索します </p>
   *
   * <p>
   * スタート位置と向かいたい位置を入力すると、 {@code std::vector<int>} 型のリストを返します。
   * これは、ブロック置き場の位置コードのリストであり、隣接ノードが連なっています。
   * たとえば、位置コード8から位置コード10に移動したい場合は、 {@code {8, 9, 10}} を返します。
   * もし位置コード9にブロックが存在している場合は、 {@code {8, 12, 13, 14, 10}} を返します。
   * 斜め移動は未対応です。
   * </p>
   *
   * @param start スタート位置の位置コード
   * @param end 向かいたい位置の位置コード
   * @return ブロック置き場の位置コードのリスト
   */
  std::vector<int> searchRoute(std::int8_t start, std::int8_t end);

  /**
   * <p> ブロック置き場における隣接ノードのコストを計算します </p>
   *
   * <p>
   * これはA*アルゴリズムで用いる再帰的な内部処理です。
   * {@link searchRoute(std::int8_t, std::int8_t)} でのみ利用しています。
   * </p>
   *
   * @param parent 親ノードのポインタ
   * @param around 周辺ノード
   * @param realCost 実コスト
   * @param end 終端ノードのノードID
   * @return 終端ノードのポインタ
   */
  Node* calculateNeighborCost(Node* parent, std::vector<Node*>* around, std::int32_t realCost,
                              std::int8_t end);

  /**
   * <p> ブロック置き場のノードのポインタのリストのポインタを取得します </p>
   *
   * @return ブロック置き場のノードのポインタのリストのポインタ
   */
  std::vector<Node*>* getBlockAreaNodeList();

 private:
  /**
   * ブロックエリアノードリスト
   */
  std::vector<Node*>* blockAreaNodeList;

  /**
   * ポジションリスト
   */
  std::vector<Position> positionList;

  /**
   * <p> 隣接ノードが空であることを示すのノードID </p>
   *
   * <p>
   * {@link #neighborsIDList}
   * の中身が固定長配列のため、隣接ノードが存在しないことを示すIDが必要になりました。 詳細は {@link
   * #neighborsIDList} を参照してください。
   * </p>
   */
  const std::int8_t EMPTY_ID = -1;

  /**
   * <p> ブロック並べエリアにおけるブロック置き場の総数 </p>
   */
  static const std::int8_t TOTAL_NODE_COUNT = 16;

  /**
   * <p> ブロック並べエリアにおける各ブロック置き場が隣接するブロック置き場の最大数 </p>
   */
  static const std::int8_t MAX_NEIGHBOR_COUNT = 4;

  /**
   * <p> ブロック置き場リスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみ利用していますが、実態を残すためにメンバ変数としています。
   * </p>
   */
  std::vector<Node> nodeList;

  /**
   * <p> ブロック置き場のポインタのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみ利用していますが、実態を残すためにメンバ変数としています。
   * </p>
   */
  std::vector<Node*> nodePtrs;

  /**
   * <p> 各ブロック置き場における隣接ノードのポインタのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみ利用していますが、実態を残すためにメンバ変数としています。
   * </p>
   */
  std::vector<std::vector<Node*>> neighborPtrs;

  /**
   * <p> 各ブロック置き場における隣接ノードIDのリスト </p>
   *
   * <p>
   * コンストラクタおよび {@link #createBlockArea()}
   * でのみ利用していますが、実態を残すためにメンバ変数としています。
   * </p>
   *
   * <p>
   * 可変長配列の中身が可変長配列の場合、中身の可変長配列の長さが変わるごとに例外処理を呼び起こす可能性があり、実行メモリが肥大化してしまいます。
   * これを防ぐため、次のような工夫を施しています。
   * </p>
   *
   * <ul>
   * <li> 可変長配列の中身を固定長配列にする </li>
   * <li> 中身の固定長配列の長さを {@link #MAX_NEIGHBOR_COUNT} に設定する </li>
   * <li> 中身の固定長配列に空きが存在するノードについては {@link #EMPTY_ID} を設定して {@link
   * #createBlockArea()} 内で無視する </li>
   * </ul>
   */
  std::vector<std::array<std::int8_t, MAX_NEIGHBOR_COUNT>> neighborsIDList;
};

#endif  // EXPLORER
