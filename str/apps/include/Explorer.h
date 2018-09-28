/**
 * @file Explorer.h
 * @brief ルート探索クラス
 * @author Keisuke MORI
 */
#ifndef __EXPLORER__
#define __EXPLORER__

#include "Node.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
// #include <memory>
// #include <cstdint>

/**
 * <p> ルート探索クラス <p>
 *
 * <p>
 * ETロボコン2018における、ブロック並べエリアのブロック置き場をノードとしたルート探索を行います。
 * 斜め移動は考慮していません。
 * </p>
 *
 * <p>
 * このクラスを利用して、別のブロック並べエリアを作成する場合は、デフォルトコンストラクタに存在する次の2つを記述してください。
 * </p>
 *
 * <ul>
 * <li> 隣接ノードIDのリスト </li>
 * <li> 相対的なノード位置のリスト </li>
 * </ul>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     Explorer explorer;
 *     explorer.createBlockArea();
 *
 *     explorer.resetBlocArea();
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
    Position()
        : x(0), y(0) {}
  };

 public:
  /**
   * <p> デフォルトコンストラクタ </p>
   *
   * <p>
   * 各ブロック置き場における隣接ノードIDのリスト、およびノード位置リストを作成し、そのサイズを元にノードリストを初期化している。
   * </p>
   */
  Explorer()
      : blockAreaNodeList(nullptr)
  {
    // 隣接ノードIDのリスト
    neighborsIDList = {
        {1, 4},
        {0, 2, 5},
        {1, 3, 6},
        {2, 7},

        {0, 5, 8},
        {1, 4, 6, 9},
        {2, 5, 7, 10},
        {3, 6, 11},

        {4, 9, 12},
        {5, 8, 10, 13},
        {6, 9, 11, 14},
        {7, 10, 15},

        {8, 13},
        {9, 12, 14},
        {10, 13, 15},
        {11, 14}};

    // 相対的なノード位置のリスト
    std::vector<std::vector<int>> currentPosition = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},

        {0, 1},
        {1, 1},
        {2, 1},
        {3, 1},

        {0, 2},
        {1, 2},
        {2, 2},
        {3, 2},

        {0, 3},
        {1, 3},
        {2, 3},
        {3, 3}};

    positionList.resize(neighborsIDList.size());
    nodeList.resize(neighborsIDList.size());
    nodePtrs.resize(neighborsIDList.size());
    neighborPtrs.resize(neighborsIDList.size());

    for (unsigned int i = 0; i < neighborsIDList.size(); i++)
    {
      positionList[i].x = currentPosition[i][0];
      positionList[i].y = currentPosition[i][1];
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

  void resetBlockArea();

  void setHasBlockIn(std::int8_t blockID);

  std::vector<int> searchRoute(std::int8_t start, std::int8_t end);

  Node* calculateNeighborCost(Node* parent, std::vector<Node*>* around, std::int32_t realCost, std::int8_t end);

  std::vector<Node*>* getBlockAreaNodeList();




 private:
  /**
   * ブロックエリアノードリスト
   */
  std::vector<Node*>* blockAreaNodeList;

  std::vector<Position> positionList;

  /**
   * <p> ブロック置き場リスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<Node> nodeList;

  /**
   * <p> ブロック置き場のポインタのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<Node*> nodePtrs;

  /**
   * <p> 各ブロック置き場における隣接ノードのポインタのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<std::vector<Node*>> neighborPtrs;

  /**
   * <p> 各ブロック置き場における隣接ノードIDのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<std::vector<int>> neighborsIDList;
};

#endif // EXPLORER
