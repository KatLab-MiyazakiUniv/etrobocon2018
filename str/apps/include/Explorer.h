/**
 * @file Explorer.h
 * @brief ルート探索クラス
 * @author Keisuke MORI
 */
#ifndef __EXPLORER__
#define __EXPLORER__

#include "Node.h"
#include <vector>
// #include <memory>
// #include <cstdlib>
// #include <cstdint>

/**
 * <p> ルート探索クラス <p>
 *
 * <p>
 * ETロボコン2018における、ブロック並べエリアのブロック置き場をノードとしたルート探索を行います。
 * 斜め移動は考慮していません。
 * </p>
 *
 * <p> Example </p>
 *
 * <pre>
 *     {@code
 *     Explorer explorer;
 *     }
 * </pre>
 */
class Explorer {
 public:
  /**
   * <p> デフォルトコンストラクタ </p>
   *
   * <p>
   * 各ブロック置き場における隣接ノードIDのリストを作成し、そのサイズを元にノードリストを初期化している。
   * </p>
   */
  Explorer()
  {
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
    nodeList.resize(neighborsIDList.size());
    neighbors.resize(neighborsIDList.size());
  }

  /**
   * <p> ブロックエリアのノードリストを作成します </p>
   *
   * <p>
   * 作成方法は、 {@link Node} クラスのドキュメントを参考にしました。
   * </p>
   */
  void createBlockArea();

 private:
  /**
   * ブロックエリアノードリスト
   */
  std::vector<Node*>* blockAreaNodeList;

  /**
   * <p> ブロック置き場リスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<Node> nodeList;

  /**
   * <p> 各ブロック置き場における隣接ノードのポインタのリスト </p>
   *
   * <p>
   * {@link #createBlockArea()} でのみの利用だが、実態を残すためにメンバ変数としている。
   * </p>
   */
  std::vector<std::vector<Node*>> neighbors;

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
